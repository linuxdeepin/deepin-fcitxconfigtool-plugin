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
#ifndef IMSETTINGWINDOW_H
#define IMSETTINGWINDOW_H

#include "widgets/comboxwidget.h"
#include "widgets/switchwidget.h"
#include <DListView>
#include <DFloatingButton>
#include <DKeySequenceEdit>
#include <DCommandLinkButton>

using namespace dcc::widgets;
using namespace Dtk::Widget;

class IMModel;

class IMSettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMSettingWindow(QWidget *parent = nullptr);
    virtual ~IMSettingWindow();
    void updateUI(); //刷新界面
signals:
    void sig_popIMAddWindow(); //弹出添加输入法界面
private:
    void initUI(); //初始化界面
    void initConnect(); //初始化信号槽
    void readConfig(); //读取配置文件
    void writeConfig(); //写入配置文件
private slots:
    void slot_defualtIMChanged(const QString &selected); //修改默认输入法
    void slot_editBtnClicked(); //启用编辑
    void slot_systemAppChanged(const QString &selected); //切换系统/应用
private:
    ComboxWidget *m_defualtIMCbox {nullptr}; //选择默认输入法
    DCommandLinkButton *m_editBtn {nullptr}; //编辑
    DListView *m_IMCurrentView {nullptr}; //当前输入法列表
    ComboxWidget *m_imSwitchCbox {nullptr}; //切换输入法（快捷键）
    DKeySequenceEdit *m_virtualKey {nullptr}; //虚拟键盘 （快捷键）
    DKeySequenceEdit *m_defualtIMKey {nullptr}; //默认输入法 （快捷键）
    ComboxWidget *m_systemAppCbox {nullptr}; //切换系统/应用
    DFloatingButton *m_addIMBtn {nullptr}; //添加输入法
};

#endif // IMSETTINGWINDOW_H
