#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "factorialworker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->resultLabel->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleFactorialResult(const QString &s)
{
    ui->resultLabel->setText("Result: " + s);
    ui->resultLabel->show();
}

void MainWindow::on_pushButton_clicked()
{
    FactorialWorker *workerThread = new FactorialWorker();
    connect(workerThread, &FactorialWorker::resultReady, this, &MainWindow::handleFactorialResult);
    connect(workerThread, &FactorialWorker::finished, workerThread, &QObject::deleteLater);
    workerThread->number = ui->factorialInput->value();
    workerThread->start();
}

void MainWindow::runEratosthenesSieve(int lower,int upper) {
       ui->listWidget->clear();
       bool prime[upper+1];
       memset(prime, true, sizeof(prime));

       for (int p=2; p*p<=upper; p++)
       {
           // If prime[p] is not changed, then it is a prime
           if (prime[p] == true)
           {
               // Update all multiples of p
               for (int i=p*2; i<=upper; i += p)
                   prime[i] = false;
           }
       }

       // Print all prime numbers
       for (int p=2; p<=upper; p++)
          if (prime[p] && p >= lower){
              ui->listWidget->addItem(QString::fromStdString(std::to_string(p)));
          }


}

void MainWindow::on_eraBtn_clicked()
{
    runEratosthenesSieve(ui->eraInputLower->value(),ui->eraInputUpper->value());
}
