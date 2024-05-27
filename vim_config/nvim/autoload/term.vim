let s:term_num = -1

function! s:start_term() abort
"    silent execute 'new'
    silent execute 'terminal'

    let s:term_num = bufnr()
endfunction

function! term#start() abort
    if s:term_num == -1
        call s:start_term()
    else
        try
            execute "buffer " . s:term_num
        catch
            " bufferが閉じられていた
            call s:start_term()
        endtry
    endif
endfunction


