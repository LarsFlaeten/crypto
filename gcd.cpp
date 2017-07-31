#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int gcd(int a, int b)
{
    if(b==0)
        return a;
    return gcd(b, mod(a,b));
}


int main(int argc, char* argv[])
{
    if(argc < 3) {
        cerr << "Usage: " << argv[0] << " a b" << endl;
        return -1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    cout << gcd(a,b) << endl;

    return 0;
}
