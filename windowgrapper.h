#ifndef WINDOWGRAPPER_H
#define WINDOWGRAPPER_H

#include <QObject>

class WindowGrapper : public QObject
{
    Q_OBJECT
public:
    explicit WindowGrapper(QObject *parent = 0);

    int fixResolution(int number);

    QString Fullscreenaspects();

signals:

public slots:

};

#endif // WINDOWGRAPPER_H