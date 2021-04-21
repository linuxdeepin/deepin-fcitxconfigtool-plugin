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
#include "keysettingsitem.h"
#include "settingsgroup.h"
#include "window/immodel/imconfig.h"
#include "publisher/publisherdef.h"
#include <DFontSizeManager>
#include <QComboBox>
#include <QMouseEvent>
#include <QLineEdit>
namespace dcc_fcitx_configtool {
namespace widgets {
Fcitx_KeyLabelWidget::Fcitx_KeyLabelWidget(QStringList list, QWidget *p)
    : QWidget(p)
    , m_curlist(list)
{
    m_eidtFlag = true;
    if (m_curlist.isEmpty()) {
        m_curlist << tr("None");
    }
    m_keyEdit = new QLineEdit(this);
    m_keyEdit->installEventFilter(this);
    m_keyEdit->setReadOnly(true);
    m_keyEdit->hide();
    m_keyEdit->setPlaceholderText(tr("Enter a new shortcut"));
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 9, 0, 9);
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_keyEdit);
    setLayout(m_mainLayout);
    setList(m_curlist);
    setShortcutShow(true);
}

Fcitx_KeyLabelWidget::~Fcitx_KeyLabelWidget()
{
    clearShortcutKey();
}

void Fcitx_KeyLabelWidget::setList(const QStringList &list)
{
    m_curlist = list;
    initLableList(m_curlist);
}

void Fcitx_KeyLabelWidget::initLableList(const QStringList &list)
{
    clearShortcutKey();
    for (const QString &key : list) {
        QString tmpKey = key.toLower();
        if (!tmpKey.isEmpty()) {
            tmpKey[0] = tmpKey[0].toUpper();
        }
        Fcitx_KeyLabel *label = new Fcitx_KeyLabel(tmpKey);
        m_list << label;
        m_mainLayout->addWidget(label);
    }
}

QString Fcitx_KeyLabelWidget::getKeyToStr()
{
    QString key;
    for (int i = 0; i < m_list.count(); ++i) {
        if (i == m_list.count() - 1) {
            key += m_list[i]->text();
        } else {
            key += (m_list[i]->text() + "_");
        }
    }
    return key.toUpper();
}

void Fcitx_KeyLabelWidget::setEnableEdit(bool flag)
{
    m_eidtFlag = flag;
}

void Fcitx_KeyLabelWidget::mousePressEvent(QMouseEvent *event)
{
    if (!m_eidtFlag)
        return;
    setShortcutShow(!m_keyEdit->isHidden());
    QWidget::mousePressEvent(event);
}

void Fcitx_KeyLabelWidget::resizeEvent(QResizeEvent *event)
{
    if (!m_eidtFlag)
        return;
    setShortcutShow(m_keyEdit->isHidden());
    QWidget::resizeEvent(event);
}

bool Fcitx_KeyLabelWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (m_keyEdit == watched) {
        if (event->type() == QEvent::Hide || event->type() == QEvent::MouseButtonPress || event->type() == QEvent::FocusOut) {
            setShortcutShow(true);
            return true;
        }
        if (event->type() == QEvent::Show) {
            setShortcutShow(false);
            return true;
        }
        if (event->type() == QEvent::KeyPress) {
            Dynamic_Cast(QKeyEvent, e, event);

            auto func = [=](QStringList &list, const QString &key) {
                clearShortcutKey();
                list.clear();
                list << key;
                initLableList(list);
                setShortcutShow(true);
            };

            if (e) {
                if (e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace) {
                    func(m_curlist, tr("None"));

                } else if (e->key() == Qt::Key_Control || e->key() == Qt::Key_Alt || e->key() == Qt::Key_Shift) {
                    setFocus();
                    func(m_newlist, publisherFunc::getKeyValue(e->key()));
                } else {
                    setShortcutShow(true);
                }
                return true;
            }
            return false;
        }
    }
    return false;
}

void Fcitx_KeyLabelWidget::keyPressEvent(QKeyEvent *event)
{
    if (!m_eidtFlag)
        return;
    m_newlist << publisherFunc::getKeyValue(event->key());
    initLableList(m_newlist);
    if (m_newlist.count() >= 2 && !checkNewKey()) {
        initLableList(m_curlist);
    }
    setShortcutShow(true);
    QWidget::keyPressEvent(event);
}

void Fcitx_KeyLabelWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (!m_eidtFlag)
        return;
    if (m_newlist.count() < 2 || !checkNewKey(true)) {
        initLableList(m_curlist);
    }
    setShortcutShow(true);
    //    QWidget::keyReleaseEvent(event);
}

void Fcitx_KeyLabelWidget::clearShortcutKey()
{
    for (Fcitx_KeyLabel *label : m_list) {
        m_mainLayout->removeWidget(label);
        label->deleteLater();
    }
    m_list.clear();
}

void Fcitx_KeyLabelWidget::setShortcutShow(bool flag)
{
    if (flag) {
        m_mainLayout->setContentsMargins(0, 9, 0, 9);
        m_keyEdit->hide();
        int w = 0;
        for (Fcitx_KeyLabel *label : m_list) {
            w += label->width() + 9;
            label->show();
        }
        setMaximumWidth(w);

    } else {
        for (Fcitx_KeyLabel *label : m_list) {
            label->hide();
        }
        m_mainLayout->setContentsMargins(0, 0, 0, 0);
        m_keyEdit->show();
        m_keyEdit->setFocus();
        m_keyEdit->clear();
        setMaximumWidth(9999);
    }
    update();
}

bool Fcitx_KeyLabelWidget::checkNewKey(bool isRelease)
{
    QStringList list {publisherFunc::getKeyValue(Qt::Key_Control),
                      publisherFunc::getKeyValue(Qt::Key_Alt),
                      publisherFunc::getKeyValue(Qt::Key_Shift),
                      publisherFunc::getKeyValue(Qt::Key_Super_L)};

    if (m_newlist.count() == 2) {
        for (int i = 0; i < list.count(); ++i) {
            if (m_newlist.at(0) == list.at(i)) {
                if (list.indexOf(m_newlist[1]) != -1) {
                    if (m_newlist[1] != m_newlist[0]) {
                        return !isRelease;
                    }
                    return false;
                }
                if (list.indexOf(m_newlist[1]) == -1) {
                    QStringList tmpList;
                    for (const QString &key : m_newlist) {
                        QString tmpKey = key.toUpper();
                        tmpList.append(tmpKey);
                    }

                    QString configName;
                    if (m_curlist != tmpList && !IMConfig::checkShortKey(m_newlist, configName)) {
                        emit shortCutError(m_newlist, configName);
                        return false;
                    }
                    setList(m_newlist);
                    focusNextChild();
                    emit editedFinish();
                    return true;
                }
            }
        }
    }
    if (m_newlist.count() >= 3) {
        if (list.indexOf(m_newlist[0]) == -1 || list.indexOf(m_newlist[1]) == -1 || list.indexOf(m_newlist[2]) != -1) {
            focusNextChild();
            return false;
        }
        QStringList tmpList;
        for (const QString &key : m_newlist) {
            QString tmpKey = key.toUpper();
            tmpList.append(tmpKey);
        }
        QString configName;
        if (m_curlist != tmpList && !IMConfig::checkShortKey(m_newlist, configName)) {
            emit shortCutError(m_newlist, configName);
            return false;
        }
        setList(m_newlist);
        focusNextChild();
        emit editedFinish();
        return true;
    }
    return true;
}

Fcitx_KeySettingsItem::Fcitx_KeySettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : Fcitx_SettingsItem(parent)
{
    m_label = new Fcitx_ShortenLabel(text, this);
    m_keyWidget = new Fcitx_KeyLabelWidget(list, parent);
    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setContentsMargins(0, 0, 10, 0);
    m_hLayout->addWidget(m_label);
    m_hLayout->addWidget(m_keyWidget);
    m_hLayout->setAlignment(m_label, Qt::AlignLeft);
    m_hLayout->addWidget(m_keyWidget, 0, Qt::AlignVCenter | Qt::AlignRight);
    setFixedHeight(48);
    setLayout(m_hLayout);
    connect(m_keyWidget, &Fcitx_KeyLabelWidget::editedFinish, this, &Fcitx_KeySettingsItem::editedFinish);
    connect(m_keyWidget, &Fcitx_KeyLabelWidget::shortCutError, this, &Fcitx_KeySettingsItem::doShortCutError);
}

void Fcitx_KeySettingsItem::setText(const QString &text)
{
    m_label->setShortenText(text);
}

QString Fcitx_KeySettingsItem::getLabelText()
{
    return m_label->text();
}

void Fcitx_KeySettingsItem::setEnableEdit(bool flag)
{
    m_keyWidget->setEnableEdit(flag);
}

void Fcitx_KeySettingsItem::setList(const QStringList &list)
{
    m_keyWidget->setList(list);
}

void Fcitx_KeySettingsItem::resizeEvent(QResizeEvent *event)
{
    updateSize();
    Fcitx_SettingsItem::resizeEvent(event);
}

void Fcitx_KeySettingsItem::paintEvent(QPaintEvent *event)
{
    updateSize();
    Fcitx_SettingsItem::paintEvent(event);
}

void Fcitx_KeySettingsItem::doShortCutError(const QStringList &list, QString &name)
{
    emit Fcitx_KeySettingsItem::shortCutError(m_label->text(), list, name);
}

void Fcitx_KeySettingsItem::updateSize()
{
    int v = width() - m_keyWidget->width() - 32;
    int titleWidth = publisherFunc::fontSize(m_label->text());
    if (titleWidth <= v) {
        m_label->setFixedWidth(titleWidth);
    } else {
        m_label->setFixedWidth(v);
    }
}

Fcitx_ComBoboxSettingsItem::Fcitx_ComBoboxSettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : Fcitx_SettingsItem(parent)
{
    m_combox = new QComboBox(this);
    m_combox->setFixedHeight(36);
    m_combox->addItems(list);
    m_label = new Fcitx_ShortenLabel(text, this);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T6);
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_label);
    m_mainLayout->addWidget(m_combox);
    m_mainLayout->setContentsMargins(10, 0, 10, 0);
    setLayout(m_mainLayout);
    setFixedHeight(48);
}

QString Fcitx_ComBoboxSettingsItem::getLabelText()
{
    return m_label->text();
}

Fcitx_ComBoboxSettingsItem::~Fcitx_ComBoboxSettingsItem()
{
}

} // namespace widgets
} // namespace dcc_fcitx_configtool
