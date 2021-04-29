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

#include "fcitxInterface/global.h"
#include <QWidget>

namespace dcc_fcitx_configtool {
namespace widgets {
class Fcitx_SettingsGroup;
class Fcitx_SettingsHead;
class Fcitx_ComboxWidget;
class Fcitx_ComBoboxSettingsItem;
class Fcitx_KeySettingsItem;
class Fcitx_IMActivityItem;
} // namespace widgets
} // namespace dcc_fcitx_configtool

namespace Dtk {
namespace Widget {
class DListView;
class DCommandLinkButton;
class DFloatingButton;

} // namespace Widget
} // namespace Dtk

class IMSettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMSettingWindow(QWidget *parent = nullptr);
    virtual ~IMSettingWindow();
    void updateUI(); //刷新界面
signals:
    void popIMAddWindow(); //弹出添加输入法界面
    void popShortKeyListWindow(const QString &curName, const QStringList &list, QString &name); //弹出快捷键冲突界面
    void popShortKeyStrWindow(const QString &curName, const QString &str, QString &name); //弹出快捷键冲突界面
private:
    void initUI(); //初始化界面
    void initConnect(); //初始化信号槽
    void readConfig(); //读取配置文件
    void itemSwap(const FcitxQtInputMethodItem &item, const bool &isUp = true);
private slots:
    void onEditBtnClicked(const bool &flag); //启用编辑
//    void onDefaultIMChanged();
    void onCurIMChanged(const FcitxQtInputMethodItemList &list);
    void onAddBtnCilcked();
    void onItemUp(const FcitxQtInputMethodItem &item);
    void onItemDown(const FcitxQtInputMethodItem &item);
    void onItemDelete(const FcitxQtInputMethodItem &item);

private:
    dcc_fcitx_configtool::widgets::Fcitx_SettingsGroup *m_IMListGroup {nullptr}; //输入法列表容器
    dcc_fcitx_configtool::widgets::Fcitx_SettingsGroup *m_shortcutGroup {nullptr}; //输入法快捷键容器
    dcc_fcitx_configtool::widgets::Fcitx_SettingsHead *m_editHead {nullptr}; //编辑按钮
    dcc_fcitx_configtool::widgets::Fcitx_ComboxWidget *m_defaultIMCbox {nullptr}; //选择默认输入法
    dcc_fcitx_configtool::widgets::Fcitx_ComBoboxSettingsItem *m_imSwitchCbox {nullptr}; //切换输入法（快捷键）
    dcc_fcitx_configtool::widgets::Fcitx_KeySettingsItem *m_virtualKey {nullptr}; //虚拟键盘 （快捷键）
//    dcc_fcitx_configtool::widgets::Fcitx_ComboxWidget *m_systemAppCbox {nullptr}; //切换系统/应用
    Dtk::Widget::DFloatingButton *m_addIMBtn {nullptr}; //添加输入法
};

#endif // IMSETTINGWINDOW_H
