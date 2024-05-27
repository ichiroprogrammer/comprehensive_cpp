" カレントファイルがxxx_yyy_zzz.cppだったとすると、
"   del_num     :0      エクステンションを取ったxxx_yyy_zzzに*を付けてglob
"               :5      xxx_yyy_z*をglob

function! s:make_stem(curr_file, del_num) abort
    if a:del_num == 0
        let stem = expand('%:r')
    else
        let name_len = len(a:curr_file)

        if name_len > a:del_num
            let name_len -= a:del_num
        else
            let name_len = 1
        endif

        let stem = expand('%')[0 : name_len]
    endif

    " ファイル名がxxx_ut.(cpp|h)だった場合の調整
    return substitute(stem, "_ut$", "", "")
endfunction

function! s:get_next_file(curr_file, stem) abort
    let candidates = glob(a:stem . "*", 1, 1)
    let candi_num = len(candidates)

    if candi_num < 2
        return ''
    endif

	for i in range(candi_num)
        if a:curr_file == candidates[i]
            let i = i + 1
            if i < candi_num
                return candidates[i]
            else
                return candidates[0]
            endif
        endif
	endfor

    echomsg 'mybe bug found in next_file.vim:'
endfunction

let s:last_file = ''
let s:last_del_num = 0

function! next_file#change(del_num) abort
    let curr_file = expand('%')

    if s:last_file == curr_file && a:del_num == 0
        let del_num = s:last_del_num
    else
        let del_num = a:del_num
    endif

    let stem = s:make_stem(curr_file, del_num)
    echo stem . '*  :' . del_num

    let next_file = s:get_next_file(curr_file, stem)
    if next_file == ''
        let s:last_file = curr_file
        let s:last_del_num = del_num < 6 ? 6 : del_num + 1
    else
        let s:last_file = next_file
        let s:last_del_num = del_num
        execute 'edit' next_file
    endif
endfunction

