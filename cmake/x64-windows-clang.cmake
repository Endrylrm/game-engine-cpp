set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)

# Force vcpkg to use the Clang-CL toolset from Visual Studio
set(VCPKG_PLATFORM_TOOLSET "ClangCL")