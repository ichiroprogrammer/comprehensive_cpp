<!-- practical/md/comment.md -->
# 5 コメント <a id="SS_5"></a>
コメントの目的は、複雑怪奇なソースコードのエクスキューズでない。
ソースコードから読み取れない情報や、ソースコードのサマリーを書くべきである。

___

__この章の構成__

5.1 [情報を付加しないコメント](comment.md#SS_5_1)  
5.2 [コメントのスタイル](comment.md#SS_5_2)  
&emsp;5.2.1 [クラスのコメント](comment.md#SS_5_2_1)  
&emsp;5.2.2 [関数のコメント](comment.md#SS_5_2_2)  
&emsp;5.2.3 [enumのコメント](comment.md#SS_5_2_3)  
&emsp;5.2.4 [型エイリアスのコメント](comment.md#SS_5_2_4)  
&emsp;5.2.5 [template仮引数のコメント](comment.md#SS_5_2_5)  
  
  

___


[インデックス](seminer_intro.md#SS_1_2)/[章の最後](comment.md#SS_5_999)/[次の章](cpp_improve.md#SS_6)

___


## 5.1 情報を付加しないコメント <a id="SS_5_1"></a>
以下のような情報を付加しないコメントは無駄であるだけではなく、可読性に悪影響を与える場合もあるため、
避けるべきである。

1. 「ファイルの最後に、ファイルの最後を示すEnd of file」、
  「sleep(1)に対しての、1秒待つ」のようなコメントは、見れば明らかであるため不要である。
2. ソースコードのコメントアウト(#if 0等を含む)をしない。
3. リポジトリが保持している情報(annotate等)をコメントに含めない。

特に2、3のコメントを書くプログラマは、バージョン管理システムに未習熟である可能性が高い。
そういうプログラマには、バージョン管理システムの書籍を読ませることを推奨する。

## 5.2 コメントのスタイル <a id="SS_5_2"></a>
有償、無名もしくは、日本でしか使われていないコメントフォーマットやそのツールを使うべきではない。
本ドキュメントでは、doxygenを推奨する。

doxygenフォーマットの各要素に対する書き方を例示する。

### 5.2.1 クラスのコメント <a id="SS_5_2_1"></a>

```cpp
    //  example/etc/comment.cpp 9

    /// @brief ディレクトリ配下の特定のファイルをリカーシブに探して、その一覧を返すクラス
    class FileFinder {
    public:
```

### 5.2.2 関数のコメント <a id="SS_5_2_2"></a>

```cpp
    //  example/etc/comment.cpp 42

    /// @brief 条件にマッチしたファイルをリカーシブに探して返す
    /// @param is_match どのようなファイルかをラムダ式で指定する
    /// @return 条件にマッチしたファイル名をvector<string>で返す
    std::vector<std::string> FindFileRecursively(IsMatch is_match);
```

### 5.2.3 enumのコメント <a id="SS_5_2_3"></a>

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

### 5.2.4 型エイリアスのコメント <a id="SS_5_2_4"></a>

```cpp
    //  example/etc/comment.cpp 36

    /// @typedef IsMatch
    /// @brief   FindFileRecursivelyの仮引数の型
    using IsMatch = std::function<bool(std::filesystem::path const&)>;
```

### 5.2.5 template仮引数のコメント <a id="SS_5_2_5"></a>

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

---

[インデックス](seminer_intro.md#SS_1_2)/[章の先頭](comment.md#SS_5)/[次の章](cpp_improve.md#SS_6)

---


<a id="SS_5_999"></a>

