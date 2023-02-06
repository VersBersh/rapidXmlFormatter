# SETUP WORKSPACE

# alias to nmake.exe
function global:make {
    nmake -f Makefile.win $args
}