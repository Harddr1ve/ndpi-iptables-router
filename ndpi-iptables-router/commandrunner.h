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

signals:
    void commandFinished(const QString &output);

    Q_INVOKABLE void runCommand(const QString &command);

};

#endif // COMMANDRUNNER_H
