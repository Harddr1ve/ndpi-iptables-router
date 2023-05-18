#include "commandrunner.h"

CommandRunner::CommandRunner(QObject *parent) : QObject(parent) {}
void CommandRunner::runCommand(const QString &command)
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << command);
    process.waitForFinished();

    // Emit the signal with the command output
    emit commandFinished(process.readAllStandardOutput());
}

