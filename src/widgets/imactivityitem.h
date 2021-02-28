#ifndef IMACTIVITYITEM_H
#define IMACTIVITYITEM_H
#include "settingsitem.h"
#include "labels/shortenlabel.h"
#include <fcitxqtinputmethoditem.h>
#include <DToolButton>
using namespace dcc_fcitx_configtool::widgets;
using namespace Dtk::Widget;
namespace dcc_fcitx_configtool {
namespace widgets {

class ToolButton : public QToolButton
{
    Q_OBJECT
public:
    ToolButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e) override;
};

class IMActivityItem : public SettingsItem
{
    Q_OBJECT
public:
    IMActivityItem(FcitxQtInputMethodItem item, bool isFirst = false, QFrame *parent = nullptr);
    ~IMActivityItem();
    void editSwitch(bool flag);
    void setSelectStatus(bool flag);
    void onUpItem();
    void onDownItem();
    void onConfigItem();
    void onDeleteItem();
signals:
    void upBtnClicked(FcitxQtInputMethodItem);
    void downBtnClicked(FcitxQtInputMethodItem);
    void configBtnClicked(FcitxQtInputMethodItem);
    void deleteBtnClicked(FcitxQtInputMethodItem);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

public:
    FcitxQtInputMethodItem m_item;
    ShortenLabel *m_labelText {nullptr};
    QHBoxLayout *m_layout {nullptr};
    ToolButton *m_upBtn {nullptr};
    ToolButton *m_downBtn {nullptr};
    DToolButton *m_configBtn {nullptr};
    DToolButton *m_deleteBtn {nullptr};
    bool m_isFirst {false};
    bool m_isEdit {false};
};

} // namespace widgets
} // namespace dcc_fcitx_configtool

#endif // IMACTIVITYITEM_H
