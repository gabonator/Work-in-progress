echo off
set sdk=C:/Programs/Devel/NaCl/nacl_sdk/pepper_46
set toolchain=%sdk%/toolchain/win_pnacl/bin
set inc1=%sdk%/include/pnacl 
set inc2=%sdk%/include
set lib=%sdk%/lib/pnacl/Release

set dest=build

echo   CLEAN
rmdir %dest% /s /q > nul 2> nul
mkdir %dest% > nul 2> nul

echo   CXX  pnacl/Release/graphics_2d.o 
call %toolchain%/pnacl-clang++ -o %dest%/graphics_2d.o -c graphics_2d.cc -g -O2 -pthread -MMD -DNDEBUG -Wno-long-long -Werror  -Wall -I%inc1% -I%inc2%

echo   LINK pnacl/Release/graphics_2d_unstripped.bc 
call %toolchain%/pnacl-clang++ -o %dest%/graphics_2d_unstripped.bc ./%dest%/graphics_2d.o -O2  -L%lib% -lppapi_cpp -lppapi 

echo   FINALIZE pnacl/Release/graphics_2d_unstripped.pexe 
call %toolchain%/pnacl-finalize -o %dest%/graphics_2d_unstripped.pexe %dest%/graphics_2d_unstripped.bc

echo   STRIP pnacl/Release/graphics_2d.pexe 
call %toolchain%/pnacl-strip %dest%/graphics_2d_unstripped.pexe -o %dest%/graphics_2d.pexe

echo   CREATE_NMF pnacl/Release/graphics_2d.nmf 
echo { "program": { "portable": { "pnacl-translate": { "url": "graphics_2d.pexe" } } } } > %dest%/graphics_2d.nmf

del %dest%\graphics_2d.d
del %dest%\graphics_2d.o
del %dest%\graphics_2d_unstripped.bc
del %dest%\graphics_2d_unstripped.pexe

copy index.html %dest%\ > nul