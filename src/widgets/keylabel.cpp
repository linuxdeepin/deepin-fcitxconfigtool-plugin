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

#include "keylabel.h"
#include <QStyle>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QApplication>

KeyLabel::KeyLabel(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
}

KeyLabel::KeyLabel(const QString &text, QWidget *parent)
    : KeyLabel(parent)
{
    QString t = text;
    if (t.isEmpty()) {
        t = tr("None");
    }

    setText(t);

    QFont font = qApp->font();
    QFontMetrics fm(font);

    setFixedWidth(fm.width(t) + 8);
}

void KeyLabel::paintEvent(QPaintEvent *event)
{
    //QLabel::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setOpacity(0.85);

    painter.setBrush(QColor(255, 255, 255));
    painter.setPen(Qt::NoPen);

    QFont font = qApp->font();
    QFontMetrics fm(font);
    int h = (height() - fm.height()) / 2 - 2;

    painter.drawRoundRect(rect().marginsRemoved(QMargins(0, h, 0, h)), 30, 30);

    painter.setPen(QColor("#359cd3"));
    painter.drawText(rect().marginsRemoved(QMargins(5, h + 2, 0, h)), text());
}
