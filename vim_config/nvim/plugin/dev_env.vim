function! dev_env#setup()
    execute ":only"
    execute ":set lines=62"
    execute ":set columns=201"
    
    "少し待たないとカラムが増える前にvsplitしてしまう
    execute ":sleep 300m"   
    execute ":vsplit"
    execute ":split"
    execute "normal \<C-W>l"
    execute ":split"
    execute "normal \<C-W>j"
    execute ":Term"
    execute "normal \<C-W>h"
    execute "normal \<C-W>k"
    set textwidth=100
endfunction

command! -nargs=0 DevEnv     call dev_env#setup()
