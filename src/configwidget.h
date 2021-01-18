/*****************************************************************************
*
* Copyright (C) 2020 Union Technology Co., Ltd.
*
* Author: Chen Shijie <chenshijie@uniontech.com>
*
* Maintainer:
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
*
*****************************************************************************/

#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include "dtkwidget_global.h"
#include <DWidget>

DWIDGET_USE_NAMESPACE

class configwidget : public DWidget
{
    Q_OBJECT

public:
    explicit configwidget(QWidget *parent = nullptr);
    ~configwidget();

private:
    void initUI();
};

#endif // CONFIGWIDGET_H
