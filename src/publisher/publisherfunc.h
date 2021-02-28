/*
* Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
* Author:     liuwenhao <liuwenhao@uniontech.com>
* Maintainer: liuwenhao <liuwenhao@uniontech.com>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PUBLISHERFUNC_H
#define PUBLISHERFUNC_H

#include <QDir>
#include <QJsonDocument>
#include <QApplication>
#include <QFont>

/*************************************
公共函数 该公共空间内存放与项目无关的通用函数

**************************************/

namespace publisherFunc {

void pause(const unsigned int &msec);
void moveToWindowCenter(QWidget *widget);
bool createDir(const QString &dir);
bool createFile(const QString &filePath, const QString &text, QIODevice::OpenMode model = QIODevice::WriteOnly);
QJsonDocument readJson(const QString &filePath);
QString readFile(const QString &filePath);
QString getImagePixel(const QString &imagePath);
QStringList getDirFileNames(const QString &dirPath, const QDir::Filters &flag = QDir::Files, const QStringList &suffix = QStringList());
QPair<int, QString> startPopen(const QString &cmd, const QString &model = QString("r"));
int fontSize(const QString &str, const QFont &font = qApp->font());

}; // namespace publisherFunc

#endif // PUBLISHERFUNC_H
