#ifndef ERATOSSIEVEWORKER_H
#define ERATOSSIEVEWORKER_H

#include <QThread>
#include <QStringList>

class EratosSieveWorker : public QThread
{
    Q_OBJECT
    void run() override;
public:
    EratosSieveWorker();
    int upper;
    int lower;
signals:
    void resultReady(QStringList result);
};

#endif // ERATOSSIEVEWORKER_H
