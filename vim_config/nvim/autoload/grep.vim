function s:grep(target, args_for_dir)
    let ignore_case=&ic
    if l:ignore_case == 0
        let ic_str = ''
    else
        let ic_str = '-i '
    end
    execute ':grep -R ' . l:ic_str . a:args_for_dir . ' "' . a:target . '"' 
endfunction

function grep#grep(...)
    let args_for_dir = s:make_args_for_dir(a:000)
    let l:target=@/
    call s:grep(l:target, args_for_dir)
endfunction

function grep#grepp(pattern, ...)
    let args_for_dir = s:make_args_for_dir(a:000)
    call s:grep(a:pattern, args_for_dir)
endfunction

function s:make_include(array)
    let beg='--include="*.'
    let end='"'
    let inc = map(a:array,  'l:beg . v:val . l:end')
    return join(inc)
endfunction

function! s:make_args_for_dir(args)
  let res = []
  call extend(res, a:args)

  if len(res) == 0
    return s:make_include(['[chCH]', 'cpp', 'sh', 'rb', 'py', 'vim', 'md', 'pu'])
  else
    if len(res) == 1 && res[0] == '-'
        return '--exclude-dir=".git"'
    else
        return s:make_include(res)
    endif
  end
endfunction

