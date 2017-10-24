setlocal

call "%~dp0\environment-prewire.bat"

set PROJECT_exe="Project\x64\Debug\Shape detection.exe"

%PROJECT_exe% Images\circle.png
%PROJECT_exe% Images\square1.png
%PROJECT_exe% Images\square2.png
%PROJECT_exe% Images\square3.png

endlocal
