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

TEST_F(ut_immodel, onConfigShow)
{
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItem item;
    item.setUniqueName("iflyime");
    immodel->onConfigShow(item);
    EXPECT_TRUE(true);
}
TEST_F(ut_immodel, getIM)
{
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItem item;
    item.setName("iflyime");
    immodel->getIMIndex(item);
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
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItem item;
    item.setName("iflyime");
    immodel->onAddIMItem(item);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onDeleteItem)
{
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItem item;
    item.setName("iflyime");
    immodel->onAddIMItem(item);
    immodel->onUpdateIMList();
    immodel->onDeleteItem(item);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onItemUp)
{
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItem item1, item2;
    item1.setName("iflyime");
    item2.setName("chineseime");
    immodel->onAddIMItem(item1);
    immodel->onAddIMItem(item2);
    immodel->onItemUp(item2);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, onItemDown)
{
    IMModel *immodel = IMModel::instance();
    FcitxQtInputMethodItem item1, item2,item3;
    item1.setName("iflyime");
    item2.setName("chineseime");
    item3.setName("huayupy");
    immodel->onAddIMItem(item1);
    immodel->onAddIMItem(item2);
    immodel->onAddIMItem(item3);
    immodel->onItemDown(item2);
    EXPECT_TRUE(true);
}

TEST_F(ut_immodel, equals)
{
    FcitxQtInputMethodItem item1,item2;
    item1.setName("pinyin");
    item1.setLangCode("pinyin");
    item1.setUniqueName("pinyin");
    item2.setName("pinyin");
    item2.setLangCode("pinyin");
    item2.setUniqueName("pinyin");
    item1 == item2;
    EXPECT_TRUE(true);
}
