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

#include <iostream>
#include "gtest/gtest.h"
#include "window/availwidget.h"
class ut_availwidget : public ::testing::Test
{
protected:
    ut_availwidget()
    {
    }

    virtual ~ut_availwidget()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ut_availwidget, clearItemStatus)
{
    AvailWidget availWidget;
    availWidget.clearItemStatus();
    EXPECT_TRUE(true);
}

TEST_F(ut_availwidget, getSeleteIm)
{
    AvailWidget availWidget;
    FcitxQtInputMethodItem value = availWidget.getSeleteIm();
}

TEST_F(ut_availwidget, onSearchIM)
{
    AvailWidget availWidget;
    availWidget.onSearchIM("fcitx-pinyin");
}

TEST_F(ut_availwidget, onUpdateUI)
{
    AvailWidget availWidget;
    FcitxQtInputMethodItemList newItemList;
    availWidget.onUpdateUI(newItemList);
}
