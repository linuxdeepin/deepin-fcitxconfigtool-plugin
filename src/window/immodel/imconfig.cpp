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
#include "imconfig.h"
#include "publisher/publisherfunc.h"
#include <fcitxqtinputmethoditem.h>
#include <com_deepin_daemon_keybinding.h>

QString IMConfig::prefix {QDir::homePath()};

QString IMConfig::defaultIM()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", QString("IMNAME"));
}

bool IMConfig::setDefaultIM(const QString &str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", "IMNAME", str);
}

QString IMConfig::IMSwitchKey()
{
    return configFile(prefix + "/.config/fcitx/config", QString("IMSwitchHotkey"));
}

bool IMConfig::setIMSwitchKey(const QString &str)
{
    return setConfigFile(prefix + "/.config/fcitx/config", "IMSwitchHotkey", str);
}

QString IMConfig::virtualKey()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-onboard.config", QString("HOTKEY"));
}

bool IMConfig::setVirtualKey(const QString &str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-onboard.config", "HOTKEY", str);
}

QString IMConfig::defaultIMKey()
{
    QString ret = configFile(prefix + "/.config/fcitx/config", QString("TriggerKey"));
    if (ret.isEmpty()) {
        ret = "CTRL_SPACE";
    }
    return ret;
}

bool IMConfig::setDefaultIMKey(const QString &str)
{
    return setConfigFile(prefix + "/.config/fcitx/config", "TriggerKey", str);
}

QString IMConfig::IMPluginKey(const QString &str)
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-implugin.config", str, QString("Setting"));
}

QString IMConfig::IMPluginPar(const QString &str)
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-implugin.config", str, QString("Parameter"));
}

bool IMConfig::checkShortKey(const QStringList &str, QString &configName)
{
    if (str.count() > 3)
        return false;
    QString keyStr;
    for (int i = 0; i < str.count(); ++i) {
        if (i + 1 == str.count()) {
            keyStr += str[i];
        } else {
            keyStr += (str[i] + "_");
        }
    }
    keyStr = keyStr.toUpper();

    return checkShortKey(keyStr, configName);
}

FcitxShortcutInfo IMConfig::findIdKey(const QString &shortcutId)
{
    FcitxShortcutInfo retshortcut;
    retshortcut.id = -1;
    retshortcut.name = "-1";
    retshortcut.type = -1;
    retshortcut.accels = "";

    __Keybinding k("com.deepin.daemon.Keybinding",
                   "/com/deepin/daemon/Keybinding",
                   QDBusConnection::sessionBus());

    QDBusPendingReply<QString> reply = k.ListAllShortcuts();
    if (reply.isError()) {
        return retshortcut;
    }

    QString info = reply.value();

    QMap<QString, FcitxShortcutInfo> map;
    QJsonArray array = QJsonDocument::fromJson(info.toStdString().c_str()).array();
    Q_FOREACH (QJsonValue value, array) {
        QJsonObject obj = value.toObject();
        //qDebug() << obj;
        if (obj.isEmpty())
            continue;
        if (obj["Accels"].toArray().isEmpty())
            continue;
        FcitxShortcutInfo shortcut;
        QString Id = obj["Id"].toString();
        if (Id == shortcutId) {
            QString accels = obj["Accels"].toArray().at(0).toString().toUpper();
            accels.replace("<", "");
            accels.replace(">", "_");
            shortcut.accels = accels;
            shortcut.id = obj["Id"].toString();
            shortcut.name = obj["Name"].toString();
            shortcut.type = obj["Type"].toInt();
            map.insert(accels, shortcut);
            return shortcut;
        }
    }

    return retshortcut;
}

bool IMConfig::modifyShortKey(const QString &id, QString &keystroke)
{
    QString name;
    QString cmd;
    if (id.compare("terminal") == 0) {
        name = "终端";
        cmd = "echo hello";
    } else if (id.compare("system-monitor") == 0) {
        name = "系统镜像";
        cmd = "echo world";
    }

    __Keybinding k("com.deepin.daemon.Keybinding",
                   "/com/deepin/daemon/Keybinding",
                   QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = k.ModifyCustomShortcut(id, name, cmd, keystroke);
    if (reply.isError()) {
        return false;
    }
    return true;
}

bool addCustomShortKey(const QString &name, const QString &action, QString &keystroke)
{
    __Keybinding k("com.deepin.daemon.Keybinding",
                   "/com/deepin/daemon/Keybinding",
                   QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = k.AddCustomShortcut(name, action, keystroke);
    if (reply.isError()) {
        return false;
    }
    QString info = reply.value();

    QString id;
    int type;
    QJsonArray array = QJsonDocument::fromJson(info.toStdString().c_str()).array();
    Q_FOREACH (QJsonValue value, array) {
        QJsonObject obj = value.toObject();
        if (obj.isEmpty())
            continue;
//        if (obj["Accels"].toArray().isEmpty())
//            continue;
        id = obj["Id"].toString();
        type = obj["Type"].toInt();
    }

    return true;
}


bool IMConfig::checkShortKey(const QString &keyStr, QString &configName)
{
    __Keybinding k("com.deepin.daemon.Keybinding",
                   "/com/deepin/daemon/Keybinding",
                   QDBusConnection::sessionBus());

    QDBusPendingReply<QString> reply = k.ListAllShortcuts();
    if (reply.isError()) {
        return false;
    }

    QString info = reply.value();

    QMap<QString, FcitxShortcutInfo> map;
    QJsonArray array = QJsonDocument::fromJson(info.toStdString().c_str()).array();
    Q_FOREACH (QJsonValue value, array) {
        QJsonObject obj = value.toObject();
        //qDebug() << obj;
        if (obj.isEmpty())
            continue;
        if (obj["Accels"].toArray().isEmpty())
            continue;
        FcitxShortcutInfo shortcut;
        QString Id = obj["Id"].toString();
        QString accels = obj["Accels"].toArray().at(0).toString().toUpper();
        accels.replace("<", "");
        accels.replace(">", "_");
        shortcut.accels = accels;
        shortcut.id = obj["Id"].toString();
        shortcut.name = obj["Name"].toString();
        shortcut.type = obj["Type"].toInt();
        map.insert(accels, shortcut);
    }

//    FcitxShortcutInfo defaultIMInfo;
//    FcitxShortcutInfo virtualKeyInfo;
//    FcitxShortcutInfo IMSwitchKeyInfo;
//    defaultIMInfo.id = "defaultIMKey";
//    defaultIMInfo.name = "defaultIMKey";
//    defaultIMInfo.type = -1;
//    defaultIMInfo.accels = IMConfig::defaultIMKey();

//    virtualKeyInfo.id = "virtualKey";
//    virtualKeyInfo.name = "virtualKey";
//    virtualKeyInfo.type = -1;
//    virtualKeyInfo.accels = IMConfig::virtualKey();

//    IMSwitchKeyInfo.id = "IMSwitchKey";
//    IMSwitchKeyInfo.name = "IMSwitchKey";
//    IMSwitchKeyInfo.type = -1;
//    IMSwitchKeyInfo.accels = IMConfig::IMSwitchKey();

//    map.insert(defaultIMInfo.accels, defaultIMInfo);
//    map.insert(virtualKeyInfo.accels, virtualKeyInfo);
//    map.insert(IMSwitchKeyInfo.accels, IMSwitchKeyInfo);

    //    qDebug() << defaultIMInfo.toString();
    //    qDebug() << virtualKeyInfo.toString();
    //    qDebug() << IMSwitchKeyInfo.toString();
    for (auto it : map) {
        qDebug() << it.accels;
    }

    if (map.find(keyStr) != map.end()) {
        configName = map.find(keyStr).value().name;
        return false;
    }
    configName = nullptr;
    return true;
}

QString IMConfig::configFile(const QString &filePath, const QString &group, const QString &key)
{
    QString read = publisherFunc::readFile(filePath);
    if (read.isEmpty() || key.isEmpty())
        return QString();

    bool lock = false;
    foreach (QString str, read.split("\n")) {
        if (!lock && str.indexOf(group) != -1) {
            lock = true;
        }
        if (lock && str.indexOf(key) != -1) {
            auto list = str.split("=");

            if (list[0].compare(key) != 0 && list[0].compare('#' + key) != 0) {
                continue;
            }

            if (list.count() != 2) {
                return QString();
            } else {
                return list[1];
            }
        }
    }
    return QString();
}

QString IMConfig::configFile(const QString &filePath, const QString &key)
{
    QString read = publisherFunc::readFile(filePath);
    if (read.isEmpty() || key.isEmpty())
        return QString();

    foreach (QString str, read.split("\n")) {
        if (str.indexOf(key) != -1) {
            auto list = str.split("=");
            if (list.count() != 2) {
                return QString();
            } else {
                return list[1];
            }
        }
    }
    return QString();
}

bool IMConfig::setConfigFile(const QString &filePath, const QString &key, const QString &value)
{
    QString read = publisherFunc::readFile(filePath);
    if (read.isEmpty() || key.isEmpty() || value.isEmpty())
        return false;

    QString file;
    foreach (QString tmp, read.split("\n")) {
        if (tmp.indexOf(key) != -1) {
            file += QString(key + "=" + value + "\n");
        } else {
            if (!tmp.isEmpty())
                file += tmp + "\n";
        }
    }
    file = file + "\n";
    if (file.isEmpty())
        return false;
    else {
        return publisherFunc::createFile(filePath, file);
    }
}
