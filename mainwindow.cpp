#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "factorialworker.h"
#include "eratossieveworker.h"
#include <QList>

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

void MainWindow::on_eraBtn_clicked()
{
    EratosSieveWorker *workerThread = new EratosSieveWorker();
    connect(workerThread, &EratosSieveWorker::resultReady, this, &MainWindow::handleEratosSieveResult);
    connect(workerThread, &EratosSieveWorker::finished, workerThread, &QObject::deleteLater);
    workerThread->lower = ui->eraInputLower->value();
    workerThread->upper = ui->eraInputUpper->value();

    workerThread->start();
}

void MainWindow::handleEratosSieveResult(QList<int> result)
{
    for (int i = 0; i < result.size(); ++i) {
        //ui->listWidget->addItem(QString::fromStdString(std::to_string(result.at(i))));
    }
}
