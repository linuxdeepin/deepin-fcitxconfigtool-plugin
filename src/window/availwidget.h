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
#ifndef AVAILWIDGET_H
#define AVAILWIDGET_H

#include "widgets/settingsgroup.h"
#include "widgets/imsettingsitem.h"
#include <QWidget>

using namespace dcc::widgets;

class AvailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AvailWidget(QWidget *parent = nullptr);
    ~AvailWidget();
    void clearItemStatus(); //清除item选中状态
    const FcitxQtInputMethodItem &getSeleteIm() const { return m_selectItem; } //获取选中item
signals:
    void seleteIM(bool); //选中状态信号 true 选中 false 未选中
public slots:
    void onSearchIM(const QString &str); //搜索输入法
    void onUpdateUI(FcitxQtInputMethodItemList); //更新界面
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void initUI(); //初始化界面
    void initConnect(); //初始化信号槽
    void cleareItemStatusAndFilter(SettingsGroup *group, bool falg = false); //清除选中 清除过滤
private:
    SettingsGroup *m_allIMGroup {nullptr}; //可用输入法列表界面
    SettingsGroup *m_searchIMGroup {nullptr}; //搜索输入法列表界面
    FcitxQtInputMethodItem m_selectItem; //选中输入法
    FcitxQtInputMethodItemList m_allAvaiIMlList; //可用输入法列表
    QString m_searchStr; //当前搜索字符串
};

#endif // AVAILWIDGET_H
