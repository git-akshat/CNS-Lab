# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

long p, q; // prime numbers
long r, s; // signature
long g, y; // keys
long M, hashval; // Message and Hash
long w, v; // verify

int connectToServer(const char* ip, long port)
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

long powermod(long a, long b, long  c)
{
	long res=1;
	for(int i=0;i<b;i++)
	{
		res = (res * a) % c;
	}
	return res;
}

long findInverse(long R , long D)
{
	int i = 0 ;
	long p[100] = {0,1};
	long q[100] = {0} ; // quotient
	long N = D;
	while(R!=0)
	{
		q[i] = D/R ;
		long oldD = D ;
		D = R ;
		R = oldD%R ;
		if(i>1)
		{
			p[i] = mod(p[i-2] - p[i-1]*q[i-2], N) ;
		}
		i++ ;
	}
	if (i == 1) return 1;
	else        return p[i] = mod(p[i-2] - p[i-1]*q[i-2], N) ;
}

long H(long m)
{
	return (m ^ 1234); //hash key = 1234 
}

long f3()
{
	return findInverse(s,q) % q;
}

long f4()
{
	long u1 = (hashval * w) % q;
	long u2 = (r * w) % q;
	return ((powermod(g,u1,p)*powermod(y,u2,p)) %p) %q;
} 

int main()
{
    char ip[50]; cout << "\nEnter server's IP address: "; cin >> ip;
    int port;    cout << "Enter port : "; cin >> port;
    int sock = connectToServer(ip, port);
    
	srand(time(NULL));
	
	recv(sock, &p, sizeof(p), 0);
    recv(sock, &q, sizeof(q), 0);
	recv(sock, &g, sizeof(g), 0);		
	recv(sock, &y, sizeof(y), 0);
	recv(sock, &M, sizeof(M), 0);
	recv(sock, &r, sizeof(r), 0);
	recv(sock, &s, sizeof(s), 0);	

	cout << "Received p =  " << p << endl;
	cout << "Received q =  " << q << endl;
	cout << "\nReceived g =  " << g << endl;
	cout << "Received y =  " << y << endl;
	cout << "\nReceived Message, M' =  " << M << endl;
	cout << "Received r' = " << r << endl;
	cout << "Received s' = " << s << endl;

	hashval = H(M); 
	cout << "\nHash value, H(M') = " << hashval << endl;
	
	//Verifying
	w = f3();  cout << "w = " << w << endl;
	v = f4();  cout << "v = " << v << endl;
	if(v == r) cout<<"\nDigital Signature Verified. " << endl << endl;
	else	   cout<<"\nDigital Signature is invalid !!!" << endl << endl;	
}

/*
Enter server's IP address: 127.0.0.1
Enter port : 6543

Client is connected to Server.
Received p =  103
Received q =  619

Received g =  1
Received y =  1

Received Message, M' =  321
Received r' = 1
Received s' = 0

Hash value, H(M') = 1427
w = 2
v = 1

Digital Signature Verified. 
*/
