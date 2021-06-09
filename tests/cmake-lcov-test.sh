#!/bin/bash
export DISPLAY=:0.0
utdir=build-ut
rm -r $utdir
rm -r ../$utdir
mkdir ../$utdir
cd ../$utdir

cmake .. -DCMAKE_INSTALL_PREFIX="/usr"
make -j4

touch ./tests/utcase.log
./tests/deepin-fcitxconfigtool-plugin_test --gtest_output=xml:./report.txt 

workdir=$(cd ../$(dirname $0)/$utdir; pwd)

mkdir -p report

lcov -d $workdir -c -o ./report/coverage.info

lcov --extract ./report/coverage.info '*/src/*' -o ./report/coverage.info

lcov --remove ./report/coverage.info '*/tests/*' '*/src/ddeInterface/*' '*/src/fcitxInterface/*' '*/src/widgets/*' '*/src/widgets/labels/*' '*fcitxconfigplugin*' -o ./report/coverage.info

genhtml -o ./report ./report/coverage.info

exit 0
