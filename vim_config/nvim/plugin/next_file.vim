if g:os == 'linux'
    nmap <M-q>      :let @q=expand('%')<CR>
else
    nmap <S-C-q>    :let @q=expand('%')<CR>
endif

command!  -count NF call next_file#change(<count>)
nmap <C-q>      :NF<CR>
