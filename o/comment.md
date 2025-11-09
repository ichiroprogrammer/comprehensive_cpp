<!-- ./md/comment.md -->
# コメント <a id="SS_7"></a>
コメントの目的は、複雑怪奇なソースコードのエクスキューズでない。
ソースコードから読み取れない情報や、ソースコードのサマリーを書くべきである。

[インデックス](introduction.md#SS_1_4)に戻る。  
___

__この章の構成__

&emsp;&emsp; [情報を付加しないコメント](comment.md#SS_7_1)  
&emsp;&emsp; [コメントのスタイル](comment.md#SS_7_2)  
&emsp;&emsp;&emsp; [クラスのコメント](comment.md#SS_7_2_1)  
&emsp;&emsp;&emsp; [関数のコメント](comment.md#SS_7_2_2)  
&emsp;&emsp;&emsp; [enumのコメント](comment.md#SS_7_2_3)  
&emsp;&emsp;&emsp; [型エイリアスのコメント](comment.md#SS_7_2_4)  
&emsp;&emsp;&emsp; [template仮引数のコメント](comment.md#SS_7_2_5)  
  
  

## 情報を付加しないコメント <a id="SS_7_1"></a>
以下のような情報を付加しないコメントは無駄であるだけではなく、可読性に悪影響を与える場合もあるため、
避けるべきである。

1. 「ファイルの最後に、ファイルの最後を示すEnd of file」、
  「sleep(1)に対しての、1秒待つ」のようなコメントは、見れば明らかであるため不要である。
2. ソースコードのコメントアウト(#if 0等を含む)をしない。
3. リポジトリが保持している情報(annotate等)をコメントに含めない。

特に2、3のコメントを書くプログラマは、バージョン管理システムに未習熟である可能性が高い。
そういうプログラマには、バージョン管理システムの書籍を読ませることを推奨する。

## コメントのスタイル <a id="SS_7_2"></a>
有償、無名もしくは、日本でしか使われていないコメントフォーマットやそのツールを使うべきではない。
本ドキュメントでは、doxygenを推奨する。

doxygenフォーマットの各要素に対する書き方を例示する。

### クラスのコメント <a id="SS_7_2_1"></a>

```cpp
    //  example/etc/comment.cpp 9

    /// @brief ディレクトリ配下の特定のファイルをリカーシブに探して、その一覧を返すクラス
    class FileFinder {
    public:
```

### 関数のコメント <a id="SS_7_2_2"></a>

```cpp
    //  example/etc/comment.cpp 42

    /// @brief 条件にマッチしたファイルをリカーシブに探して返す
    /// @param is_match どのようなファイルかをラムダ式で指定する
    /// @return 条件にマッチしたファイル名をvector<string>で返す
    std::vector<std::string> FindFileRecursively(IsMatch is_match);
```

### enumのコメント <a id="SS_7_2_3"></a>

```cpp
    //  example/etc/comment.cpp 20

    /// @enum FileSort
    /// FindFileRecursivelyの条件
    enum class FileSort {
        File,              ///< pathがファイル
        Dir,               ///< pathがディレクトリ
        FileNameHeadIs_f,  ///< pathがファイル且つ、そのファイル名の先頭が"f"
    };
```

### 型エイリアスのコメント <a id="SS_7_2_4"></a>

```cpp
    //  example/etc/comment.cpp 36

    /// @typedef IsMatch
    /// @brief   FindFileRecursivelyの仮引数の型
    using IsMatch = std::function<bool(std::filesystem::path const&)>;
```

### template仮引数のコメント <a id="SS_7_2_5"></a>

```cpp
    //  example/etc/comment.cpp 62

    /// @brief BASIC_TYPEで指定する基本型のビット長を持つ固定小数点を扱うためのクラス
    /// @tparam BASIC_TYPE       全体のビット長や、符号を指定するための整数型
    /// @tparam FRACTION_BIT_NUM 小数点保持のためのビット長
    template <typename BASIC_TYPE, uint32_t FRACTION_BIT_NUM>
    class FixedPoint {
    public:
        FixedPoint(BASIC_TYPE integer = 0, typename std::make_unsigned_t<BASIC_TYPE> fraction = 0) noexcept
            : value_{get_init_value(integer, fraction)}
        {
            // ...
        }
```


