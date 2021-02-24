rmdir EnTT_test_vs2019 /s /q
mkdir EnTT_test_vs2019
cd EnTT_test_vs2019
cmake.exe -DVCPKG_TARGET_TRIPLET=x64-windows-static -G "Visual Studio 16 2019" ..
cd..

pause