function! CTags(...)
    if a:0 == 0
        let l:dir="."
    else
        let l:dir=a:1
    end
    silent execute '!ctags -R --extras=+q ' . l:dir
endfunction

command!  -nargs=? -complete=dir Ctags call CTags(<f-args>)

