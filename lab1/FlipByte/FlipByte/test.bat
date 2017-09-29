set PROGRAM="%~1"

rem test with an empty list of arguments
%PROGRAM% > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '0' goto err
fc.exe "%TEMP%\output.txt" empty.txt
if %ERRORLEVEL% EQU '1' goto err

rem test with a lot of arguments
%PROGRAM% 6 7 8 9 10 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '0' goto err
fc.exe "%TEMP%\output.txt" tooMuch.txt
if %ERRORLEVEL% EQU '1' goto err

rem test with the lower boundary argument
%PROGRAM% 0 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '1' goto err
fc.exe "%TEMP%\output.txt" number0.txt
if %ERRORLEVEL% EQU '1' goto err

rem test with the upper boundary argument
%PROGRAM% 255 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '1' goto err
fc.exe "%TEMP%\output.txt" number255.txt
if %ERRORLEVEL% EQU '1' goto err

rem test with a negative argument value
%PROGRAM% -5 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '0' goto err
fc.exe "%TEMP%\output.txt" negativeNumber.txt
if %ERRORLEVEL% EQU '1' goto err

rem test with a argument exceeding the range
%PROGRAM% 123456789 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '0' goto err
fc.exe "%TEMP%\output.txt" number123456789.txt
if %ERRORLEVEL% EQU '1' goto err

rem test with a string in the argument
%PROGRAM% abcd > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '0' goto err
fc.exe "%TEMP%\output.txt" abcd.txt
if %ERRORLEVEL% EQU '1' goto err

rem test with the normal value of the argument
%PROGRAM% 6 > "%TEMP%\output.txt"
if %ERRORLEVEL% EQU '1' goto err
fc.exe "%TEMP%\output.txt" number6.txt
if %ERRORLEVEL% EQU '0' goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1