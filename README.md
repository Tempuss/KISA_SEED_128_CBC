# KISA_SEED_128_CBC
KISA에서 제공하는 SEED 128 CBC (pkcs#5 pkcs#7) 암호화 python에서 사용할수 있게한 소스코드입니다.
python으로 포팅한건 아니고 c++ 소스코드를 빌드해서 python에서 호출할수 있게 한 샘플 코드입니다.

## 작성이유
- KISA에서 제공하는 SEED 암호화를 사용하고 싶었으나, python에서 사용하기 위한 코드가 없어서 직접 작성함
- python 개발 환경에서 seed 암호화를 사용해야 하는 분들에게 도움이 되기를 바랍니다...
- 제발 국내 모든 기관/업체들은 이런 암호화 대신 AES를 사용해주세요...
- 호환성도 구리고 cpu엔디언 환경 마다 암복호화 결과도 다르고 국제적으로 많이 쓰이지도 않고 영어메뉴얼도 없고 공식 github도 없고  pdf랑 소스코드만 있는 암호가 어딨어요..
- ### 호환성 때문에 빡쳐서 걍 내가 만들고 만다. 아오 

## 사용법 

## Reference
- [국산 암호 SEED 테스트 페이지](http://146.56.42.71/DEV/cms/lib/index.php) 
- [SEED암호화 설명 페이지](https://seed.kisa.or.kr/kisa/algorithm/EgovSeedInfo.do) 
- [SEED 암호화 공식 코드](https://seed.kisa.or.kr/kisa/Board/17/detailView.do)
- [SEED_블록암호_알고리즘에_대한_소스코드_활용_매뉴얼.pdf](https://github.com/user-attachments/files/16186385/SEED_._._._._._.pdf)
