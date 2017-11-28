echo off
echo Setting up environment for Qt usage...
set PATH=C:\Qt\Qt5.6.2\5.6\mingw49_32\bin;C:/Qt/Qt5.6.2/Tools/mingw492_32\bin;%PATH%
rcc.exe -binary MtncMod.qrc -o ../../../../BIN/MtncMod.rcc