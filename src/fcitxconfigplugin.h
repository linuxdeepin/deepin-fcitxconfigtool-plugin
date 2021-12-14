/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     liuwenhao <liuwenhao@uniontech.com>
*
* Maintainer: liuwenhao <liuwenhao@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef FCITXCONFIGPLUGIN_H
#define FCITXCONFIGPLUGIN_H

#include <interface/namespace.h>
#include <interface/moduleinterface.h>
#include <interface/frameproxyinterface.h>
#include <QObject>

class QTranslator;
class IMWindow;
class FcitxConfigPlugin : public QObject, public DCC_NAMESPACE::ModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ModuleInterface_iid FILE "api.json")
    Q_INTERFACES(DCC_NAMESPACE::ModuleInterface)

public:
    FcitxConfigPlugin();
    ~FcitxConfigPlugin() override;
    void deleteImWindow();

    virtual void preInitialize(bool sync = false, DCC_NAMESPACE::FrameProxyInterface::PushType = DCC_NAMESPACE::FrameProxyInterface::PushType::Normal) override;
    virtual void initialize() override;
    virtual const QString name() const override;
    virtual const QString displayName() const override;
    virtual QIcon icon() const override;
    virtual QString translationPath() const override;
    virtual QString path() const override;
    virtual QString follow() const override;
    virtual void deactive()override;
    virtual void addChildPageTrans() const override;
public Q_SLOTS:
    virtual void active() override;

protected:
    void initSearchData() override;
private:
    QTranslator  m_translator;
    IMWindow *m_imWindow;
};

#endif // DEEPINAIASSITANTCONTROLPLUGIN_H
