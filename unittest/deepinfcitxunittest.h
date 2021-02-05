/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     chenshijie <chenshijie@uniontech.com>
*
* Maintainer: chenshijie <chenshijie@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DEEPINFCITX_UNIT_TEST_H
#define DEEPINFCITX_UNIT_TEST_H
#include <QObject>
#include <gtest/gtest.h>

class DeepinFcitxUnitTest : public QObject
    , public ::testing::Test
{
    Q_OBJECT

public:
    DeepinFcitxUnitTest() {}
    virtual ~DeepinFcitxUnitTest() {}
};

#endif // DEEPINFCITX_UNIT_TEST_H
