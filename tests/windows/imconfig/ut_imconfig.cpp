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
#include "window/immodel/imconfig.h"
class ut_imconfig : public ::testing::Test
{
protected:
    ut_imconfig()
    {
    }

    virtual ~ut_imconfig()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ut_imconfig, defualtIM)
{
    IMConfig imconfig;
    QString defaultIm = imconfig.defaultIM();
    imconfig.setDefaultIM(defaultIm);
}

TEST_F(ut_imconfig, IMSwitch)
{
    IMConfig imconfig;
    QString imSwitch = imconfig.IMSwitchKey();
    imconfig.setIMSwitchKey(imSwitch);
}

TEST_F(ut_imconfig, virtualKey)
{
    IMConfig imconfig;
    QString virtualKey = imconfig.virtualKey();
    imconfig.setVirtualKey(virtualKey);
}

TEST_F(ut_imconfig, defualtIMKey)
{
    IMConfig imconfig;
    QString defualtIMKey = imconfig.defaultIMKey();
    imconfig.setDefaultIMKey(defualtIMKey);
}
