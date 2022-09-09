// Copyright (C) 2012~2012 by CSSlayer                                   *
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DUMMYCONFIG_H
#define DUMMYCONFIG_H

#include <fcitx-config/fcitx-config.h>
#include <stdio.h>
#include <QMap>
#include <QString>

namespace Fcitx {

/**
 * @class DummyConfig
 * @brief 配置文件读取类
 */
class DummyConfig
{
public:
    DummyConfig();
    ~DummyConfig();
    void setConfigDesc(FcitxConfigFileDesc *cfdesc);

    FcitxGenericConfig *genericConfig();

    /**
     *@brief 读取配置文件，填入结构体
     */
    void load(FILE *fp);

    /**
     *@brief 使用结构体绑定值
     */
    void bind(char *group, char *option, FcitxSyncFilter filter = nullptr, void *arg = nullptr);
    bool isValid();

    /**
     *@brief 文件修改后调用此函数，刷新界面
     */
    void configSyncToUi();

    /**
     *@brief 获取配置文件结构体指针
     */
    FcitxConfigFile *getConfigFile();
private:
    QMap<QString, void *> m_dummyValue;
    FcitxConfigFileDesc *m_cfdesc;
    FcitxConfigFile *m_cfile {nullptr};
    FcitxGenericConfig m_config;
};

}

#endif // DUMMYCONFIG_H
