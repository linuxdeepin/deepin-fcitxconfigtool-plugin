#include <DApplication>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DMainWindow>
#include "window/imwindow.h"
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    //DApplication::loadDXcbPlugin();
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    a.setOrganizationName("deepin");
    a.setApplicationName("deepin-fcitxconfigtool-plugin");
    a.setApplicationVersion("1.0");
    a.setProductIcon(QIcon());
    a.setProductName("deepin-fcitxconfigtool-plugin");
    a.setApplicationDescription("This is a dtk deepin-fcitxconfigtool-plugin");
    a.loadTranslator();
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "deepin-fcitxconfigtool-plugin"));

    IMWindow w;
    w.show();
    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
