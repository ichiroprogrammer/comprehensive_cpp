if exists('s:loaded')
    finish
else
    let s:loaded = 1
endif

function! s:get_os()
    if isdirectory('c:/')
        if isdirectory('/usr')
            return 'cygwin'
        else
            return 'windows'
        endif
    endif

    let old=&ignorecase
    let uname=system('uname')

    let &ignorecase = 1

    if uname =~ ".*linux.*"
        let ret = 'linux'
    else
        let ret = 'unknown'
    endif

    let &ignorecase = old
    return ret
endfunction

let g:os=s:get_os()

let s:dir=expand('<sfile>:p:h')

execute 'source ' . s:dir . '/' . 'org.vim'
execute 'source ' . s:dir . '/' . 'package.vim'

if !has('nvim')
    execute 'set runtimepath+=' . s:dir
    if g:os == 'linux'
        set runtimepath+=/usr/share/vim/
    elseif g:os == 'cygwin'
        set runtimepath+=/usr/share/vim/vim82
    elseif g:os == 'windows'

    endif
endif
