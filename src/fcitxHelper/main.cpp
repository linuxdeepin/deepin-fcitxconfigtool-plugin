/***************************************************************************
 *   Copyright (C) 2012~2012 by CSSlayer                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#include <QCoreApplication>
#include <QTimer>
#include <QProcess>
#include <signal.h>



bool exeCommand(const QString &cmd, const QStringList &args, QString &output, QString &err)
{
    QProcess process;
    process.setProgram(cmd);
    process.setArguments(args);

    process.start();
    // Wait for Process to finish without timeout.
    process.waitForFinished(-1);
    output += process.readAllStandardOutput();
    err += process.readAllStandardError();

    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
        return true;
    }
    return false;
}


void signal_callback_handler(int signum, siginfo_t *siginfo, void *context) {
    Q_UNUSED(context)
    if (signum == SIGTERM && (long)siginfo->si_pid == 1) {
        QString output, error;
        exeCommand("pidof fcitx | xargs kill -9", QStringList(), output, error);
        exit(signum);
    }
}

const static QString PROCESS_NAME = "/usr/bin/fcitx-autostart";

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    //进城被init杀死，视为关机
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &signal_callback_handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGTERM, &act, NULL);
    QTimer timer;
    timer.start(4000);
    QObject::connect(&timer, &QTimer::timeout, [=]{
        QString output, error;
        exeCommand("pidof", QStringList() << "fcitx", output, error);
        if (output.isEmpty()) {
            QProcess process;
            process.setProgram(PROCESS_NAME);
            process.startDetached();
        }
    });

    app.exec();
}
