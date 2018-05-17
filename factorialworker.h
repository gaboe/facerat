#ifndef FACTORIALWORKER_H
#define FACTORIALWORKER_H
#include <QObject>
#include <QThread>
#include <QString>

class FactorialWorker : public QThread
{
    Q_OBJECT
    void run() override;
    void factorial(int arr[], int n);
    QString display(int arr[]);
signals:
    void resultReady(const QString &s);
public:
    int number;

};

#endif // FACTORIALWORKER_H

