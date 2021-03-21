rmdir vcpkg /s /q
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
rem update to Mar 19th: https://github.com/microsoft/vcpkg/commit/9986c28da97f316fe3c79be0538af8f46a200796
git checkout 9986c28da97f316fe3c79be0538af8f46a200796
powershell "dir *.ps* -recurse | Set-AuthenticodeSignature -Certificate (dir cert:\currentuser\my -code)"
call bootstrap-vcpkg.bat
rem vcpkg integrate install
vcpkg install --recurse glm entt yaml-cpp --triplet x64-windows-static
cd..