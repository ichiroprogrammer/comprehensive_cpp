# exercise solid/design pattern by C++ 

このリポジトリはC++によるsolid/design patternの理解を促すための演習問題である。

# 使い方

演習は./exercise/xxx_qのソースコードの
    //[Q] ...
    のような個所に掲載されている。

exercise/xxx_a/exercise/xxx_qの回答例である。

# ビルド方法 <a id="build"></a> 

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

# ビルド環境
[cygwin](https://www.cygwin.com/install.html)に以下のパケージをインストールことで、

* bash (version:5.2.21)
* git (version:2.45.1)
* g++ (version:12.4.0)
* clang-format (version:8.0.1)
* make (version:4.4.1)

[ビルド](#build)できる予定であるが、
もし問題が起こる場合、ichiro.inoue@exmtion.co.jpまでご連絡ください。


