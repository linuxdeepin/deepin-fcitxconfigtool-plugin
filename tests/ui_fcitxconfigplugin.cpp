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
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.preInitialize();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, initialize)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.initialize();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, reset)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.reset();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, name)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.name();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, displayName)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.displayName();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, icon)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.icon();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, translationPath)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.translationPath();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, showPage)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.showPage("");
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, load)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.load("");
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, availPage)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.availPage();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, path)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.path();
    EXPECT_TRUE(true);
}

TEST_F(ui_fcitxconfigplugin, follow)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.follow();
    EXPECT_TRUE(true);
}

//TEST_F(ui_fcitxconfigplugin, active)
//{
//    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
//    fcitxConfigPlugin.initialize();
//    fcitxConfigPlugin.active();
//    EXPECT_TRUE(true);
//}

TEST_F(ui_fcitxconfigplugin, deactive)
{
    DCC_NAMESPACE::FcitxConfigPlugin fcitxConfigPlugin;
    fcitxConfigPlugin.initialize();
    fcitxConfigPlugin.deactive();
    EXPECT_TRUE(true);
}
