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
#include "window/settingsdef.h"
#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include "window/gsettingwatcher.h"

class ut_gsettingwatcher : public ::testing::Test
{
protected:
    ut_gsettingwatcher()
    {
    }

    virtual ~ut_gsettingwatcher()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ut_gsettingwatcher, bind)
{
    GSettingWatcher *gSettingWatcher = GSettingWatcher::instance();

    QString gsettingsName = GSETTINGS_ADD_IM;
    QWidget widget;

    QListView qlistview;
    QStandardItem qstandarditem;

    gSettingWatcher->bind(gsettingsName, &widget);
    gSettingWatcher->bind(gsettingsName,&qlistview, &qstandarditem);
}

TEST_F(ut_gsettingwatcher, erase)
{
    GSettingWatcher *gSettingWatcher = GSettingWatcher::instance();
    QString gsettingsName = GSETTINGS_ADD_IM;
    QWidget widget;
    gSettingWatcher->erase(gsettingsName);
    gSettingWatcher->erase(gsettingsName, &widget);
}

TEST_F(ut_gsettingwatcher, insertState)
{
    GSettingWatcher *gSettingWatcher = GSettingWatcher::instance();
    QString key = GSETTINGS_ADD_IM;
    gSettingWatcher->insertState(key);
}

TEST_F(ut_gsettingwatcher, setStatus)
{
    GSettingWatcher *gSettingWatcher = GSettingWatcher::instance();

    QString gsettingsName = GSETTINGS_ADD_IM;
    QWidget widget;

    QListView qlistview;
    QStandardItem qstandarditem;

    gSettingWatcher->setStatus(gsettingsName, &widget);
    gSettingWatcher->setStatus(gsettingsName,&qlistview, &qstandarditem);
}

TEST_F(ut_gsettingwatcher, getStatus)
{
    GSettingWatcher *gSettingWatcher = GSettingWatcher::instance();
    QString key = GSETTINGS_ADD_IM;
    gSettingWatcher->getStatus(key);
}

TEST_F(ut_gsettingwatcher, getMenuState)
{
    GSettingWatcher *gSettingWatcher = GSettingWatcher::instance();
    gSettingWatcher->getMenuState();
}


TEST_F(ut_gsettingwatcher, onStatusModeChanged)
{
    GSettingWatcher *gSettingWatcher = GSettingWatcher::instance();
    QString key = GSETTINGS_ADD_IM;
    gSettingWatcher->onStatusModeChanged(key);
}







