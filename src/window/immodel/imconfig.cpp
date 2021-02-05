#include "imconfig.h"
#include "publisher/publisherfunc.h"
#include <QDebug>
QString IMConfig::prefix {QDir::homePath()};
QString IMConfig::defualtIM()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", QString("IMNAME"));
}

bool IMConfig::setDefualtIM(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", "IMNAME", str, false);
}

QString IMConfig::IMSwitch()
{
    return configFile(prefix + "/.config/fcitx/config", QString("IMSwitchHotkey"));
}

bool IMConfig::setIMSwitch(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/config", "IMSwitchHotkey", str, false);
}

QString IMConfig::virtualKey()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-onboard.config", QString("HOTKEY")).replace("_", "+");
}

bool IMConfig::setVirtualKey(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-onboard.config", "HOTKEY", str, true);
}

QString IMConfig::defualtIMKey()
{
    return configFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", QString("HOTKEY")).replace("_", "+");
}

bool IMConfig::setDefualtIMKey(QString str)
{
    return setConfigFile(prefix + "/.config/fcitx/conf/fcitx-defaultim.config", "HOTKEY", str, true);
}

QString IMConfig::IMConfigCmd(FcitxQtInputMethodItem item)
{
    return QString();
}

QString IMConfig::configFile(QString filePath, QString key)
{
    if (prefix.isEmpty())
        return QString();
    QString read = publisherFunc::readFile(filePath);
    foreach (QString str, read.split("\n")) {
        if (str.indexOf(key) != -1) {
            auto list = str.split("=");
            if (list.count() != 2) {
                return QString();
            } else {
                qDebug() << list;
                return list[1];
            }
        }
    }
    return QString();
}

bool IMConfig::setConfigFile(QString filePath, QString key, QString value, bool isHotKey)
{
    if (prefix.isEmpty())
        return false;
    QString read = publisherFunc::readFile(filePath);
    QString file;
    foreach (QString tmp, read.split("\n")) {
        if (tmp.indexOf(key) != -1) {
            if (isHotKey)
                file += QString(key + "=" + value + "\n").replace("+", "_").toUpper();
            else {
                file += QString(key + "=" + value + "\n");
            }
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
