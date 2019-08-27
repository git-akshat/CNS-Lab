#include<bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#define MAX 10000
using namespace std;

int main()
{
	int rnum, k=0;
	bool prime;
	int arr[1000];

	for(int j=2; j<1000; j++)
	{
		prime = true;
		for(int i=2; i<=j/2; i++)
		{
			if(j % i == 0)
			{
				prime = false;
				break;
			}
		}

		if(prime)
		{
			arr[k++] = j;
		}
	}

	srand(time(NULL));
	rnum = rand()%1000;
	cout << "Random prime number is: " <<arr[rnum] <<endl;
}
