gcc -fPIC -c KISA_SEED_CBC.c -o KISA_SEED_CBC.o
rm seed_128_lib.so
gcc -shared -o seed_128_lib.so KISA_SEED_CBC.o
rm KISA_SEED_CBC.o

# 맥 OS 환경에서 간혹 안되는 경우가 있는데 아래 코드로 해결 가능
#arch -x86_64 gcc -fPIC -c KISA_SEED_CBC.c -o KISA_SEED_CBC.o
#rm seed_128_lib.so
#arch -x86_64 gcc -shared -o seed_128_lib.so KISA_SEED_CBC.o

