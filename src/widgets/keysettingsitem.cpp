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
#include <QComboBox>
#include <QMouseEvent>
#include <DFontSizeManager>
namespace dcc_fcitx_configtool {
namespace widgets {
KeyLabelWidget::KeyLabelWidget(QStringList list, QWidget *p)
    : QWidget(p)
    , curlist(list)
{
    m_keyEdit = new QLineEdit(this);
    m_keyEdit->installEventFilter(this);
    m_keyEdit->setReadOnly(true);
    m_keyEdit->hide();

    m_keyEdit->setPlaceholderText(tr("Enter a new shortcut"));

    connect(m_keyEdit, SIGNAL(editingFinished()), this, SLOT(editFinish()));

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 9, 0, 9);
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_keyEdit);
    setLayout(m_mainLayout);
    if (curlist.isEmpty()) {
        curlist << tr("None");
    }
    setList(curlist);
    setShortcutShow(true);
}

KeyLabelWidget::~KeyLabelWidget()
{
    clearShortcutKey();
}

void KeyLabelWidget::setList(const QStringList &list)
{
    curlist = list;
    initLableList(curlist);
}

void KeyLabelWidget::initLableList(const QStringList &list)
{
    clearShortcutKey();
    for (const QString &key : list) {
        appendKey(key);
    }
}

void KeyLabelWidget::appendKey(QString str)
{
    QString tmpKey = str.toLower();
    if (!tmpKey.isEmpty()) {
        tmpKey[0] = tmpKey[0].toUpper();
    }
    KeyLabel *label = new KeyLabel(tmpKey);
    m_list << label;
    m_mainLayout->addWidget(label);
}

QString KeyLabelWidget::getKeyToStr()
{
    QString key;
    for (int i = 0; i < m_list.count(); ++i) {
        if (i == m_list.count() - 1) {
            key += m_list[i]->text();
        } else {
            key += (m_list[i]->text() + "+");
        }
    }
    return QKeySequence(key).toString().replace("+", "_").toUpper();
}

void KeyLabelWidget::mousePressEvent(QMouseEvent *event)
{
    setShortcutShow(!m_keyEdit->isHidden());
    QWidget::mousePressEvent(event);
}

void KeyLabelWidget::resizeEvent(QResizeEvent *event)
{
    setShortcutShow(m_keyEdit->isHidden());
    QWidget::resizeEvent(event);
}

bool KeyLabelWidget::eventFilter(QObject *watched, QEvent *event)
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
            QKeyEvent *e = static_cast<QKeyEvent *>(event);
            if (e) {
                if (e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace) {
                    clearShortcutKey();
                    curlist.clear();
                    curlist << tr("None");
                    initLableList(curlist);
                    setShortcutShow(true);
                } else if (e->key() == Qt::Key_Control || e->key() == Qt::Key_Alt || e->key() == Qt::Key_Shift) {
                    setFocus();
                    clearShortcutKey();
                    newlist.clear();
                    newlist << publisherFunc::getKeyValue(e->key());
                    initLableList(newlist);
                    setShortcutShow(true);

                } else {
                    setShortcutShow(true);
                }
            }
            return true;
        }
    }
    return false;
}

void KeyLabelWidget::keyPressEvent(QKeyEvent *event)
{
    QString key = publisherFunc::getKeyValue(event->key());
    qDebug() << "keyPressEvent" << key;

    newlist << publisherFunc::getKeyValue(event->key());
    initLableList(newlist);
    if (newlist.count() >= 2 && !checkNewKey()) {
        initLableList(curlist);
    }
    setShortcutShow(true);
    QWidget::keyPressEvent(event);
}

void KeyLabelWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (newlist.count() < 2 || !checkNewKey(true)) {
        initLableList(curlist);
    }
    setShortcutShow(true);

    QWidget::keyReleaseEvent(event);
}

void KeyLabelWidget::clearShortcutKey()
{
    for (KeyLabel *label : m_list) {
        m_mainLayout->removeWidget(label);
        label->deleteLater();
    }
    m_list.clear();
}

void KeyLabelWidget::setShortcutShow(bool flag)
{
    if (flag) {
        m_mainLayout->setContentsMargins(0, 9, 0, 9);
        m_keyEdit->hide();
        int w = 0;
        for (KeyLabel *label : m_list) {
            w += label->width() + 9;
            label->show();
        }
        setMaximumWidth(w);

    } else {
        for (KeyLabel *label : m_list) {
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

bool KeyLabelWidget::checkNewKey(bool isRelease)
{
    qDebug() << "checkNewKey" << newlist;
    QStringList list {publisherFunc::getKeyValue(Qt::Key_Control),
                      publisherFunc::getKeyValue(Qt::Key_Alt),
                      publisherFunc::getKeyValue(Qt::Key_Shift),
                      publisherFunc::getKeyValue(Qt::Key_Super_L)};
    qDebug() << list;
    if (newlist.count() == 2) {
        for (int i = 0; i < list.count(); ++i) {
            if (newlist.at(0) == list.at(i)) {
                if (list.indexOf(newlist[1]) != -1) {
                    if (newlist[1] != newlist[0]) {
                        return !isRelease;

                    } else {
                        return false;
                    }
                }
                if (list.indexOf(newlist[1]) == -1) {
                    if (IMConfig::checkShortKey(newlist)) {
                    }
                    setList(newlist);
                    focusNextChild();
                    emit editedFinish();
                    return true;
                }
            }
        }
    }
    if (newlist.count() == 3) {
        if (list.indexOf(newlist[2]) == -1) {
            setList(newlist);
            focusNextChild();
            emit editedFinish();
            return true;
        } else {
            focusNextChild();
            return false;
        }
    }
    return true;
}

KeySettingsItem::KeySettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : SettingsItem(parent)
{
    m_label = new ShortenLabel(text, this);
    m_keyWidget = new KeyLabelWidget(list, parent);
    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setContentsMargins(10, 0, 10, 0);
    m_hLayout->addWidget(m_label);
    m_hLayout->addWidget(m_keyWidget);
    m_hLayout->setAlignment(m_label, Qt::AlignLeft);
    m_hLayout->addWidget(m_keyWidget, 0, Qt::AlignVCenter | Qt::AlignRight);
    setFixedHeight(48);
    setLayout(m_hLayout);
    connect(m_keyWidget, &KeyLabelWidget::editedFinish, this, &KeySettingsItem::editedFinish);
}

void KeySettingsItem::setList(const QStringList &list)
{
    m_keyWidget->setList(list);
}

void KeySettingsItem::resizeEvent(QResizeEvent *event)
{
    int v = width() - m_keyWidget->width() - 32;
    int titleWidth = publisherFunc::fontSize(m_label->text());
    if (titleWidth <= v) {
        m_label->setFixedWidth(titleWidth);
    } else {
        m_label->setFixedWidth(v);
    }

    qDebug() << size() << m_keyWidget->size() << m_label->size();
    SettingsItem::resizeEvent(event);
}

void KeySettingsItem::paintEvent(QPaintEvent *event)
{
    int v = width() - m_keyWidget->width() - 32;
    int titleWidth = publisherFunc::fontSize(m_label->text());
    if (titleWidth <= v) {
        m_label->setFixedWidth(titleWidth);
    } else {
        m_label->setFixedWidth(v);
    }

    SettingsItem::paintEvent(event);
}

ComBoboxSettingsItem::ComBoboxSettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : SettingsItem(parent)
{
    m_combox = new QComboBox(this);
    m_combox->setFixedHeight(36);
    m_combox->addItems(list);
    m_label = new ShortenLabel(text, this);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T7);
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_label);
    m_mainLayout->addWidget(m_combox);
    m_mainLayout->setContentsMargins(10, 0, 10, 0);
    setLayout(m_mainLayout);
    setFixedHeight(48);
}

ComBoboxSettingsItem::~ComBoboxSettingsItem()
{
}

} // namespace widgets
} // namespace dcc_fcitx_configtool
