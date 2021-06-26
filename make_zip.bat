copy src\mc-mass.ico mc-mass.ico

call %QTDIR%/bin/qtenv2.bat

cd /D "%~dp0"

echo %cd%

rmdir /S /Q mc-mass

mkdir mc-mass
mkdir mc-mass\bin
mkdir mc-mass\data
copy /y bin\*.exe mc-mass\bin
xcopy data mc-mass\data /E
copy "%QTDIR%\bin\Qt5OpenGL.dll" mc-mass\bin

rem cd qt\bin
rem call "%QTDIR%\bin\windeployqt.exe" --release mscsim.exe
rem cd ..\..
call "%QTDIR%\bin\windeployqt.exe" --release mc-mass\bin\mc-mass.exe

"C:\Program Files\7-Zip\7z.exe" a mc-mass_0.2_win64.zip -r mc-mass\

pause
