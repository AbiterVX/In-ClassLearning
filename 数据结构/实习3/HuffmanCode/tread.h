#ifndef TREAD_H
#define TREAD_H

#endif // TREAD_H


#include<QObject>
#include<QThread>

class WorkerThread:public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject *parent=0):QThread(parent)
    {

    }

protected:
    virtual void run() Q_DECL_OVERRIDE
    {
        int nValue=0;
        while (nValue<100)
        {
            msleep(50);
            ++nValue;

            emit resultReady(nValue);
        }
    }

signals:
    void resultReady(int value);

};
