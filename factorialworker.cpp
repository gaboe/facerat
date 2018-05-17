#include "factorialworker.h"
#include "QDebug"

#define MAX 500

QString FactorialWorker::factorial(int number)
{
    int res[MAX];

    // Initialize result
    res[0] = 1;
    int res_size = 1;

    // Apply simple factorial formula n! = 1 * 2 * 3 * 4...*n
    for (int x=2; x<=number; x++){
        res_size = multiply(x, res, res_size);
        qDebug() << res_size;
    }

    auto str = QString("");
    std::string result = "";
    for (int i=res_size-1; i>=0; i--){
        auto a = res[i];
        result += std::to_string(a);
    }
    qDebug() << "result to emit";

    return QString::fromStdString(result);
}

// This function multiplies x with the number
// represented by res[].
// res_size is size of res[] or number of digits in the
// number represented by res[]. This function uses simple
// school mathematics for multiplication.
// This function may value of res_size and returns the
// new value of res_size
int FactorialWorker::multiply(int x, int res[], int res_size)
{
    int carry = 0;  // Initialize carry

    // One by one multiply n with individual digits of res[]
    for (int i=0; i<res_size; i++)
    {
        int prod = res[i] * x + carry;

        // Store last digit of 'prod' in res[]
        res[i] = prod % 10;

        // Put rest in carry
        carry  = prod/10;
    }

    // Put carry in res and increase result size
    while (carry)
    {
        res[res_size] = carry%10;
        carry = carry/10;
        res_size++;
    }
    return res_size;
}


void FactorialWorker::run() {
    emit resultReady(factorial(number));
}
