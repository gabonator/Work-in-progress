@echo off

"C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\devenv" tunwin32.vcxproj /build "Debug|Win32" /project tunwin32
del /ah *.suo
del *.sdf
del *.user

rmdir ipch /s /q
attrib +r debug\tunwin32.exe
del debug\*.* /q
attrib -r debug\tunwin32.exe
