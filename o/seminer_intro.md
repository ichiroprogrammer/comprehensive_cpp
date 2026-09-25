<!-- ./md/seminer_intro.md -->
# 1 イントロダクション <a id="SS_1"></a>
本ドキュメントは、C++でのプログラミング、デザイン、ソフトウェア開発におけるプロセス、
ワークフロー等を解説するセミナーのテキストである。

## 1.1 ドキュメントの緒注意 <a id="SS_1_1"></a>
__技術用語の用法__

* 参照
    * 「～を参照する」というような文脈で使われる**「参照」**はそのまま使用する。
    * C++での参照型を表す**参照**は使わず、代わりに**「リファレンス」**を使用する。
* 例外
    * 「～の場合は例外である」というような文脈で使われる**「例外」**はそのまま使用する。
    * C++でthrowすると発生する事象を表す**例外**は使わず、代わりに**「エクセプション」**を使用する。
* classとクラス
    * **class**はC++のキーワードとして使用する。
    * **クラス**は上記以外で使用する。
* プログラミングとコーディング、ソースコードとコード、インスタンスとオブジェクト、に関しては同義語として使用する。

__コード例について__

次章以降では、ソースコードを使って説明を行う場合がある。このような場合の注意点を述べる。

* 「`// ...`」のような行は、ソースコードの省略を表す。
* 特定の規則、法則、慣習等を説明するためのソースコードは、シンプルさを優先するため、
  その他の規則、法則、慣習に従っていない場合があるが、
  [Trailing Underscore(末尾アンダースコア)](cpp_idioms.md#SS_17_11_4)には従っている。
  また、一般に標準ライブラリのコンテナクラスをnewする必要はないが、
  コードの動作を示すためにあえてそのようにする場合がある。
* ソースコード内に動作説明のような本来不要なコメントがあるのは、
  読者にその意味を知らせるためであるため、製品コードのコメントをこのようにするべきではない。
* 例示したコードの動作の確認、明示のために
  [google test(gtest)](http://opencv.jp/googletestdocs/primer.html)のアサーション(下表)を使用する。


__google test_のアサーションの簡単な説明__

|アサーションマクロ  | 意味                                     |
|:-------------------|:-----------------------------------------|
| ASSERT_TRUE(x)     | xがtrue                                  |
| ASSERT_FALSE(x)    | xがfalse                                 |
| ASSERT_EQ(x, y)    | (x == y)がtrue                           |
| ASSERT_NE(x, y)    | (x != y)がtrue                           |
| ASSERT_GE(x, y)    | (x >= y)がtrue                           |
| ASSERT_GT(x, y)    | (x >  y)がtrue                           |
| ASSERT_LE(x, y)    | (x <= y)がtrue                           |
| ASSERT_LT(x, y)    | (x <  y)がtrue                           |
| ASSERT_STREQ(x, y) | (std::string(x) == std::string(y))がtrue |
| ASSERT_DEATH(x, y) | xを実行するとアボートすればtrue          |
| ASSERT_THROW(x, y) | xを実行するとy例外が発生すればtrue       |


## 1.2 インデックス <a id="SS_1_2"></a>
___

__中級セミナー__

- [プログラミング規約](programming_convention.md#SS_2)
- [コーディングスタイル](coding_style.md#SS_4)
- [命名規則](naming_practice.md#SS_5)
- [コメント](comment.md#SS_6)
- [C++の進化と主な変更点](cpp_improve.md#SS_14)

__上級セミナー__

- [アーキテクチャ](architecture.md#SS_9)
- [SOLID](solid.md#SS_7)
- [デザインパターン](design_pattern.md#SS_8)

__演習__

- [演習](exercise_q.md#SS_18)
- [解答](exercise_a.md#SS_19)


__Appendix__

- [コード解析](code_analysis.md#SS_3)
- [開発プロセスとインフラ](process_and_infra.md#SS_10)
- [C++コア言語仕様](core_lang_spec.md#SS_15)
- [標準ライブラリとプログラミングの概念](stdlib_and_concepts.md#SS_16)
- [C++慣用語句](cpp_idioms.md#SS_17)
- [並行処理](concurrency.md#SS_11)
- [テンプレートメタプログラミング](template_meta_programming.md#SS_12)
- [ダイナミックメモリアロケーション](dynamic_memory_allocation.md#SS_13)
- [参考文献](bibliography.md#SS_20)

---



