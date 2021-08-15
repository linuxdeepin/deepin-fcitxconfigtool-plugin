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
#include "DLineEdit"
#include <QComboBox>
#include <QPushButton>

using namespace Dtk::Widget;
using namespace dcc_fcitx_configtool::widgets;
namespace dcc_fcitx_configtool {
namespace widgets {

class FcitxKeyLabelWidget : public QWidget
{
    Q_OBJECT
public:
    FcitxKeyLabelWidget(QStringList list = {}, QWidget *p = nullptr);
    virtual ~FcitxKeyLabelWidget();
    void setKeyId(const QString &id);
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
    QList<FcitxKeyLabel *> m_list;
    QString m_id;
    QStringList m_curlist;
    QStringList m_newlist;
    bool m_eidtFlag;
};

class FcitxKeySettingsItem : public FcitxSettingsItem
{
    Q_OBJECT
public:
    FcitxKeySettingsItem(const QString &text = "", const QStringList &list = {}, QFrame *parent = nullptr);
    void setKeyId(const QString &id);
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
    FcitxShortenLabel *m_label {nullptr};
    QHBoxLayout *m_hLayout {nullptr};
    FcitxKeyLabelWidget *m_keyWidget {nullptr};
};

class FcitxComBoboxSettingsItem : public FcitxSettingsItem
{
    Q_OBJECT
public:
    FcitxComBoboxSettingsItem(const QString &text, const QStringList &list = {}, QFrame *parent = nullptr);
    virtual ~FcitxComBoboxSettingsItem();
    QComboBox *comboBox() { return m_combox; }
    QString getLabelText();

private:
    QHBoxLayout *m_mainLayout {nullptr};
    QComboBox *m_combox {nullptr};
    FcitxShortenLabel *m_label {nullptr};
};

class FcitxPushButtonSettingsItem : public FcitxSettingsItem
{
    Q_OBJECT
public:
    FcitxPushButtonSettingsItem(const QString &text, const QStringList &list = {}, QFrame *parent = nullptr);
    virtual ~FcitxPushButtonSettingsItem();
    QPushButton *pushbutton() { return m_pushbutton; }

private:
    QHBoxLayout *m_mainLayout {nullptr};
    QPushButton *m_pushbutton {nullptr};
};
} // namespace widgets
} // namespace dcc_fcitx_configtool
#endif // KETSETTINGSITEM_H
