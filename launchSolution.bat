setlocal

call %~dp0\environment-prewire.bat 
start "" "%~dp0\shape-detection\Shape detection.sln"

endlocal