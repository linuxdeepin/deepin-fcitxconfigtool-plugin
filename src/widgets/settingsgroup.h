/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
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

#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <DBackgroundGroup>

#include <QFrame>
#include <QTimer>

#include "translucentframe.h"

class QVBoxLayout;

DWIDGET_USE_NAMESPACE

namespace dcc_fcitx_configtool {
namespace widgets {

class Fcitx_SettingsItem;
class Fcitx_SettingsHeaderItem;
class Fcitx_SettingsHead;

class Fcitx_SettingsGroup : public Fcitx_TranslucentFrame
{
    Q_OBJECT

public:
    enum BackgroundStyle {
        ItemBackground = 0,
        GroupBackground,
        NoneBackground
    };

    explicit Fcitx_SettingsGroup(QFrame *parent = nullptr, BackgroundStyle bgStyle = ItemBackground);
    explicit Fcitx_SettingsGroup(const QString &title, QFrame *parent = nullptr);
    ~Fcitx_SettingsGroup();

    Fcitx_SettingsHeaderItem *headerItem() { return m_headerItem; }
    void setHeaderVisible(const bool visible);

    Fcitx_SettingsItem *getItem(int index);
    void insertWidget(QWidget *widget);
    void insertItem(const int index, Fcitx_SettingsItem *item);
    void appendItem(Fcitx_SettingsItem *item);
    void appendItem(Fcitx_SettingsItem *item, BackgroundStyle bgStyle);
    void removeItem(Fcitx_SettingsItem *item);
    void moveItem(Fcitx_SettingsItem *item, const int index);
    void setSpacing(const int spaceing);

    int itemCount() const;
    void clear();
    QVBoxLayout *getLayout() const { return m_layout; }

private:
    BackgroundStyle m_bgStyle {ItemBackground};
    QVBoxLayout *m_layout;
    Fcitx_SettingsHeaderItem *m_headerItem;
    DTK_WIDGET_NAMESPACE::DBackgroundGroup *m_bggroup {nullptr};
};

} // namespace widgets
} // namespace dcc_fcitx_configtool

#endif // SETTINGSGROUP_H
