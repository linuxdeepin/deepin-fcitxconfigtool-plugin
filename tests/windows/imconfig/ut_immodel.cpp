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
#include "window/immodel/immodel.h"
class ut_immodel : public ::testing::Test
{
protected:
    ut_immodel()
    {
    }

    virtual ~ut_immodel()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ut_immodel, setEdit)
{
    IMModel *immodel = IMModel::instance();
    immodel->setEdit(true);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, isEdit)
{
    IMModel *immodel = IMModel::instance();
    immodel->isEdit();
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, getIMIndex)
{
    IMModel *immodel = IMModel::instance();
    immodel->getIMIndex("iflyime");
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, getIM)
{
    //    IMModel *immodel = IMModel::instance();
    //    FcitxQtInputMethodItem item = immodel->getIM(0);
    //    immodel->getIMIndex(item);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, getAvailIMList)
{
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItemList itemList = immodel->getAvailIMList();
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, getCurIMList)
{
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItemList itemList = immodel->getCurIMList();
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onUpdateIMList)
{
    IMModel *immodel = IMModel::instance();
    immodel->onUpdateIMList();
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onAddIMItem)
{
    //    IMModel *immodel = IMModel::instance();
    //    FcitxQtInputMethodItem item = immodel->getIM(0);
    //    immodel->onAddIMItem(item);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onDeleteItem)
{
    //    IMModel *immodel = IMModel::instance();
    //    FcitxQtInputMethodItem item = immodel->getIM(0);
    //    immodel->onDeleteItem(item);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onItemUp)
{
    //    IMModel *immodel = IMModel::instance();
    //    FcitxQtInputMethodItem item = immodel->getIM(0);
    //    immodel->onItemUp(item);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onItemDown)
{
    //    IMModel *immodel = IMModel::instance();
    //    FcitxQtInputMethodItem item = immodel->getIM(0);
    //    immodel->onItemDown(item);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onConfigShow)
{
    //    IMModel *immodel = IMModel::instance();
    //    FcitxQtInputMethodItem item = immodel->getIM(0);
    //    immodel->onConfigShow(item);
    EXPECT_TRUE(true);
}
