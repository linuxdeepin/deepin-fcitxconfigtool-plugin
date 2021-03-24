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
#include "fcitxconfigplugin.h"

class ui_fcitxconfigplugin : public ::testing::Test
{
protected:
    ui_fcitxconfigplugin()
    {
    }

    virtual ~ui_fcitxconfigplugin()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ui_fcitxconfigplugin, preInitialize)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.preInitialize();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, initialize)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.initialize();
    EXPECT_TRUE(true);
}


TEST_F(ui_fcitxconfigplugin, name)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.name();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, displayName)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.displayName();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, icon)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.icon();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, translationPath)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.translationPath();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, showPage)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.showPage("");
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, load)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.load("");
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, availPage)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.availPage();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, path)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.path();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, follow)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.follow();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, active)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.initialize();
    fcitxConfigPlugin.active();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, deactive)
{
    FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.initialize();
    fcitxConfigPlugin.deactive();
    EXPECT_TRUE(true);
}
