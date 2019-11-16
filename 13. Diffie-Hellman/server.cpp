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

long powermod(long a, long b, long  q)
{
	long res=1;
	for(long i=0;i<b;i++)
	{
		res=(res*a)%q;
	}
	return res;
}

int main()
{
    int port;
    cout << "\nEnter port : "; cin >> port;
    int sock = createServer(port);
    
	
	long q, alpha;
	cout<<"\nEnter a prime number, q : "; cin >> q;
	cout<<"Enter primitive root of q, alpha : "; cin >> alpha;
	
	long Yc;
	recv(sock, &Yc, sizeof(Yc), 0);	 // recv client's public key
	cout<< "\nClient's public key,  Yc = " << Yc <<endl;
	
	srand(time(NULL));
	long Xs = rand() % (q-1) +1; // server's private key (1<Xa<q)
	cout<< "\nServer's private key, Xs = " << Xs <<endl;
	
	long Ys = powermod(alpha, Xs, q); // server's public key
	send(sock, &Ys, sizeof(Ys), 0);	 // send server's public key
	cout<< "Server's public key,  Ys = " << Ys <<endl;
	
	long k = powermod(Yc,Xs,q);	
	cout<<"\nSecret Key, k = "<<k<<endl;

	int msg;
	cout<<"\nEnter a message(integer) to send : "; cin>>msg;
	
	int cipher=msg^k;
	send(sock, &cipher, sizeof(cipher), 0);
	cout << "Encrypted msg sent to client: " << cipher << endl << endl;
}

/*
Enter port : 4444

Server Online. Waiting for client....
Connection Established.

Enter a prime number, q : 11
Enter primitive root of q, alpha : 2

Client's public key,  Yc = 5

Server's private key, Xs = 10
Server's public key,  Ys = 1

Secret Key, k = 1

Enter a message(integer) to send : 453
Encrypted msg sent to client: 452
*/