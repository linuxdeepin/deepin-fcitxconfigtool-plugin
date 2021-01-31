#ifndef IMWIDOW_H
#define IMWIDOW_H
#include "imaddwindow.h"
#include "imsettingwindow.h"
#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>

class IMWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMWindow(QWidget *parent = nullptr);
    virtual ~IMWindow();
private:
    void initUI();                      //初始化界面
    void initConnect();                 //初始化信号槽
    void initFcitxInterface();          //初始化fcitx接口
private:
    QStackedWidget *m_stackedWidget{};  //栈窗口
    IMSettingWindow *m_settingWindow{}; //输入法编辑窗口
    IMAddWindow *m_addWindow{};         //输入法添加窗口
};

#endif // IMWIDOW_H
