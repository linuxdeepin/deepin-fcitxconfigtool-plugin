/*

* Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.

*

* Author:     lwh <liuwenhao@uniontech.com>

*

* Maintainer: lwh <liuwenhao@uniontech.com>

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
#include <fcitxqtinputmethoditem.h>
using namespace dcc::widgets;

namespace dcc {
namespace widgets {

class IMSettingsItem : public SettingsItem
{
    Q_OBJECT

public:
    explicit IMSettingsItem(QString str =QString(),QFrame *parent = nullptr);
    ~IMSettingsItem();
    void setFcitxItem(FcitxQtInputMethodItem item);
    void setFilterStr(QString str);
    void addBackground();
    void setItemSelected(bool status);
signals:
    void sig_itemClicked(IMSettingsItem*item);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event)override;
    void enterEvent(QEvent *event)override;
    void leaveEvent(QEvent *event)override;

public:
    QLabel *m_labelText{nullptr};
    QLabel *m_labelIcon{nullptr};
    QHBoxLayout*m_layout{nullptr};
    FcitxQtInputMethodItem m_item;

};

}
}
#endif // IMSETTINGSITEM_H

