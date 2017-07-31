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

int phi_naive(int n)
{
    unsigned int result = 1;
    for(int i = 2; i < n; i++)
        if(gcd(i, n) == 1)
            result++;

    return result;
}

int phi_opt(int n)
{
    int result = n;   // Initialize result as n
    
    // Consider all prime factors of n and for every prime
    // factor p, multiply result with (1 - 1/p)
    for (int p=2; p*p<=n; ++p)
    {
        // Check if p is a prime factor.
        if (n % p == 0)
        {
            // If yes, then update n and result
            while (n % p == 0)
                n /= p;
            result -= result / p;
            
        }
       
    }
    // If n has a prime factor greater than sqrt(n)
    // (There can be at-most one such prime factor)
    if (n > 1)
        result -= result / n;
    return (int)result;
}




int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " N" << endl;
        return -1;
    }

    int N = atoi(argv[1]);

    cout << phi_opt(N) << endl;
    //cout << phi_naive(N) << endl;

    return 0;
}
