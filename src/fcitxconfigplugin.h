﻿#ifndef FCITXCONFIGPLUGIN_H
#define FCITXCONFIGPLUGIN_H

#include <interface/namespace.h>
#include <interface/moduleinterface.h>
#include <interface/frameproxyinterface.h>
#include <QObject>
#include <QTranslator>

class IMWindow;
class FcitxConfigPlugin : public QObject, public DCC_NAMESPACE::ModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ModuleInterface_iid FILE "api.json")
    Q_INTERFACES(DCC_NAMESPACE::ModuleInterface)

public:
    FcitxConfigPlugin() ;
    ~FcitxConfigPlugin() override;

    virtual void preInitialize(bool sync = false);
    virtual void initialize() override;
    virtual const QString name() const override;
    virtual const QString displayName() const override;
    virtual QIcon icon() const override;
    virtual QString translationPath() const override;
    virtual QString path() const override;
    virtual QString follow() const override;
    virtual void deactive()override;

public Q_SLOTS:
    virtual void active() override;

private:
    QTranslator  m_translator;
    IMWindow *imWindow;

};

#endif // DEEPINAIASSITANTCONTROLPLUGIN_H
