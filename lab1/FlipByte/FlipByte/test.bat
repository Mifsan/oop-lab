set PROGRAM="%~1"

rem blah
%PROGRAM% > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 0 goto err
fc.exe "%TEMP%\output.txt" empty.txt
if %ERRORLEVEL% EQU 1 goto err

rem blah
%PROGRAM% 6 7 8 9 10 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 0 goto err
fc.exe "%TEMP%\output.txt" tooMuch.txt
if %ERRORLEVEL% EQU 1 goto err

rem blah
%PROGRAM% 0 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 1 goto err
fc.exe "%TEMP%\output.txt" number0.txt
if %ERRORLEVEL% EQU 1 goto err

rem blah
%PROGRAM% 255 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 1 goto err
fc.exe "%TEMP%\output.txt" number255.txt
if %ERRORLEVEL% EQU 1 goto err

rem blah
%PROGRAM% -5 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 0 goto err
fc.exe "%TEMP%\output.txt" negativeNumber.txt
if %ERRORLEVEL% EQU 1 goto err

rem blah
%PROGRAM% 123456789 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 0 goto err
fc.exe "%TEMP%\output.txt" number123456789.txt
if %ERRORLEVEL% EQU 1 goto err

rem blah
%PROGRAM% abcd > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 0 goto err
fc.exe "%TEMP%\output.txt" abcd.txt
if %ERRORLEVEL% EQU 1 goto err

rem blah
%PROGRAM% 6 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU 1 goto err
fc.exe "%TEMP%\output.txt" number6.txt
if %ERRORLEVEL% EQU 0 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1