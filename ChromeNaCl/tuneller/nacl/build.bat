echo off
setlocal enabledelayedexpansion

set sdk=C:/Programs/Devel/NaCl/nacl_sdk/pepper_46
set toolchain=%sdk%/toolchain/win_pnacl/bin

rem set sdk=C:/Programs/Devel/NaCl/pepper_25
rem set toolchain=%sdk%/toolchain/win_x86_pnacl/host_x86_32/bin

set inc1=%sdk%/include/pnacl 
set inc2=%sdk%/include
set lib=%sdk%/lib/pnacl/Release
set dest=build
set program=tuneller

rmdir %dest% /s /q > nul 2> nul
mkdir %dest% > nul 2> nul

set dest=build
set objects=
for %%f in (*.cc, *.cpp) do (
  echo   CXX  %%f %%~nf.o
  call %toolchain%/pnacl-clang++ -o %dest%/%%~nf.o -c %%f -g -O2 -pthread -MMD -DNDEBUG -Wno-long-long -Werror  -Wall -I%inc1% -I%inc2%
  set objects=!objects! %dest%/%%~nf.o
)

for /R ../source %%f in (*.cc, *.cpp) do (
  echo   CXX  %%f %%~nf.o
  call %toolchain%/pnacl-clang++ -o %dest%/%%~nf.o -c %%f -g -O2 -pthread -MMD -DNDEBUG -Wno-long-long -Werror  -Wall -I%inc1% -I%inc2%
  set objects=!objects! %dest%/%%~nf.o
)


rem echo   CXX  pnacl/Release/%program%.o 
rem call %toolchain%/pnacl-clang++ -o %dest%/%program%.o -c %program%.cc -g -O2 -pthread -MMD -DNDEBUG -Wno-long-long -Werror  -Wall -I%inc1% -I%inc2%

echo   LINK pnacl/Release/%program%_unstripped.bc 
call %toolchain%/pnacl-clang++ -o %dest%/%program%_unstripped.bc !objects! -O2  -L%lib% -lppapi_cpp -lppapi 

echo   FINALIZE pnacl/Release/%program%_unstripped.pexe 
call %toolchain%/pnacl-finalize -o %dest%/%program%_unstripped.pexe %dest%/%program%_unstripped.bc

echo   STRIP pnacl/Release/%program%.pexe 
call %toolchain%/pnacl-strip %dest%/%program%_unstripped.pexe -o %dest%/%program%.pexe

echo   CREATE_NMF pnacl/Release/%program%.nmf 
echo { "program": { "portable": { "pnacl-translate": { "url": "%program%.pexe" } } } } > %dest%/%program%.nmf

del %dest%\*.d
del %dest%\*.o
del %dest%\*.bc
del %dest%\%program%_unstripped.pexe

copy index.html %dest%\ > nul
copy screenshot.jpg %dest%\ > nul