if g:os == 'windows'
    set shell=C:/cygwin64/bin/bash.exe
else
    set shell=/bin/bash
endif

set shellpipe=\|&\ tee
set shellcmdflag=-c
set shellslash

tnoremap <silent> <C-q> <C-\><C-n>
command! -nargs=0 Term     call term#start()

