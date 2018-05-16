#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "factorialworker.h"
#include "eratossieveworker.h"
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->resultLabel->hide();
    ui->listWidget->hide();
    ui->eraCount->hide();
    ui->eraShowBtn->hide();
    ui->factorialProgressBar->hide();
    ui->eraProgressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleFactorialResult(const QString &s)
{
    ui->factorialProgressBar->setValue(100);
    ui->factorialProgressBar->hide();
    ui->resultLabel->setText("Result: " + s);
    ui->resultLabel->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->factorialProgressBar->show();
    ui->factorialProgressBar->setValue(4);
    FactorialWorker *workerThread = new FactorialWorker();
    connect(workerThread, &FactorialWorker::resultReady, this, &MainWindow::handleFactorialResult);
    connect(workerThread, &FactorialWorker::finished, workerThread, &QObject::deleteLater);
    workerThread->number = ui->factorialInput->value();
    workerThread->start();
}

void MainWindow::on_eraBtn_clicked()
{
    ui->listWidget->hide();
    ui->eraCount->hide();
    ui->eraShowBtn->hide();
    ui->eraProgressBar->show();
    ui->eraProgressBar->setValue(11);
    EratosSieveWorker *workerThread = new EratosSieveWorker();
    connect(workerThread, &EratosSieveWorker::resultReady, this, &MainWindow::handleEratosSieveResult);
    connect(workerThread, &EratosSieveWorker::finished, workerThread, &QObject::deleteLater);
    workerThread->lower = ui->eraInputLower->value();
    workerThread->upper = ui->eraInputUpper->value();

    workerThread->start();
}

void MainWindow::handleEratosSieveResult(QStringList result)
{
    ui->listWidget->addItems(result);
    ui->eraCount->setText(QString::fromStdString(std::to_string(result.length())));
    ui->eraProgressBar->hide();
    ui->eraCount->show();
    ui->eraShowBtn->show();
}

void MainWindow::on_eraShowBtn_clicked()
{
    ui->listWidget->show();
}
