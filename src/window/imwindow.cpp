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
#include "imwindow.h"
#include "imaddwindow.h"
#include "imsettingwindow.h"
#include "shortcutkeywindow.h"
#include "immodel/immodel.h"
#include "publisher/publisherdef.h"
#include "fcitxInterface/config.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QTranslator>
#include <libintl.h>
#include <QToolButton>
#include <QComboBox>
#include <QAccessible>
#include "widgets/accessiblewidget.h"
#include "widgets/titlelabel.h"
// 接口工厂
QAccessibleInterface *accessibleFactory(const QString &classname, QObject *object)
{
    QAccessibleInterface *interface = nullptr;

    if (object && object->isWidgetType()) {
        if (classname == "QLabel")
            interface = new AccessibleLabel(qobject_cast<QLabel *>(object));

        if (classname == "QPushButton")
            interface = new AccessiblePButton(qobject_cast<QPushButton *>(object));

        if (classname == "QToolButton")
            interface = new AccessibleTButton(qobject_cast<QToolButton *>(object));

        if (classname == "QComboBox")
            interface = new AccessibleComboBox(qobject_cast<QComboBox *>(object));

        if (classname == "Fcitx_KeyLabelWidget")
            interface = new AccessibleKeyLabelWidget(qobject_cast<Fcitx_KeyLabelWidget *>(object));

        if (classname == "Fcitx_KeySettingsItem")
            interface = new AccessibleKeySettingsItem(qobject_cast<Fcitx_KeySettingsItem *>(object));

        if (classname == "Fcitx_ComBoboxSettingsItem")
            interface = new AccessibleComBoboxSettingsItem(qobject_cast<Fcitx_ComBoboxSettingsItem *>(object));

        if (classname == "DFloatingButton")
            interface = new AccessibleDFloatingButton(qobject_cast<DFloatingButton *>(object));

        if (classname == "DSearchEdit")
            interface = new AccessibleDSearchEdit(qobject_cast<DSearchEdit *>(object));

        if (classname == "DCommandLinkButton")
            interface = new AccessibleDCommandLinkButton(qobject_cast<DCommandLinkButton *>(object));

        if (classname == "Fcitx_TitleLabel")
            interface = new AccessibleTitleLabel(qobject_cast<Fcitx_TitleLabel *>(object));
    }

    return interface;
}

IMWindow::IMWindow(QWidget *parent)
    : DWidget(parent)
{
    initFcitxInterface();
    initUI();
    initConnect();
}

IMWindow::~IMWindow()
{
    IMModel::instance()->deleteIMModel();
    DeleteObject_Null(m_stackedWidget);
//    DeleteObject_Null(m_settingWindow);
//    DeleteObject_Null(m_addWindow);
//    DeleteObject_Null(m_shortcutKeyWindow);
    DeleteObject_Null(m_pLayout);
}

void IMWindow::initFcitxInterface()
{
    bindtextdomain("fcitx", LOCALEDIR);
    bind_textdomain_codeset("fcitx", "UTF-8");
    FcitxLogSetLevel(FCITX_NONE);
    FcitxQtInputMethodItem::registerMetaType();
    FcitxQtKeyboardLayout::registerMetaType();
    if (!Fcitx::Global::instance()->inputMethodProxy()) {
        QProcess::startDetached("fcitx -r");
    }

    // 安装工厂
    QAccessible::installFactory(accessibleFactory);
}

void IMWindow::initUI()
{
    m_stackedWidget = new QStackedWidget(this);
    m_settingWindow = new IMSettingWindow(this);
    m_addWindow = new IMAddWindow(this);
    m_shortcutKeyWindow = new ShortcutKeyWindow(this);
    m_stackedWidget->addWidget(m_settingWindow);
    m_stackedWidget->addWidget(m_addWindow);
    m_stackedWidget->addWidget(m_shortcutKeyWindow);
    m_stackedWidget->setCurrentIndex(0);
    //界面布局
    m_pLayout = new QVBoxLayout(this);
    m_pLayout->addWidget(m_stackedWidget);
    m_pLayout->setMargin(0);
    m_pLayout->setSpacing(0);
}

void IMWindow::initConnect()
{
    auto func = [=]() {
        m_stackedWidget->setCurrentIndex(PopIMSettingWindow);
        m_settingWindow->updateUI();
    };
    connect(m_addWindow, &IMAddWindow::popSettingsWindow, func);
    connect(m_shortcutKeyWindow, &ShortcutKeyWindow::popSettingsWindow, func);

    connect(m_settingWindow, &IMSettingWindow::popIMAddWindow, [=]() {
        m_stackedWidget->setCurrentIndex(PopIMAddWindow);
        m_addWindow->updateUI();
    });

    connect(m_settingWindow, &IMSettingWindow::popShortKeyListWindow, [=](const QString &curName, const QStringList &list, QString &name) {
        QString tmpString;
        for (const QString &key : list) {
            if (key != list.last()) {
                tmpString += key + "+";
            } else {
                tmpString += key;
            }
        }

        m_shortcutKeyWindow->setValue(curName, name, tmpString);
        m_stackedWidget->setCurrentIndex(PopShortcutKeyWindow);
        m_settingWindow->updateUI();
    });
    /*
        connect(m_settingWindow, &IMSettingWindow::popShortKeyListWindow, [=](const QString &curName, const QStringList &list, QString &name) {
            QString tmpString;
            for (const QString &key : list) {
                if (key != list.last()) {
                    tmpString += key + "+";
                } else {
                    tmpString += key;
                }
            }

            m_shortcutKeyWindow->setValue(curName, name, tmpString);
            m_stackedWidget->setCurrentIndex(PopShortcutKeyWindow);
            m_settingWindow->updateUI();
        });
        connect(m_settingWindow, &IMSettingWindow::popShortKeyStrWindow, [=](const QString &curName, const QString &str, QString &name) {
            m_shortcutKeyWindow->setValue(curName, name, str);
            m_stackedWidget->setCurrentIndex(PopShortcutKeyWindow);
            m_settingWindow->updateUI();
        });
    */

}
