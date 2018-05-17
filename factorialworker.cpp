#include "factorialworker.h"
#include "QDebug"
#include "QString"
#include <iostream>
#include <cstring>
int max = 50000;

void FactorialWorker::factorial(int arr[], int n){
    if (!n || isInterruptionRequested()) return;
    int carry = 0;
    for (int i=max-1; i>=0; --i){
        arr[i] = (arr[i] * n) + carry;
        carry = arr[i]/10;
        arr[i] %= 10;
    }
    factorial(arr,n-1);
}

QString FactorialWorker::display(int arr[]){
    int ctr = 0;
    auto s = QString("");
    for (int i=0; i<max; i++){
        if (!ctr && arr[i])
            ctr = 1;
        if(ctr)
        {
            s = s.append(QString::fromStdString(std::to_string(arr[i])));
            qDebug() << arr[i];
        }
    }
    return s;
}

void FactorialWorker::run() {
    int *arr = new int[max];
    std::memset(arr,0,max*sizeof(int));
    arr[max-1] = 1;
    factorial(arr,number);
    if(isInterruptionRequested())
        return;

    emit resultReady(display(arr));
}
