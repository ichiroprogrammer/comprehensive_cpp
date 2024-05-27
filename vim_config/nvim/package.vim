if &compatible
    set nocompatible " Be iMproved
endif

" このファイルのあるディレクトリ/../nvim_pkg/deinにパッケージを入れる。
let g:pkg_dir=simplify(expand('<sfile>:p:h') . '/../nvim_pkg/dein')

" Required:
" Add the dein installation directory into runtimepath
execute 'set runtimepath+=' . g:pkg_dir . '/repos/github.com/Shougo/dein.vim'
execute 'set runtimepath+=' . g:pkg_dir . '/repos/github.com/'

" Required:
call dein#begin(g:pkg_dir)

" Let dein manage dein
" Required:
call dein#add(g:pkg_dir . '/repos/github.com/Shougo/dein.vim')
if !has('nvim')
    call dein#add('roxma/nvim-yarp')
    call dein#add('roxma/vim-hug-neovim-rpc')
endif

call dein#add('Shougo/deoplete.nvim')
call dein#add('zchee/deoplete-clang')

" Add or remove your plugins here like this:
call dein#add('Shougo/neosnippet.vim')
call dein#add('Shougo/neosnippet-snippets')
call dein#add('Shougo/neoinclude.vim')

call dein#add('tpope/vim-fugitive')
call dein#add('reireias/vim-cheatsheet')
call dein#add('mattn/vim-maketable')
call dein#add('aklt/plantuml-syntax')

" Required:
call dein#end()

" Required:
filetype plugin indent on
syntax enable

let g:cheatsheet#cheat_file = expand('<sfile>:p:h') . '/cheatsheet.md'
let g:table_mode_corner = '|'

if g:os == 'windows'
    let g:python_host_prog  = 'C:\cygwin64\bin\python2.7.exe'
    let g:python3_host_prog  = 'C:\cygwin64\bin\python3.8.exe'
elseif g:os == 'cygwin'

elseif g:os == 'linux'
    let g:ruby_host_prog = '/usr/local/bin/neovim-ruby-host'
    let g:python_host_prog  = '/usr/bin/python2'
    let g:python3_host_prog  = '/usr/bin/python3'
else
    echo 'unkown os'
endif

" deoplete
if has('python3')
    let g:deoplete#enable_at_startup = 1
    let g:deoplete#sources#clang#libclang_path = '/usr/lib/llvm-10/lib/libclang.so'
    let g:deoplete#sources#clang#clang_header = '/usr/lib/llvm-10/lib/clang/'
    let g:deoplete#sources#clang#clang_complete_database = './'
    "g:deoplete#sources#clang#flags	See this section	No
    "g:deoplete#sources#clang#sort_algo	''	No
    "g:deoplete#sources#clang#include_default_arguments	False	No
    "g:deoplete#sources#clang#filter_availability_kinds
endif
