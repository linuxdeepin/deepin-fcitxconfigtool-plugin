<<<<<<< HEAD
=======
#include "window/immodel/immodel.h"
>>>>>>> cdc386b... feat: 添加输入法界面完成
#include <DApplication>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DMainWindow>
#include "window/imwindow.h"
#include <QVBoxLayout>
<<<<<<< HEAD

DWIDGET_USE_NAMESPACE

=======
#include <thread>

DWIDGET_USE_NAMESPACE

void testUpdate();
using namespace std;
>>>>>>> cdc386b... feat: 添加输入法界面完成
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
<<<<<<< HEAD
    Dtk::Widget::moveToCenter(&w);
=======
    //Dtk::Widget::moveToCenter(&w);

    TestIMModel::testIMModel();
    //TestIMModel::testItemSwap();
>>>>>>> cdc386b... feat: 添加输入法界面完成

    return a.exec();
}
