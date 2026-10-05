# C++プログラミング/パターン 演習問題

このディレクトリは、

- C++によるC++の有用なパターン
- 落とし穴
- solid
- design pattern

の理解を促すための演習問題を掲載している。

## ビルド環境
1. [cygwin](https://www.cygwin.com/install.html)(`https://www.cygwin.com/install.html`) にジャンプし、
   自分の環境にあったインストーラをダウンロード

2. インストーラを立ち上げ、以下のパケージを選択しインストール
    - bash(これは選択しなくても自動でインストールされるかもしれない)
    - git
    - g++
    - clang(clang-format)
    - make
3. ここまででインストールは完了。以下確認。
4. windowsのメニューから`cygwin`を選択し、cygwinターミナルを起動する。
5. cygwinターミナルから以下を実行(ターミナルのホームディレクトリは通常`C:/cygwin64/home/yourname`)

```sh
$ git --version
git version 2.51.0

$ g++ --version
g++ (GCC) 14.4.0
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ clang --version
clang version 22.1.8 (ssh://tyan0@cygwin.com/git/cygwin-packages/clang 19fccdabbb57f99161f3845d51607c9f9ccc3b94)
Target: x86_64-pc-windows-cygnus
Thread model: posix
InstalledDir: /usr/bin

$ make --version
GNU Make 4.4.1
このプログラムは x86_64-pc-cygwin 用にビルドされました
Copyright (C) 1988-2023 Free Software Foundation, Inc.
ライセンス GPLv3+: GNU GPL バージョン 3 以降 <https://gnu.org/licenses/gpl.html>
これはフリーソフトウェアです: 自由に変更および配布できます.
法律の許す限り、　無保証　です.
```

もしコマンドの実行でエラーが起こるようであれば、そのコマンドのインストールがされていない。
もう一度インストーラからそのコマンドをインストールする。

[ビルド](#build)できる予定であるが、もし問題が起こる場合、ichiro.inoue@exmtion.co.jpまでご連絡ください。

## ビルド方法 <a id="build"></a> 

```sh
$ exercise/build.sh   # すべてのソースコードがビルドされる。

$ cd exercise/some_dir
$ make                # some_dir内のソースコードのビルド
$ make ut             #  some_dir内のソースコードの単体テスト
```

ほとんどの演習問題は[Q}の指示に従いコードを書き単体テストで動作を確かめることで完了できる。

makefileの各種のターゲットは

```sh
make help
```

を実行すればわかる。


## 使い方

演習は./exercise/xxx_qのソースコードの

>//[Q] ...
のような個所に掲載されている。

exercise/xxx_aは、
exercise/xxx_qの回答例である。

ソースコードの編集は各自の好みのエディタで問題ないが、特に内容であれば、VS-Codeを推奨する。

windowsのエクスプローラーからcygwinのディレクトリを操作したい場合は、
`C:/cygwin64/home/yourname`
から対象ディレクトリを探せば容易に見つかるはずである。


## README.htmlの生成方法

```sh
$ cd <GIT_TOP>/exercise
$ ../md_gen/export/sh/md_to_html.sh -t "C++演習問題集" -a "講師名"  -H -f README.md
$ mv o/README.html .
$ rm -rf o/
```


