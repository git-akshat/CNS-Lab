/* Author : AKSHAT AGARWAL 

12. Implement RSA algorithm using client-server concept. Using this illustrate secret key distribution scenario with confidentiality and authentication. The program should support the following :
    - Both client and server generate {PU, PR} and distribute PU to each other.
    - Establish a secret key K between client and server by exchanging the messages as shown in below figure.
    ![fig-12]("https://github.com/git-akshat/CNS-Lab/blob/master/12.%20RSA%20(Authentication/)/figure.png") */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

/* Server Program */

# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int p, q, e, d, n, phi; // global variables
int PUs[2], PRs[2];     // server's keys
int PUc[2];             // client's public key
int sock;

void createServer(int port)  // TCP connection
{
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};

    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "\nServer Online. Waiting for client...." << endl;

    listen(sersock, 5);
    sock = accept(sersock, NULL, NULL);
    cout << "Connection Established." << endl;
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
    cout << "\nEnter two prime numbers (>100): "; cin >> p >> q;
    n = p * q ;
    phi = (p-1) * (q-1);

    srand(time(NULL));
    do{ e = randInRange(1, phi); } while(gcd(e,phi) != 1);
    for(d=1; d<phi; d++)
    {
        if((d*e)%phi == 1) break;
    }
    
    PUs[0] = e; PUs[1] = n; // public key
    PRs[0] = d; PRs[1] = n; // private key
    cout << "\nPublic key , PUs = {" << e << ", " << n << "}" << endl;
    cout <<   "Private key, PRs = {" << d << ", " << n << "}" << endl;
}

void shareKey() // first send then receive
{
    send(sock, &PUs, sizeof(PUs), 0); // send Server's public key to client
    recv(sock, &PUc, sizeof(PUc), 0); // receive public key from client
    cout << "Sent Server's Public key to client." << endl;
    cout << "\nPublic key received from client : {" << PUc[0] << ", " << PUc[1] << "}" << endl;
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
    int port;  cout<<"\nEnter port : ";  cin>>port;
    srand(time(NULL));

    createServer(port);
    genKey();
    shareKey(); // share public keys

    int ID;  cout<<"\nEnter Server's ID number (<100): "; cin>>ID;
    int N1 = rand()%100; // nonce
    cout << "Nonce generated, N1 = " << N1 << endl;
    
    // step-1: send En(PUc, [N1||ID]) to client
    int msg = N1*100 + ID; // append ID to nonce
    int cipher = encrypt(msg, PUc);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "Sent encrypted (N1||ID) to client : " << cipher << endl;

    // step-2: recv cipher from client and Dec(PRs, (N1||N2))
    recv(sock, &cipher, sizeof(cipher), 0);
    cout << "\nReceived encrypted (N1||N2) from client : " << cipher << endl;
    msg = decrypt(cipher, PRs);
    int N1c = msg/100; // N1 received from client
    int N2 = msg%100;
    cout << "Decrypted Server's Nonce, N1 = " << N1c << endl;
    cout << "Decrypted Client's Nonce, N2 = " << N2 << endl;
    if(N1 != N1c) {cout << "\nNonce didn't match!\n"; exit(-1);}
    else {cout << "------ Client Authenticated ------" << endl;}

    // step-3: send En(PUc, N2) to client
    cipher = encrypt(N2, PUc);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "\nSent encrypted (N2) to client : " << cipher << endl;

    // step-4: send C = En(PUc, En(PRs, k))
    int k; // secret key
    cout << "\nEnter secret key (integer) to send : "; cin >> k;
    cipher = encrypt(encrypt(k,PRs), PUc);
    send(sock, &cipher, sizeof(cipher), 0);
    cout << "Sent encrypted secret key to client : " << cipher << endl << endl;
}

/*
Enter port : 8888

Server Online. Waiting for client....
Connection Established.

Enter two prime numbers (>100): 101 131

Public key , PUs = {4551, 13231}
Private key, PRs = {1951, 13231}
Sent Server's Public key to client.

Public key received from client : {7477, 18281}

Enter Server's ID number (<100): 29
Nonce generated, N1 = 50
Sent encrypted (N1||ID) to client : 9531

Received encrypted (N1||N2) from client : 7905
Decrypted Server's Nonce, N1 = 50
Decrypted Client's Nonce, N2 = 23
----Authenticated client----

Sent encrypted (N2) to client : 15328

Enter secret key (integer) to send : 454 
Sent encrypted secret key to client : 15001
*/