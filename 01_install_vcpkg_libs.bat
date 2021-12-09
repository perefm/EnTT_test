rmdir vcpkg /s /q
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
rem git checkout tags/2021.05.12
powershell "dir *.ps* -recurse | Set-AuthenticodeSignature -Certificate (dir cert:\currentuser\my -code)"
call bootstrap-vcpkg.bat
vcpkg install --recurse glm entt yaml-cpp --triplet x64-windows-static
cd..