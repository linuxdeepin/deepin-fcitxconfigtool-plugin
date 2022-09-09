// Copyright (C) 2011~2011 by CSSlayer                                   *
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef KCM_FCITX_GLOBAL_H
#define KCM_FCITX_GLOBAL_H

// Qt
#include <QHash>
#include <QTimer>

// Fcitx
#include <fcitx-config/fcitx-config.h>
#include <fcitxqtinputmethodproxy.h>
#include <fcitxqtkeyboardproxy.h>

class FcitxQtKeyboardProxy;
class FcitxQtInputMethodProxy;
class FcitxQtConnection;
namespace Fcitx {

class Global : public QObject
{
    Q_OBJECT
public:
    static Global *instance();
    static void deInit();
    virtual ~Global();
    FcitxConfigFileDesc *GetConfigDesc(const QString &name);
    FcitxQtConnection *connection() { return m_connection; }
    FcitxQtInputMethodProxy *inputMethodProxy() { return (m_inputmethod && m_inputmethod->isValid()) ? m_inputmethod : 0; }
    FcitxQtKeyboardProxy *keyboardProxy() { return (m_keyboard && m_keyboard->isValid()) ? m_keyboard : 0; }
    QString testWrapper(const QString &path) const;

signals:
    void connectStatusChanged(bool connected);

private slots:
    void connected();
    void disconnected();

private:
    Global();
    QHash<QString, FcitxConfigFileDesc *> *m_hash;
    FcitxQtConnection *m_connection;
    FcitxQtInputMethodProxy *m_inputmethod;
    FcitxQtKeyboardProxy *m_keyboard;
    static Global *inst;
    QTimer *m_timer;
};

} // namespace Fcitx

#endif
