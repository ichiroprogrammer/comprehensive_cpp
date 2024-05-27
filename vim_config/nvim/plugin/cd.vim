command! -nargs=0 Cd    call cd#change_dir()
nmap <C-c>       :Cd<CR>

nmap <S-c>       :cd ..<CR>:pwd<CR>

