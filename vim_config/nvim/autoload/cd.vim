function! s:is_term()
    let bn = bufname("%")
    if bn =~ 'term://'
        return 1
    else
        return 0
    endif
endfunction

function! cd#find_dir_candidate()
    for i in range(50)
        silent execute 'normal "uyy'
        let reg=@u
        if reg =~ 'ichiro@[^ ]\+ \~.*'
            return substitute(reg, 'ichiro@[^ ]\+', '', '') 
        endif
        silent execute 'normal k'
    endfor

    return ''
endfunction


function! cd#change_dir()
    if s:is_term() == 1
        let dir_candidate=cd#find_dir_candidate()

        if dir_candidate == ''
            echo "no dir candidate"
        else
            silent execute ':cd ' . dir_candidate
        endif
    else
        silent execute ':cd %:h'
    endif
endfunction
