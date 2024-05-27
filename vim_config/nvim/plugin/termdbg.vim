command! -nargs=1 -complete=file DbgStart   call termdbg#start(<q-args>)
command! -nargs=0 DbgKey     call termdbg#key_map()


