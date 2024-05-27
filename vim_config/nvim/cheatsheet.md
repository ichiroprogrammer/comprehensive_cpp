# My CheatSheet

## dein
* https://github.com/Shougo/dein.vimからdeinとダウンロードしてセットアップ
    * curl ... > installer.sh   # インストーラのダウンロード
    * sh ./installer.sh ~/$XDG_CONFIG_HOME/nvim_pkg/dein    # deinのダウンロード
* :call dein#install()			# 他のパッケージインストール

## terminal(windows app)操作
* Alt-space -> x    最大化
* Alt-space -> r    元のサイズに戻す
* Alt-space -> n    最小化
* Alt-space -> m    ウィンドウの移動
* Alt-space -> s    ウィンドウのサイズ変更
* window-m          全アプリの最小化
* window-d          デスクトップの表示/全アプリの表示


## 正規表現
[正規表現アトム](https://vim-jp.org/vimdoc-ja/pattern.html#pattern-atoms)

\_.         改行含むすべての文字にマッチ

## NextFile 
<M-q>           現在のファイル名を@qに代入
<Num><C-q>      現在のファイル名を<Num>文字消して、"その文字列.\*"とマッチしたファイルを開く
                Numが省略された場合<Num>は0として処理する
                Numが0であった場合、"サフィックスを削除した文字列.\*"とマッチしたファイルを開く

## MultiHl
:MultiHlAdd     現在のカーソルの下のwordを'\<word\>にして、@/に追加。
:MultiHlAddR    現在のカーソルの下のwordをそのまま@/に追加。
:MultiHlAddI    <WORD> WORDをそのまま@/に追加。
:MultiHlClear   @/に""を入力。

## git diff
:GitDiff        : gitリポジトリのdiffリスト
:GitDiffResize  : 画面をリサイズして、gitリポジトリのdiffリスト
:GitDiffOff     : \*.newをbwipeoutしてdiffモード終了
{Visual}a       : git add from '< to '>
c"              : git commit -m "までコマンドラインに入力
d               : 水平分割diff表示
vd              : 垂直分割diff表示
h               : HEADとの水平分割diff表示
vh              : HEADとの垂直分割diff表示
<C-Q>           : git diffモード終了
{Visual}L       : cygstart/wslstart from '< to '>
{Visual}r       : git reset from '< to '>
s               : diffリストの再ロード

## grep
:Grep [suffix ...]          : grep -R --include=\*.suffix ... @/
:GrepP pattern [suffix ...] : grep -R --include=\*.suffix ... pattern

suffixを省略した場合、cpp c h rb py vimがsuffixになる。
全体をgrepしたい場合は - を指定する。
:Grep、:Grepp実行後はquick fixウインドが開いて結果を見ることができる。
<C-g><C-n>で次へ移動、<C-g><C-p>で前に移動できる。

:set ignorecaseが行われていた場合には、grepのオプションに-iが追加される。
:Grepが行われた場合に実際に起動されるgrepコマンドは、:grepである。
:grepが行われた場合に実際に起動されるgrepコマンドは、:set grepprg=...で設定されている。


## :terminalの使い方
* <C-q>                                     vimモード
* a, i等の通常のinsertモード移行で          terminalモード

でソースコード全体からの補完ができるらしいので調べる。

## termdebug
* nvim-gdbはやめて、こちらにした。

:DbgStart <prog>    termdebugをロードして、gdb <prog>
:DbgKey             下記mapをバッファローカルでmap

オリジナルコマンド  map
:Run [args]         R   [args] または以前の引数でプログラムを実行する
:Arguments              {args}  次の :Run のために引数を設定する
:Break              B   カーソル位置にブレークポイントを設定する。
:Clear              D   カーソル位置のブレークポイントを削除する
:Step               S   gdb の "step" コマンドを実行する
:Over               N   gdb の "next" コマンドを実行する
:Finish             F   gdb の "finish" コマンドを実行する
:Continue           C   gdb の "continue" コマンドを実行する
:Stop                   プログラムを中断する

## Session
* gitプロジェクトの全ディレクトリを使用してpathやtabsをセットする。
* mksessionでgitリポジトリのトップにSession.vimを作る。

:ProjectBegin       Session.vimをsourceして、path、tabsをセットする。
:ProjectDir         現在のセッションが使用しているgitリポジトリの
                    トップディレクトリを表示。
:ProjectMake        Session.vimを作る。
:ProjectNew         現在のセッションをカレントディレクトリを含む
                    gitリポジトリにする。
  
## PathSet
* pathにカレントディレクトリ以下のディレクトリをセットする。

:PathAdd            pathにディレクトリを追加する
:PathClear          pathを./のみにする
:PathSet            PathClearしてからPathAddする

## Buff
軽いのが取り柄のバッファエクスプローラ。

:Buff               :buffersの情報からBuffers問う名前のバッファを開く。
o                   プロンプトの下のバッファを開く。
d                   プロンプトの下のバッファをスワイプアウトする。
D                   プロンプトの下のバッファを強制スワイプアウトする。

## チップス
* 現在のrcフィルの確認
        :echo $MYGVIMRC

* マップの定義位置
        :verbose map <C-Q>

* vimコマンドの出力の取り込み
        :let @a=execute('scriptnames')  "scriptnamesの出力をレジスタaに入れる。

* globalで行に移動し、そこでコマンド実行
        :global/^</normal AHEHE     "先頭が"<"である行の末尾に"HEHE"を追加する。

* コマンドの繰り返し数の注意
        :map <C-A>  3w
  とした場合、 
        2<C-A>
  は
        23w
  となるため、このコマンドは23ワードの移動になるが、それはおそらく意図したものではない。
  <Num><C-A>を<C-A>の<Num>回の繰り返しにしたい場合、式レジスタを使い以下のように書く。
        :map <C-A>  @='3w'<CR>

### todo
* 言語サポート
    * gdbのpでSTLコンテナのきれいな表示がしたい。
    * rtag.vim
    * Tagbar: a class outline viewer for Vim

* そのうち調べる
    * コメントフォーマット。'formatoptions' の設定
    * 'showcmd'、'backspace'
    * 関数escape(@", '\\/')
    * packadd! matchit  「と」のマッチング
    * colorscheme evening
    * :mksession、:wviminfo、:rviminfo
    * terminal 端末通信 call/drop
