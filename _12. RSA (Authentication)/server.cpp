# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int p, q, n, phi; // global variables
int PUs[2], PRs[2];
int PUc[2];
int sock;

int createServer(int port)
{
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};

    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "\nServer Online. Waiting for client...." << endl;

    listen(sersock, 5);
    sock = accept(sersock, NULL, NULL);
    cout << "Connection Established." << endl;
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
    
    PUs[2] = {e, n}; // public key
    PRs[2] = {d, n}; // private key
    cout << "\nPublic key , PUs = {" << e << ", " << n << "}" << endl;
    cout <<   "Private key, PRs = {" << d << ", " << n << "}" << endl;
}

void sharekey()
{
    send(sock, &PUs, sizeof(PUs), 0); // send Server's public key to client
    recv(sock, &PUc, sizeof(PUc), 0); // receive public key from client
    
    cout << "\nPublic key received from client : {" << PUc[0] << ", " << PUc[1] << "}" << endl;
    cout << "\nSent Server's Public key to client." << endl;
}

// C = M^e mod n
int encrypt(int M, int P[2])
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
    int port;  cout<<"\nEnter port : ";  cin>>port;
    srand(time(NULL));

    createServer(port);
    genkey();
    shareKey(); // share public keys

    int ID;  cout<<"\nEnter an ID number : "; cin>>ID;
    int N1 = rand()%100; // nonce
    cout << "Nonce, N1 = " << N1;
    
    // step-1: send Enc(PUc, [N1||ID]) to client
    int msg = N1*100 + ID; // append ID to nonce
    int cipher = encrypt(msg, PUc);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "\nSent encrypted nonce and ID to client." << endl;

    // step-2: recv cipher from client and Dec(PRs, (N1||N2))
    recv(sock, &cipher, sizeof(cipher), 0);
    cout << "Received encrypted (N1||N2) from client : " << cipher;
    msg = decrypt(cipher, PRs);
    int N1c = msg/100; // N1 received from client
    int N2 = msg%100;
    cout << "\nDecrypted Server's Nonce, N1 = " << N1c;
    cout << "\nDecrypted Client's Nonce, N2 = " << N2;
    if(N1 != N1c) {cout << "\nNonce didn't match!"; exit(-1);}

    // step-3: send En(PUc, N2) to client
    cipher = encrypt(N2, PUc);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "Sent encrypted N2 to client.";

    // step-4: send M = En(PUc, En(PRs, k))
    int k; // secret key
    cout << "Enter secret key (integer) to send : "; cin >> k;
    cipher = encrypt(encrypt(k,PRs), PUc);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "Sent secret key to client."

    int M; // plaintext message
    cout << "\nEnter message(M<" << PU[1] << ") to encrypt : "; cin >> M;

    int C = encrypt(M, PU);
    cout << "\nEncrypted Text : " << C << endl;
    send(sock, &C, sizeof(C), 0); // send ciphertext to client
    cout << "\nSent ciphertext to client." << endl << endl;
}