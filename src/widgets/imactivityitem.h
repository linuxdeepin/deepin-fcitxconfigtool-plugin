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

#ifndef IMACTIVITYITEM_H
#define IMACTIVITYITEM_H
#include "settingsitem.h"
#include "labels/shortenlabel.h"
#include "labels/clicklabel.h"
#include <fcitxqtinputmethoditem.h>
#include <DToolButton>

using namespace dcc_fcitx_configtool::widgets;
using namespace Dtk::Widget;
namespace dcc_fcitx_configtool {
namespace widgets {

class ToolButton : public DToolButton
{
    Q_OBJECT
public:
    using DToolButton::DToolButton;

protected:
    void paintEvent(QPaintEvent *e) override;
};

class FcitxIMActivityItem : public FcitxSettingsItem
{
    Q_OBJECT
public:
    FcitxIMActivityItem(FcitxQtInputMethodItem item, QFrame *parent = nullptr);
    ~FcitxIMActivityItem();
    void editSwitch(const bool &flag);
    void setSelectStatus(const bool &flag);

signals:
    void upBtnClicked(FcitxQtInputMethodItem);
    void downBtnClicked(FcitxQtInputMethodItem);
    void configBtnClicked(FcitxQtInputMethodItem);
    void deleteBtnClicked(FcitxQtInputMethodItem);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onUpItem();
    void onDownItem();
    void onConfigItem();
    void onDeleteItem();

public:
    FcitxQtInputMethodItem m_item;
    FcitxShortenLabel *m_labelText {nullptr};
    QHBoxLayout *m_layout {nullptr};
    DToolButton *m_upBtn {nullptr};
    DToolButton *m_downBtn {nullptr};
    DToolButton *m_configBtn {nullptr};
    ClickLabel *m_deleteLabel {nullptr};
    bool m_isEdit {false};
};

} // namespace widgets
} // namespace dcc_fcitx_configtool

#endif // IMACTIVITYITEM_H
