@echo off

rem projekt
set CHIP=12f683
set name=pokus
set VOLT=5.0

rem system
set compiler=C:\Programs\Devel\pic\PICC960\bin\picc.exe
set programmer=c:\Programs\Devel\pic\pickit\pk2cmd.exe

rem ===============================================
set CFLAGS=--chip=%CHIP% -P --opt=default,+asm,-speed,9 --warn=0 --double=24 -q -g --asmlist
set LFLAGS=--runtime=default,+clear,+init,-keep,+osccal,-download,-ramtest,-resetbits

setlocal ENABLEDELAYEDEXPANSION

rem %programmer% 
rem goto :eof
rem %programmer% /PPIC%chip% /T /A5.0
rem goto :eof

if not exist %compiler% (
  echo Neviem najst kompilator "%compiler%"
  goto err
)

if not exist %programmer% (
  echo Neviem najst programator "%programmer%"
  goto err
)

rem skompilujeme .c subory
set objs=
for %%f in (*.c) do (
  %compiler% %cflags% -c %%f
  if errorlevel 1 (
    echo.
    echo Nepodarilo sa skompilovat "%%f"
    goto err
  )
  set objs=!objs! %%f
)

rem zlinkujeme
%compiler% -o%name%.cof -m%name%.map %LFLAGS% %OBJS% %CFLAGS%
if errorlevel 1 (
  echo Nepodarilo sa zlinkovat
  goto err
)

rem napalime
if "%volt%"=="" (
  %programmer% /PPIC%chip% /F%name%.hex /M /T
) else (
  %programmer% /PPIC%chip% /F%name%.hex /M /T /A%volt%
)

if errorlevel 1 (
  echo Nepodarilo sa napalit
  goto err
)
     
:clean
rem clean
del *.obj *.p1 *.cof *.rlf *.sdb *.hxl *.sym *.map
del *.lst
goto :eof

:err
echo Failed.
rem clean
del *.obj *.p1 *.lst *.cof *.rlf *.sdb *.hxl *.sym *.map
goto :eof
