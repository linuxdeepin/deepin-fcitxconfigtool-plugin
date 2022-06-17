deepin-fcitxconfigtool-plugin 

dde控制中心输入法管理插件，目前做了基于fcitx4输入法框架的适配。

## Installation

```
sudo apt install deepin-fcitxconfigtool-plugin 
```

### Build from source code

```
sudo apt build-dep deepin-fcitxconfigtool-plugin 
sudo apt install  debhelper qt5-qmake libqt5widgets5 libqt5network5 libdtkwidget-dev libdtkgui-dev libdtkgui5 libdtkgui5-bin libdtkcore5-bin libdtkcore-dev qttools5-dev qttools5-dev-tools pkg-config cmake fcitx-bin fcitx-libs-dev libfcitx-qt5-1 libfcitx-qt5-data libfcitx-qt5-dev iso-codes libdbus-glib-1-dev libgtk-3-dev libgtk2.0-dev libunique-dev libdframeworkdbus-dev libgtest-dev libgmock-dev dde-control-center-dev extra-cmake-modules libkf5i18n-dev
```

## 使用说明
```shell
git clone https://github.com/linuxdeepin/deepin-fcitxconfigtool-plugin.git
sudo apt build-dep deepin-fcitxconfigtool-plugin 
cd ./deepin-fcitxconfigtool-plugin 
sudo dpkg-buildpackage -b
cd ..
sudo dpkg -i *.deb
```

## 学习开发说明

欢迎进行pr，鼓励大家参与输入法管理器的产品设计与代码编写。


## Getting involved

We encourage you to report issues and contribute changes
- [Contribution guide for developers](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers-en) (English)
- [开发者代码贡献指南](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers) (中文)
- [Translate for your language on Transifex](https://www.transifex.com/linuxdeepin/)

### Contributors
1.  csslayer
2.  liuwenhao
3.  chenshijie
4.  zhaoyue

## License

This project is licensed under GPLv3 or any later version.
