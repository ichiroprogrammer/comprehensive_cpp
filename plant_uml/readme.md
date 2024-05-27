# plant uml

## オンラインレンダラー

[plant umlオンラインサーバー](https://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa70000)
を使い、plant umlのソースコードを可視化できる。


## ditaaの特殊文字
":"、"\*"、"?"等のditaaの特殊文字はエスケープできないため、C++の疑似ソースとditaaは相性が悪い。
そういった場合、下記表のutf-8半角コードを代用する。

|char|UTF-8 Hex|unicode| 
|----|---------|-------|
| ꞉  |ea 9e 89 | a789  |
| ꞊  |ea 9e 8a | a78a  |
| …  |e2 80 a6 | 2026  |

下記の手順でvimから入力できる。

1. インサートモードにする
2. CTRL-Vを入力する(数字で入力モードになる)
3. uを入力する(その後に入力した文字が16進数4桁モードになる)
4. 上記表のunicodeの列の文字列を入力する("꞉"を入力したい場合、a789を入力)


上記文字以外を使いたい場合は、
[utf-8のコード](https://orange-factory.com/dnf/utf-8.html)から探すと良い。

