import logging
import os
from ctypes import POINTER, c_int, c_ubyte, cdll

logger = logging.getLogger()


class SeedCbcCipher:
    """
    KISA Seed 128 CBC pkcs5padding / pkcs7padding 암호화 모듈
    c++로된 소스코드를 동적라이브러로 컴파일 하여 ctypes로 호출하는 방식으로 구현

    seed 128 : https://seed.kisa.or.kr/kisa/algorithm/EgovSeedInfo.do
    c++ 소스코드 : https://seed.kisa.or.kr/kisa/Board/17/detailView.do
    """

    seed_lib = None
    iv = None
    key = None
    script_dir = os.path.dirname(__file__)

    # 상대 경로를 절대 경로로 변환
    libray_path = os.path.join(script_dir, "lib/seed_128_cbc/seed_128_lib.so")
    padding_size = 16

    # pkcs5padding은 8byte
    # pkcs7padding은 16byte를 패딩으로 사용하지만 하위호환이 가능함으로 16으로 지정
    # 패딩 : https://www.sinsiway.com/kr/pr/blog/view/489/page/21

    def _load_encryption_library(self):
        """
        Seed 암호화 동적라이브러리 load

        해당 라이브러리는 lib/seed_128_cbc/compile.sh에서 생성
        """
        try:
            seed_encryption_library = cdll.LoadLibrary(self.libray_path)
        except OSError as e:
            logger.error(
                f"Seed 암호화 라이브러리 load 실패 - 파일이 없습니다.detail:{str(e)}"
            )
        except Exception as e:
            logger.error(f"Seed 암호화 라이브러리 load 실패 - {str(e)}")
        else:
            self.seed_lib = seed_encryption_library

    def __init__(self, iv: bytes, key: bytes):
        self._load_encryption_library()
        if self.seed_lib is None:
            raise Exception("Seed 암호화 라이브러리가 없습니다")

        if not iv:
            raise Exception("Initialize Vector 값이 없습니다.")

        if not key:
            raise Exception("암호화 key 값이 없습니다.")

        self.iv = iv

        self.key = key

    def strip_padding(self, byte_str):
        # 뒤에서부터 탐색하여 \x00이 아닌 바이트를 찾음
        end_index = len(byte_str)
        while end_index > 0 and byte_str[end_index - 1] == 0:
            end_index -= 1

        # \x00이 아닌 바이트까지의 부분 바이트 문자열을 반환
        return byte_str[:end_index]

    def encrypt(self, plain_text: bytes) -> bytes:
        """
        Seed 128 cbc pkcs5/pkcs7padding 암호화
        :param plain_text: 암호화할 텍스트 문자열 bytes
        """
        seed_cbc_encrypt = self.seed_lib.SEED_CBC_Encrypt
        seed_cbc_encrypt.restype = c_int
        seed_cbc_encrypt.argtypes = [
            POINTER(c_ubyte),  # Key
            POINTER(c_ubyte),  # IV
            POINTER(c_ubyte),  # PlainText
            c_int,  # PlainText Length
            POINTER(c_ubyte),  # CipherText (output)
        ]

        key_array = (c_ubyte * len(self.key))(*self.key)
        iv_array = (c_ubyte * len(self.iv))(*self.iv)
        text_array = (c_ubyte * (len(plain_text) + 0))(*plain_text)
        cipher_text_array = (
            c_ubyte
            * (
                len(plain_text)
                + (self.padding_size - (len(plain_text) % self.padding_size))
            )
        )()  # 패딩 추가

        result_length = seed_cbc_encrypt(
            key_array,
            iv_array,
            text_array,
            len(plain_text),
            cipher_text_array,
        )

        if result_length == 0:
            raise Exception("seed 암호화 실패")

        return bytes(cipher_text_array)

    def decrypt(self, cipher_text: bytes) -> bytes:
        """
        Seed 128 cbc pkcs5/pkcs7padding 복호화
         :param cipher_text: 암호화된 문자열 bytes
        """
        seed_cbc_decrypt = self.seed_lib.SEED_CBC_Decrypt
        seed_cbc_decrypt.restype = c_int
        seed_cbc_decrypt.argtypes = [
            POINTER(c_ubyte),  # Key
            POINTER(c_ubyte),  # IV
            POINTER(c_ubyte),  # CipherText
            c_int,  # CipherText Length
            POINTER(c_ubyte),  # Decrypted result (output)
        ]

        key_array = (c_ubyte * len(self.key))(*self.key)
        iv_array = (c_ubyte * len(self.iv))(*self.iv)
        cipher_array = (c_ubyte * len(cipher_text))(*cipher_text)
        plain_text_array = (c_ubyte * len(cipher_text))()

        result_length = seed_cbc_decrypt(
            key_array, iv_array, cipher_array, len(cipher_text), plain_text_array
        )

        if result_length == 0:
            raise Exception("seed 복호화 실패")

        # padding 제거
        return self.strip_padding(bytes(plain_text_array))
