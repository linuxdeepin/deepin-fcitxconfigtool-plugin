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
#ifndef IMWIDOW_H
#define IMWIDOW_H

#include <QWidget>

class IMAddWindow;
class IMSettingWindow;
class QStackedWidget;

class IMWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMWindow(QWidget *parent = nullptr);
    virtual ~IMWindow();

private:
    void initUI(); //初始化界面
    void initConnect(); //初始化信号槽
    void initFcitxInterface(); //初始化fcitx接口
private:
    QStackedWidget *m_stackedWidget {nullptr}; //栈窗口
    IMSettingWindow *m_settingWindow {nullptr}; //输入法编辑窗口
    IMAddWindow *m_addWindow {nullptr}; //输入法添加窗口
};

#endif // IMWIDOW_H
