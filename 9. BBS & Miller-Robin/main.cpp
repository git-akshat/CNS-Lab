#include<bits/stdc++.h>
#define MAX 10000
using namespace std;

vector<int>primeArray;
unsigned int B[8];
void generatePrime()
{
    int counter=0;
	bool prime;
    for(int i=2; i<MAX; i++)
	{
		prime = true;
		for(int j=2; j<=i/2; j++)
		{
			if(i % j == 0)
			{
				prime = false;
				break;
			}
		}

		if(prime)
		{
			primeArray.push_back(i);
		}

	}
	/*
	for(int k=0;k<20;k++)
    {
        cout<<"\n"<<primeArray[k];
    }
    */
}

int findPrime()
{
    generatePrime();
    srand(time(NULL));
    int random = rand()%primeArray.size();
    for(int i = random; i<primeArray.size(); i++)
    {
        int temp;
        if(primeArray[i]%4==3 && primeArray[i]!=temp)
        {
            temp=primeArray[i];
            return primeArray[i];
        }

        if(i==primeArray.size()-1)
            i=0;
    }

}

void BlumBlumShub()
{
    int p = findPrime();
    int q = findPrime();
    cout<<"\nP = "<<p<<"\nQ = "<<q<<endl;
    int n=p*q;
    int s=n+1;
    int X[8];
    X[0]=(s*s)%n;
    for(int i=1; i<8; i++)
    {
        X[i]=(X[i-1]*X[i-1])%n;
        B[i]=X[i]%2;
    }
}
int main()
{
    BlumBlumShub();
    cout<<"Array B: ";
    for(int i=0;i<8;i++)
        cout<<B[i];
}
/*






int powMod(int n,int powr,int mod)
{
    int i,j,x=0;
    for(i=0;i<powr;i++)
    {
        x=n*2;
    }
    j=x%mod;
    //cout<<"+++"<<j<<"+++"<<endl;
    return j;

}
void rabinMiller(int num)
{
    int k,q,n,a;
    int com=0,incon=0;
    n=num-1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(n==(pow(2,i)*j))
            {
                k=i;
                q=j;
            }
        }
    }
    //Genrate random number a such that 1<a<n-1
    //int w=num/4,h=0;
    //cout<<"No.of Iterations ="<<w<<endl;
    //while(h!=w)
    //{
        //h++;
        a=rand()%(n-2)+2;
        //cout<<"a ="<<a<<endl;
        if(powMod(a,q,num)==1)
        {
         incon+=1;
         cout<<"Inconclusive\n";
         //continue;
        }
        for(int j=0;j<k;j++)
        {
            int x=pow(2,j)*q;
            if(powMod(a,x,num)==n)
            {
                incon+=1;
                cout<<"Inconclusive\n";
                //continue;
            }
        }
        com+=1;
        cout<<"Composite\n";
    //}
    //cout<<"\nComposite ="<<com;
    //cout<<"\nInconclusive ="<<incon;
}

//int bbs(int p,int q,)

int main()
{
    srand(time(NULL));
    int num,p,q,n;
    cout<<"Enter the number to be checked";
    cin>>num;
    //cout<<"Enter the value of p and q ";
    //cin>>p>>q;
    n=p*q;

    rabinMiller(num);
    return 0;
}
*/
