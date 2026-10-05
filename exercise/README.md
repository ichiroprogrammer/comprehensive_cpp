# C++プログラミング/パターン 演習問題

このディレクトリは、

- C++によるC++の有用なパターン
- 落とし穴
- solid
- design pattern

の理解を促すための演習問題を掲載している。

## ビルド環境
[cygwin](https://www.cygwin.com/install.html)に以下のパケージをインストールことで、

* bash
* git
* g++
* clang(clang-format)
* make

[ビルド](#build)できる予定であるが、もし問題が起こる場合、ichiro.inoue@exmtion.co.jpまでご連絡ください。

## ビルド方法 <a id="build"></a> 

```sh
exercise/build.sh   # すべてのソースコードがビルドされる。

cd exercise/some_dir
make                # some_dir内のソースコードのビルド
make ut             #  some_dir内のソースコードの単体テスト
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


