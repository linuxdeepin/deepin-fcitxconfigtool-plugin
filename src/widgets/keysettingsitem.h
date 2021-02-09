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
#ifndef KETSETTINGSITEM_H
#define KETSETTINGSITEM_H

#include "keylabel.h"
#include "settingsitem.h"
#include <QComboBox>
#include <DKeySequenceEdit>

using namespace Dtk::Widget;
using namespace dcc::widgets;

class KeyLabelWidget : public QWidget
{
    Q_OBJECT
public:
    KeyLabelWidget(QStringList list = {}, QWidget *p = nullptr);
    virtual ~KeyLabelWidget();
    void setList(const QStringList &list);
    QString getKeyToStr();
public slots:
    void editFinish();
signals:
    void editedFinish();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QHBoxLayout *m_mainLayout {nullptr};
    DKeySequenceEdit *m_keyEdit {nullptr};
    QList<KeyLabel *> m_list;
};

class KeySettingsItem : public SettingsItem
{
    Q_OBJECT
public:
    KeySettingsItem(const QString &text, const QStringList &list = {}, QFrame *parent = nullptr);
    void setList(const QStringList &list);
    QString getKeyToStr() { return m_keyWidget->getKeyToStr(); }
signals:
    void editedFinish();

private:
    QLabel *m_lable;
    QHBoxLayout *m_hLayout;
    KeyLabelWidget *m_keyWidget;
};

class ComBoboxSettingsItem : public SettingsItem
{
    Q_OBJECT
public:
    ComBoboxSettingsItem(const QString &text, const QStringList &list = {}, QFrame *parent = nullptr);
    virtual ~ComBoboxSettingsItem();
    QComboBox *comboBox() { return m_combox; }

private:
    QHBoxLayout *m_mainLayout {nullptr};
    QComboBox *m_combox {nullptr};
    QLabel *m_label {nullptr};
};

#endif // KETSETTINGSITEM_H
