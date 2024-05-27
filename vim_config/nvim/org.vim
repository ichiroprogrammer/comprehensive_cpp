" misc
set hidden
set ruler
set hlsearch
set nowrapscan
set laststatus=2
set noequalalways
set backspace=indent,eol,start
set incsearch
set background=dark
set statusline=%<%f[%n]%h%m%r%=%l,%c%V\ %P
set fileformats=unix,dos,mac
set printoptions=number:y

set virtualedit=block

" Makefileやbashスクリプトでgfを効かせるため
set isfname-=:
set isfname-=,
set isfname-=\=

" encoding
"set encoding=utf-8
set fileencoding=utf-8
set fileencodings=iso-2022-jp,euc-jp,sjis,utf-8

"
syntax on

" to use quick fix
"make setting
set makeprg=/usr/bin/make
set errorformat+=In\ file\ included\ from\ %f:%l:%m     "gcc
set errorformat+=%f:%l:%m                               "gcc
set errorformat+=%f\|%l\|%m                             "grep from vim
set errorformat+=%t\\,%f\\,%l\\,%c\\,%m

"grep setting
set grepprg=/usr/bin/grep\ -nH

let &makeef = expand('<sfile>:p:h') . '/' . getpid()

" default text
set tabstop=4
set shiftwidth=4
set expandtab
set nowrap
set cindent
"set iskeyword+=-
