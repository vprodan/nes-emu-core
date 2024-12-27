#include <cstdint>
#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    uint8_t a = 0b10000001;

    int8_t b = a;

    cout << static_cast<int>(a) << " " << static_cast<int>(b) << endl;

    return 0;
}