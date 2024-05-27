let s:scratch_buffer = 'Scratch'

function! scratch#begin()
    let winid = bufwinid(s:scratch_buffer)
    if winid isnot# -1
        call win_gotoid(winid)
    else
        execute 'new' s:scratch_buffer
        set buftype=nofile
        set noswapfile
    endif
endfunction

command! -nargs=0 Scratch     call scratch#begin()

