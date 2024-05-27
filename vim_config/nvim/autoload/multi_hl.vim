function! multi_hl#add_word(word, row)

    let curr = @/
    if a:row
        let new_word = a:word
    else
        let new_word = '\<' . a:word . '\>'
    endif

    if len(curr) != 0
        let search = curr . '\|' . new_word
    else
        let search = new_word
    endif

    let @/ = search

endfunction

function! multi_hl#clear()
    let @/ = ''
endfunction
