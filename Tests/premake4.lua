solution "Sapling Tests"
  configurations {"Test"}

  project "SaplingTests"
    kind "ConsoleApp"
    language "C++"
    files { "../**.h", "../**.cpp", "../**.hpp"}
    excludes {"../main.cpp"}
    links { "stdc++", "gtest", "Horde3D", "Horde3DUtils", "glfw", "jansson"}
    includedirs{"../", "/usr/local/include"}
    libdirs{"/usr/local/lib"}
    buildoptions{'-Wall'}
  configuration "Test"
    defines {"DEBUG"}
    flags {"Symbols"}
