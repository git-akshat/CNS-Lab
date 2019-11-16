# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int connectToServer(const char* ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), inet_addr(ip)};

    if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 ){
        cout << "\nRun server program first." << endl; exit(0);
    }else{
        cout << "\nClient is connected to Server." << endl; 
    }
    return sock;
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

int extEucledian(int R , int phi)
{
	int i = 0 ;
	int p[100] = {0,1};
	int q[100] = {0} ; // quotient
    int D = phi;

	while(R!=0)
	{
		q[i] = D/R ;
		int oldD = D ;
		D = R ;
		R = oldD%R ;
		if(i>1)
		{
			p[i] = (p[i-2] - p[i-1]*q[i-2]) % phi;
            if(p[i] < 0) p[i] = phi+p[i]; // if mod value is negative
		}
		i++ ;
	}
	if (i != 1)
    {
        p[i] = (p[i-2] - p[i-1]*q[i-2]) % phi;
        if(p[i] < 0) p[i] = phi+p[i];
    }
    return p[i];
}

// M = C^d mod n
int decrypt(int C, int PR[2])
{
    int M = 1;
    for(int i=1; i<=PR[0]; i++)
    {
        M = (M*C) % PR[1];
    }
    return M;
}

int main()
{
    char ip[50];
    int port;
    cout << "\nEnter server's IP address: "; cin >> ip;
    cout << "Enter port : "; cin >> port;
    int sock = connectToServer(ip, port);

    int p,q; 
    cout << "\nEnter two prime numbers : "; cin >> p >> q;
    int n = p * q ;
    int phi = (p-1) * (q-1);

    int e, d;
    srand(time(NULL));
    do{ e = rand()%(phi-2)+2; } while(gcd(e,phi) != 1);
    d = extEucledian(e, phi);
    
    int PU[2] = {e, n}; // public key
    int PR[2] = {d, n}; // private key
    cout << "\nPublic key , PU = {" << e << ", " << n << "}" << endl;
    cout << "Private key, PR = {" << d << ", " << n << "}" << endl;

    send(sock, &PU, sizeof(PU), 0); // send public key to server
    cout << "\nSent Public key to server." << endl;

    int C; // ciphertext
    recv(sock, &C, sizeof(C), 0); // receive ciphertext from server
    cout << "\nCiphertext received from server : " << C << endl;

    int M = decrypt(C, PR); // decrypted text
    cout << "\nDecrypted Text : " << M << endl << endl;
}

/*
akshat@pop-os:~/Desktop$ g++ client.cpp -o c.out
akshat@pop-os:~/Desktop$ ./c.out

Enter server's IP address: 192.168.224.74
Enter port : 4444

Client is connected to Server.

Enter two prime numbers : 23 17

Public key , PU = {3, 391}
Private key, PR = {235, 391}

Sent Public key to server.

Ciphertext received from server : 116

Decrypted Text : 231
*/