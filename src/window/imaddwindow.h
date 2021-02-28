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
#ifndef IMADDWINDOW_H
#define IMADDWINDOW_H

#include <QWidget>
#include <fcitxqtinputmethoditem.h>
namespace dcc_fcitx_configtool {
namespace widgets {
class ButtonTuple;
} // namespace widgets
} // namespace dcc_fcitx_configtool

namespace Dtk {
namespace Widget {
class DSearchEdit;
class DCommandLinkButton;
} // namespace Widget
} // namespace Dtk

class AvailWidget;

class IMAddWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMAddWindow(QWidget *parent = nullptr);
    virtual ~IMAddWindow();
    void updateUI(); //刷新界面
signals:
    void popSettingsWindow(); //弹出设置窗口
    void addIM(FcitxQtInputMethodItem item);

private:
    void initUI(); //初始化界面
    void initConnect(); //初始化信号槽
private slots:
    void onAddIM(); //添加输入法
    void onOpenStore(); //打开应用商店
private:
    Dtk::Widget::DSearchEdit *m_searchLEdit {nullptr}; //搜索框
    AvailWidget *m_availWidget {nullptr}; //可用输入法列表窗口
    Dtk::Widget::DCommandLinkButton *m_storeBtn {nullptr}; //应用商店按钮
    dcc_fcitx_configtool::widgets::ButtonTuple *m_buttonTuple {nullptr}; //取消/添加按钮
};

#endif // IMADDWINDOW_H
