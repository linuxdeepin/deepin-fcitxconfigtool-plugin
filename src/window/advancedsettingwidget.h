/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     zhaoyue <zhaoyue@uniontech.com>
*
* Maintainer: zhaoyue <zhaoyue@uniontech.com>
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

#ifndef FCITXCONFIGPAGE_H
#define FCITXCONFIGPAGE_H

// Qt
#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QMap>
#include <QLabel>

// Fcitx
#include <fcitx-config/fcitx-config.h>
#include <fcitx-config/hotkey.h>
#include <fcitx/addon.h>

class QCheckBox;
class QVBoxLayout;
class QStandardItemModel;
struct _FcitxConfigFileDesc;

class QTabWidget;

namespace Fcitx
{
class DummyConfig;
class Global;

/**
 * @class DeleteItemThread
 * @brief
 */
class AdvancedSettingWidget : public QWidget
{
    Q_OBJECT

    enum UIType {
        CW_Simple = 0x1,
        CW_Full = 0x2,
        CW_NoShow = 0x0
    };

public:
    explicit AdvancedSettingWidget(QWidget* parent = nullptr);
    virtual ~AdvancedSettingWidget();
    DummyConfig* config() { return m_config; }
private:
    QWidget* createConfigUi();
    void setupConfigUi();
    void createConfigOptionWidget(FcitxConfigGroupDesc* cgdesc, FcitxConfigOptionDesc* codesc, QString& label, QString& tooltip, QWidget*& inputWidget, void*& newarg);
    void getConfigDesc(const QString &name);

private:
    QHash<QString, FcitxConfigFileDesc *> *m_hash;
    struct _FcitxConfigFileDesc* m_cfdesc;
    QString m_prefix;
    QString m_name;
    QString m_addonName;
    QVBoxLayout* m_globalSettingsLayout;
    QVBoxLayout* m_addOnsLayout;
    QWidget* m_widget {nullptr};
    QWidget* m_fullWidget {nullptr};
    DummyConfig* m_config {nullptr};
    UIType m_simpleUiType;
    UIType m_fullUiType;
    QMap<QString, void*> m_argsMap;

};

class arrowButton : public QLabel
{
    Q_OBJECT
public:
    explicit arrowButton(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *ev) override;
signals:
    void pressed(bool isHidden);
private:
    bool m_hide{false};
};

}

#endif
