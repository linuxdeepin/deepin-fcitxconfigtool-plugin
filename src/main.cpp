#include <iostream>
#include <DApplication>


#include <QDesktopWidget>
#include "widget.h"
using namespace std;
//using namespace keyboard;

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication *app = DApplication::globalApplication(argc, argv);
    app->setOrganizationName("deepin");
    app->setApplicationName("deepin-fcitxconfigtool-plugin");
    Widget widget;
    widget.resize(800,960);
    QDesktopWidget* desktop = QApplication::desktop();
    widget.move((desktop->width() - 800)/2, (desktop->height() - 960)/2);
    widget.show();



    return app->exec();
}
