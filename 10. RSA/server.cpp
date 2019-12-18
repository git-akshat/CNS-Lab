/* Author : AKSHAT AGARWAL 

10. Implement RSA algorithm using client-server concept. The program should support the following :
    - Client generates {PU, PR} and distributes PU to Server.
    - Sever encrypts message M using client’s public key {PU}.
    - Client decrypts the message sent by server using its private key {PR} */

/* Server Program */

# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int createServer(int port) // TCP connection
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

int powermod(int a, int b, int n)
{
    int res = 1;
    for(int i=0; i<b; i++)
    {
        res = (res*a) % n;
    }
    return res;
}

// C = M^e mod n
int encrypt(int M, int PU[2]) // PU = {e, n}
{
    return powermod(M, PU[0], PU[1]);
}

int main()
{
    int port;
    cout << "\nEnter port : "; cin >> port;
    int sock = createServer(port);

    int PU[2];
    recv(sock, &PU, sizeof(PU), 0); // receive public key from client
    cout << "\nPublic key received from client : {" << PU[0] << ", " << PU[1] << "}" << endl;

    int M; // plaintext message (M < n)
    cout << "\nEnter message(M<" << PU[1] << ") to encrypt : "; cin >> M;

    int C = encrypt(M, PU);
    cout << "\nEncrypted Text : " << C << endl;
    send(sock, &C, sizeof(C), 0); // send ciphertext to client
    cout << "\nSent ciphertext to client." << endl << endl;
}

/*
Enter port : 4444

Server Online. Waiting for client....
Connection Established.

Public key received from client : {3, 391}

Enter message(M<391) to encrypt : 231

Encrypted Text : 116

Sent ciphertext to client.
*/