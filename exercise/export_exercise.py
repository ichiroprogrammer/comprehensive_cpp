#!/usr/bin/env python3

import argparse
import os
import shutil
import sys
import subprocess

readme_content = """
# exercise solid/design pattern by C++ 

このリポジトリはC++によるsolid/design patternの理解を促すための演習問題である。

# 使い方

演習は./exercise/xxx_qのソースコードの
    //[Q] ...
    のような個所に掲載されている。

exercise/xxx_a/exercise/xxx_qの回答例である。

# ビルド方法

    exercise/build.sh   # すべてのソースコードがビルドされる。

    cd exercise/some_dir
    make            # some_dir内のソースコードのビルド
    make ut         #  some_dir内のソースコードの単体テスト

    ほとんどの演習問題は[Q}の指示に従いコードを書き単体テストで動作を確かめることで完了できる。

makefileの各種のターゲットは

    make help

    を実行すればわかる。

# パッケージ
    このソースをビルドするためには救たなくとも以下のパッケージは必要である。

    bash, g++, make, git
"""

def make_readme(dir):
    with open(os.path.join(dir, "README.md"), "w", encoding="utf-8") as file:
        file.write(readme_content)


def _subprocess_run(cmd):
    print("executing ", cmd)

    # subprocess.run()を使ってコマンドを実行し、標準出力をキャプチャ
    result = subprocess.run(
            cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    # 標準出力を改行で分割してリストに変換
    output_lines = result.stdout.splitlines()
    
    return output_lines

def get_args(args=None):
    parser = argparse.ArgumentParser(description="dir")
    parser.add_argument("--dir", type=str, default=None) # VPATH

    args = parser.parse_args(args)
    return os.path.abspath(args.dir)

def copy_directories(src_dirs: list[str], dst_dir: str) -> None:

    os.makedirs(dst_dir, exist_ok=True)

    for src_dir in src_dirs:
        src_path = os.path.abspath(src_dir) # コピー元のディレクトリパス
        src_parent = os.path.dirname(src_dir) 
        dst_path = os.path.join(dst_dir, src_dir) # コピー先のディレクトリパス
        
        # ディレクトリを再帰的にコピー
        shutil.copytree(src_path, dst_path, dirs_exist_ok=True)


def make_git_repos(dir):
    cmd = f"git -C {dir} init"
    _subprocess_run(cmd)

    cmd = f"git -C {dir} config --local user.email you@exercise.com"
    _subprocess_run(cmd)
    cmd = f"git -C {dir} config --local user.name exercise.taro"
    _subprocess_run(cmd)

    make_readme(dir)
    cmd = f"git -C {dir} add ."
    _subprocess_run(cmd)

    cmd = f"git -C {dir} commit -m fist-commit"
    _subprocess_run(cmd)

def _main():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(base_dir)

    cmd = f"git clean -dfx ."
    _subprocess_run(cmd)

    working_dir  = os.path.join(base_dir, "..")
    os.chdir(working_dir)

    src_dirs = ["exercise", "deep/build", "deep/h", "deep/make", "googletest"]

    dst_dir = os.path.join(get_args(), "exercise.git")
    copy_directories(src_dirs, dst_dir)

    make_git_repos(dst_dir)

if __name__ == "__main__":
    _main()


