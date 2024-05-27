function! s:get_git_top()
    let top = system('git rev-parse --show-toplevel')
    return substitute(top, "\n", '/', 'g')
endfunction

let s:git_session_top = s:get_git_top()
let s:git_session_file = s:git_session_top . 'Session.vim'

function! s:get_dirs() abort
    " ディレクトリのみを抽出
    let dir_filter = '|sed -e /^[^/]\\+$/d  -e  s\@/[^/]\\+$\@\@g | sort | uniq'
    let dirs_str = system("git ls-files --full-name " . s:git_session_top . dir_filter)

    let dirs_list = split(dirs_str, "\n")

    let full_dirs = map(dirs_list, 's:git_session_top . v:val')

    call add(full_dirs, s:git_session_top)

    return full_dirs
endfunction

function! git_session#set_path()
    let dirs = s:get_dirs()
    let &path ='./,/usr/include/c++/9/,' . join(dirs, ',') 

    let tag_dirs = map(dirs, 'v:val . "tags"')
    let &tags ='tags,./tags,' .  join(tag_dirs, ',')
endfunction

function! git_session#begin() abort
    let top = s:get_git_top()

    if top != s:git_session_top
        echo 'must be on the dir under ' . s:git_session_top
        return
    endif

    try
        execute 'source ' . s:git_session_file
    catch
        echo 'no session file'
    endtry
    call git_session#set_path()
endfunction

function! git_session#dir() abort
    echo s:git_session_top
endfunction

function! git_session#make() abort
    let top = s:get_git_top()

    if top != s:git_session_top
        echo 'must be on the dir under ' . s:git_session_top
        return
    endif

    execute 'mksession! ' . s:git_session_file
endfunction

function! git_session#new_session() abort
    let s:git_session_top = s:get_git_top()
    let s:git_session_file = s:git_session_top . 'Session.vim'
    call git_session#begin()
endfunction
