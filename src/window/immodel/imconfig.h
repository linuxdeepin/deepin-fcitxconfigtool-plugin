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
