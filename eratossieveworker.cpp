#include "eratossieveworker.h"
#include <QStringList>
#include <QString>
#include <QDebug>
void EratosSieveWorker::run()
{
    auto result = new QStringList();
    bool prime[upper+1];
    memset(prime, true, sizeof(prime));
    for (int p=2; p*p<=upper; p++)
    {
        if(isInterruptionRequested())
            return;
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples of p
            for (int i=p*2; i<=upper; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    for (int p=2; p<=upper; p++){

        if(isInterruptionRequested())
            return;
        if (prime[p] && p >= lower){
            qDebug() << p;
            result->append(QString::fromStdString(std::to_string(p)));
        }
    }
    if(isInterruptionRequested())
        return;

    emit resultReady(*result);
}

EratosSieveWorker::EratosSieveWorker()
{

}
