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

#ifndef IMSETTINGSITEM_H
#define IMSETTINGSITEM_H

#include "settingsitem.h"
#include "labels/shortenlabel.h"
#include <fcitxqtinputmethoditem.h>

namespace dcc_fcitx_configtool {
namespace widgets {

class Fcitx_IMSettingsItem : public Fcitx_SettingsItem
{
    Q_OBJECT

public:
    explicit Fcitx_IMSettingsItem(QString str = QString(), QFrame *parent = nullptr);
    ~Fcitx_IMSettingsItem();
    void setFcitxItem(const FcitxQtInputMethodItem &item);
    void setFilterStr(QString str);
    void setItemSelected(bool status);
signals:
    void itemClicked(Fcitx_IMSettingsItem *item);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

public:
    Fcitx_ShortenLabel *m_labelText {nullptr};
    QLabel *m_labelIcon {nullptr};
    QHBoxLayout *m_layout {nullptr};
    FcitxQtInputMethodItem m_item;
};
} // namespace widgets
} // namespace dcc_fcitx_configtool

#endif // IMSETTINGSITEM_H
