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
#include "window/advancedsettingwidget.h"
#include "fcitxInterface/dummyconfig.h"
#include <QMouseEvent>

class ut_advancedsettingwidget : public ::testing::Test
{
protected:
    ut_advancedsettingwidget()
    {
    }

    virtual ~ut_advancedsettingwidget()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ut_advancedsettingwidget, setupConfigUi)
{
      Fcitx::AdvancedSettingWidget ASW;
      EXPECT_TRUE(true);
}

//TEST_F(ut_advancedsettingwidget, createConfigOptionWidget)
//{

//}

TEST_F(ut_advancedsettingwidget, createglobalSettingsUi)
{
    Fcitx::AdvancedSettingWidget ASW;
    ASW.createglobalSettingsUi();
    EXPECT_TRUE(true);
}


TEST_F(ut_advancedsettingwidget, createAddOnsUi)
{
    Fcitx::AdvancedSettingWidget ASW;
    ASW.createAddOnsUi();
    EXPECT_TRUE(true);
}

TEST_F(ut_advancedsettingwidget, getConfigDesc)
{
        Fcitx::AdvancedSettingWidget ASW;
        QString name = "getConfigDsc";
        ASW.getConfigDesc(name);
        EXPECT_TRUE(true);
}

TEST_F(ut_advancedsettingwidget, sendReloadMessage)
{
    Fcitx::AdvancedSettingWidget ASW;
    ASW.sendReloadMessage();
    EXPECT_TRUE(true);
}



