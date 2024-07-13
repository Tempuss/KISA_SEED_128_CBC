from unittest.mock import MagicMock

from seed import SeedCbcCipher

test_key = b"\x88\xE3\x4F\x8F\x08\x17\x79\xF1\xE9\xF3\x94\x37\x0A\xD4\x05\x89"
test_iv = b"\x26\x8D\x66\xA7\x35\xA8\x1A\x81\x6F\xBA\xD9\xFA\x36\x16\x25\x01"
# test_iv = b"실제로주는IV"
# 실제로주는KEY
# test_key = b64decode("7Iuk7KCc66Gc7KO864qUS0VZ")


plain_text = b"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
encrypted_text = (
    b"\x75\xdd\xa4\xb0\x65\xff\x86\x42\x7d\x44\x8c\x54\x03\xd3\x5a\x07\xd3\x5a\xab\x86\x7c\x8b\xf2\x55"
    b"\x7d\x82\x38\x8e\xa7\xc0\xd0\xf1"
)


def test_load_library_success(mocker):
    mocker.patch("ctypes.cdll.LoadLibrary", return_value=MagicMock())
    cipher = SeedCbcCipher(iv=test_iv, key=test_key)
    assert cipher.seed_lib is not None


def test_encrypt_success(mocker):
    cipher = SeedCbcCipher(iv=test_iv, key=test_key)
    ciphertext = cipher.encrypt(plain_text)
    assert ciphertext == encrypted_text


def test_encrypt_decrypt_success(mocker):
    cipher = SeedCbcCipher(iv=test_iv, key=test_key)
    ciphertext = cipher.encrypt(plain_text)
    decrypted_text = cipher.decrypt(ciphertext)
    assert plain_text == decrypted_text
