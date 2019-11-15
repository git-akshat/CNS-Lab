# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

long p, q; // prime numbers
long r, s; // signature
long k, x, y, g; // keys
long M, hashval; // Message and Hash

int createServer(long port)
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

long mod(long a, long b)
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

long f1()
{
	return (findInverse(k,q) * (hashval + x*r )) % q; 
}

long f2() 
{
	return powermod(g, k, p) % q;
}

int main()
{
    int port;  cout << "\nEnter port : "; cin >> port;
    int sock = createServer(port);
    
	srand(time(NULL));

	cout << "\nEnter a prime number, p : "; cin >> p; 
	cout << "Enter a prime number, q (p-1 div by q and q>3) : "; cin >> q;
    if( (p-1)%q != 0 || q <=2) { cout << "\nInvalid input\n"; exit(-1); }

	cout<<"Enter message, M = "; cin >> M;
	
	hashval = H(M); 
    cout << "\nH(M) = " << hashval << endl;
	
    long h;
	do{
		h = rand()%(p-4)+2;   // 1 < h < p-1
		g = powermod(h,(p-1)/q, p);	//g > 1
	} while(g<=1);
	cout << "g = " << g << endl;

	x = rand()%(q-2) + 1;	cout << "Server's Private key, x = " << x << endl;
	y = powermod(g, x, p);	cout << "Server's Public  key, y = " << y << endl;
	k = rand()%(q-2) + 1;   cout << "Secret key, k = " << k << endl;

	//Signing
	r = f2();
	s = f1();
    cout << "\nServer's Digital Signature = {" << r << ", " << s << "}" << endl;

    send(sock, &p, sizeof(p), 0);
    send(sock, &q, sizeof(q), 0);	
	send(sock, &g, sizeof(g), 0);	
	send(sock, &y, sizeof(y), 0);	
    send(sock, &hashval, sizeof(hashval), 0);
    send(sock, &r, sizeof(r), 0);
	send(sock, &s, sizeof(s), 0);	

    cout << "\nSent p, q, g, and public key to client.";
	cout <<"\nSent hash message along with signature to client." << endl << endl;
}

/*
p=71, q=7
p=569, q=71
p=809, q=101
p=619, q=103
*/

/*
Enter port : 6543

Server Online. Waiting for client....
Connection Established.

Enter a large prime number, p : 619
Enter a large prime number, q (p-1 div by q) : 103
Enter message, M = 321

Hash value, H(M) = 1427
g = 1
Server's Private key, x = 522
Server's Public  key, y = 1

Secret key, k = 19
Server's Digital Signature = {1, 0}

Sent p, q, g, and public key to client.
Sent message along with signature to client.
*/
