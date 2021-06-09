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
#include "imsettingwindow.h"
#include "immodel/immodel.h"
#include "immodel/imconfig.h"

#include "widgets/settingsheaderitem.h"
#include "widgets/settingsgroup.h"
#include "widgets/comboxwidget.h"
#include "widgets/keysettingsitem.h"
#include "widgets/imactivityitem.h"
#include "widgets/settingshead.h"
#include "publisher/publisherdef.h"
#include "widgets/contentwidget.h"
#include "window/shortcutkeywindow.h"

#include <DFloatingButton>
#include <DCommandLinkButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <libintl.h>

using namespace Fcitx;
using namespace dcc_fcitx_configtool::widgets;
IMSettingWindow::IMSettingWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnect();
    updateUI();
}

IMSettingWindow::~IMSettingWindow()
{
    m_IMListGroup->clear();
    m_shortcutGroup->clear();
    DeleteObject_Null(m_IMListGroup);
    DeleteObject_Null(m_shortcutGroup);
    DeleteObject_Null(m_editHead);
    DeleteObject_Null(m_mainLayout);
    DeleteObject_Null(m_imSwitchCbox);
    DeleteObject_Null(m_defaultIMKey);
//    DeleteObject_Null(m_addIMBtn);
}

void IMSettingWindow::initUI()
{
    //创建标题
    auto newTitleHead = [this](QString str, bool isEdit = false) {
        Fcitx_SettingsHead *head = new Fcitx_SettingsHead();
        head->setParent(this);
        head->setTitle(str);
        head->setEditEnable(isEdit);
        head->layout()->setContentsMargins(10, 4, 10, 0);
        if (isEdit) {
            m_editHead = head;
            m_editHead->getTitleLabel()->setAccessibleName("Edit");
        }
        return head;
    };

    m_mainLayout = new QVBoxLayout();
    QWidget* mainWidget = new QWidget(this);
    m_mainLayout->addWidget(mainWidget);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    //界面布局
    QVBoxLayout *subLayout = new QVBoxLayout(mainWidget);
    subLayout->setContentsMargins(0, 0, 0, 10);
    subLayout->setSpacing(0);

    //滑动窗口
    Fcitx_ContentWidget *scrollArea = new Fcitx_ContentWidget(this);

    QWidget *scrollAreaWidgetContents = new QWidget(scrollArea);
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(scrollAreaWidgetContents);
    scrollAreaLayout->setContentsMargins(10, 0, 10, 0);
    scrollAreaLayout->setSpacing(0);
    scrollArea->setContent(scrollAreaWidgetContents);
    scrollAreaWidgetContents->setLayout(scrollAreaLayout);

    //默认输入法
//    m_defaultIMGroup = new Fcitx_SettingsGroup();
//    m_defaultIMCbox = new Fcitx_ComboxWidget(tr("Default"));
//    m_defaultIMCbox->addBackground();
//    m_defaultIMCbox->comboBox()->setFixedHeight(36);
//    m_defaultIMGroup->appendItem(m_defaultIMCbox);

    //输入法管理 编辑按钮
    m_IMListGroup = new Fcitx_SettingsGroup();
    m_IMListGroup->setSpacing(2);
    onCurIMChanged(IMModel::instance()->getCurIMList());

    //快捷键 切换输入法 切换虚拟键盘 切换至默认输入法
    m_shortcutGroup = new Fcitx_SettingsGroup();
    m_shortcutGroup->setSpacing(2);

    m_imSwitchCbox = new Fcitx_ComBoboxSettingsItem(tr("Switch input methods"), {"CTRL_SHIFT", "ALT_SHIFT", "CTRL_SUPER", "ALT_SUPER"});
    //    m_defaultIMKey = new Fcitx_KeySettingsItem(tr("Switch to the first input method"));
//    m_imSwitchKey = new Fcitx_KeySettingsItem(tr("Switch input methods"));
    m_defaultIMKey = new Fcitx_KeySettingsItem(tr("Switch to the first input method"));
//    m_virtualKey = new Fcitx_KeySettingsItem(tr("Call out Onboard"));
//    m_systemAppCbox = new Fcitx_ComboxWidget(tr("Applies to"));
//    m_systemAppCbox->comboBox()->addItems({tr("System"), tr("Application")});
//    m_systemAppCbox->layout()->setContentsMargins(10, 0, 0, 0);
    m_shortcutGroup->appendItem(m_imSwitchCbox);
//    m_shortcutGroup->appendItem(m_imSwitchKey);
    m_shortcutGroup->appendItem(m_defaultIMKey);
//    m_shortcutGroup->appendItem(m_virtualKey);
//    m_shortcutGroup->appendItem(m_systemAppCbox, Fcitx_SettingsGroup::NoneBackground);
    //暂时隐藏
//    m_virtualKey->setVisible(false);
//    m_systemAppCbox->setVisible(false);

    //控件添加至滑动窗口内
//    scrollAreaLayout->addWidget(newTitleHead(tr("Input Method")));
//    scrollAreaLayout->addSpacing(10);
//    scrollAreaLayout->addWidget(m_defaultIMGroup);
    scrollAreaLayout->addWidget(newTitleHead(tr("Manage Input Methods"), true));
    scrollAreaLayout->addSpacing(10);
    scrollAreaLayout->addWidget(m_IMListGroup);
    scrollAreaLayout->addSpacing(11);
    scrollAreaLayout->addWidget(newTitleHead(tr("Shortcuts")));
    scrollAreaLayout->addSpacing(10);
    scrollAreaLayout->addWidget(m_shortcutGroup);
    scrollAreaLayout->addStretch();

    //添加界面按钮
    m_addIMBtn = new DFloatingButton(DStyle::SP_IncreaseElement, this);
    QHBoxLayout *headLayout = new QHBoxLayout(this);
    headLayout->setMargin(0);
    headLayout->setSpacing(0);
    headLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    headLayout->addWidget(m_addIMBtn);
    headLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    //添加至主界面内
    subLayout->addWidget(scrollArea);
    subLayout->addSpacing(17);
    subLayout->addLayout(headLayout);

    readConfig();
}

void IMSettingWindow::initConnect()
{
    auto reloadFcitx = [=](bool flag) {
        if (Global::instance()->inputMethodProxy() && flag)
            Global::instance()->inputMethodProxy()->ReloadConfig();
    };
    connect(m_defaultIMKey, &Fcitx_KeySettingsItem::editedFinish, [=]() {
//        Fcitx_ShortcutInfo defaultShortCutInfo = IMConfig::findIdKey("terminal");
        reloadFcitx(IMConfig::setDefaultIMKey(m_defaultIMKey->getKeyToStr()));
        m_defaultIMKey->setList(m_defaultIMKey->getKeyToStr().split("_"));
    });
//    connect(m_imSwitchKey, &Fcitx_KeySettingsItem::editedFinish, [=]() {
//        reloadFcitx(IMConfig::setVirtualKey(m_virtualKey->getKeyToStr()));
//        Fcitx_ShortcutInfo imswitchShortCutInfo = IMConfig::findIdKey("system-monitor");
//    });


//    connect(m_defaultIMKey, &Fcitx_KeySettingsItem::editedFinish, [=]() {
//        reloadFcitx(IMConfig::setDefaultIMKey(m_defaultIMKey->getKeyToStr()));
//    });
//    connect(m_imSwitchKey, &Fcitx_KeySettingsItem::editedFinish, [=]() {
//        reloadFcitx(IMConfig::setVirtualKey(m_virtualKey->getKeyToStr()));
//    });

//    connect(m_defaultIMKey, &Fcitx_KeySettingsItem::shortCutError, this, &IMSettingWindow::popShortKeyListWindow);
//    connect(m_virtualKey, &Fcitx_KeySettingsItem::shortCutError, this, &IMSettingWindow::popShortKeyListWindow);

    connect(m_imSwitchCbox->comboBox(), &QComboBox::currentTextChanged, [=]() {
        m_imSwitchCbox->comboBox()->setAccessibleName(m_imSwitchCbox->comboBox()->currentText());
        reloadFcitx(IMConfig::setIMSwitchKey(m_imSwitchCbox->comboBox()->currentText()));
    });

    connect(m_defaultIMKey, &Fcitx_KeySettingsItem::shortCutError, this, &IMSettingWindow::popShortKeyListWindow);
//    connect(m_imSwitchKey, &Fcitx_KeySettingsItem::shortCutError, this, &IMSettingWindow::popShortKeyListWindow);


    connect(IMModel::instance(), &IMModel::curIMListChanaged, this, &IMSettingWindow::onCurIMChanged);
    connect(m_addIMBtn, &DFloatingButton::clicked, this, &IMSettingWindow::onAddBtnCilcked);
//    connect(m_defaultIMCbox, &Fcitx_ComboxWidget::onSelectChanged, this, &IMSettingWindow::onDefaultIMChanged);
//    connect(m_defaultIMCbox->comboBox(), &QComboBox::currentTextChanged, this, &IMSettingWindow::onDefaultIMChanged);
    connect(m_editHead, &Fcitx_SettingsHead::editChanged, this, &IMSettingWindow::onEditBtnClicked);
}

//读取配置文件
void IMSettingWindow::readConfig()
{
//    Fcitx_ShortcutInfo defaultShortCutInfo = IMConfig::findIdKey("terminal");
//    Fcitx_ShortcutInfo imswitchShortCutInfo = IMConfig::findIdKey("system-monitor");
//    m_defaultIMKey->setKeyId("terminal");
//    m_defaultIMKey->setKeyId("system-monitor");
//    m_defaultIMKey->setList(defaultShortCutInfo.accels.split("_"));
//    m_imSwitchKey->setList(imswitchShortCutInfo.accels.split("_"));

    int index = m_imSwitchCbox->comboBox()->findText(IMConfig::IMSwitchKey());
    m_imSwitchCbox->comboBox()->setCurrentIndex(index < 0 ? 0 : index);
//    index = IMModel::instance()->getIMIndex(IMConfig::defaultIM());
//    m_defaultIMCbox->comboBox()->setCurrentIndex(index < 0 ? 0 : index);
    m_defaultIMKey->setList(IMConfig::defaultIMKey().split("_"));
//    m_virtualKey->setList(IMConfig::virtualKey().split("_"));
}

void IMSettingWindow::updateUI()
{
    if (IMModel::instance()->isEdit()) {
        onEditBtnClicked(false);
    }
    readConfig();
}

void IMSettingWindow::itemSwap(const FcitxQtInputMethodItem &item, const bool &isUp)
{
    Dynamic_Cast_CheckNull(Fcitx_IMActivityItem, t, m_IMListGroup->getItem(IMModel::instance()->getIMIndex(item)));
    int row = IMModel::instance()->getIMIndex(item);
    if (isUp) {
//        if (row < 2) {
//            return;
//        }
        m_IMListGroup->moveItem(t, row - 1);
        IMModel::instance()->onItemUp(item);
    } else {
        if (row == IMModel::instance()->getCurIMList().count() - 1) {
            return;
        }
        m_IMListGroup->moveItem(t, row + 1);
        IMModel::instance()->onItemDown(item);
    }
    t->setSelectStatus(false);

    Dynamic_Cast_CheckNull(Fcitx_IMActivityItem, t2, m_IMListGroup->getItem(row));
    t2->setSelectStatus(true);
}

//默认输入法改变
void IMSettingWindow::onDefaultIMChanged()
{
//    QString key = m_defaultIMCbox->comboBox()->currentText();
//    FcitxQtInputMethodItem item = IMModel::instance()->getIM(m_defaultIMCbox->comboBox()->currentIndex());
//    if (!item.uniqueName().isEmpty()) {
//        IMConfig::setDefaultIM(item.uniqueName());
//        if (Global::instance()->inputMethodProxy()) {
//            Global::instance()->inputMethodProxy()->ReloadConfig();
//        }
//        return;
//    }
}

//编辑当前输入法列表
void IMSettingWindow::onEditBtnClicked(const bool &flag)
{
    IMModel::instance()->setEdit(flag);
    m_editHead->setEdit(flag);
    for (int i = 0; i < m_IMListGroup->itemCount(); ++i) {
        Dynamic_Cast(Fcitx_IMActivityItem, mItem, m_IMListGroup->getItem(i));
        if (mItem) {
            mItem->editSwitch(flag);
        }
    }
}

//当前输入法列表改变
void IMSettingWindow::onCurIMChanged(const FcitxQtInputMethodItemList &list)
{
//    disconnect(m_defaultIMCbox, &Fcitx_ComboxWidget::onSelectChanged, this, &IMSettingWindow::onDefaultIMChanged);
    m_IMListGroup->clear();
//    m_defaultIMCbox->comboBox()->clear();
    for (int i = 0; i < list.count(); ++i) {
        Fcitx_IMActivityItem *tmp;
//        if (i == 0) {
//            tmp = new Fcitx_IMActivityItem(list[i], true);
//        } else {
            tmp = new Fcitx_IMActivityItem(list[i]);
            connect(tmp, &Fcitx_IMActivityItem::configBtnClicked, IMModel::instance(), &IMModel::onConfigShow);
            connect(tmp, &Fcitx_IMActivityItem::upBtnClicked, this, &IMSettingWindow::onItemUp);
            connect(tmp, &Fcitx_IMActivityItem::downBtnClicked, this, &IMSettingWindow::onItemDown);
            connect(tmp, &Fcitx_IMActivityItem::deleteBtnClicked, this, &IMSettingWindow::onItemDelete);
            tmp->editSwitch(IMModel::instance()->isEdit());
//        }
        m_IMListGroup->appendItem(tmp);
//        m_defaultIMCbox->comboBox()->addItem(list[i].name());
    }

//    int index = IMModel::instance()->getIMIndex(IMConfig::defaultIM());
//    if (index < 0) {
//        index = 0;
//        m_defaultIMCbox->comboBox()->setCurrentIndex(index);
//        onDefaultIMChanged();
//    } else {
//        m_defaultIMCbox->comboBox()->setCurrentIndex(index);
//    }
//    connect(m_defaultIMCbox, &Fcitx_ComboxWidget::onSelectChanged, this, &IMSettingWindow::onDefaultIMChanged);
}

void IMSettingWindow::onItemUp(const FcitxQtInputMethodItem &item)
{
    itemSwap(item, true);
}

void IMSettingWindow::onItemDown(const FcitxQtInputMethodItem &item)
{
    itemSwap(item, false);
}

void IMSettingWindow::onItemDelete(const FcitxQtInputMethodItem &item)
{
    auto it = m_IMListGroup->getItem(IMModel::instance()->getIMIndex(item));
//    if (item.name() == IMConfig::defaultIM()) {
//        int index = m_defaultIMCbox->comboBox()->findText(item.name());
//        if (index >= 0) {
//            m_defaultIMCbox->comboBox()->removeItem(index);
//            m_defaultIMCbox->comboBox()->setCurrentIndex(1);
//        }
//        index = m_defaultIMCbox->comboBox()->count() >= 2 ? 0 : 1;
//        IMConfig::setDefaultIM(IMModel::instance()->getIM(index).uniqueName());
//    } else {
//        int index = m_defaultIMCbox->comboBox()->findText(item.name());
//        if (index >= 0) {
//            m_defaultIMCbox->comboBox()->removeItem(index);
//        }
//    }

    m_IMListGroup->removeItem(it);
    it->deleteLater();
    IMModel::instance()->onDeleteItem(item);
}

//添加按钮点击
void IMSettingWindow::onAddBtnCilcked()
{
    if (IMModel::instance()->isEdit())
        onEditBtnClicked(false);
    emit popIMAddWindow();
}
