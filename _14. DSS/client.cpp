# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int connectToServer(const char* ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port),inet_addr(ip)};
    
    if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 ){
        cout << "\nRun server program first." << endl; exit(0);
    }else{
        cout << "\nClient is connected to Server." << endl; 
    }
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
	return (M^1234); //hash key=1234
}

long f3(long s,long q)
{
	return findInverse(s,q)%q;
}

long f4(long y,long p,long q,long g,long hashval, long w,long r)
{
	long u1,u2;
	u1=(H(hashval)*w)%q;
	u2=(r*w)%q;
	return ( powermod(g,u1,p) * powermod(y,u2,p) )%q;
} 

int main()
{
    char ip[50]; cout << "\nEnter server's IP address: "; cin >> ip;
    int port;    cout << "Enter port : "; cin >> port;
    int sock = connectToServer(ip, port);
    
	srand(time(NULL));
	long p,q,r,s,w,v,g,hashval,y;
	cout<<"p = "; cin>>p;
	cout<<"q = "; cin>>q;

	recv(sock, &hashval, sizeof(hashval), 0);	
	recv(sock, &r, sizeof(r), 0);
	recv(sock, &s, sizeof(s), 0);	
	recv(sock, &g, sizeof(g), 0);		
	recv(sock, &y, sizeof(y), 0);

	cout<<"Packet received with values"<<endl;
	cout<<"Hash : "<<hashval<<endl;
	cout<<"R    : "<<r<<endl;
	cout<<"S    : "<<s<<endl;
	cout<<"Y    : "<<y<<endl;
	cout<<"G    : "<<g<<endl;
	
	//Verifying
	w=f3(s,q);
	v=f4(y,p,q,g,hashval,w,r);
	if(v==r) cout<<"Digital Signature Verified"<<endl;
	else cout<<"Digital Signature is invalid"<<endl;	
}
