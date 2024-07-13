# KISA_SEED_128_CBC
KISA에서 제공하는 SEED 128 CBC (pkcs#5 pkcs#7) 암호화 python에서 사용할수 있게한 소스코드입니다.
python으로 포팅한건 아니고 c++ 소스코드를 빌드해서 python에서 호출할수 있게 한 샘플 코드입니다.

## 작성이유
- KISA에서 제공하는 SEED 암호화를 사용하고 싶었으나, 온라인상에 php,java로 구현한 코드는 있으나 python에서 사용하기 위한 코드가 없어서 직접 작성함
- python 개발 환경에서 seed 암호화를 사용해야 하는 분들에게 도움이 되기를 바랍니다...
- 제발 국내 모든 기관/업체들은 이런 암호화 대신 AES를 사용해주세요...
- 호환성도 구리고 cpu엔디언 환경 마다 암복호화 결과도 다르고 국제적으로 많이 쓰이지도 않고 영어메뉴얼도 없고 공식 github도 없고  pdf랑 소스코드만 있는 암호가 어딨어요..
- ### 호환성 때문에 빡쳐서 내가 만들고 만다. 

## 주의사항
- Seed암호화는 실행하는 환경의 cpu 아키텍처에 따라 암복호화가 되지 않을수 있습니다.
- 암호화(리틀엔디언) -> 복호화(리틀엔디언) = 가능
- 암호화(리틀엔디언) -> 복호화(빅엔디언) = 불가능
- 일반적인 x86, x64, AMD 계열은 리틀엔디안 환경이므로, x86 아키텍처에서는 문제가 없을것으로 예상됩니다
- 자세한 내용은 `EED_블록암호_알고리즘에_대한_소스코드_활용_매뉴얼.pdf` 의 3번 고려사항 참고

## 사용법 

```python
from seed import SeedCbcCipher



key = b"\x88\xE3\x4F\x8F\x08\x17\x79\xF1\xE9\xF3\x94\x37\x0A\xD4\x05\x89"
iv = b"\x26\x8D\x66\xA7\x35\xA8\x1A\x81\x6F\xBA\xD9\xFA\x36\x16\x25\x01"

# 암호화할 문자열 byte 형태로 입력
plain_text = b"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"



cipher = SeedCbcCipher(iv=iv, key=key)

# 암호화
ciphertext = cipher.encrypt(plain_text)

# 복호화
decrypted_text = cipher.decrypt(ciphertext)



```

## Reference
- [국산 암호 SEED 테스트 페이지](http://146.56.42.71/DEV/cms/lib/index.php) 
- [SEED암호화 설명 페이지](https://seed.kisa.or.kr/kisa/algorithm/EgovSeedInfo.do) 
- [SEED 암호화 공식 코드](https://seed.kisa.or.kr/kisa/Board/17/detailView.do)
- [SEED_블록암호_알고리즘에_대한_소스코드_활용_매뉴얼.pdf](https://github.com/user-attachments/files/16186385/SEED_._._._._._.pdf)
