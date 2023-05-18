#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H

#include <QString>
#include <QProcess>
#include <QDebug>

class CommandRunner : public QObject
{
    Q_OBJECT
public:
    explicit CommandRunner(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void runCommand(const QString &command)
    {
        QProcess process;
        process.start("bash", QStringList() << "-c" << command);
        process.waitForFinished();

        // Emit the signal with the command output
        emit commandFinished(process.readAllStandardOutput());
    }

signals:
    void commandFinished(const QString &output);
    void finish(const QString &out);



};

#endif // COMMANDRUNNER_H
