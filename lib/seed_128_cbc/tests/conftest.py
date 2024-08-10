import os
import subprocess
import traceback

import pytest


@pytest.fixture(autouse=True, scope="session")
def build_kisa_seed_lib():
    file_path = f"lib/seed_128_cbc/seed_128_lib.so"
    os.remove(file_path)

    command = f"cd lib/seed_128_cbc; bash compile.sh"

    try:

        subprocess.run(command, shell=True)
        print("seed 암호화 라이브러리 컴파일 성공")
    except subprocess.CalledProcessError as e:
        print("seed 암호화 라이브러리 컴파일 오류 발생:")
        traceback.print_exc()
