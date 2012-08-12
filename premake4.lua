solution "Sapling"
   configurations { "Debug", "Release" }
   postbuildcommands {"LD_LIBRARY_PATH=lib/"} 
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
      buildoptions{"-std=c++11 -Wall"} 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

  project "Samples"
    kind "ConsoleApp"
    language "C++"
      files { "Samples/demo/*.h", "Samples/demo/*.cpp"}
      links{"Sapling", 'glfw','Horde3D', 'Horde3DUtils', "jansson"}
      includedirs{"."} 
      if os.is('linux') then --Try to find horde3d and glfw
        libdirs{'/usr/local/lib'}
        includedirs{'/usr/local/include/'}
      end
      buildoptions{"-std=c++11 -Wall"} 
      targetdir "Samples/demo"
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

