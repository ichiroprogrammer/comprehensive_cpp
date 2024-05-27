command! -nargs=0 GitDiff       call git_diff#begin(0)
command! -nargs=0 GitDiffResize call git_diff#begin(1)
command! -nargs=0 GitDiffOff    call git_diff#show_diff_off()
