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

#include <fcitx-config/fcitx-config.h>
#include <fcitxqtinputmethodproxy.h>
#include <fcitxqtkeyboardproxy.h>
#include <fcitxqtconnection.h>
#include "fcitxqthelper.h"

Q_GLOBAL_STATIC(FcitxQtHelper, staticFcitxQtHelper)

FcitxQtHelper::FcitxQtHelper(QObject *parent) : QObject(parent)
{
    connection = new FcitxQtConnection(this);

    connect(connection, &FcitxQtConnection::connected, this, &FcitxQtHelper::connected);
    connect(connection, &FcitxQtConnection::disconnected, this, &FcitxQtHelper::disconnected);

    connection->startConnection();
}

FcitxQtHelper::~FcitxQtHelper()
{
    QHash<QString, FcitxConfigFileDesc *>::iterator iter;
    for (iter = configFileDescHash.begin(); iter != configFileDescHash.end(); iter ++) {
        FcitxConfigFreeConfigFileDesc(iter.value());
    }
}

FcitxQtHelper *FcitxQtHelper::instance()
{
    return staticFcitxQtHelper;
}

FcitxQtConnection *FcitxQtHelper::getConnection()
{
    return connection;
}

FcitxQtInputMethodProxy *FcitxQtHelper::getInputMethodProxy()
{
    return (inputMethodProxy && inputMethodProxy->isValid()) ? inputMethodProxy : nullptr;
}

FcitxQtKeyboardProxy *FcitxQtHelper::getKeyboardProxy()
{
    return (keyboardProxy && keyboardProxy->isValid()) ? keyboardProxy : nullptr;
}

void FcitxQtHelper::connected()
{
    if (nullptr != inputMethodProxy) {
        delete inputMethodProxy;
    }

    if (nullptr != keyboardProxy) {
        delete keyboardProxy;
    }

    qDebug() << connection->isConnected();

    inputMethodProxy = new FcitxQtInputMethodProxy(connection->serviceName(), "/inputmethod",
                                                   *connection->connection(), this);
    if (false == inputMethodProxy->isValid()) {
        qDebug() << inputMethodProxy->lastError();
    }
    inputMethodProxy->setTimeout(3000);

    keyboardProxy = new FcitxQtKeyboardProxy(connection->serviceName(), "/keyboard",
                                             *connection->connection(), this);
    if (false == keyboardProxy->isValid()) {
        qDebug() << keyboardProxy->lastError();
    }

    keyboardProxy->setTimeout(3000);

    emit connectStatusChanged(true);
}

void FcitxQtHelper::disconnected()
{
    if (nullptr != inputMethodProxy) {
        delete inputMethodProxy;
        inputMethodProxy = nullptr;
    }

    if (nullptr != keyboardProxy) {
        delete keyboardProxy;
        keyboardProxy = nullptr;
    }

    emit connectStatusChanged(false);
}

FcitxConfigFileDesc *FcitxQtHelper::getConfigDesc(const QString &name)
{
    if (configFileDescHash.count(name) <= 0) {
        FILE *fp = FcitxXDGGetFileWithPrefix("configdesc", name.toLatin1().constData(), "r", nullptr);
        FcitxConfigFileDesc *cfdesc =  FcitxConfigParseConfigFileDescFp(fp);
        if (nullptr != cfdesc) {
            configFileDescHash.insert(name, cfdesc);
        }
        return cfdesc;
    } else {
        return configFileDescHash.value(name);
    }
}
