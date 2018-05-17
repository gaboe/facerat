#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "eratossieveworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    EratosSieveWorker *eratosSieveThread;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleFactorialResult(const QString &s);
    void on_pushButton_clicked();

private slots:
    void on_eraBtn_clicked();
    void on_eraShowBtn_clicked();
    void on_eraPauseBtn_clicked();

    void on_eraCancelBtn_clicked();

private:
    Ui::MainWindow *ui;
    unsigned long long int getFactorial(int n);
    int multiply(int x, int res[], int res_size);
    QString factorial(int n);
    void runEratosthenesSieve(int lower, int upper);
    void handleEratosSieveResult(QStringList result);
    void incrementEraProgressBar();
    bool isEratosSieveSleeping = false;
    void handleSleepingEratosSieve();
};

#endif // MAINWINDOW_H
