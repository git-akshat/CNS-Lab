# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int p, q, n, phi; // global variables
int PUc[2], PRc[2];
int PUs[2];
int sock;

int connectToServer(const char* ip, int port)
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), inet_addr(ip)};

    if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 ){
        cout << "\nRun server program first." << endl; exit(0);
    }else{
        cout << "\nClient is connected to Server." << endl; 
    }
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

void genKey()
{
    cout << "\nEnter two prime numbers : "; cin >> p >> q;
    int n = p * q ;
    int phi = (p-1) * (q-1);

    int e, d;
    srand(time(NULL));
    do{ e = rand()%(phi-2)+2; } while(gcd(e,phi) != 1);
    for(d=1; d<phi; d++)
    {
        if((d*e)%phi == 1) break;
    }
    
    PUc[2] = {e, n}; // public key
    PRc[2] = {d, n}; // private key
    cout << "\nPublic key , PUc = {" << e << ", " << n << "}" << endl;
    cout <<   "Private key, PRc = {" << d << ", " << n << "}" << endl;
}

void shareKey()
{
    recv(sock, &PUs, sizeof(PUs), 0); // receive public key from server
    send(sock, &PUc, sizeof(PUc), 0); // send client's public key to server

    cout << "\nPublic key received from server : {" << PUs[0] << ", " << PUs[1] << "}" << endl;
    cout << "\nSent client's Public key to server." << endl;
}

// M = C^d mod n
int encryptDecrypt(int M, int P[2])
{
    int C=1;
    for(int i=1; i<=P[0]; i++)
    {
        C = (C * M) % P[1];
    }
    return C;
}

int decrypt(int C, int P[2])
{
    return encrypt(C,P);
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
    cout << "Received encrypted (N1||ID) from server : " << cipher;
    int msg = decrypt(cipher, PRc);
    int N1 = msg/100;
    int ID = msg%100;
    cout << "\nServer's nonce, N1 = " << N1;
    cout << "\nServer's ID = " << ID;

    // step-2: send En(PUs, (N1||N2)) to server
    int N2 = rand() % 100; // nonce
    msg = N1*100 + N2;
    cipher = encrypt(msg, PUs);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "Sent encrypted (N1||N2) to server.";

    // step-3: recv enc(N2) from client and Dec(PRc, N2)
    recv(sock, &cipher, sizeof(cipher), 0);
    int N2s = decrypt(cipher, PRc);
    cout << "\nDecrypted Client's Nonce, N2 = " << N2s;
    if(N2s != N2) {cout << "\nNonce didn't match!"; exit(-1);}

    // step-4: recv cipher and perform k = Dec(PUs, Dec(PRc, M))
    int k;
    recv(sock, &cipher, sizeof(cipher), 0);
    k = decrypt(decrypt(cipher, PRc), PUs);
    cout << "Decrypted Secret Key : " << k;

    int M = decrypt(C, PR); // decrypted text
    cout << "\nDecrypted Text : " << M << endl << endl;
}