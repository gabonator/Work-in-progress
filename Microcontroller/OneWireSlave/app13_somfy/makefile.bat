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
rem del *.lst
goto :eof

:err
echo Failed.
rem clean
del *.obj *.p1 *.lst *.cof *.rlf *.sdb *.hxl *.sym *.map
goto :eof


# microchip pic in visual studio makefile
# 
# gabonator@inmail.sk
#
#
CHIP=16F887
COMPILER=C:\Programs\Devel\PICC\9.60\bin\picc.exe
CFLAGS=--chip=$(CHIP) -P --opt=default,+asm,-speed,9 --warn=0 --double=24 -q -g --asmlist $(FMTWARNING) $(FMTADVISORY) $(FMTERROR)
LFLAGS=--runtime=default,+clear,+init,-keep,+osccal,-download,-ramtest,-resetbits
FMTERROR="--errformat=%f(%l) : error [%n] %%s %l.%c" 
FMTADVISORY="--msgformat=Advisory[%n] %%s" 
FMTWARNING="--warnformat=%f(%l) : warning [%n] %%s %l.%c" 
NAME=pictest

OBJS=maly.c delay.c

.c.obj::
	$(COMPILER) $(CFLAGS) -c $<

all: 	test.hex

cleansub:
	del *.p1 *.lst *.cof *.sdb *.hxl *.sym *.map *.i
clean: 
	del *.obj *.p1 *.lst *.cof *.hex *.rlf *.sdb *.hxl *.sym

build: $(OBJS)
link:
	$(COMPILER) -otest.cof -mtest.map $(LFLAGS) $(OBJS) $(CFLAGS)

test.hex: build link

run:	program on

program:
	PK2CMD /PPIC$(CHIP) /Ftest.hex /M
on:
	PK2CMD /PPIC$(CHIP) /T /A$(VOLT)
off:
	PK2CMD /PPIC$(CHIP) /W


