// Copyright (C) 2012~2012 by CSSlayer                                   *
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VERTICALSCROLLAREA_H
#define VERTICALSCROLLAREA_H

#include <QScrollArea>
namespace Fcitx
{
class VerticalScrollArea : public QScrollArea {
    Q_OBJECT
public:
    explicit VerticalScrollArea(QWidget* parent = 0);
    void setWidget(QWidget *widget);
protected:
    virtual bool eventFilter(QObject* o, QEvent* e);
};
}

#endif // VERTICALSCROLLAREA_H