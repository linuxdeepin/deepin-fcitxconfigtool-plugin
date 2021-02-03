#版本设置
set(VERSION 0.1)
#项目名称设置
project(deepin-fcitxconfigtool-plugin)
#二进制名称
set(BIN_NAME deepin-fcitxconfigtool-plugin)
# 环境设置
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)#moc 预编译包含QObject文件，生成xx_moc.h cpp
set(CMAKE_AUTORCC ON)#开启rcc 编译资源文件qrc
set(CMAKE_AUTOUIC ON)#开启uic 编译转换*.ui文件生存设计界面对应的.h .cpp文件
set(CMAKE_CXX_STANDARD 14)

# 查找库
find_package(PkgConfig REQUIRED)
find_package(DtkWidget REQUIRED)
find_package(DtkGui REQUIRED)
find_package(DtkCore REQUIRED)
find_package(DtkCMake REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS DBus REQUIRED)
find_package(Qt5 COMPONENTS LinguistTools REQUIRED)
find_package(Qt5 COMPONENTS Concurrent REQUIRED)
find_package(Qt5Widgets REQUIRED)
FIND_PACKAGE(Fcitx REQUIRED)
FIND_PACKAGE(FcitxQt5DBusAddons REQUIRED)
FIND_PACKAGE(FcitxQt5WidgetsAddons REQUIRED)


#设置资源目录 加载资源文件 翻译文件 源码
set(APP_RES_DIR "../res")
set(APP_QRC "${APP_RES_DIR}/fcitxconfig.qrc")
#创建翻译文件 
set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../translations")
set(TS_FILES "${TS_DIR}/${PROJECT_NAME}_en_US.ts")
#更新翻译
find_program(LUPDATE_EXECUTABLE lupdate)
foreach(_ts_file ${TS_FILES})
    execute_process(
        COMMAND ${LUPDATE_EXECUTABLE} -recursive ${CMAKE_SOURCE_DIR} -ts ${_ts_file})  #递归扫描源码 输出ts文件
endforeach()

#创建qm文件
file (GLOB DTNG_TS_FILES ${TS_DIR}/*.ts)
qt5_create_translation(DTNG_QM_FILES
     ${DTNG_TS_FILES}
     ${DTNG_QM_FILES})

FILE(GLOB_RECURSE HEAD_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
FILE(GLOB_RECURSE SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(ALL_SRCS
    ${HEAD_FILES}
    ${SOURCE_FILES}
    ${APP_QRC}
    ${DTNG_QM_FILES})

add_executable(${BIN_NAME} ${ALL_SRCS})

#add_library(${BIN_NAME}
#        MODULE
#        ${ALL_SRCS}
#        ${DTNG_QM_FILES}
#        )

target_include_directories(${BIN_NAME} PUBLIC
        ${DdeControlCenter_INCLUDE_DIR}
        ${DtkWidget_INCLUDE_DIRS}
        ${DFrameworkDBus_INCLUDE_DIRS}
        ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
        )

target_link_libraries(${BIN_NAME} PRIVATE
        ${DdeControlCenter_LIBRARIES}
        ${DFrameworkDBus_LIBRARIES}
        ${DtkWidget_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5DBus_LIBRARIES}
        ${Qt5Concurrent_LIBRARIES}
        ${DtkCore_INCLUDE_DIRS}
        ${OBJECT_BINARY_DIR}
        ${FCITX4_FCITX_UTILS_LIBRARIES}
        ${FCITX4_FCITX_CONFIG_LIBRARIES}
        ${FCITX4_FCITX_LIBRARIES}
        FcitxQt5::WidgetsAddons
        FcitxQt5::DBusAddons
        )


# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

# 设置执行 make install 时哪个目标应该被 install 到哪个位置
#install(TARGETS ${BIN_NAME} LIBRARY DESTINATION /lib/${PROJECT_NAME}/modules)

# 安装 .qm 文件
install(FILES ${DTNG_QM_FILES} DESTINATION share/${PROJECT_NAME}/translations)
