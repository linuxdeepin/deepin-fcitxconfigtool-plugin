#版本设置
set(VERSION 0.1)
#二进制名称
set(BIN_NAME deepin-fcitxconfigtool-plugin)
#项目名称设置
project(${BIN_NAME})

# 环境设置
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)#moc 预编译包含QObject文件，生成xx_moc.h cpp
set(CMAKE_AUTORCC ON)#开启rcc 编译资源文件qrc
set(CMAKE_AUTOUIC ON)#开启uic 编译转换*.ui文件生存设计界面对应的.h .cpp文件
set(CMAKE_CXX_STANDARD 14)

# 查找库
if(DOTEST)
    enable_testing()
    find_package(GTest REQUIRED)
    find_package(Qt5 COMPONENTS Test REQUIRED)
endif()
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
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Fcitx REQUIRED)
find_package(FcitxQt5DBusAddons REQUIRED)
find_package(FcitxQt5WidgetsAddons REQUIRED)

#设置资源目录 加载资源文件 翻译文件 源码
set(APP_RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../res")
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

FILE(GLOB_RECURSE HEAD_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ddeInterface/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fcitxInterface/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/window/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/i18n.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fcitxconfigplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fcitxqthelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/publisher/*.h)

FILE(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ddeInterface/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fcitxInterface/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/i18n.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fcitxconfigplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fcitxqthelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/publisher/*.cpp)

FILE(GLOB_RECURSE TEST_HEAD_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../unittest/*.h)

FILE(GLOB_RECURSE TEST_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../unittest/*.cpp)

set(ALL_SRCS
    ${HEAD_FILES}
    ${SOURCE_FILES}
    ${APP_QRC}
    ${DTNG_QM_FILES}
    )

set(TEST_SRCS
    ${TEST_HEAD_FILES}
    ${TEST_SOURCE_FILES}
    )

#add_library(${BIN_NAME}
#        MODULE
#        ${ALL_SRCS}
#        ${DTNG_QM_FILES}
#        )

if(DOTEST)
    add_executable(${PROJECT_NAME}_test
        ${ALL_SRCS}
        ${DTNG_QM_FILES}
        ${TEST_SRCS}
        )
else()
    add_executable(${PROJECT_NAME}
        ${ALL_SRCS}
        ${DTNG_QM_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )
endif()

if(DOTEST)
    target_include_directories(${PROJECT_NAME}_test PUBLIC
            ${DdeControlCenter_INCLUDE_DIR}
            ${DtkCore_INCLUDE_DIRS}
            ${DtkWidget_INCLUDE_DIRS}
            ${DFrameworkDBus_INCLUDE_DIRS}
            ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
            ${GTEST_INCLUDE_DIR}
            )
else()
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${DdeControlCenter_INCLUDE_DIR}
            ${DtkCore_INCLUDE_DIRS}
            ${DtkWidget_INCLUDE_DIRS}
            ${DFrameworkDBus_INCLUDE_DIRS}
            ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
            )
endif()

if(DOTEST)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE
            ${DdeControlCenter_LIBRARIES}
            ${DFrameworkDBus_LIBRARIES}
            ${DtkWidget_LIBRARIES}
            ${Qt5Widgets_LIBRARIES}
            ${Qt5DBus_LIBRARIES}
            ${Qt5Concurrent_LIBRARIES}
            ${OBJECT_BINARY_DIR}
            ${FCITX4_FCITX_UTILS_LIBRARIES}
            ${FCITX4_FCITX_CONFIG_LIBRARIES}
            ${FCITX4_FCITX_LIBRARIES}
            FcitxQt5::WidgetsAddons
            FcitxQt5::DBusAddons
            ${Qt5Test_LIBRARIES}
            ${GTEST_LIBRARIES}
            )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
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
endif()

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

# 设置执行 make install 时哪个目标应该被 install 到哪个位置
#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION /lib/${PROJECT_NAME}/modules)

# 安装 .qm 文件
install(FILES ${DTNG_QM_FILES} DESTINATION share/${PROJECT_NAME}/translations)

if(DOTEST)
#------------------------------ 创建'make test'指令---------------------------------------
add_custom_target(test
    COMMAND mkdir -p coverageResult
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})


add_custom_command(TARGET test
    COMMAND echo " =================== CREAT LCOV REPROT BEGIN ==================== "

    #1.清理原先的gcov信息
    COMMAND lcov --directory ./CMakeFiles/${PROJECT_NAME}_test.dir --zerocounters
    COMMAND lcov --directory ./CMakeFiles/${PROJECT_NAME}.dir --zerocounters
    COMMAND ./src/${PROJECT_NAME}_test

    #2.收集gcov信息到.info文件中
    COMMAND lcov --directory . --capture --output-file ./coverageResult/${PROJECT_NAME}_Coverage.info

    #3.过滤一些我们不感兴趣的文件的覆盖率信息
    COMMAND echo " =================== do filter begin ==================== "
    COMMAND lcov --remove ./coverageResult/${PROJECT_NAME}_Coverage.info
    '*/${PROJECT_NAME}_test_autogen/*' '*/${PROJECT_NAME}_autogen/*' '*/usr/include/*' '*/tests/*' '*/googletest/*'
    -o ./coverageResult/${PROJECT_NAME}_Coverage.info
    COMMAND echo " =================== do filter end ==================== "

    #3.将.info信息生成报告到reprot文件夹中
    COMMAND genhtml -o ./coverageResult/report ./coverageResult/${PROJECT_NAME}_Coverage.info

    COMMAND echo " =================== CREAT LCOV REPROT END ==================== "

    COMMAND echo " Coverage files have been output to ${CMAKE_BINARY_DIR}/coverageResult/report "

    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

#'make test'命令依赖与我们的测试程序
    add_dependencies(test ${PROJECT_NAME}_test)
endif()
