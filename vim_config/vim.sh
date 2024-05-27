function os_name()
{
    local -r uname=$(uname)

    if [[ $uname =~ .*[lL]inux.* ]]; then
        echo linux
    elif [[ $uname =~ .*CYGWIN_NT.* ]]; then
        echo cygwin
    else
        echo unknown
    fi
}

readonly OS=$(os_name)

if [[ $OS == 'cygwin' ]]; then
    function gvim()
    {
        (
            gvim_prog=$(which gvim)
            export XDG_CONFIG_HOME=$(cygpath -w $XDG_CONFIG_HOME)
            $gvim_prog "$@"
        )
    }

    function _nvim_qt()
    {
        (
            export XDG_CONFIG_HOME=$(cygpath -w $XDG_CONFIG_HOME)
            nvim-qt "$@"
        )
    }

    function _nvim()
    {
        (
            export XDG_CONFIG_HOME=$(cygpath -w $XDG_CONFIG_HOME)
            nvim "$@"
        )
    }
    alias nvim-qt=_nvim_qt
    alias nvim=_nvim

elif [[ $OS == 'linux' ]]; then
    function tnvim()
    {
        /mnt/c/Users/ichiro.inoue/AppData/Local/wsltty/bin/mintty.exe \
            --WSL= \
            --configdir='C:\Users\ichiro.inoue\AppData\Roaming\wsltty' \
            nvim "$@"
    }

    alias tn=tnvim
fi
