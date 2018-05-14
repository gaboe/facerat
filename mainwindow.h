#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_eraBtn_clicked();

private:
    Ui::MainWindow *ui;
    unsigned long long int getFactorial(int n);
    int multiply(int x, int res[], int res_size);
    QString factorial(int n);
    void runEratosthenesSieve(int lower, int upper);
};

#endif // MAINWINDOW_H
