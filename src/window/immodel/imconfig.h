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
#ifndef IMCONFIG_H
#define IMCONFIG_H
#include <QDir>
#include <QObject>
#include <fcitxqtinputmethoditem.h>
//默认输入法 切换方式 虚拟键盘 默认输入法快捷键
class IMConfig
{
public:
    static QString defualtIM();
    static bool setDefualtIM(QString);
    static QString IMSwitch();
    static bool setIMSwitch(QString);
    static QString virtualKey();
    static bool setVirtualKey(QString);
    static QString defualtIMKey();
    static bool setDefualtIMKey(QString);
    static QString IMConfigCmd(FcitxQtInputMethodItem item);
    static QString prefix;

private:
    static QString configFile(QString filePath, QString key);
    static bool setConfigFile(QString filePath, QString key, QString value, bool isHotKey);
};

#endif // IMCONFIG_H
