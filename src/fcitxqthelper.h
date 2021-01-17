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

#ifndef FCITXQTHELPER_H
#define FCITXQTHELPER_H

#include <QHash>
#include <QObject>

#include <fcitx-config/fcitx-config.h>

class FcitxQtKeyboardProxy;
class FcitxQtInputMethodProxy;
class FcitxQtConnection;

class FcitxQtHelper : public QObject
{
    Q_OBJECT
public:
    explicit FcitxQtHelper(QObject *parent = nullptr);
    ~FcitxQtHelper();

    static FcitxQtHelper *instance();

    FcitxConfigFileDesc *getConfigDesc(const QString &name);
    FcitxQtConnection *getConnection();
    FcitxQtInputMethodProxy *getInputMethodProxy();
    FcitxQtKeyboardProxy *getKeyboardProxy();

signals:
    void connectStatusChanged(bool connected);

private slots:
    void connected();
    void disconnected();

private:
    Q_DISABLE_COPY(FcitxQtHelper)

    QHash<QString, FcitxConfigFileDesc *>   configFileDescHash;
    FcitxQtConnection                       *connection = nullptr;
    FcitxQtInputMethodProxy                 *inputMethodProxy = nullptr;
    FcitxQtKeyboardProxy                    *keyboardProxy = nullptr;
};

#endif // FCITXQTHELPER_H
