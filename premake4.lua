solution "Sapling"
   configurations { "Debug", "Release" }
   postbuildcommands {"LD_LIBRARY_PATH=."} 
   project "Sapling"
      kind "SharedLib"
      language "C++"
      targetdir 'lib' 
      files { "*.hpp", "*.cpp" , "*.h", "Systems/*", "Components/*", "Wrappers/*.h","Wrappers/*.cpp"}
      links{'glfw','Horde3D', 'Horde3DUtils', "jansson"}
      includedirs{"."} 
      if os.is('linux') then --Try to find horde3d and glfw
        libdirs{'/usr/local/lib'}
        includedirs{'/usr/local/include/'}
      end
      buildoptions{"-Wall"} 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

  project "Samples"
    kind "ConsoleApp"
    language "C++"
      files { "Samples/*.h", "Samples/*.cpp"}
      links{"Sapling", 'glfw','Horde3D', 'Horde3DUtils', "jansson"}
      includedirs{"."} 
      if os.is('linux') then --Try to find horde3d and glfw
        libdirs{'/usr/local/lib'}
        includedirs{'/usr/local/include/'}
      end
      buildoptions{"-Wall"} 
      targetdir "Samples"
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }


  project "Tests"
    kind "ConsoleApp"
    language "C++"
      files { "Tests/*.h", "Tests/*.cpp"}
      links{"Sapling", 'glfw','Horde3D', 'Horde3DUtils', "jansson", "gtest", "stdc++"}
      includedirs{"."} 
      if os.is('linux') then --Try to find horde3d and glfw
        libdirs{'/usr/local/lib'}
        includedirs{'/usr/local/include/'}
      end
      buildoptions{"-Wall"} 
      targetdir "Tests"
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
