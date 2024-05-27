# このリポジトリの目的
wsl-ubuntu vim/nvim、cygwin vim、windows gvim/nvim/nvim-qtの設定方法や設定ファイルを保存する。


# このリポジトリのファイル
## README.md
このファイル。

## ./nvimディレクトリ

|ファイル名        |内容                              |
|:-----------------|:---------------------------------|
|nvim/init.vim     |nvimから最初に読み込まれる        |
|nvim/org.vim      |オリジナルの設定                  |
|nvim/package.vim  |deinを使用した外部パッケージの設定|
|nvim/plugin/      |自作プラグイン                    |
|nvim/autoload/    |自作プラグインのオートロード      |
|nvim/rplugin/     |自作プラグイン                    |
|nvim/ftplugin/    |filetype別プラグイン              |
|nvim/cheatsheet.md|自分用ヘルプ。:Cheatで表示        |

## ./vimディレクトリ
|ファイル名|内容                                             |
|:---------|:------------------------------------------------|
|vim/vimrc |~/.vimrcにコピーかシンボリックリンクを張って使用 |
|vim/gimrc |~/.gvimrcにコピーかシンボリックリンクを張って使用|

## その他
|ファイル名|内容                                                                                 |
|:---------|:------------------------------------------------------------------------------------|
|vim.sh    |bashrc等からsource                                                                   |
|inputrc   |readline(gdb)を使用するアプリケーションのrcファイル。~/.inputrcにコピーして使用する。|


# 環境変数
ここで説明する環境変数は下記のvim系プログラムを初期設定をするためのものである。
* ubuntu上のvim、nvim
* cygwin上のvim
* windows上のgvim、nvim、nvim-qt
* cygwinターミナルから起動されたwindows上のgvim、nvim、nvim-qt

下記の環境変数XDG_CONFIG_HOMEはすべて同一の実態(ディレクトリ)を指している。

環境変数VIMやVIMRUNTIMEは設定しない。設定しない場合、
* windows版gvimでは、
    * VIMは、'$HOME/.vim'がセットされる。
    * VIMRUNTIMEは、'$HOME/.vim/vimNN'がセットされる。

* windows版nvim-qでは、Neovimにバンドルされているパッケージが入っているディレクトリが
  VIMやVIMRUNTIMEにセットされる。

## wsl-ubuntu
* .bashrcに下記を追加する。

        export XDG_CONFIG_HOME=~/.config
        source $XDG_CONFIG_HOME/vim.sh

## cygwin
* .bashrcに下記を追加する。

        # LINUX_HOMEはubuntuのホームディレクトリを指定
        export LINUX_HOME=/cygdrive/c/XXX
        export XDG_CONFIG_HOME=$LINUX_HOME/.config
        source $XDG_CONFIG_HOME/vim.sh

## windows
* 環境変数に以下を追加する

        # XXXは上記と同じものを指定
        # YYYはcygwinのホームディレクトリを指定
        XDG_CONFIG_HOME C:\XXX\.config
        HOME C:\cygwin64\home\YYY


# インストール
1. 上記「環境変数」に従って環境変数、bashrcを設定
2. このリポジトリを'$LINUX_HOME/.confg'にgit clone
3. https://github.com/Shougo/dein.vim
   に従ってdeinを'$LINUX_HOME/.config/nvim_pkg/dein'にインストール
4. 外部パッケージのインストールのために、wsl-ubuntu nvim立ち上げて:call deine#install()を実行
5. cygwin vimの設定として、'$LINUX_HOME/.confg/vim/vimrc'をcygwinのホームディレクトリの
   .vimrcにコピーするかシンボリックリンクを張る。
6. windows gvimの設定として、'$LINUX_HOME/.confg/vim/gvimrc'をcygwinのホームディレクトリの
   .gvimrcにコピーするかシンボリックリンクを張る。


# 現在の問題点
* パス形式の違いでwindows nvim/nvim-qtから動作しないプラグインがある。
* cygwin vimはpython3対応でコンパイルされていないため、pythonが必要なプラグインは動作しない。
* deinから設定したvim-fugitiveはcygwin vimでは動作しないため、
  https://github.com/tpope/vim-fugitive
  に書いてある設定が必要である。


# スクリプト読み込みのデバッグ
|コマンド                      |意味                                      |
|:-----------------------------|:-----------------------------------------|
|:echo $MYVIMRC                |最初に読み込まれる設定ファイルの表示      |
|:scriptnames                  |現在読み込まれているスクリプトファイル一覧|
|:let @a=execute('scriptnames')|scriptnamesの出力をレジスタaに取り込む    |
|:checkhealt                   |足りないパッケージや設定等のチェック      |
