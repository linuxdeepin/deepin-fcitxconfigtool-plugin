/*****************************************************************************
*
* Copyright (C) 2020 Union Technology Co., Ltd.
*
* Author: Chen Shijie <chenshijie@uniontech.com>
*
* Maintainer:
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
*
*****************************************************************************/

#ifndef ADDIMWIDGET_H
#define ADDIMWIDGET_H

#include "addimlistmodel.h"

#include <fcitxqtinputmethoditem.h>

#include "dtkwidget_global.h"
#include <DWidget>
#include <DSearchEdit>
#include <DListView>
DWIDGET_USE_NAMESPACE

class AddImWidget : public DWidget
{
    Q_OBJECT

public:
    explicit AddImWidget(QWidget *parent = nullptr);
    ~AddImWidget();

signals:
    /// \brief addIm
    /// add selected im
    void addIm(QModelIndex item);
    void updateIMList(const FcitxQtInputMethodItemList &list, const QString &selection);

private:
    void initUI();
    void initConnect();

public slots:
    void filterAddIMList();

private slots:
    void onCloseBt();
    void onSureBt();
    void onTextChanged(const QString &str);

private:
    DListView *listview;
    AddIMListModel  *addimListModel = nullptr;
    bool curImputLan = true;
    DCheckBox *checkBox;
    DPushButton *ptCancel;
    DPushButton *ptSure;
    DSearchEdit *searchEdit;
    FcitxQtInputMethodItemList ImItemList ;
};

#endif // AddImWidget_H
