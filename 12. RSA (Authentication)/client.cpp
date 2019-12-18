/* Author : AKSHAT AGARWAL 

12. Implement RSA algorithm using client-server concept. Using this illustrate secret key distribution scenario with confidentiality and authentication. The program should support the following :
    - Both client and server generate {PU, PR} and distribute PU to each other.
    - Establish a secret key K between client and server by exchanging the messages as shown in below figure.
    ![fig-12]("https://github.com/git-akshat/CNS-Lab/blob/master/12.%20RSA%20(Authentication/)/figure.png") */

/* Client Program */

# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;


int p, q, e, d, n, phi; // global variables
int PUc[2], PRc[2];     // client's keys
int PUs[2];             // server's public key
int sock;

void connectToServer(const char* ip, int port)
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), inet_addr(ip)};

    if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 ){
        cout << "\nRun server program first." << endl; exit(0);
    }else{
        cout << "\nClient is connected to Server." << endl; 
    }
}

int randInRange(int low, int high) // excluding high and low
{
    return rand()%(high-(low+1)) + (low+1) ;
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

void genKey()
{
    cout << "\nEnter two prime numbers (>100) : "; cin >> p >> q;
    n = p * q ;
    phi = (p-1) * (q-1);

    srand(time(NULL));
    do{ e = randInRange(1, phi); } while(gcd(e,phi) != 1);
    for(d=1; d<phi; d++)
    {
        if((d*e)%phi == 1) break;
    }
    
    PUc[0] = e; PUc[1] = n; // public key
    PRc[0] = d; PRc[1] = n; // private key
    cout << "\nPublic key , PUc = {" << e << ", " << n << "}" << endl;
    cout <<   "Private key, PRc = {" << d << ", " << n << "}" << endl;
}

void shareKey() // first receive then send
{
    recv(sock, &PUs, sizeof(PUs), 0); // receive public key from server
    send(sock, &PUc, sizeof(PUc), 0); // send client's public key to server
    cout << "Public key received from server, PUs = {" << PUs[0] << ", " << PUs[1] << "}" << endl;
    cout << "\nSent client's Public key to server." << endl;
}

int powermod(int a, int b, int n)
{
    int res = 1;
    for(int i=0; i<b; i++)
    {
        res = (res*a) % n;
    }
    return res;
}

int encrypt(int M, int PU[2])
{
    return powermod(M, PU[0], PU[1]);
}

int decrypt(int C, int PR[2])
{
    return powermod(C, PR[0], PR[1]);
}

int main()
{
    char ip[50];  cout<<"\nEnter server's IP address: "; cin>>ip;
    int port;     cout<<"Enter port : ";  cin>>port;
    srand(time(NULL));

    connectToServer(ip, port);
    genKey();
    shareKey(); // share public keys

    // step-1: recv cipher from server and Dec(PRc, [N1||ID])
    int cipher;
    recv(sock, &cipher, sizeof(cipher), 0);
    cout << "\nReceived encrypted (N1||ID) from server : " << cipher << endl;
    int msg = decrypt(cipher, PRc);
    int N1 = msg/100;
    int ID = msg%100;
    cout << "Decrypted Server's ID,   IDs = " << ID << endl;
    cout << "Decrypted Server's nonce, N1 = " << N1 << endl;

    // step-2: send En(PUs, (N1||N2)) to server
    int N2 = rand() % 100; // nonce
    cout << "\nNonce generated, N2 = " << N2 << endl;
    msg = N1*100 + N2;
    cipher = encrypt(msg, PUs);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "Sent encrypted (N1||N2) to server : " << cipher << endl;

    // step-3: recv enc(N2) from client and Dec(PRc, N2)
    recv(sock, &cipher, sizeof(cipher), 0);
    cout << "\nReceived encrypted (N2) from server : " << cipher << endl;
    int N2s = decrypt(cipher, PRc);
    cout << "Decrypted Client's Nonce, N2 = " << N2s << endl;
    if(N2s != N2) {cout << "\nNonce didn't match!\n"; exit(-1);}
    else {cout << "----- Server Authenticated -----" << endl;}

    // step-4: recv cipher and perform k = Dec(PUs, Dec(PRc, C))
    int k;
    recv(sock, &cipher, sizeof(cipher), 0);
    cout << "\nReceived cipher from Server : " << cipher << endl;
    k = decrypt(decrypt(cipher, PRc), PUs);
    cout << "Decrypted Secret Key : " << k << endl << endl;
}

/*
Enter server's IP address: 127.0.0.1
Enter port : 8888

Client is connected to Server.

Enter two prime numbers (>100) : 101 181

Public key , PUc = {7477, 18281}
Private key, PRc = {14413, 18281}
Public key received from server, PUs = {4551, 13231}

Sent client's Public key to server.

Received encrypted (N1||ID) from server : 9531
Decrypted Server's ID,   IDs = 29
Decrypted Server's nonce, N1 = 50

Nonce generated, N2 = 23
Sent encrypted (N1||N2) to server : 7905

Received encrypted (N2) from server : 15328
Decrypted Client's Nonce, N2 = 23
-----Authenticated Server-----

Received cipher from Server : 15001
Decrypted Secret Key : 454
*/