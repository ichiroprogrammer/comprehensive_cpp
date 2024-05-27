command! -nargs=0 MultiHlAdd    call multi_hl#add_word(expand('<cword>'), 0)
command! -nargs=0 MultiHlAddR   call multi_hl#add_word(expand('<cword>'), 1)
command! -nargs=1 MultiHlAddI      call multi_hl#add_word(<q-args>, 1)
command! -nargs=0 MultiHlClear     call multi_hl#clear()
