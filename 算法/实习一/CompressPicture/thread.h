#ifndef THREAD_H
#define THREAD_H

#endif // THREAD_H

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
