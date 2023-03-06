#include <iostream>
using namespace std;

int sumDigits (int num){

    if (num == 0)
    return 0;

    return (num % 10 + sumDigits(num / 10));
}

int main (){

    int numberr = 12345;
    int sum = sumDigits(numberr);
    cout << "The sum is: " << sum << endl;

    return 0;
}