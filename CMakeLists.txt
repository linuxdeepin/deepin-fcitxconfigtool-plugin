#cmake版本设置 
cmake_minimum_required(VERSION 3.7)
project(deepin-fcitxconfigtool-plugin)

set(DOTEST OFF)
#编译设置
if(DOTEST)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -fprofile-arcs -ftest-coverage -lgcov")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pthread -fprofile-arcs -ftest-coverage -lgcov")
      # Enable Qt builtin debug mode
      add_definitions("-DQT_MESSAGELOGCONTEXT -std=c++11")
    else()
      # -Wl, -O2 Enable linker optimizations
      # -Wl, --gc-sections Remove unused code resulting from -fdsta-sections and
      # -ffunction-sections
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -fprofile-arcs -ftest-coverage -lgcov -Wl,--gc-sections")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fprofile-arcs -ftest-coverage -lgcov -Wl,--gc-sections -pthread")
    endif()
else()
    if (CMAKE_BUILD_TYPE MATCHES Debug)
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pthread")
      # Enable Qt builtin debug mode
      add_definitions("-DQT_MESSAGELOGCONTEXT -std=c++11")
    else()
      # -Wl, -O2 Enable linker optimizations
      # -Wl, --gc-sections Remove unused code resulting from -fdsta-sections and
      # -ffunction-sections
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wl,--gc-sections")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wl,--gc-sections -pthread")
    endif()
endif()

#加载子目录
add_subdirectory(src)

#调用外部程序  生成qm文件
execute_process(COMMAND bash translate_generation.sh
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
