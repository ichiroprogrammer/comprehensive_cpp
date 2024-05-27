function! path_set#add()
    let temp = system('find $(pwd) -type d')
    let dirs = split(temp, "\n")
    let paths = &path . ',' . join(dirs, ',')
    let &path = paths
endfunction

function! path_set#clear()
    let &path = './'
endfunction

function! path_set#set()
    call path_set#clear()
    call path_set#add()
endfunction

command! -nargs=0 PathAdd  call path_set#add()
command! -nargs=0 PathClear  call path_set#clear()
command! -nargs=0 PathSet  call path_set#set()
