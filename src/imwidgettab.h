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

#ifndef IM_WIDGET_TAB_H
#define IM_WIDGET_TAB_H

#include <QLabel>

#include "dtkwidget_global.h"
#include "imlistmodel.h"
#include "addimwidget.h"
#include <fcitxqtinputmethoditem.h>

#include <DPushButton>
#include <DListView>

DWIDGET_USE_NAMESPACE

/**
 * @class ImWidgetTab
 * @brief
 */

class ImWidgetTab : public QLabel
{
    Q_OBJECT
public:
    explicit ImWidgetTab(QWidget *parent = nullptr);
    ~ImWidgetTab();

signals:
    void updateIMList(const FcitxQtInputMethodItemList &list, const QString &selection);

private:
    void initUI();
    void initSubUI();
    void initConnect();

private slots:
    void fcitxUpdateIMList();

    void fcitxImWidgetAddimButtonClicked();
    void fcitxImWidgetDelimButtonClicked();
    void fcitxImWidgetMoveupButtonClicked();
    void fcitxImWidgetMovedownButtonClicked();
    void fcitxImWidgetConfigureButtonClicked();
    void fcitxImWidgetDefaultLayoutButtonClicked();
    void fcitxImWidgetRowActivated();

private:
    DPushButton *addimbutton = nullptr;
    DPushButton *delimbutton = nullptr;
    DPushButton *moveupbutton = nullptr;
    DPushButton *movedownbutton = nullptr;
    DPushButton *configurebutton = nullptr;
    DPushButton *defaultlayoutbutton = nullptr;

    DListView *listView = nullptr;
    IMListModel  *imListModel = nullptr;

    AddImWidget *addImWidget = nullptr;

    FcitxQtInputMethodItemList imItemList ;
};



#endif // BUTTONTAB_H
