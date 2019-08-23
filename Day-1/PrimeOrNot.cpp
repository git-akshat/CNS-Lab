#include<bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#define MAX 10000
using namespace std;

int main()
{
	int n;
	bool prime = true;

	srand(time(NULL));
	n = rand()%100;

	cout << "Random number is: " << n << endl;

    for(int i=2; i<=n/2; i++)
    {
        if(n % i == 0)
        {
            prime = false;
            break;
        }
    }

    if(prime)
    {
        cout << "It is a Prime number" << endl;
    }
    else{
        cout << "It is a Composite number" << endl;
    }

}

