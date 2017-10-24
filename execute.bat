setlocal

call "%~dp0\environment-prewire.bat"

set PROJECT_exe="%~dp0shape-detection\x64\Debug\Shape detection.exe"
set IMAGES_dir=%~dp0shape-detection\Images

%PROJECT_exe% "%IMAGES_dir%\circle.png"
%PROJECT_exe% "%IMAGES_dir%\square1.png"
%PROJECT_exe% "%IMAGES_dir%\square2.png"
%PROJECT_exe% "%IMAGES_dir%\square3.png"

endlocal
