let s:buffers_buffer = 'Buffers'

function! s:line(num, buff_name)
    if a:buff_name == s:buffers_buffer
        return printf("%3d [%s]\n", a:num, a:buff_name)
    else
        return printf("%3d %s\n", a:num, a:buff_name)
    endif
endfunction

function! s:load_buffers_list()
    let l:line = line('.')
    let l:col = col('.')

    let buffs = split(execute('buffers'), "\n")

    setlocal modifiable

    silent execute ':%delete'
    for b in buffs
        let new_b = substitute(b, '^ *\(\d\+\).*\"\(.*\)\".*', { m -> s:line(m[1], m[2])}, 'g')
        silent execute ':normal i' . new_b 
    endfor
    silent execute ':$delete'

    setlocal modifiable
    call cursor(l:line, l:col)
endfunction

function! buffers#close_buff(force)
    let word = expand("<cword>")

    if word =~ '\d\+'
        let to_delete = bufname(str2nr(word))
    elseif word =~ '.\+'
        let to_delete = word
    else
        echo 'no file'
        return
    endif

    if to_delete == s:buffers_buffer
        execute 'bdelete!' . word
    else
        let bwipeout = 'bwipeout' . (a:force == 0 ? ' ' : '! ')
        execute bwipeout . word
        call s:load_buffers_list()
    endif
endfunction

function! buffers#open_buff()
    let word = expand("<cword>")

    if word =~ '\d\+'
        execute 'buffer ' . word
    elseif word =~ '.\+'
        execute 'buffer ' . word
    else
        echo 'no file'
    endif
endfunction

function! s:key_map() abort
    nnoremap <silent> <buffer> <Plug>(buffers-delete) :call buffers#close_buff(0)<CR>
    nmap <buffer> d <Plug>(buffers-delete)

    nnoremap <silent> <buffer> <Plug>(buffers-delete-force) :call buffers#close_buff(1)<CR>
    nmap <buffer> D <Plug>(buffers-delete-force)

    nnoremap <silent> <buffer> <Plug>(buffers-open) :call buffers#open_buff()<CR>
    nmap <buffer> o <Plug>(buffers-open)

    nnoremap <silent> <buffer> <Plug>(buffers-reload) :call buffers#begin()<CR>
    nmap <buffer> r <Plug>(buffers-reload)
endfunction

function! buffers#begin()
    let winid = bufwinid(s:buffers_buffer)
    if winid isnot# -1
        call win_gotoid(winid)
    else
        execute 'new' s:buffers_buffer
        set buftype=nofile
        set noswapfile
        call s:key_map()
    endif
    call s:load_buffers_list()
endfunction
