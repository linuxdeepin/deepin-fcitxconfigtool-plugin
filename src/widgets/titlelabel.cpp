/*
 * Copyright (C) 2011 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     lq <longqi_cm@deepin.com>
 *
 * Maintainer: lq <longqi_cm@deepin.com>
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

#include "titlelabel.h"

#include <DFontSizeManager>

#include <QFont>
#include <QEvent>

DWIDGET_USE_NAMESPACE

Fcitx_TitleLabel::Fcitx_TitleLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    auto tf = this->font();
    tf.setWeight(QFont::Medium);
    setFont(tf);

    DFontSizeManager::instance()->bind(this, DFontSizeManager::T5);
}

Fcitx_TitleLabel::Fcitx_TitleLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : Fcitx_TitleLabel(parent, f)
{
    setText(text);
}

bool Fcitx_TitleLabel::event(QEvent *e)
{
    if (e->type() == QEvent::ApplicationFontChange) {
        auto tf = this->font();
        tf.setWeight(QFont::Medium);
        setFont(tf);
    }

    return QLabel::event(e);
}
