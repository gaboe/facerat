#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "factorialworker.h"
#include "eratossieveworker.h"
#include <QStringList>
#include <QTimer>

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
    ui->eraPauseBtn->hide();
    ui->eraCancelBtn->hide();
    ui->factorialPauseBtn->hide();
    ui->factorialCancelBtn->hide();
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
    ui->factorialPauseBtn->hide();
    ui->factorialCancelBtn->hide();
}

void MainWindow::on_pushButton_clicked()
{
    ui->resultLabel->hide();
    ui->pushButton->hide();
    ui->factorialProgressBar->show();
    ui->factorialProgressBar->setValue(80);
    ui->factorialPauseBtn->show();
    ui->factorialCancelBtn->show();
    factorialThread = new FactorialWorker();
    connect(factorialThread, &FactorialWorker::resultReady, this, &MainWindow::handleFactorialResult);
    connect(factorialThread, &FactorialWorker::finished, factorialThread, &QObject::deleteLater);
    factorialThread->number = ui->factorialInput->value();

    factorialThread->start();
}

void MainWindow::on_eraBtn_clicked()
{
    ui->listWidget->hide();
    ui->eraCount->hide();
    ui->eraShowBtn->hide();
    ui->eraBtn->hide();
    ui->eraProgressBar->show();
    ui->eraProgressBar->setValue(5);
    ui->eraPauseBtn->show();
    ui->eraCancelBtn->show();

    QTimer::singleShot(50, this, MainWindow::incrementEraProgressBar);
    eratosSieveThread = new EratosSieveWorker();
    connect(eratosSieveThread, &EratosSieveWorker::resultReady, this, &MainWindow::handleEratosSieveResult);
    connect(eratosSieveThread, &EratosSieveWorker::finished, eratosSieveThread, &QObject::deleteLater);
    eratosSieveThread->lower = ui->eraInputLower->value();
    eratosSieveThread->upper = ui->eraInputUpper->value();

    eratosSieveThread->start();
}

void MainWindow::incrementEraProgressBar()
{
    if(isEratosSieveSleeping){
        QTimer::singleShot(50, this, MainWindow::incrementEraProgressBar);
        return;
    }

    ui->eraProgressBar->setValue(ui->eraProgressBar->value() + 1);
    if(eratosSieveThread && !eratosSieveThread->isFinished()){
        if(ui->eraProgressBar->value() < 70)
            QTimer::singleShot(50, this, MainWindow::incrementEraProgressBar);
        else
            QTimer::singleShot(500, this, MainWindow::incrementEraProgressBar);
    }

}

void MainWindow::handleEratosSieveResult(QStringList result)
{
    ui->listWidget->addItems(result);
    ui->eraCount->setText(QString::fromStdString(std::to_string(result.length())));

    if(!isEratosSieveSleeping){
        ui->eraPauseBtn->hide();
        ui->eraCancelBtn->hide();
        ui->eraProgressBar->hide();
        ui->eraCount->show();
        ui->eraShowBtn->show();
        ui->eraBtn->show();
    }
}

void MainWindow::on_eraShowBtn_clicked()
{
    ui->listWidget->show();
}

void MainWindow::on_eraPauseBtn_clicked()
{
    isEratosSieveSleeping = !isEratosSieveSleeping;
    if(!isEratosSieveSleeping)
    {
        ui->eraPauseBtn->setText("Pause");
    }
    if(!isEratosSieveSleeping && eratosSieveThread && eratosSieveThread->isFinished()){
        ui->eraPauseBtn->hide();
        ui->eraCancelBtn->hide();
        ui->eraProgressBar->hide();
        ui->eraCount->show();
        ui->eraShowBtn->show();
        ui->eraBtn->show();

    }
    else if(isEratosSieveSleeping && eratosSieveThread && !eratosSieveThread->isFinished()){
        ui->eraPauseBtn->setText("Continue");
    }
}

void MainWindow::on_eraCancelBtn_clicked()
{
    if(eratosSieveThread && !eratosSieveThread->isFinished()){
        ui->eraPauseBtn->hide();
        ui->eraCancelBtn->hide();
        ui->eraProgressBar->hide();
        ui->eraBtn->show();
        eratosSieveThread->requestInterruption();
        eratosSieveThread->wait();
        eratosSieveThread->deleteLater();
    }
}

void MainWindow::on_factorialCancelBtn_clicked()
{
    if(factorialThread && !factorialThread->isFinished()){
        ui->pushButton->show();
        ui->factorialPauseBtn->hide();
        ui->factorialCancelBtn->hide();
        ui->factorialProgressBar->hide();
        ui->pushButton->shortcut();
        factorialThread->requestInterruption();
        factorialThread->wait();
        factorialThread->deleteLater();
    }
}
