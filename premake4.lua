solution "Sapling"
   configurations { "Debug", "Release" }
 
   project "Sapling"
      kind "ConsoleApp"
      language "C++"
      files { "*.hpp", "*.cpp" , "*.h", "Systems/*", "Components/*", "Wrappers/*.h","Wrappers/*.cpp"}
      links{'glfw','Horde3D', 'Horde3DUtils', "jansson"}
      includedirs{"."} 
      if os.is('linux') then --Try to find horde3d and glfw
        libdirs{'/usr/local/lib'}
        includedirs{'/usr/local/include/'}
      end
      
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }    
