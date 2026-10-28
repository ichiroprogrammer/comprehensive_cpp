<!-- ./md/sample_code.md -->
# Sample Code <a id="SS_25"></a>
## vim <a id="SS_25_1"></a>
### vim_config/README.md <a id="SS_25_1_1"></a>


```vim
          1 # このリポジトリの目的
          2 wsl-ubuntu vim/nvim、cygwin vim、windows gvim/nvim/nvim-qtの設定方法や設定ファイルを保存する。
          3 
          4 
          5 # このリポジトリのファイル
          6 ## README.md
          7 このファイル。
          8 
          9 ## ./nvimディレクトリ
         10 
         11 |ファイル名        |内容                              |
         12 |:-----------------|:---------------------------------|
         13 |nvim/init.vim     |nvimから最初に読み込まれる        |
         14 |nvim/org.vim      |オリジナルの設定                  |
         15 |nvim/package.vim  |deinを使用した外部パッケージの設定|
         16 |nvim/plugin/      |自作プラグイン                    |
         17 |nvim/autoload/    |自作プラグインのオートロード      |
         18 |nvim/rplugin/     |自作プラグイン                    |
         19 |nvim/ftplugin/    |filetype別プラグイン              |
         20 |nvim/cheatsheet.md|自分用ヘルプ。:Cheatで表示        |
         21 
         22 ## ./vimディレクトリ
         23 |ファイル名|内容                                             |
         24 |:---------|:------------------------------------------------|
         25 |vim/vimrc |~/.vimrcにコピーかシンボリックリンクを張って使用 |
         26 |vim/gimrc |~/.gvimrcにコピーかシンボリックリンクを張って使用|
         27 
         28 ## その他
         29 |ファイル名|内容                                                                                 |
         30 |:---------|:------------------------------------------------------------------------------------|
         31 |vim.sh    |bashrc等からsource                                                                   |
         32 |inputrc   |readline(gdb)を使用するアプリケーションのrcファイル。~/.inputrcにコピーして使用する。|
         33 
         34 
         35 # 環境変数
         36 ここで説明する環境変数は下記のvim系プログラムを初期設定をするためのものである。
         37 * ubuntu上のvim、nvim
         38 * cygwin上のvim
         39 * windows上のgvim、nvim、nvim-qt
         40 * cygwinターミナルから起動されたwindows上のgvim、nvim、nvim-qt
         41 
         42 下記の環境変数XDG_CONFIG_HOMEはすべて同一の実態(ディレクトリ)を指している。
         43 
         44 環境変数VIMやVIMRUNTIMEは設定しない。設定しない場合、
         45 * windows版gvimでは、
         46     * VIMは、'$HOME/.vim'がセットされる。
         47     * VIMRUNTIMEは、'$HOME/.vim/vimNN'がセットされる。
         48 
         49 * windows版nvim-qでは、Neovimにバンドルされているパッケージが入っているディレクトリが
         50   VIMやVIMRUNTIMEにセットされる。
         51 
         52 ## wsl-ubuntu
         53 * .bashrcに下記を追加する。
         54 
         55         export XDG_CONFIG_HOME=~/.config
         56         source $XDG_CONFIG_HOME/vim.sh
         57 
         58 ## cygwin
         59 * .bashrcに下記を追加する。
         60 
         61         # LINUX_HOMEはubuntuのホームディレクトリを指定
         62         export LINUX_HOME=/cygdrive/c/XXX
         63         export XDG_CONFIG_HOME=$LINUX_HOME/.config
         64         source $XDG_CONFIG_HOME/vim.sh
         65 
         66 ## windows
         67 * 環境変数に以下を追加する
         68 
         69         # XXXは上記と同じものを指定
         70         # YYYはcygwinのホームディレクトリを指定
         71         XDG_CONFIG_HOME C:\XXX\.config
         72         HOME C:\cygwin64\home\YYY
         73 
         74 
         75 # インストール
         76 1. 上記「環境変数」に従って環境変数、bashrcを設定
         77 2. このリポジトリを'$LINUX_HOME/.confg'にgit clone
         78 3. https://github.com/Shougo/dein.vim
         79    に従ってdeinを'$LINUX_HOME/.config/nvim_pkg/dein'にインストール
         80 4. 外部パッケージのインストールのために、wsl-ubuntu nvim立ち上げて:call deine#install()を実行
         81 5. cygwin vimの設定として、'$LINUX_HOME/.confg/vim/vimrc'をcygwinのホームディレクトリの
         82    .vimrcにコピーするかシンボリックリンクを張る。
         83 6. windows gvimの設定として、'$LINUX_HOME/.confg/vim/gvimrc'をcygwinのホームディレクトリの
         84    .gvimrcにコピーするかシンボリックリンクを張る。
         85 
         86 
         87 # 現在の問題点
         88 * パス形式の違いでwindows nvim/nvim-qtから動作しないプラグインがある。
         89 * cygwin vimはpython3対応でコンパイルされていないため、pythonが必要なプラグインは動作しない。
         90 * deinから設定したvim-fugitiveはcygwin vimでは動作しないため、
         91   https://github.com/tpope/vim-fugitive
         92   に書いてある設定が必要である。
         93 
         94 
         95 # スクリプト読み込みのデバッグ
         96 |コマンド                      |意味                                      |
         97 |:-----------------------------|:-----------------------------------------|
         98 |:echo $MYVIMRC                |最初に読み込まれる設定ファイルの表示      |
         99 |:scriptnames                  |現在読み込まれているスクリプトファイル一覧|
        100 |:let @a=execute('scriptnames')|scriptnamesの出力をレジスタaに取り込む    |
        101 |:checkhealt                   |足りないパッケージや設定等のチェック      |
```

### vim_config/inputrc <a id="SS_25_1_2"></a>


```vim
          1 set editing-mode vi
          2 set completion-ignore-case on
          3 set show-all-if-unmodified on
```

### vim_config/nvim/autoload/buffers.vim <a id="SS_25_1_3"></a>


```vim
          1 let s:buffers_buffer = 'Buffers'
          2 
          3 function! s:line(num, buff_name)
          4     if a:buff_name == s:buffers_buffer
          5         return printf("%3d [%s]\n", a:num, a:buff_name)
          6     else
          7         return printf("%3d %s\n", a:num, a:buff_name)
          8     endif
          9 endfunction
         10 
         11 function! s:load_buffers_list()
         12     let l:line = line('.')
         13     let l:col = col('.')
         14 
         15     let buffs = split(execute('buffers'), "\n")
         16 
         17     setlocal modifiable
         18 
         19     silent execute ':%delete'
         20     for b in buffs
         21         let new_b = substitute(b, '^ *\(\d\+\).*\"\(.*\)\".*', { m -> s:line(m[1], m[2])}, 'g')
         22         silent execute ':normal i' . new_b 
         23     endfor
         24     silent execute ':$delete'
         25 
         26     setlocal modifiable
         27     call cursor(l:line, l:col)
         28 endfunction
         29 
         30 function! buffers#close_buff(force)
         31     let word = expand("<cword>")
         32 
         33     if word =~ '\d\+'
         34         let to_delete = bufname(str2nr(word))
         35     elseif word =~ '.\+'
         36         let to_delete = word
         37     else
         38         echo 'no file'
         39         return
         40     endif
         41 
         42     if to_delete == s:buffers_buffer
         43         execute 'bdelete!' . word
         44     else
         45         let bwipeout = 'bwipeout' . (a:force == 0 ? ' ' : '! ')
         46         execute bwipeout . word
         47         call s:load_buffers_list()
         48     endif
         49 endfunction
         50 
         51 function! buffers#open_buff()
         52     let word = expand("<cword>")
         53 
         54     if word =~ '\d\+'
         55         execute 'buffer ' . word
         56     elseif word =~ '.\+'
         57         execute 'buffer ' . word
         58     else
         59         echo 'no file'
         60     endif
         61 endfunction
         62 
         63 function! s:key_map() abort
         64     nnoremap <silent> <buffer> <Plug>(buffers-delete) :call buffers#close_buff(0)<CR>
         65     nmap <buffer> d <Plug>(buffers-delete)
         66 
         67     nnoremap <silent> <buffer> <Plug>(buffers-delete-force) :call buffers#close_buff(1)<CR>
         68     nmap <buffer> D <Plug>(buffers-delete-force)
         69 
         70     nnoremap <silent> <buffer> <Plug>(buffers-open) :call buffers#open_buff()<CR>
         71     nmap <buffer> o <Plug>(buffers-open)
         72 
         73     nnoremap <silent> <buffer> <Plug>(buffers-reload) :call buffers#begin()<CR>
         74     nmap <buffer> r <Plug>(buffers-reload)
         75 endfunction
         76 
         77 function! buffers#begin()
         78     let winid = bufwinid(s:buffers_buffer)
         79     if winid isnot# -1
         80         call win_gotoid(winid)
         81     else
         82         execute 'new' s:buffers_buffer
         83         set buftype=nofile
         84         set noswapfile
         85         call s:key_map()
         86     endif
         87     call s:load_buffers_list()
         88 endfunction
```

### vim_config/nvim/autoload/cd.vim <a id="SS_25_1_4"></a>


```vim
          1 function! s:is_term()
          2     let bn = bufname("%")
          3     if bn =~ 'term://'
          4         return 1
          5     else
          6         return 0
          7     endif
          8 endfunction
          9 
         10 function! cd#find_dir_candidate()
         11     for i in range(50)
         12         silent execute 'normal "uyy'
         13         let reg=@u
         14         if reg =~ 'ichiro@[^ ]\+ \~.*'
         15             return substitute(reg, 'ichiro@[^ ]\+', '', '') 
         16         endif
         17         silent execute 'normal k'
         18     endfor
         19 
         20     return ''
         21 endfunction
         22 
         23 
         24 function! cd#change_dir()
         25     if s:is_term() == 1
         26         let dir_candidate=cd#find_dir_candidate()
         27 
         28         if dir_candidate == ''
         29             echo "no dir candidate"
         30         else
         31             silent execute ':cd ' . dir_candidate
         32         endif
         33     else
         34         silent execute ':cd %:h'
         35     endif
         36 endfunction
```

### vim_config/nvim/autoload/git_diff.vim <a id="SS_25_1_5"></a>


```vim
          1 let s:git_diff_buffer = 'GIT DIFF'
          2 let s:git_diff_buffer_cur =''
          3 let s:git_diff_buffer_new =''   " .newと表示されるが実際には改定前ファイル
          4 
          5 set patchexpr=git_diff#patch()
          6 
          7 function! git_diff#patch() abort
          8     silent execute '!patch -R  -o ' . v:fname_out .  ' ' . v:fname_in . ' < ' . v:fname_diff
          9 endfunction
         10 
         11 function! s:echo_err(msg) abort
         12   echohl ErrorMsg
         13   echomsg 'git_diff.vim:' a:msg
         14   echohl None
         15 endfunction
         16 
         17 " pattern : 0       just changed
         18 "         : 1       change filename
         19 function! s:modified_pattern(pattern) abort
         20     if  a:pattern == 0
         21         return '^[ADMU? ][DMU? ] \+'
         22     elseif  a:pattern == 1
         23         return 'R[M ] \+.* -> '
         24     endif
         25     call s:echo_err('modified_pattern wrong')
         26 endfunction
         27 
         28 function! s:get_target_name() abort
         29     let l:line=getline(".")
         30 
         31     if match(l:line, s:modified_pattern(0)) isnot# -1
         32         return substitute(l:line, s:modified_pattern(0), "", "")
         33     elseif match(l:line, s:modified_pattern(1)) isnot# -1
         34         return substitute(l:line, s:modified_pattern(1), "", "")
         35     else
         36         call s:echo_err(l:line . ' :this file is not modefied')
         37         return ''
         38     endif
         39 endfunction
         40 
         41 function! s:git_diff(patch_target, patch_file_name, from_head) abort
         42     if a:from_head == 0
         43         silent execute '!git diff ' .  a:patch_target .  ' > ' .  a:patch_file_name
         44     else
         45         silent execute '!git diff HEAD ' .  a:patch_target .  ' > ' .  a:patch_file_name
         46     endif
         47 endfunction
         48 
         49 function! s:each(line1, line2, func_ref) abort
         50     let l:col = col('.')
         51 
         52     for i in range(a:line1, a:line2)
         53         call cursor(i, l:col)
         54         call a:func_ref()
         55     endfor
         56 endfunction
         57 
         58 function! s:launch_file() abort
         59     let l:target=s:get_target_name()
         60 
         61     if g:os == 'linux'
         62         silent execute '!wslstart ' .  l:target
         63     else 
         64         if g:os == 'cygwin'
         65             silent execute '!wslstart ' .  l:target
         66         else
         67             echo 'not support launch'
         68         endif
         69     endif
         70 endfunction
         71 
         72 function! git_diff#launch_file(line1, line2) abort
         73     call s:each(a:line1, a:line2, function('s:launch_file'))
         74 endfunction
         75 
         76 
         77 function! s:git_add() abort
         78     let l:target=s:get_target_name()
         79 
         80     silent execute '!git add ' .  l:target
         81     call git_diff#make_list_load()
         82 endfunction
         83 
         84 function! git_diff#git_add(line1, line2) abort
         85     call s:each(a:line1, a:line2, function('s:git_add'))
         86 endfunction
         87 
         88 function! s:git_reset() abort
         89     let l:target=s:get_target_name()
         90 
         91     if len(l:target) == 0
         92         return
         93     endif
         94 
         95     silent execute '!git reset ' .  l:target
         96     call git_diff#make_list_load()
         97 endfunction
         98 
         99 function! git_diff#git_reset(line1, line2) abort
        100     call s:each(a:line1, a:line2, function('s:git_reset'))
        101 endfunction
        102 
        103 function! git_diff#make_list_load() abort
        104     setlocal modifiable
        105 
        106     let l:line = line('.')
        107     let l:col = col('.')
        108     silent execute ':%delete'
        109     silent execute 'r! git status -s'
        110     silent execute ':1delete'
        111     call cursor(l:line, l:col)
        112 
        113     setlocal nomodifiable
        114 endfunction
        115 
        116 function! s:key_map_end() abort
        117     delcommand GitAdd
        118     delcommand GitReset
        119 endfunction
        120 
        121 function! s:key_map_begin() abort
        122     command! -range GitAdd :call git_diff#git_add(<line1>, <line2>)
        123     map <silent> <buffer> a :GitAdd<CR>
        124 
        125     command! -range LauchFile :call git_diff#launch_file(<line1>, <line2>)
        126     map <silent> <buffer> L :LauchFile<CR>
        127 
        128     command! -range GitReset :call git_diff#git_reset(<line1>, <line2>)
        129     map <silent> <buffer> r :GitReset<CR>
        130 
        131     nnoremap <silent> <buffer> <Plug>(diff-open) :<C-u>call git_diff#show_diff(0, 0)<CR>
        132     nmap <buffer> d <Plug>(diff-open)
        133 
        134     nnoremap <silent> <buffer> <Plug>(diff-open-V) :<C-u>call git_diff#show_diff(1, 0)<CR>
        135     nmap <buffer> vd <Plug>(diff-open-V)
        136 
        137     nnoremap <silent> <buffer> <Plug>(diff-open-h) :<C-u>call git_diff#show_diff(0, 1)<CR>
        138     nmap <buffer> h <Plug>(diff-open-h)
        139 
        140     nnoremap <silent> <buffer> <Plug>(diff-open-Vh) :<C-u>call git_diff#show_diff(1, 1)<CR>
        141     nmap <buffer> vh <Plug>(diff-open-Vh)
        142 
        143     nnoremap <silent> <buffer> <Plug>(diff-list-close) :<C-u>call git_diff#end()<CR>
        144     nmap <buffer> <C-Q> <Plug>(diff-list-close)
        145 
        146     nnoremap <silent> <buffer> <Plug>(diff-reload) :<C-u>call git_diff#make_list_load()<CR>
        147     nmap <buffer> s <Plug>(diff-reload)
        148 
        149     nnoremap <silent> <buffer> <Plug>(git-commit) :!git commit -m 
        150     nmap <buffer> c <Plug>(git-commit)
        151 endfunction
        152 
        153 "vertial    : 0 normal split to show diff buffers
        154 "           : 1 virtial split to show diff buffers
        155 "from_head  : 0 git diff 
        156 "           : 1 git diff HEAD
        157 function! git_diff#show_diff(vertical, from_head) abort
        158     call git_diff#show_diff_off()
        159 
        160     let l:target=s:get_target_name()
        161 
        162     if getftime(l:target) == -1
        163         s:echo_err('file not exits')
        164     endif
        165 
        166     let s:git_diff_buffer_cur = l:target
        167     let s:git_diff_buffer_new = l:target . '.new'
        168 
        169     let l:temp_file = tempname()
        170     call s:git_diff(l:target, l:temp_file, a:from_head)
        171 
        172     execute ':sp'
        173 	execute ':e ' . l:target
        174 
        175     if a:vertical == 0
        176 	    execute ':diffpatch ' . l:temp_file
        177 
        178         " 上バッファがオリジナル。下バッファが変更後ファイル
        179         execute "normal \<C-w>j"
        180     else
        181 	    execute ':vert diffpatch ' . l:temp_file
        182 
        183         " 左バッファがオリジナル。右バッファが変更後ファイル
        184         execute "normal \<C-w>l"
        185     endif
        186 
        187     call delete(l:temp_file)
        188 endfunction
        189 
        190 function! git_diff#show_diff_off()
        191     execute ':diffoff!'
        192 
        193     if s:git_diff_buffer_cur != ''
        194         let winid = bufwinid(s:git_diff_buffer_cur)
        195 
        196         if winid isnot# -1
        197             call win_gotoid(winid)
        198             :quit
        199         endif
        200 
        201         let s:git_diff_buffer_cur = ''
        202     endif
        203 
        204     if s:git_diff_buffer_new != ''
        205         let winid = bufwinid(s:git_diff_buffer_new)
        206 
        207         if winid isnot# -1
        208             call win_gotoid(winid)
        209             execute 'bwipeout! ' . s:git_diff_buffer_new
        210         endif
        211 
        212         let s:git_diff_buffer_new = ''
        213     endif
        214 endfunction
        215 
        216 function! git_diff#begin(resize) abort
        217     let winid = bufwinid(s:git_diff_buffer)
        218     if winid isnot# -1
        219         call win_gotoid(winid)
        220     else
        221         execute 'edit' s:git_diff_buffer
        222         set buftype=nofile
        223         set noswapfile
        224         setlocal nomodifiable
        225 
        226         call s:key_map_begin()
        227         call git_diff#make_list_load()
        228     endif
        229 
        230     if a:resize != 0
        231         execute ":only"
        232         let l:lines=&lines
        233         echo l:lines
        234         if l:lines < 50
        235             execute ":set lines=50"
        236         endif
        237         execute ":set columns=201"
        238     endif
        239 
        240 endfunction
        241 
        242 function! git_diff#end()
        243     call git_diff#show_diff_off()
        244     call s:key_map_end()
        245     bwipeout!
        246 endfunction
        247 
```

### vim_config/nvim/autoload/git_session.vim <a id="SS_25_1_6"></a>


```vim
          1 function! s:get_git_top()
          2     let top = system('git rev-parse --show-toplevel')
          3     return substitute(top, "\n", '/', 'g')
          4 endfunction
          5 
          6 let s:git_session_top = s:get_git_top()
          7 let s:git_session_file = s:git_session_top . 'Session.vim'
          8 
          9 function! s:get_dirs() abort
         10     " ディレクトリのみを抽出
         11     let dir_filter = '|sed -e /^[^/]\\+$/d  -e  s\@/[^/]\\+$\@\@g | sort | uniq'
         12     let dirs_str = system("git ls-files --full-name " . s:git_session_top . dir_filter)
         13 
         14     let dirs_list = split(dirs_str, "\n")
         15 
         16     let full_dirs = map(dirs_list, 's:git_session_top . v:val')
         17 
         18     call add(full_dirs, s:git_session_top)
         19 
         20     return full_dirs
         21 endfunction
         22 
         23 function! git_session#set_path()
         24     let dirs = s:get_dirs()
         25     let &path ='./,/usr/include/c++/9/,' . join(dirs, ',') 
         26 
         27     let tag_dirs = map(dirs, 'v:val . "tags"')
         28     let &tags ='tags,./tags,' .  join(tag_dirs, ',')
         29 endfunction
         30 
         31 function! git_session#begin() abort
         32     let top = s:get_git_top()
         33 
         34     if top != s:git_session_top
         35         echo 'must be on the dir under ' . s:git_session_top
         36         return
         37     endif
         38 
         39     try
         40         execute 'source ' . s:git_session_file
         41     catch
         42         echo 'no session file'
         43     endtry
         44     call git_session#set_path()
         45 endfunction
         46 
         47 function! git_session#dir() abort
         48     echo s:git_session_top
         49 endfunction
         50 
         51 function! git_session#make() abort
         52     let top = s:get_git_top()
         53 
         54     if top != s:git_session_top
         55         echo 'must be on the dir under ' . s:git_session_top
         56         return
         57     endif
         58 
         59     execute 'mksession! ' . s:git_session_file
         60 endfunction
         61 
         62 function! git_session#new_session() abort
         63     let s:git_session_top = s:get_git_top()
         64     let s:git_session_file = s:git_session_top . 'Session.vim'
         65     call git_session#begin()
         66 endfunction
```

### vim_config/nvim/autoload/grep.vim <a id="SS_25_1_7"></a>


```vim
          1 function s:grep(target, args_for_dir)
          2     let ignore_case=&ic
          3     if l:ignore_case == 0
          4         let ic_str = ''
          5     else
          6         let ic_str = '-i '
          7     end
          8     execute ':grep -R ' . l:ic_str . a:args_for_dir . ' "' . a:target . '"' 
          9 endfunction
         10 
         11 function grep#grep(...)
         12     let args_for_dir = s:make_args_for_dir(a:000)
         13     let l:target=@/
         14     call s:grep(l:target, args_for_dir)
         15 endfunction
         16 
         17 function grep#grepp(pattern, ...)
         18     let args_for_dir = s:make_args_for_dir(a:000)
         19     call s:grep(a:pattern, args_for_dir)
         20 endfunction
         21 
         22 function s:make_include(array)
         23     let beg='--include="*.'
         24     let end='"'
         25     let inc = map(a:array,  'l:beg . v:val . l:end')
         26     return join(inc)
         27 endfunction
         28 
         29 function! s:make_args_for_dir(args)
         30   let res = []
         31   call extend(res, a:args)
         32 
         33   if len(res) == 0
         34     return s:make_include(['[chCH]', 'cpp', 'sh', 'rb', 'py', 'vim', 'md', 'pu'])
         35   else
         36     if len(res) == 1 && res[0] == '-'
         37         return '--exclude-dir=".git"'
         38     else
         39         return s:make_include(res)
         40     endif
         41   end
         42 endfunction
         43 
```

### vim_config/nvim/autoload/multi_hl.vim <a id="SS_25_1_8"></a>


```vim
          1 function! multi_hl#add_word(word, row)
          2 
          3     let curr = @/
          4     if a:row
          5         let new_word = a:word
          6     else
          7         let new_word = '\<' . a:word . '\>'
          8     endif
          9 
         10     if len(curr) != 0
         11         let search = curr . '\|' . new_word
         12     else
         13         let search = new_word
         14     endif
         15 
         16     let @/ = search
         17 
         18 endfunction
         19 
         20 function! multi_hl#clear()
         21     let @/ = ''
         22 endfunction
```

### vim_config/nvim/autoload/next_file.vim <a id="SS_25_1_9"></a>


```vim
          1 " カレントファイルがxxx_yyy_zzz.cppだったとすると、
          2 "   del_num     :0      エクステンションを取ったxxx_yyy_zzzに*を付けてglob
          3 "               :5      xxx_yyy_z*をglob
          4 
          5 function! s:make_stem(curr_file, del_num) abort
          6     if a:del_num == 0
          7         let stem = expand('%:r')
          8     else
          9         let name_len = len(a:curr_file)
         10 
         11         if name_len > a:del_num
         12             let name_len -= a:del_num
         13         else
         14             let name_len = 1
         15         endif
         16 
         17         let stem = expand('%')[0 : name_len]
         18     endif
         19 
         20     " ファイル名がxxx_ut.(cpp|h)だった場合の調整
         21     return substitute(stem, "_ut$", "", "")
         22 endfunction
         23 
         24 function! s:get_next_file(curr_file, stem) abort
         25     let candidates = glob(a:stem . "*", 1, 1)
         26     let candi_num = len(candidates)
         27 
         28     if candi_num < 2
         29         return ''
         30     endif
         31 
         32 	for i in range(candi_num)
         33         if a:curr_file == candidates[i]
         34             let i = i + 1
         35             if i < candi_num
         36                 return candidates[i]
         37             else
         38                 return candidates[0]
         39             endif
         40         endif
         41 	endfor
         42 
         43     echomsg 'mybe bug found in next_file.vim:'
         44 endfunction
         45 
         46 let s:last_file = ''
         47 let s:last_del_num = 0
         48 
         49 function! next_file#change(del_num) abort
         50     let curr_file = expand('%')
         51 
         52     if s:last_file == curr_file && a:del_num == 0
         53         let del_num = s:last_del_num
         54     else
         55         let del_num = a:del_num
         56     endif
         57 
         58     let stem = s:make_stem(curr_file, del_num)
         59     echo stem . '*  :' . del_num
         60 
         61     let next_file = s:get_next_file(curr_file, stem)
         62     if next_file == ''
         63         let s:last_file = curr_file
         64         let s:last_del_num = del_num < 6 ? 6 : del_num + 1
         65     else
         66         let s:last_file = next_file
         67         let s:last_del_num = del_num
         68         execute 'edit' next_file
         69     endif
         70 endfunction
         71 
```

### vim_config/nvim/autoload/term.vim <a id="SS_25_1_10"></a>


```vim
          1 let s:term_num = -1
          2 
          3 function! s:start_term() abort
          4 "    silent execute 'new'
          5     silent execute 'terminal'
          6 
          7     let s:term_num = bufnr()
          8 endfunction
          9 
         10 function! term#start() abort
         11     if s:term_num == -1
         12         call s:start_term()
         13     else
         14         try
         15             execute "buffer " . s:term_num
         16         catch
         17             " bufferが閉じられていた
         18             call s:start_term()
         19         endtry
         20     endif
         21 endfunction
         22 
         23 
```

### vim_config/nvim/autoload/termdbg.vim <a id="SS_25_1_11"></a>


```vim
          1 ":Run [args]    [args] または以前の引数でプログラムを実行する
          2 ":Arguments     {args}  次の :Run のために引数を設定する
          3 ":Break         カーソル位置にブレークポイントを設定する。
          4 ":Break         {position}
          5 "               指定位置にブレークポイントを設定する。
          6 ":Clear         カーソル位置のブレークポイントを削除する
          7 ":Step          gdb の "step" コマンドを実行する
          8 ":Over          gdb の "next" コマンドを実行する
          9 "               (:Next だと Vim のコマンドとかぶるので)
         10 ":Finish        gdb の "finish" コマンドを実行する
         11 ":Continue      gdb の "continue" コマンドを実行する
         12 ":Stop          プログラムを中断する
         13 
         14 
         15 " todo
         16 "  b    をトグルにしたい
         17 "
         18 function! termdbg#key_map() abort
         19     nnoremap <silent> <buffer> <Plug>(gdb-run) :Run<CR>
         20     nmap <buffer> R <Plug>(gdb-run)
         21 
         22     nnoremap <silent> <buffer> <Plug>(gdb-break) :Break<CR>
         23     nmap <buffer> B <Plug>(gdb-break)
         24 
         25     nnoremap <silent> <buffer> <Plug>(gdb-continue) :Continue<CR>
         26     nmap <buffer> C <Plug>(gdb-continue)
         27 
         28     nnoremap <silent> <buffer> <Plug>(gdb-break-clear) :Clear<CR>
         29     nmap <buffer> D <Plug>(gdb-break-clear)
         30 
         31     nnoremap <silent> <buffer> <Plug>(gdb-finish) :Finish<CR>
         32     nmap <buffer> F <Plug>(gdb-finish)
         33 
         34     nnoremap <silent> <buffer> <Plug>(gdb-next) :Over<CR>
         35     nmap <buffer> N <Plug>(gdb-next)
         36 
         37     nnoremap <silent> <buffer> <Plug>(gdb-step) :Step<CR>
         38     nmap <buffer> S <Plug>(gdb-step)
         39 
         40 endfunction
         41 
         42 function! termdbg#start(program)
         43     silent execute ':packadd termdebug'
         44     silent execute ':Termdebug ' . a:program
         45 endfunction
         46 
```

### vim_config/nvim/cheatsheet.md <a id="SS_25_1_12"></a>


```vim
          1 # My CheatSheet
          2 
          3 ## dein
          4 * https://github.com/Shougo/dein.vimからdeinとダウンロードしてセットアップ
          5     * curl ... > installer.sh   # インストーラのダウンロード
          6     * sh ./installer.sh ~/$XDG_CONFIG_HOME/nvim_pkg/dein    # deinのダウンロード
          7 * :call dein#install()			# 他のパッケージインストール
          8 
          9 ## terminal(windows app)操作
         10 * Alt-space -> x    最大化
         11 * Alt-space -> r    元のサイズに戻す
         12 * Alt-space -> n    最小化
         13 * Alt-space -> m    ウィンドウの移動
         14 * Alt-space -> s    ウィンドウのサイズ変更
         15 * window-m          全アプリの最小化
         16 * window-d          デスクトップの表示/全アプリの表示
         17 
         18 
         19 ## 正規表現
         20 [正規表現アトム](https://vim-jp.org/vimdoc-ja/pattern.html#pattern-atoms)
         21 
         22 \_.         改行含むすべての文字にマッチ
         23 
         24 ## NextFile 
         25 <M-q>           現在のファイル名を@qに代入
         26 <Num><C-q>      現在のファイル名を<Num>文字消して、"その文字列.\*"とマッチしたファイルを開く
         27                 Numが省略された場合<Num>は0として処理する
         28                 Numが0であった場合、"サフィックスを削除した文字列.\*"とマッチしたファイルを開く
         29 
         30 ## MultiHl
         31 :MultiHlAdd     現在のカーソルの下のwordを'\<word\>にして、@/に追加。
         32 :MultiHlAddR    現在のカーソルの下のwordをそのまま@/に追加。
         33 :MultiHlAddI    <WORD> WORDをそのまま@/に追加。
         34 :MultiHlClear   @/に""を入力。
         35 
         36 ## git diff
         37 :GitDiff        : gitリポジトリのdiffリスト
         38 :GitDiffResize  : 画面をリサイズして、gitリポジトリのdiffリスト
         39 :GitDiffOff     : \*.newをbwipeoutしてdiffモード終了
         40 {Visual}a       : git add from '< to '>
         41 c"              : git commit -m "までコマンドラインに入力
         42 d               : 水平分割diff表示
         43 vd              : 垂直分割diff表示
         44 h               : HEADとの水平分割diff表示
         45 vh              : HEADとの垂直分割diff表示
         46 <C-Q>           : git diffモード終了
         47 {Visual}L       : cygstart/wslstart from '< to '>
         48 {Visual}r       : git reset from '< to '>
         49 s               : diffリストの再ロード
         50 
         51 ## grep
         52 :Grep [suffix ...]          : grep -R --include=\*.suffix ... @/
         53 :GrepP pattern [suffix ...] : grep -R --include=\*.suffix ... pattern
         54 
         55 suffixを省略した場合、cpp c h rb py vimがsuffixになる。
         56 全体をgrepしたい場合は - を指定する。
         57 :Grep、:Grepp実行後はquick fixウインドが開いて結果を見ることができる。
         58 <C-g><C-n>で次へ移動、<C-g><C-p>で前に移動できる。
         59 
         60 :set ignorecaseが行われていた場合には、grepのオプションに-iが追加される。
         61 :Grepが行われた場合に実際に起動されるgrepコマンドは、:grepである。
         62 :grepが行われた場合に実際に起動されるgrepコマンドは、:set grepprg=...で設定されている。
         63 
         64 
         65 ## :terminalの使い方
         66 * <C-q>                                     vimモード
         67 * a, i等の通常のinsertモード移行で          terminalモード
         68 
         69 でソースコード全体からの補完ができるらしいので調べる。
         70 
         71 ## termdebug
         72 * nvim-gdbはやめて、こちらにした。
         73 
         74 :DbgStart <prog>    termdebugをロードして、gdb <prog>
         75 :DbgKey             下記mapをバッファローカルでmap
         76 
         77 オリジナルコマンド  map
         78 :Run [args]         R   [args] または以前の引数でプログラムを実行する
         79 :Arguments              {args}  次の :Run のために引数を設定する
         80 :Break              B   カーソル位置にブレークポイントを設定する。
         81 :Clear              D   カーソル位置のブレークポイントを削除する
         82 :Step               S   gdb の "step" コマンドを実行する
         83 :Over               N   gdb の "next" コマンドを実行する
         84 :Finish             F   gdb の "finish" コマンドを実行する
         85 :Continue           C   gdb の "continue" コマンドを実行する
         86 :Stop                   プログラムを中断する
         87 
         88 ## Session
         89 * gitプロジェクトの全ディレクトリを使用してpathやtabsをセットする。
         90 * mksessionでgitリポジトリのトップにSession.vimを作る。
         91 
         92 :ProjectBegin       Session.vimをsourceして、path、tabsをセットする。
         93 :ProjectDir         現在のセッションが使用しているgitリポジトリの
         94                     トップディレクトリを表示。
         95 :ProjectMake        Session.vimを作る。
         96 :ProjectNew         現在のセッションをカレントディレクトリを含む
         97                     gitリポジトリにする。
         98   
         99 ## PathSet
        100 * pathにカレントディレクトリ以下のディレクトリをセットする。
        101 
        102 :PathAdd            pathにディレクトリを追加する
        103 :PathClear          pathを./のみにする
        104 :PathSet            PathClearしてからPathAddする
        105 
        106 ## Buff
        107 軽いのが取り柄のバッファエクスプローラ。
        108 
        109 :Buff               :buffersの情報からBuffers問う名前のバッファを開く。
        110 o                   プロンプトの下のバッファを開く。
        111 d                   プロンプトの下のバッファをスワイプアウトする。
        112 D                   プロンプトの下のバッファを強制スワイプアウトする。
        113 
        114 ## チップス
        115 * 現在のrcフィルの確認
        116         :echo $MYGVIMRC
        117 
        118 * マップの定義位置
        119         :verbose map <C-Q>
        120 
        121 * vimコマンドの出力の取り込み
        122         :let @a=execute('scriptnames')  "scriptnamesの出力をレジスタaに入れる。
        123 
        124 * globalで行に移動し、そこでコマンド実行
        125         :global/^</normal AHEHE     "先頭が"<"である行の末尾に"HEHE"を追加する。
        126 
        127 * コマンドの繰り返し数の注意
        128         :map <C-A>  3w
        129   とした場合、 
        130         2<C-A>
        131   は
        132         23w
        133   となるため、このコマンドは23ワードの移動になるが、それはおそらく意図したものではない。
        134   <Num><C-A>を<C-A>の<Num>回の繰り返しにしたい場合、式レジスタを使い以下のように書く。
        135         :map <C-A>  @='3w'<CR>
        136 
        137 ### todo
        138 * 言語サポート
        139     * gdbのpでSTLコンテナのきれいな表示がしたい。
        140     * rtag.vim
        141     * Tagbar: a class outline viewer for Vim
        142 
        143 * そのうち調べる
        144     * コメントフォーマット。'formatoptions' の設定
        145     * 'showcmd'、'backspace'
        146     * 関数escape(@", '\\/')
        147     * packadd! matchit  「と」のマッチング
        148     * colorscheme evening
        149     * :mksession、:wviminfo、:rviminfo
        150     * terminal 端末通信 call/drop
```

### vim_config/nvim/ftplugin/c.vim <a id="SS_25_1_13"></a>


```vim
          1 setlocal tabstop=4
          2 setlocal shiftwidth=4
          3 setlocal expandtab
          4 setlocal tags=tags,./tags
          5 
          6 " paren and etc matching
          7 set matchpairs+=<:>
          8 hi MatchParen ctermbg=0 cterm=bold,reverse
          9 
```

### vim_config/nvim/ftplugin/python.vim <a id="SS_25_1_14"></a>


```vim
          1 setlocal tabstop=4
          2 setlocal shiftwidth=4
          3 setlocal expandtab
          4 setlocal tags=tags,./tags
          5 
```

### vim_config/nvim/ftplugin/ruby.vim <a id="SS_25_1_15"></a>


```vim
          1 setlocal tabstop=2
          2 setlocal shiftwidth=2
          3 setlocal expandtab
          4 setlocal tags=tags,./tags
```

### vim_config/nvim/init.vim <a id="SS_25_1_16"></a>


```vim
          1 if exists('s:loaded')
          2     finish
          3 else
          4     let s:loaded = 1
          5 endif
          6 
          7 function! s:get_os()
          8     if isdirectory('c:/')
          9         if isdirectory('/usr')
         10             return 'cygwin'
         11         else
         12             return 'windows'
         13         endif
         14     endif
         15 
         16     let old=&ignorecase
         17     let uname=system('uname')
         18 
         19     let &ignorecase = 1
         20 
         21     if uname =~ ".*linux.*"
         22         let ret = 'linux'
         23     else
         24         let ret = 'unknown'
         25     endif
         26 
         27     let &ignorecase = old
         28     return ret
         29 endfunction
         30 
         31 let g:os=s:get_os()
         32 
         33 let s:dir=expand('<sfile>:p:h')
         34 
         35 execute 'source ' . s:dir . '/' . 'org.vim'
         36 execute 'source ' . s:dir . '/' . 'package.vim'
         37 
         38 if !has('nvim')
         39     execute 'set runtimepath+=' . s:dir
         40     if g:os == 'linux'
         41         set runtimepath+=/usr/share/vim/
         42     elseif g:os == 'cygwin'
         43         set runtimepath+=/usr/share/vim/vim82
         44     elseif g:os == 'windows'
         45 
         46     endif
         47 endif
```

### vim_config/nvim/org.vim <a id="SS_25_1_17"></a>


```vim
          1 " misc
          2 set hidden
          3 set ruler
          4 set hlsearch
          5 set nowrapscan
          6 set laststatus=2
          7 set noequalalways
          8 set backspace=indent,eol,start
          9 set incsearch
         10 set background=dark
         11 set statusline=%<%f[%n]%h%m%r%=%l,%c%V\ %P
         12 set fileformats=unix,dos,mac
         13 set printoptions=number:y
         14 
         15 set virtualedit=block
         16 
         17 " Makefileやbashスクリプトでgfを効かせるため
         18 set isfname-=:
         19 set isfname-=,
         20 set isfname-=\=
         21 
         22 " encoding
         23 "set encoding=utf-8
         24 set fileencoding=utf-8
         25 set fileencodings=iso-2022-jp,euc-jp,sjis,utf-8
         26 
         27 "
         28 syntax on
         29 
         30 " to use quick fix
         31 "make setting
         32 set makeprg=/usr/bin/make
         33 set errorformat+=In\ file\ included\ from\ %f:%l:%m     "gcc
         34 set errorformat+=%f:%l:%m                               "gcc
         35 set errorformat+=%f\|%l\|%m                             "grep from vim
         36 set errorformat+=%t\\,%f\\,%l\\,%c\\,%m
         37 
         38 "grep setting
         39 set grepprg=/usr/bin/grep\ -nH
         40 
         41 let &makeef = expand('<sfile>:p:h') . '/' . getpid()
         42 
         43 " default text
         44 set tabstop=4
         45 set shiftwidth=4
         46 set expandtab
         47 set nowrap
         48 set cindent
         49 "set iskeyword+=-
```

### vim_config/nvim/package.vim <a id="SS_25_1_18"></a>


```vim
          1 if &compatible
          2     set nocompatible " Be iMproved
          3 endif
          4 
          5 " このファイルのあるディレクトリ/../nvim_pkg/deinにパッケージを入れる。
          6 let g:pkg_dir=simplify(expand('<sfile>:p:h') . '/../nvim_pkg/dein')
          7 
          8 " Required:
          9 " Add the dein installation directory into runtimepath
         10 execute 'set runtimepath+=' . g:pkg_dir . '/repos/github.com/Shougo/dein.vim'
         11 execute 'set runtimepath+=' . g:pkg_dir . '/repos/github.com/'
         12 
         13 " Required:
         14 call dein#begin(g:pkg_dir)
         15 
         16 " Let dein manage dein
         17 " Required:
         18 call dein#add(g:pkg_dir . '/repos/github.com/Shougo/dein.vim')
         19 if !has('nvim')
         20     call dein#add('roxma/nvim-yarp')
         21     call dein#add('roxma/vim-hug-neovim-rpc')
         22 endif
         23 
         24 call dein#add('Shougo/deoplete.nvim')
         25 call dein#add('zchee/deoplete-clang')
         26 
         27 " Add or remove your plugins here like this:
         28 call dein#add('Shougo/neosnippet.vim')
         29 call dein#add('Shougo/neosnippet-snippets')
         30 call dein#add('Shougo/neoinclude.vim')
         31 
         32 call dein#add('tpope/vim-fugitive')
         33 call dein#add('reireias/vim-cheatsheet')
         34 call dein#add('mattn/vim-maketable')
         35 call dein#add('aklt/plantuml-syntax')
         36 
         37 " Required:
         38 call dein#end()
         39 
         40 " Required:
         41 filetype plugin indent on
         42 syntax enable
         43 
         44 let g:cheatsheet#cheat_file = expand('<sfile>:p:h') . '/cheatsheet.md'
         45 let g:table_mode_corner = '|'
         46 
         47 if g:os == 'windows'
         48     let g:python_host_prog  = 'C:\cygwin64\bin\python2.7.exe'
         49     let g:python3_host_prog  = 'C:\cygwin64\bin\python3.8.exe'
         50 elseif g:os == 'cygwin'
         51 
         52 elseif g:os == 'linux'
         53     let g:ruby_host_prog = '/usr/local/bin/neovim-ruby-host'
         54     let g:python_host_prog  = '/usr/bin/python2'
         55     let g:python3_host_prog  = '/usr/bin/python3'
         56 else
         57     echo 'unkown os'
         58 endif
         59 
         60 " deoplete
         61 if has('python3')
         62     let g:deoplete#enable_at_startup = 1
         63     let g:deoplete#sources#clang#libclang_path = '/usr/lib/llvm-10/lib/libclang.so'
         64     let g:deoplete#sources#clang#clang_header = '/usr/lib/llvm-10/lib/clang/'
         65     let g:deoplete#sources#clang#clang_complete_database = './'
         66     "g:deoplete#sources#clang#flags	See this section	No
         67     "g:deoplete#sources#clang#sort_algo	''	No
         68     "g:deoplete#sources#clang#include_default_arguments	False	No
         69     "g:deoplete#sources#clang#filter_availability_kinds
         70 endif
```

### vim_config/nvim/plugin/buffers.vim <a id="SS_25_1_19"></a>


```vim
          1 command! -nargs=0 Buff     call buffers#begin()
```

### vim_config/nvim/plugin/cd.vim <a id="SS_25_1_20"></a>


```vim
          1 command! -nargs=0 Cd    call cd#change_dir()
          2 nmap <C-c>       :Cd<CR>
          3 
          4 nmap <S-c>       :cd ..<CR>:pwd<CR>
          5 
```

### vim_config/nvim/plugin/clear_undo.vim <a id="SS_25_1_21"></a>


```vim
          1 function! ClearUndo()
          2     let old_undolevels = &undolevels
          3     set undolevels=-1
          4     exe "normal a \<BS>\<Esc>"
          5     let &undolevels = old_undolevels
          6     unlet old_undolevels
          7 endfunction
          8 
          9 command! -nargs=0 ClearUndo call ClearUndo()
         10 
         11 
```

### vim_config/nvim/plugin/ctags_ext.vim <a id="SS_25_1_22"></a>


```vim
          1 function! CTags(...)
          2     if a:0 == 0
          3         let l:dir="."
          4     else
          5         let l:dir=a:1
          6     end
          7     silent execute '!ctags -R --extras=+q ' . l:dir
          8 endfunction
          9 
         10 command!  -nargs=? -complete=dir Ctags call CTags(<f-args>)
         11 
```

### vim_config/nvim/plugin/dev_env.vim <a id="SS_25_1_23"></a>


```vim
          1 function! dev_env#setup()
          2     execute ":only"
          3     execute ":set lines=62"
          4     execute ":set columns=201"
          5     
          6     "少し待たないとカラムが増える前にvsplitしてしまう
          7     execute ":sleep 300m"   
          8     execute ":vsplit"
          9     execute ":split"
         10     execute "normal \<C-W>l"
         11     execute ":split"
         12     execute "normal \<C-W>j"
         13     execute ":Term"
         14     execute "normal \<C-W>h"
         15     execute "normal \<C-W>k"
         16     set textwidth=100
         17 endfunction
         18 
         19 command! -nargs=0 DevEnv     call dev_env#setup()
```

### vim_config/nvim/plugin/git_diff.vim <a id="SS_25_1_24"></a>


```vim
          1 command! -nargs=0 GitDiff       call git_diff#begin(0)
          2 command! -nargs=0 GitDiffResize call git_diff#begin(1)
          3 command! -nargs=0 GitDiffOff    call git_diff#show_diff_off()
```

### vim_config/nvim/plugin/git_session.vim <a id="SS_25_1_25"></a>


```vim
          1 command! -nargs=0 SessionBegin  call git_session#begin()
          2 command! -nargs=0 SessionDir    call git_session#dir()
          3 command! -nargs=0 SessionMake   call git_session#make()
          4 command! -nargs=0 SessionNew    call git_session#new_session()
          5 command! -nargs=0 SessionPath   call git_session#set_path()
```

### vim_config/nvim/plugin/grep.vim <a id="SS_25_1_26"></a>


```vim
          1 command!  -nargs=? Grep call grep#grep(<f-args>)
          2 command!  -nargs=+ Grepp call grep#grepp(<f-args>)
          3 
```

### vim_config/nvim/plugin/keybind.vim <a id="SS_25_1_27"></a>


```vim
          1 "Set up key binding
          2 
          3 " window control
          4 nmap ;   4<C-W>+
          5 nmap -   4<C-W>-
          6 noremap L   <C-L>
          7 nmap >   <C-W>>
          8 nmap <   <C-W><
          9 nmap <C-k>   <C-W>k
         10 nmap <C-j>   <C-W>j
         11 nmap <C-h>   <C-W>h
         12 nmap <C-l>   <C-W>l
         13 nmap <C-p>   <C-o>
         14 
         15 "next/prev file
         16 nmap <C-n>   :bn<CR>
         17 nmap <C-p>   :bp<CR>
         18 
         19 "next/prev quick fix
         20 nmap <C-g><C-n>  :cn<CR>
         21 nmap <C-g><C-p>  :cp<CR>
         22 
```

### vim_config/nvim/plugin/multi_hl.vim <a id="SS_25_1_28"></a>


```vim
          1 command! -nargs=0 MultiHlAdd    call multi_hl#add_word(expand('<cword>'), 0)
          2 command! -nargs=0 MultiHlAddR   call multi_hl#add_word(expand('<cword>'), 1)
          3 command! -nargs=1 MultiHlAddI      call multi_hl#add_word(<q-args>, 1)
          4 command! -nargs=0 MultiHlClear     call multi_hl#clear()
```

### vim_config/nvim/plugin/next_file.vim <a id="SS_25_1_29"></a>


```vim
          1 if g:os == 'linux'
          2     nmap <M-q>      :let @q=expand('%')<CR>
          3 else
          4     nmap <S-C-q>    :let @q=expand('%')<CR>
          5 endif
          6 
          7 command!  -count NF call next_file#change(<count>)
          8 nmap <C-q>      :NF<CR>
```

### vim_config/nvim/plugin/path_set.vim <a id="SS_25_1_30"></a>


```vim
          1 function! path_set#add()
          2     let temp = system('find $(pwd) -type d')
          3     let dirs = split(temp, "\n")
          4     let paths = &path . ',' . join(dirs, ',')
          5     let &path = paths
          6 endfunction
          7 
          8 function! path_set#clear()
          9     let &path = './'
         10 endfunction
         11 
         12 function! path_set#set()
         13     call path_set#clear()
         14     call path_set#add()
         15 endfunction
         16 
         17 command! -nargs=0 PathAdd  call path_set#add()
         18 command! -nargs=0 PathClear  call path_set#clear()
         19 command! -nargs=0 PathSet  call path_set#set()
```

### vim_config/nvim/plugin/scratch.vim <a id="SS_25_1_31"></a>


```vim
          1 let s:scratch_buffer = 'Scratch'
          2 
          3 function! scratch#begin()
          4     let winid = bufwinid(s:scratch_buffer)
          5     if winid isnot# -1
          6         call win_gotoid(winid)
          7     else
          8         execute 'new' s:scratch_buffer
          9         set buftype=nofile
         10         set noswapfile
         11     endif
         12 endfunction
         13 
         14 command! -nargs=0 Scratch     call scratch#begin()
         15 
```

### vim_config/nvim/plugin/term.vim <a id="SS_25_1_32"></a>


```vim
          1 if g:os == 'windows'
          2     set shell=C:/cygwin64/bin/bash.exe
          3 else
          4     set shell=/bin/bash
          5 endif
          6 
          7 set shellpipe=\|&\ tee
          8 set shellcmdflag=-c
          9 set shellslash
         10 
         11 tnoremap <silent> <C-q> <C-\><C-n>
         12 command! -nargs=0 Term     call term#start()
         13 
```

### vim_config/nvim/plugin/termdbg.vim <a id="SS_25_1_33"></a>


```vim
          1 command! -nargs=1 -complete=file DbgStart   call termdbg#start(<q-args>)
          2 command! -nargs=0 DbgKey     call termdbg#key_map()
          3 
          4 
```

### vim_config/nvim/rplugin/python3/next_file.py <a id="SS_25_1_34"></a>


```vim
          1 import pynvim
          2 import glob
          3 
          4 @pynvim.plugin
          5 class NextFile(object):
          6 
          7     def __init__(self, nvim):
          8         self.nvim = nvim
          9         self.delete_len = 0
         10         self.latest_file = None
         11         self.file_list = []
         12 
         13     @pynvim.command('NextFile', nargs='?', range='', sync = True)
         14     def next_file(self, args, range):
         15         if len(args) != 0 :
         16             try :
         17                 self.delete_len = int(args[0])
         18             except:
         19                 self.delete_len = 0
         20 
         21         curr_filename = self.nvim.eval("expand('%')")
         22         next_filename = self._next_filename(curr_filename)
         23         self.nvim.command(f"edit {next_filename}")
         24 
         25     def _next_filename(self, filename) :
         26 
         27         if self.delete_len == 0 :
         28             body, *_ = filename.split(".")
         29         else:
         30             body = filename[0 : len(filename) - self.delete_len]
         31             self.latest_file = None
         32 
         33         if self.latest_file != filename :
         34             self.file_list = glob.glob(body + "*")
         35 
         36         for i, f in enumerate(self.file_list) :
         37             if filename == f :
         38                 self.latest_file = self.file_list[(i + 1) % len(self.file_list)]
         39 
         40                 return self.latest_file
         41 
```

### vim_config/vim.sh <a id="SS_25_1_35"></a>


```vim
          1 function os_name()
          2 {
          3     local -r uname=$(uname)
          4 
          5     if [[ $uname =~ .*[lL]inux.* ]]; then
          6         echo linux
          7     elif [[ $uname =~ .*CYGWIN_NT.* ]]; then
          8         echo cygwin
          9     else
         10         echo unknown
         11     fi
         12 }
         13 
         14 readonly OS=$(os_name)
         15 
         16 if [[ $OS == 'cygwin' ]]; then
         17     function gvim()
         18     {
         19         (
         20             gvim_prog=$(which gvim)
         21             export XDG_CONFIG_HOME=$(cygpath -w $XDG_CONFIG_HOME)
         22             $gvim_prog "$@"
         23         )
         24     }
         25 
         26     function _nvim_qt()
         27     {
         28         (
         29             export XDG_CONFIG_HOME=$(cygpath -w $XDG_CONFIG_HOME)
         30             nvim-qt "$@"
         31         )
         32     }
         33 
         34     function _nvim()
         35     {
         36         (
         37             export XDG_CONFIG_HOME=$(cygpath -w $XDG_CONFIG_HOME)
         38             nvim "$@"
         39         )
         40     }
         41     alias nvim-qt=_nvim_qt
         42     alias nvim=_nvim
         43 
         44 elif [[ $OS == 'linux' ]]; then
         45     function tnvim()
         46     {
         47         /mnt/c/Users/ichiro.inoue/AppData/Local/wsltty/bin/mintty.exe \
         48             --WSL= \
         49             --configdir='C:\Users\ichiro.inoue\AppData\Roaming\wsltty' \
         50             nvim "$@"
         51     }
         52 
         53     alias tn=tnvim
         54 fi
```

### vim_config/vim/gvimrc <a id="SS_25_1_36"></a>


```vim
          1 "このファイルは$HOME/.gvimrcにコピーするかシンボリックリンクを張る。
          2 
          3 set guifont=ＭＳ_ゴシック:h10:cSHIFTJIS
          4 
          5 let g:bg_coler='black'
          6 highlight Normal guibg='black' guifg='white'
          7 
```

### vim_config/vim/vimrc <a id="SS_25_1_37"></a>


```vim
          1 "このファイルは$HOME/.vimrcにコピーするかシンボリックリンクを張る。
          2 
          3 source $XDG_CONFIG_HOME/nvim/init.vim
```

## C++ <a id="SS_25_2"></a>
### example/dynamic_memory_allocation/malloc_ut.cpp <a id="SS_25_2_1"></a>


```cpp
          1 #include <sys/unistd.h>
          2 
          3 #include <cassert>
          4 #include <cstdint>
          5 #include <mutex>
          6 
          7 #include "gtest_wrapper.h"
          8 
          9 #include "dynamic_memory_allocation_ut.h"
         10 #include "spin_lock.h"
         11 #include "utils.h"
         12 
         13 // @@@ sample begin 0:0
         14 
         15 extern "C" void* sbrk(ptrdiff_t __incr);
         16 // @@@ sample end
         17 
         18 namespace MallocFree {
         19 // @@@ sample begin 1:0
         20 
         21 namespace {
         22 
         23 struct header_t {
         24     header_t* next;
         25     size_t    n_units;  // header_tが何個あるか
         26 };
         27 
         28 header_t*        header{nullptr};
         29 SpinLock         spin_lock{};
         30 constexpr size_t unit_size{sizeof(header_t)};
         31 
         32 inline bool sprit(header_t* header, size_t n_units, header_t*& next) noexcept
         33 {
         34     // @@@ ignore begin
         35     assert(n_units > 1);  // ヘッダとバッファなので最低でも2
         36 
         37     next = nullptr;
         38 
         39     if (header->n_units == n_units || header->n_units == n_units + 1) {
         40         next = header->next;
         41         return true;
         42     }
         43     else if (header->n_units > n_units) {
         44         next            = header + n_units;
         45         next->n_units   = header->n_units - n_units;
         46         next->next      = header->next;
         47         header->n_units = n_units;
         48         return true;
         49     }
         50 
         51     return false;
         52     // @@@ ignore end
         53 }
         54 
         55 inline void concat(header_t* front, header_t* rear) noexcept
         56 {
         57     // @@@ ignore begin
         58     if (front + front->n_units == rear) {  // 1枚のメモリになる
         59         front->n_units += rear->n_units;
         60         front->next = rear->next;
         61     }
         62     else {
         63         front->next = rear;
         64     }
         65     // @@@ ignore end
         66 }
         67 
         68 header_t* set_back(void* mem) noexcept { return static_cast<header_t*>(mem) - 1; }
         69 
         70 static_assert(sizeof(header_t) == alignof(std::max_align_t));
         71 
         72 void* malloc_inner(size_t size) noexcept
         73 {
         74     // @@@ ignore begin
         75     // size分のメモリとヘッダ
         76     auto n_units = (Roundup(unit_size, size) / unit_size) + 1;
         77     auto lock    = std::lock_guard{spin_lock};
         78 
         79     auto curr = header;
         80     for (header_t* prev = nullptr; curr != nullptr; prev = curr, curr = curr->next) {
         81         header_t* next;
         82 
         83         if (!sprit(curr, n_units, next)) {
         84             continue;
         85         }
         86 
         87         if (prev == nullptr) {
         88             header = next;
         89         }
         90         else {
         91             prev->next = next;
         92         }
         93         break;
         94     }
         95 
         96     if (curr != nullptr) {
         97         ++curr;
         98     }
         99 
        100     return curr;
        101     // @@@ ignore end
        102 }
        103 }  // namespace
        104 // @@@ sample end
        105 // @@@ sample begin 2:0
        106 
        107 void free(void* mem) noexcept
        108 {
        109     header_t* mem_to_free = set_back(mem);
        110 
        111     mem_to_free->next = nullptr;
        112 
        113     auto lock = std::lock_guard{spin_lock};
        114 
        115     if (header == nullptr) {
        116         header = mem_to_free;
        117         return;
        118     }
        119     // @@@ sample end
        120     // @@@ sample begin 2:1
        121 
        122     if (mem_to_free < header) {
        123         concat(mem_to_free, header);
        124         header = mem_to_free;
        125         return;
        126     }
        127 
        128     auto curr = header;
        129     for (; curr->next != nullptr; curr = curr->next) {
        130         if (mem_to_free < curr->next) {  // 常に curr < mem_to_free
        131             concat(mem_to_free, curr->next);
        132             concat(curr, mem_to_free);
        133             return;
        134         }
        135     }
        136 
        137     concat(curr, mem_to_free);
        138     // @@@ sample end
        139     // @@@ sample begin 2:2
        140 }
        141 // @@@ sample end
        142 // @@@ sample begin 3:0
        143 
        144 void* malloc(size_t size) noexcept
        145 {
        146     void* mem = malloc_inner(size);
        147     // @@@ sample end
        148     // @@@ sample begin 3:1
        149 
        150     if (mem == nullptr) {
        151         auto const add_size = Roundup(unit_size, 1024 * 1024 + size);  // 1MB追加
        152 
        153         header_t* add = static_cast<header_t*>(sbrk(add_size));
        154         add->n_units  = add_size / unit_size;
        155         free(++add);
        156         mem = malloc_inner(size);
        157     }
        158     // @@@ sample end
        159     // @@@ sample begin 3:2
        160 
        161     return mem;
        162 }
        163 // @@@ sample end
        164 
        165 namespace {
        166 TEST(NewDelete_Opt, malloc)
        167 {
        168     {
        169         void* mem = malloc(1024);
        170 
        171         ASSERT_NE(nullptr, mem);
        172         free(mem);
        173 
        174         void* ints[8]{};
        175 
        176         constexpr auto n_units = Roundup(unit_size, unit_size + sizeof(int)) / unit_size;
        177 
        178         for (auto& i : ints) {
        179             i = malloc(sizeof(int));
        180 
        181             header_t* h = set_back(i);
        182             ASSERT_EQ(h->n_units, n_units);
        183         }
        184 
        185         for (auto& i : ints) {
        186             free(i);
        187         }
        188     }
        189 
        190     // @@@ sample begin 4:0
        191 
        192     void* mem[1024];
        193 
        194     for (auto& m : mem) {  // 32バイト x 1024個のメモリ確保
        195         m = malloc(32);
        196     }
        197 
        198     // memを使用した何らかの処理
        199     // @@@ ignore begin
        200     // @@@ ignore end
        201 
        202     for (auto i = 0U; i < ArrayLength(mem); i += 2) {  // 512個のメモリを解放
        203         free(mem[i]);
        204     }
        205     // @@@ sample end
        206 
        207     for (auto i = 1U; i < ArrayLength(mem); i += 2) {
        208         free(mem[i]);
        209     }
        210 }
        211 }  // namespace
        212 }  // namespace MallocFree
```

### example/dynamic_memory_allocation/mpool_variable.h <a id="SS_25_2_2"></a>


```cpp
          1 #pragma once
          2 #include <cassert>
          3 #include <cstdint>
          4 #include <mutex>
          5 #include <optional>
          6 
          7 #include "mpool.h"
          8 #include "spin_lock.h"
          9 #include "utils.h"
         10 
         11 namespace Inner_ {
         12 
         13 struct header_t {
         14     header_t* next;
         15     size_t    n_units;  // header_tが何個あるか
         16 };
         17 
         18 constexpr auto unit_size = sizeof(header_t);
         19 
         20 inline std::optional<header_t*> sprit(header_t* header, size_t n_units) noexcept
         21 {
         22     assert(n_units > 1);  // ヘッダとバッファなので最低でも2
         23 
         24     if (header->n_units == n_units || header->n_units == n_units + 1) {
         25         return header->next;
         26     }
         27     else if (header->n_units > n_units) {
         28         auto next       = header + n_units;
         29         next->n_units   = header->n_units - n_units;
         30         next->next      = header->next;
         31         header->n_units = n_units;
         32         return next;
         33     }
         34 
         35     return std::nullopt;
         36 }
         37 
         38 inline void concat(header_t* front, header_t* rear) noexcept
         39 {
         40     if (front + front->n_units == rear) {  // 1枚のメモリになる
         41         front->n_units += rear->n_units;
         42         front->next = rear->next;
         43     }
         44     else {
         45         front->next = rear;
         46     }
         47 }
         48 
         49 inline header_t* set_back(void* mem) noexcept { return static_cast<header_t*>(mem) - 1; }
         50 
         51 static_assert(sizeof(header_t) == alignof(std::max_align_t));
         52 
         53 template <uint32_t MEM_SIZE>
         54 struct buffer_t {
         55     alignas(std::max_align_t) uint8_t buffer[Roundup(sizeof(header_t), MEM_SIZE)];
         56 };
         57 }  // namespace Inner_
         58 
         59 // @@@ sample begin 0:0
         60 
         61 template <uint32_t MEM_SIZE>
         62 class MPoolVariable final : public MPool {
         63 public:
         64     // @@@ sample end
         65     // @@@ sample begin 0:1
         66     MPoolVariable() noexcept : MPool{MEM_SIZE}
         67     {
         68         header_->next    = nullptr;
         69         header_->n_units = sizeof(buff_) / Inner_::unit_size;
         70     }
         71     // @@@ sample end
         72     // @@@ sample begin 0:2
         73 
         74     class const_iterator {
         75     public:
         76         explicit const_iterator(Inner_::header_t const* header) noexcept : header_{header} {}
         77         const_iterator(const_iterator const&) = default;
         78         const_iterator(const_iterator&&)      = default;
         79 
         80         const_iterator& operator++() noexcept  // 前置++のみ実装
         81         {
         82             assert(header_ != nullptr);
         83             header_ = header_->next;
         84 
         85             return *this;
         86         }
         87 
         88         Inner_::header_t const* operator*() noexcept { return header_; }
         89 
         90         // clang-format off
         91 
         92     #if __cplusplus <= 201703L  // c++17
         93         bool operator==(const_iterator const& rhs) noexcept { return header_ == rhs.header_; }
         94         bool operator!=(const_iterator const& rhs) noexcept { return !(*this == rhs); }
         95     #else  // c++20
         96 
         97         auto operator<=>(const const_iterator&) const = default;
         98     #endif
         99         // clang-format on
        100 
        101     private:
        102         Inner_::header_t const* header_;
        103     };
        104 
        105     const_iterator begin() const noexcept { return const_iterator{header_}; }
        106     const_iterator end() const noexcept { return const_iterator{nullptr}; }
        107     const_iterator cbegin() const noexcept { return const_iterator{header_}; }
        108     const_iterator cend() const noexcept { return const_iterator{nullptr}; }
        109     // @@@ sample end
        110     // @@@ sample begin 0:3
        111 
        112 private:
        113     using header_t = Inner_::header_t;
        114 
        115     Inner_::buffer_t<MEM_SIZE> buff_{};
        116     header_t*                  header_{reinterpret_cast<header_t*>(buff_.buffer)};
        117     mutable SpinLock           spin_lock_{};
        118     size_t                     unit_count_{sizeof(buff_) / Inner_::unit_size};
        119     size_t                     unit_count_min_{sizeof(buff_) / Inner_::unit_size};
        120 
        121     virtual void* alloc(size_t size) noexcept override
        122     {
        123         // @@@ ignore begin
        124         // size分のメモリとヘッダ
        125         auto n_units = (Roundup(Inner_::unit_size, size) / Inner_::unit_size) + 1;
        126 
        127         auto lock = std::lock_guard{spin_lock_};
        128 
        129         auto curr = header_;
        130 
        131         for (header_t* prev{nullptr}; curr != nullptr; prev = curr, curr = curr->next) {
        132             auto opt_next = std::optional<header_t*>{sprit(curr, n_units)};
        133 
        134             if (!opt_next) {
        135                 continue;
        136             }
        137 
        138             auto next = *opt_next;
        139             if (prev == nullptr) {
        140                 header_ = next;
        141             }
        142             else {
        143                 prev->next = next;
        144             }
        145             break;
        146         }
        147 
        148         if (curr != nullptr) {
        149             unit_count_ -= curr->n_units;
        150             unit_count_min_ = std::min(unit_count_, unit_count_min_);
        151             ++curr;
        152         }
        153 
        154         return curr;
        155         // @@@ ignore end
        156     }
        157 
        158     virtual void free(void* mem) noexcept override
        159     {
        160         // @@@ ignore begin
        161         header_t* to_free = Inner_::set_back(mem);
        162 
        163         to_free->next = nullptr;
        164 
        165         auto lock = std::lock_guard{spin_lock_};
        166 
        167         unit_count_ += to_free->n_units;
        168         unit_count_min_ = std::min(unit_count_, unit_count_min_);
        169 
        170         if (header_ == nullptr) {
        171             header_ = to_free;
        172             return;
        173         }
        174 
        175         if (to_free < header_) {
        176             concat(to_free, header_);
        177             header_ = to_free;
        178             return;
        179         }
        180 
        181         header_t* curr = header_;
        182 
        183         for (; curr->next != nullptr; curr = curr->next) {
        184             if (to_free < curr->next) {  // 常に curr < to_free
        185                 concat(to_free, curr->next);
        186                 concat(curr, to_free);
        187                 return;
        188             }
        189         }
        190 
        191         concat(curr, to_free);
        192         // @@@ ignore end
        193     }
        194 
        195     virtual size_t get_size() const noexcept override { return 1; }
        196     virtual size_t get_count() const noexcept override { return unit_count_ * Inner_::unit_size; }
        197     virtual size_t get_count_min() const noexcept override { return unit_count_min_ * Inner_::unit_size; }
        198 
        199     virtual bool is_valid(void const* mem) const noexcept override
        200     {
        201         return (&buff_ < mem) && (mem < &buff_.buffer[ArrayLength(buff_.buffer)]);
        202     }
        203     // @@@ sample end
        204     // @@@ sample begin 0:4
        205 };
        206 // @@@ sample end
```



