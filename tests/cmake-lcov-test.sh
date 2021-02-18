#!/bin/bash
workspace=$1

cd $workspace

dpkg-buildpackage -b -d -uc -us

project_path=$(cd `dirname $0`; pwd)

cd "${project_path}/obj-"*"-linux-gnu"

make test

#获取工程名

project_name="${project_path##*/}"

#获取打包生成文件夹路径
pathname=$(find . -name obj*)

test_path="$(cd `dirname $0`; pwd)/tests"

cd $project_path/../

sudo dpkg -i deepin-fcitxconfigtool-plugin*.deb

echo $test_path

echo ${DISPLAY}

export DISPLAY=':0.0'

cd $test_path

./deepin-fcitxconfigtool-plugin_test

mkdir -p coverage

lcov -d ../ -c -o ./coverage/coverage.info

lcov --extract ./coverage/coverage.info '*/src/*' -o ./coverage/coverage.info

lcov --remove ./coverage/coverage.info '*/tests/*' -o ./coverage/coverage.info

mkdir ../report

genhtml -o ../report ./coverage/coverage.info

exit 0
