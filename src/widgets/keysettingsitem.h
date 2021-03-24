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
#include "labels/shortenlabel.h"
#include <QComboBox>

using namespace Dtk::Widget;
using namespace dcc_fcitx_configtool::widgets;
namespace dcc_fcitx_configtool {
namespace widgets {

class Fcitx_KeyLabelWidget : public QWidget
{
    Q_OBJECT
public:
    Fcitx_KeyLabelWidget(QStringList list = {}, QWidget *p = nullptr);
    virtual ~Fcitx_KeyLabelWidget();
    void setList(const QStringList &list);
    QString getKeyToStr();
    void setEnableEdit(bool flag);

signals:
    void editedFinish();
    void shortCutError(const QStringList &list, QString &name);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void clearShortcutKey();
    void setShortcutShow(bool flag);
    bool checkNewKey(bool isRelease = false);
    void initLableList(const QStringList &list);

private:
    QHBoxLayout *m_mainLayout {nullptr};
    QLineEdit *m_keyEdit {nullptr};
    QList<Fcitx_KeyLabel *> m_list;
    QStringList m_curlist;
    QStringList m_newlist;
    bool m_eidtFlag;
};

class Fcitx_KeySettingsItem : public Fcitx_SettingsItem
{
    Q_OBJECT
public:
    Fcitx_KeySettingsItem(const QString &text = "", const QStringList &list = {}, QFrame *parent = nullptr);
    void setList(const QStringList &list);
    QString getKeyToStr() { return m_keyWidget->getKeyToStr(); }
    void setEnableEdit(bool flag);
    QString getLabelText();
    void setText(const QString &text);

signals:
    void editedFinish();
    void shortCutError(const QString &curName, const QStringList &list, QString &name);

public slots:
    void doShortCutError(const QStringList &list, QString &name);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void updateSize();

private:
    Fcitx_ShortenLabel *m_label {nullptr};
    QHBoxLayout *m_hLayout {nullptr};
    Fcitx_KeyLabelWidget *m_keyWidget {nullptr};
};

class Fcitx_ComBoboxSettingsItem : public Fcitx_SettingsItem
{
    Q_OBJECT
public:
    Fcitx_ComBoboxSettingsItem(const QString &text, const QStringList &list = {}, QFrame *parent = nullptr);
    virtual ~Fcitx_ComBoboxSettingsItem();
    QComboBox *comboBox() { return m_combox; }
    QString getLabelText();

private:
    QHBoxLayout *m_mainLayout {nullptr};
    QComboBox *m_combox {nullptr};
    Fcitx_ShortenLabel *m_label {nullptr};
};
} // namespace widgets
} // namespace dcc_fcitx_configtool
#endif // KETSETTINGSITEM_H
