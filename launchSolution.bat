setlocal

call %~dp0\environment-prewire.bat 
start "" "%~dp0\Project\Shape detection.sln"

endlocal