#ifndef FACTORIALWORKER_H
#define FACTORIALWORKER_H
#include <QObject>
#include <QThread>
#include <QString>

class FactorialWorker : public QThread
{
    Q_OBJECT
    void run() override;
    QString factorial(int number);
    int multiply(int x, int res[], int res_size);
signals:
    void resultReady(const QString &s);
public:
    int number;

};

#endif // FACTORIALWORKER_H

