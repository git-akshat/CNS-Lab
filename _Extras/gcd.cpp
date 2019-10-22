#include<bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#define MAX 10000

using namespace std;

int main()
{
    int m, n;
    int gcd;

    cout << "Enter value of m: " ;
    cin >> m;

    cout << "Enter value of n: " ;
    cin >> n;

    for(int i = m<n?m:n ; i >= 1; i--)
    {
        if(m%i == 0 && n%i == 0)
        {
            gcd = i;
            break;
        }
    }

    cout << "GCD = " << gcd << endl;
}
