#include "runterminal.h"
#include <QDebug>
#include <QProcess>

runTerminal::runTerminal(QWidget *parent) :
    QWidget(parent)
{
}
QString runTerminal::sayHello()
{
    return "Hello";
}

void runTerminal::runcmd(QString cmd, QStringList args)
{
    QString tmparg;
    foreach(tmparg,args)
    {
        tmparg += tmparg;
    }

    qDebug() << tmparg;
    qDebug () << "Command to run:" << cmd;

    //Creates the new process.
    process = new QProcess(this);

    //Stats the process
    process->start(cmd, args);

    //Sets the connections
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(readstdoutput()));
    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(readstderr()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),this, SLOT(onProcessFinished(int, QProcess::ExitStatus)));

    //TerminalWindowDialog = new TerminalWindow();
    //connect(process,SIGNAL(readyReadStandardError()),TerminalWindowDialog,SLOT(setText()));
}

void runTerminal::readstdoutput()
{
    strdata = process->readAllStandardOutput();
    qDebug() << "Standard output:" << strdata;
}

void runTerminal::readstderr()
{
    stderrdata = process->readAllStandardError();
    qDebug() << "Standard Error:" <<stderrdata;
}

void runTerminal::onProcessFinished(int exitCode, QProcess::ExitStatus status)
{

    qDebug() << "Exitcode:" << exitCode << "\nExitstatus:" << status;

    if(exitCode == 0)
    {
        statusDescription = trUtf8("Done recording");
    }
    else
    {
        statusDescription = trUtf8("Recording failed!");

    }

    qDebug() << statusDescription;

    delete process;
    process = NULL;

}

void runTerminal::stopProcess()
{
    //This function is more or less from Juergen Heinemann's "qx11grab". Great work from a great person! :-)
    // Visit his project at: http://qt-apps.org/content/show.php?content=89204
    char q = 'q';
    if ( ( process->write ( &q ) != -1 ) && ( process->waitForBytesWritten () ) ){
          process->closeWriteChannel();
    }
    else
    {
        process->kill();
    }


   // process->kill();
}
