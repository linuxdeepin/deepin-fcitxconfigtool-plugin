/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
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

#ifndef SETTINGSHEAD_H
#define SETTINGSHEAD_H

#include "settingsitem.h"
#include "titlelabel.h"
#include <QPushButton>

DWIDGET_BEGIN_NAMESPACE
class DCommandLinkButton;
DWIDGET_END_NAMESPACE
class QGSettings;
namespace dcc_fcitx_configtool {
namespace widgets {

class FcitxNormalLabel;

class FcitxSettingsHead : public FcitxSettingsItem
{
    Q_OBJECT

public:
    enum State {
        Edit,
        Cancel
    };

public:
    explicit FcitxSettingsHead(QFrame *parent = nullptr);
    ~FcitxSettingsHead();

    void setTitle(const QString &title);
    void setEditEnable(bool state = true);
    FcitxTitleLabel* getTitleLabel();
public Q_SLOTS:
    void toEdit();
    void toCancel();
    void setEdit(bool flag);

Q_SIGNALS:
    void editChanged(bool edit);

private Q_SLOTS:
    void refershButton();
    void onClicked();
    void onStatusModeChanged(const QString &key);
private:
    FcitxTitleLabel *m_title;
    DTK_WIDGET_NAMESPACE::DCommandLinkButton *m_edit;
    bool m_editVisible;
    QGSettings *m_gsetting;
    State m_state;
};

} // namespace widgets
} // namespace dcc_fcitx_configtool

#endif // SETTINGSHEAD_H
