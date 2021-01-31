#ifndef IMSETTINGWINDOW_H
#define IMSETTINGWINDOW_H

#include "widgets/comboxwidget.h"
#include "widgets/switchwidget.h"
#include "widgets/titlelabel.h"
#include "immodel/immodel.h"
#include <DListView>
#include <DFloatingButton>
#include <DKeySequenceEdit>
#include <DCommandLinkButton>

using namespace dcc::widgets;
using namespace Dtk::Widget;
class IMSettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMSettingWindow(QWidget *parent = nullptr);
    virtual ~IMSettingWindow();
    void updateUI();                                                //刷新界面
signals:
    void sig_popIMListWindow();                                     //弹出添加输入法界面
    void sig_updateIMList(const FcitxQtInputMethodItemList& list);  //更新输入法列表
private slots:
    void slot_defualtIMChanged(const QString &selected);            //修改默认输入法
    void slot_switchSystem(const bool& checked);                    //启用系统托盘
    void slot_editBtnClicked();                                     //启用编辑
    void slot_systemAppChanged(const QString &selected);            //切换系统/应用
private:
    void initUI();                                                  //初始化界面
    void initConnect();                                             //初始化信号槽
    void readConfig();                                              //读取配置文件
    void writeConfig();                                             //写入配置文件
private:
    ComboxWidget *m_defualtIMCbox{nullptr};                         //选择默认输入法
    SwitchWidget *m_switchSystem{nullptr};                          //启用系统托盘
    DCommandLinkButton *m_editBtn{nullptr};                         //编辑
    DListView *m_IMCurrentView{nullptr};                            //当前输入法列表
    IMModel *m_curIMModel{nullptr};                                 //当前输入法model
    ComboxWidget *m_imSwitchCbox{nullptr};                          //切换输入法（快捷键）
    DKeySequenceEdit*m_virtualKey{nullptr};                         //虚拟键盘 （快捷键）
    DKeySequenceEdit*m_defualtIMKey{nullptr};                       //默认输入法 （快捷键）
    ComboxWidget *m_systemAppCbox{nullptr};                         //切换系统/应用
    DFloatingButton *m_addIMBtn{nullptr};                           //添加输入法

};

#endif // IMSETTINGWINDOW_H
