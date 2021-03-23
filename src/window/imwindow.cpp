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
#include "fcitxInterface/config.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QTranslator>
#include <libintl.h>

IMWindow::IMWindow(QWidget *parent)
    : QWidget(parent)
{
    initFcitxInterface();
    initUI();
    initConnect();
}

IMWindow::~IMWindow()
{
    IMModel::instance()->deleteIMModel();
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
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(m_stackedWidget);
    pLayout->setMargin(0);
    pLayout->setSpacing(0);
    setLayout(pLayout);
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
