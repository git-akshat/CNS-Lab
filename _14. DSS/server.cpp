# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int createServer(int port)
{
	int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
    
    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "\nServer Online. Waiting for client...." << endl;
    
    listen(sersock, 5);
    int sock = accept(sersock, NULL, NULL);
    cout << "Connection Established." << endl;
    return sock;
}

int mod(int a, int b)
{
	return a >= 0 ? (a%b) : b-(abs(a)%b) ;
}

long powermod(long a, long b, long  q)
{
	long res=1;
	for(long i=0;i<b;i++)
	{
		res=(res*a)%q;
	}
	return res;
}

int findInverse(int R , int D)
{
	int i = 0 ;
	int p[100] = {0,1};
	int q[100] = {0} ; // quotient

	while(R!=0)
	{
		q[i] = D/R ;
		int oldD = D ;
		D = R ;
		R = oldD%R ;
		if(i>1)
		{
			p[i] = mod(p[i-2] - p[i-1]*q[i-2], D) ;
		}
		i++ ;
	}
	if (i == 1) return p[i]=1;
	else return p[i] = mod(p[i-2] - p[i-1]*q[i-2], D) ;
}

long H(long M)
{
	return ( M^1234 ); //hash key=1234 
}

long f1(long M,long k,long x,long r,long q)
{
	return ( findInverse(k,q) * ( H(M) + x*r ) )%q; 
}

long f2(long k, long p, long q, long g) 
{
	return powermod(g,k,p)%q;
}


int main()
{
    int port;  cout << "\nEnter port : "; cin >> port;
    int sock = createServer(port);
    
	srand(time(NULL));
	long p,q,r,s,k,g,M,h,x,y,hashval;

	cout<<"p = "; cin>>p;
	cout<<"q = "; cin>>q;
	cout<<"M = "; cin>>M;
	
	hashval=H(M);
	h=rand()%(p-3)+2;
	g=powermod(h,(p-1)/q,p);

	x=rand()%(q-2)+1;	//User private key
	y=powermod(g,x,p);	//User public key

	k=rand()%(q-2)+1;

	//Signing
	r=f2(k,p,q,g);
	s=f1(M,k,x,r,q);

	send(sock, &hashval, sizeof(hashval), 0);	
	send(sock, &r, sizeof(r), 0);
	send(sock, &s, sizeof(s), 0);	
	send(sock, &g, sizeof(g), 0);	
	send(sock, &y, sizeof(y), 0);	

	cout<<"Packet sent with values"<<endl;
	cout<<"Hash : "<<hashval<<endl;
	cout<<"R    : "<<r<<endl;
	cout<<"S    : "<<s<<endl;
	cout<<"Y    : "<<y<<endl;
	cout<<"G    : "<<g<<endl;
}
