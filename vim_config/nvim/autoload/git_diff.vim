let s:git_diff_buffer = 'GIT DIFF'
let s:git_diff_buffer_cur =''
let s:git_diff_buffer_new =''   " .newと表示されるが実際には改定前ファイル

set patchexpr=git_diff#patch()

function! git_diff#patch() abort
    silent execute '!patch -R  -o ' . v:fname_out .  ' ' . v:fname_in . ' < ' . v:fname_diff
endfunction

function! s:echo_err(msg) abort
  echohl ErrorMsg
  echomsg 'git_diff.vim:' a:msg
  echohl None
endfunction

" pattern : 0       just changed
"         : 1       change filename
function! s:modified_pattern(pattern) abort
    if  a:pattern == 0
        return '^[ADMU? ][DMU? ] \+'
    elseif  a:pattern == 1
        return 'R[M ] \+.* -> '
    endif
    call s:echo_err('modified_pattern wrong')
endfunction

function! s:get_target_name() abort
    let l:line=getline(".")

    if match(l:line, s:modified_pattern(0)) isnot# -1
        return substitute(l:line, s:modified_pattern(0), "", "")
    elseif match(l:line, s:modified_pattern(1)) isnot# -1
        return substitute(l:line, s:modified_pattern(1), "", "")
    else
        call s:echo_err(l:line . ' :this file is not modefied')
        return ''
    endif
endfunction

function! s:git_diff(patch_target, patch_file_name, from_head) abort
    if a:from_head == 0
        silent execute '!git diff ' .  a:patch_target .  ' > ' .  a:patch_file_name
    else
        silent execute '!git diff HEAD ' .  a:patch_target .  ' > ' .  a:patch_file_name
    endif
endfunction

function! s:each(line1, line2, func_ref) abort
    let l:col = col('.')

    for i in range(a:line1, a:line2)
        call cursor(i, l:col)
        call a:func_ref()
    endfor
endfunction

function! s:launch_file() abort
    let l:target=s:get_target_name()

    if g:os == 'linux'
        silent execute '!wslstart ' .  l:target
    else 
        if g:os == 'cygwin'
            silent execute '!wslstart ' .  l:target
        else
            echo 'not support launch'
        endif
    endif
endfunction

function! git_diff#launch_file(line1, line2) abort
    call s:each(a:line1, a:line2, function('s:launch_file'))
endfunction


function! s:git_add() abort
    let l:target=s:get_target_name()

    silent execute '!git add ' .  l:target
    call git_diff#make_list_load()
endfunction

function! git_diff#git_add(line1, line2) abort
    call s:each(a:line1, a:line2, function('s:git_add'))
endfunction

function! s:git_reset() abort
    let l:target=s:get_target_name()

    if len(l:target) == 0
        return
    endif

    silent execute '!git reset ' .  l:target
    call git_diff#make_list_load()
endfunction

function! git_diff#git_reset(line1, line2) abort
    call s:each(a:line1, a:line2, function('s:git_reset'))
endfunction

function! git_diff#make_list_load() abort
    setlocal modifiable

    let l:line = line('.')
    let l:col = col('.')
    silent execute ':%delete'
    silent execute 'r! git status -s'
    silent execute ':1delete'
    call cursor(l:line, l:col)

    setlocal nomodifiable
endfunction

function! s:key_map_end() abort
    delcommand GitAdd
    delcommand GitReset
endfunction

function! s:key_map_begin() abort
    command! -range GitAdd :call git_diff#git_add(<line1>, <line2>)
    map <silent> <buffer> a :GitAdd<CR>

    command! -range LauchFile :call git_diff#launch_file(<line1>, <line2>)
    map <silent> <buffer> L :LauchFile<CR>

    command! -range GitReset :call git_diff#git_reset(<line1>, <line2>)
    map <silent> <buffer> r :GitReset<CR>

    nnoremap <silent> <buffer> <Plug>(diff-open) :<C-u>call git_diff#show_diff(0, 0)<CR>
    nmap <buffer> d <Plug>(diff-open)

    nnoremap <silent> <buffer> <Plug>(diff-open-V) :<C-u>call git_diff#show_diff(1, 0)<CR>
    nmap <buffer> vd <Plug>(diff-open-V)

    nnoremap <silent> <buffer> <Plug>(diff-open-h) :<C-u>call git_diff#show_diff(0, 1)<CR>
    nmap <buffer> h <Plug>(diff-open-h)

    nnoremap <silent> <buffer> <Plug>(diff-open-Vh) :<C-u>call git_diff#show_diff(1, 1)<CR>
    nmap <buffer> vh <Plug>(diff-open-Vh)

    nnoremap <silent> <buffer> <Plug>(diff-list-close) :<C-u>call git_diff#end()<CR>
    nmap <buffer> <C-Q> <Plug>(diff-list-close)

    nnoremap <silent> <buffer> <Plug>(diff-reload) :<C-u>call git_diff#make_list_load()<CR>
    nmap <buffer> s <Plug>(diff-reload)

    nnoremap <silent> <buffer> <Plug>(git-commit) :!git commit -m 
    nmap <buffer> c <Plug>(git-commit)
endfunction

"vertial    : 0 normal split to show diff buffers
"           : 1 virtial split to show diff buffers
"from_head  : 0 git diff 
"           : 1 git diff HEAD
function! git_diff#show_diff(vertical, from_head) abort
    call git_diff#show_diff_off()

    let l:target=s:get_target_name()

    if getftime(l:target) == -1
        s:echo_err('file not exits')
    endif

    let s:git_diff_buffer_cur = l:target
    let s:git_diff_buffer_new = l:target . '.new'

    let l:temp_file = tempname()
    call s:git_diff(l:target, l:temp_file, a:from_head)

    execute ':sp'
	execute ':e ' . l:target

    if a:vertical == 0
	    execute ':diffpatch ' . l:temp_file

        " 上バッファがオリジナル。下バッファが変更後ファイル
        execute "normal \<C-w>j"
    else
	    execute ':vert diffpatch ' . l:temp_file

        " 左バッファがオリジナル。右バッファが変更後ファイル
        execute "normal \<C-w>l"
    endif

    call delete(l:temp_file)
endfunction

function! git_diff#show_diff_off()
    execute ':diffoff!'

    if s:git_diff_buffer_cur != ''
        let winid = bufwinid(s:git_diff_buffer_cur)

        if winid isnot# -1
            call win_gotoid(winid)
            :quit
        endif

        let s:git_diff_buffer_cur = ''
    endif

    if s:git_diff_buffer_new != ''
        let winid = bufwinid(s:git_diff_buffer_new)

        if winid isnot# -1
            call win_gotoid(winid)
            execute 'bwipeout! ' . s:git_diff_buffer_new
        endif

        let s:git_diff_buffer_new = ''
    endif
endfunction

function! git_diff#begin(resize) abort
    let winid = bufwinid(s:git_diff_buffer)
    if winid isnot# -1
        call win_gotoid(winid)
    else
        execute 'edit' s:git_diff_buffer
        set buftype=nofile
        set noswapfile
        setlocal nomodifiable

        call s:key_map_begin()
        call git_diff#make_list_load()
    endif

    if a:resize != 0
        execute ":only"
        let l:lines=&lines
        echo l:lines
        if l:lines < 50
            execute ":set lines=50"
        endif
        execute ":set columns=201"
    endif

endfunction

function! git_diff#end()
    call git_diff#show_diff_off()
    call s:key_map_end()
    bwipeout!
endfunction

