#cmake版本设置 
cmake_minimum_required(VERSION 3.7)
#工程名称设置
project(deepin-fcitxconfigtool-plugin)

#编译设置
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
  # Enable Qt builtin debug mode
  add_definitions("-DQT_MESSAGELOGCONTEXT")
else()
  # -Wl, -O2 Enable linker optimizations
  # -Wl, --gc-sections Remove unused code resulting from -fdsta-sections and
  # -ffunction-sections
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -Wl,--gc-sections")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wl,--gc-sections")
endif()

#加载子目录
add_subdirectory(src)

#调用外部程序  生成qm文件
execute_process(COMMAND bash "translate_generation.sh"
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
