/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     liuwenhao <liuwenhao@uniontech.com>
*
* Maintainer: liuwenhao <liuwenhao@uniontech.com>
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
#ifndef IMMODEL_H
#define IMMODEL_H

#include <QTimer>
#include <QMimeData>
#include <QStandardItemModel>
#include <DStandardItem>
#include <DStyle>
#include <DListView>
#include <fcitxqtinputmethoditem.h>
#include "publisherdef.h"
#include <QProcess>
#include <QThread>

const int IMchangedTime = 200; //输入法设置改变间隔
const int IMConTime = 5000; //输入法断开连接等待间隔
using namespace Dtk::Widget;

class TestIMModel;

class IMModel : public QStandardItemModel
{
    Q_OBJECT
public:
    friend TestIMModel;
    static IMModel *instance();
    static void deleteIMModel();
    //重载
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &index) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    //self
    void setEdit(bool flag); //设置编辑状态
    bool isEdit() { return m_isEdit; } //获取编辑状态
    void addIMItem(FcitxQtInputMethodItem item); //添加输入法
    const FcitxQtInputMethodItemList &availIMList() const;
signals:
    void sig_availIMList(FcitxQtInputMethodItemList);
public slots:
    void slot_updateIMList(); //更新输入法列表
private:
    explicit IMModel();
    IMModel(const IMModel &tmp) = delete;
    IMModel operator=(const IMModel &tmp) = delete;
    virtual ~IMModel() override;

    void loadItem(); //加载显示item
    void deleteItem(DStandardItem *item); //删除item
    void itemUp(DStandardItem *item); //item上移
    void itemDown(DStandardItem *item); //item下移
    void itemSawp(int index, int index2); //交换item
    void configShow(DStandardItem *item); //显示输入法设置界面
    void IMListSvae(); //保存输入法列表至fcitx
    void addActionList(DStandardItem *item); //添加action至item
private:
    static IMModel *m_ins;
    FcitxQtInputMethodItemList m_curIMList; //当前使用输入法
    FcitxQtInputMethodItemList m_availeIMList; //当前未使用输入法
    bool m_isEdit {false}; //编辑状态
    QTimer m_timer; //输入法修改定时器  当输入法界面作出修改后触发
    QTimer m_timer2; //输入法修改定时器  当输入法界面作出修改后触发
};

class TestIMModel
{
public:
    static void testUpdate()
    {
        auto func = [=] {
            for_int(1000)
            {
                qDebug() << i;
                QProcess::startDetached("fcitx -r");
                QThread::msleep(3000);
            }
        };

        std::thread t(func);
        t.detach();
    }

    static void testItemSwap()
    {
        for_int(1000)
        {
            IMModel *model = IMModel::instance();

            int a = model->m_curIMList.count();

            int b = rand() % a - 1;
            int c = rand() % b;
            qDebug() << i << a << b << c;
            if (b > 0 && c > 0)
                IMModel::instance()->itemSawp(c, b);
            QThread::msleep(800);
        }
    }

    static void testIMModel()
    {
        TestIMModel::testUpdate();
        //TestIMModel::testItemSwap();
    }
};

#endif // IMMODEL_H
