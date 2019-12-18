/* Author : AKSHAT AGARWAL 

14. Implement DSS algorithm for signing and verification of messages between two parties (obtain H(M) using simple XOR method of hash computation on M). */

/* Client Program */

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

long mod(long a, long b)
{
    return a >= 0 ? (a%b) : b-(abs(a)%b) ;
}

long powermod(long a, long b, long  c)
{
    long res=1;
    for(int i=0; i<b; i++)
    {
        res = (res * a) % c;
    }
    return res;
}

long findInverse(long R , long D)
{
    int i = 0;
    long N = D; // copy D to N for taking mod 
    long p[100] = {0,1};
    long q[100] = {0} ;
    
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

long H(long M)
{
    return (M ^ 1234); //hash key = 1234 
}

int main()
{
    char ip[50]; cout << "\nEnter server's IP address: "; cin >> ip;
    int port;    cout << "Enter port : "; cin >> port;
    int sock = connectToServer(ip, port);

    long p, q; // prime numbers
    long r, s; // signature
    long g, y; // keys
    long M, hashval; // Message and Hash
    long w, v; // verify
    srand(time(NULL));

    recv(sock, &p, sizeof(p), 0);
    recv(sock, &q, sizeof(q), 0);
    recv(sock, &g, sizeof(g), 0);		
    recv(sock, &y, sizeof(y), 0);
    recv(sock, &M , sizeof(M), 0);
    recv(sock, &r, sizeof(r), 0);
    recv(sock, &s, sizeof(s), 0);	

    cout << "Received p =  " << p << endl;
    cout << "Received q =  " << q << endl;
    cout << "Received g =  " << g << endl;
    cout << "Received y =  " << y << endl;
    cout << "Received M'=  " << M << endl;
    cout << "Received r' = " << r << endl;
    cout << "Received s' = " << s << endl;

    hashval = H(M) ; 
    cout << "\nH(M') = " << hashval << endl;

    //Verifying
    w = findInverse(s,q) % q;  cout << "w = " << w << endl;
    long u1 = (hashval * w) % q;
    long u2 = (r * w) % q;
    v = ((powermod(g,u1,p)*powermod(y,u2,p)) %p) %q;  cout<<"v = "<<v<<endl;
    if(v == r) cout<<"\nDigital Signature Verified. " << endl << endl;
    else	   cout<<"\nDigital Signature is invalid !!!" << endl << endl;	
}

/*
Enter server's IP address: 127.0.0.1
Enter port : 3333

Client is connected to Server.
Received p =  13
Received q =  3
Received g =  3
Received y =  3
Received M' =  1057
Received r' = 0
Received s' = 1

H(M') = 243
w = 1
v = 0

Digital Signature Verified.
*/
