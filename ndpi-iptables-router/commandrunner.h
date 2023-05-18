#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H

#include <QString>
#include <QProcess>
#include <QDebug>

class CommandRunner : public QObject
{
    Q_OBJECT
public:
    explicit CommandRunner(QObject *parent = nullptr);

    Q_INVOKABLE void runCommand(const QString &command);

signals:
    void commandFinished(const QString &output);
    void finish(const QString &out);



};

#endif // COMMANDRUNNER_H
