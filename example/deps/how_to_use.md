# ./g++/depsの開発
## ./g++/depsのビルド
./g++/depsのビルドは以下のコマンドで行うことができる。

        > make

## ./g++/depsのテスト
### 単体テスト
./g++/depsの単体テストはgoogle testで記述されている。以下のコマンドで単体テストを行うことができる。

        > make ut

### 統合テスト
以下のコマンドで統合テストを行うことができる。

        > make it

### 品質確認
上記テストはsanitizeerを使用したバイナリで実行することも可能である。
また、scan-buildやclangでのコンパイルにより静的解析もできる。

        make [target]
          all             : all target are built.
          ut [UT_OPT=...] : all ut are executed.
          clean           : delete files created on build.
          format          : format *.cpp *.h by clang-formatter.
          clang           : static analysis by clang.
          sanitizer       : build with sanitizeer.
          san-ut          : all ut built with sanitizer are executed.
          san-it          : it built with sanitizer are executed.
          scan-build      : static analysis by scan-build.

### 単体テスト、統合テストの統合
上記したような手順を正確に実行するために、./build.shが用意されている。

        build.sh  [option]
            -c    : clean before build
            -d    : dry run
            -j N  : make -j N for sample build [default:0]
            -h    : show this message

### todo
* it.shがイマイチ。
