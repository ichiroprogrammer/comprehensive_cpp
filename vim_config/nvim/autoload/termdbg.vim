":Run [args]    [args] または以前の引数でプログラムを実行する
":Arguments     {args}  次の :Run のために引数を設定する
":Break         カーソル位置にブレークポイントを設定する。
":Break         {position}
"               指定位置にブレークポイントを設定する。
":Clear         カーソル位置のブレークポイントを削除する
":Step          gdb の "step" コマンドを実行する
":Over          gdb の "next" コマンドを実行する
"               (:Next だと Vim のコマンドとかぶるので)
":Finish        gdb の "finish" コマンドを実行する
":Continue      gdb の "continue" コマンドを実行する
":Stop          プログラムを中断する


" todo
"  b    をトグルにしたい
"
function! termdbg#key_map() abort
    nnoremap <silent> <buffer> <Plug>(gdb-run) :Run<CR>
    nmap <buffer> R <Plug>(gdb-run)

    nnoremap <silent> <buffer> <Plug>(gdb-break) :Break<CR>
    nmap <buffer> B <Plug>(gdb-break)

    nnoremap <silent> <buffer> <Plug>(gdb-continue) :Continue<CR>
    nmap <buffer> C <Plug>(gdb-continue)

    nnoremap <silent> <buffer> <Plug>(gdb-break-clear) :Clear<CR>
    nmap <buffer> D <Plug>(gdb-break-clear)

    nnoremap <silent> <buffer> <Plug>(gdb-finish) :Finish<CR>
    nmap <buffer> F <Plug>(gdb-finish)

    nnoremap <silent> <buffer> <Plug>(gdb-next) :Over<CR>
    nmap <buffer> N <Plug>(gdb-next)

    nnoremap <silent> <buffer> <Plug>(gdb-step) :Step<CR>
    nmap <buffer> S <Plug>(gdb-step)

endfunction

function! termdbg#start(program)
    silent execute ':packadd termdebug'
    silent execute ':Termdebug ' . a:program
endfunction

