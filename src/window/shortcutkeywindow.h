#ifndef SHORTCUTKEYWINDOW_H
#define SHORTCUTKEYWINDOW_H
#include "fcitxInterface/global.h"
#include "window/immodel/imconfig.h"
#include "widgets/buttontuple.h"

#include <QSpacerItem>
#include <QWidget>
#include <QLabel>
namespace dcc_fcitx_configtool {
namespace widgets {
class Fcitx_SettingsGroup;
class Fcitx_KeySettingsItem;
class Fcitx_ButtonTuple;
} // namespace widgets
} // namespace dcc_fcitx_configtool

class ShortcutKeyWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ShortcutKeyWindow(QWidget *parent = nullptr);
    ~ShortcutKeyWindow();
    void initUI();
    void initConnect();
    void setBottomTip();
    void setKeySettings();
    void setLabelText();

signals:
    void popSettingsWindow(); //弹出设置窗口

public slots:
    void setValue(QString curName, QString conflictName, QString shortCut);

private:
//    dcc_fcitx_configtool::widgets::Fcitx_SettingsGroup *m_shortcutGroup;
//    dcc_fcitx_configtool::widgets::Fcitx_KeySettingsItem *m_keySettingsItem;
//    dcc_fcitx_configtool::widgets::Fcitx_ButtonTuple *m_buttonTuple;
//    QLabel *m_bottomTip;
//    QPushButton *cancel;
//    QString m_log;
//    QString m_curName;
//    QString m_conflictName;
//    QString m_shortCut;
};
#endif // SHORTCUTKEYWINDOW_H
