/* Author : AKSHAT AGARWAL 

10. Implement RSA algorithm using client-server concept. The program should support the following :
    - Client generates {PU, PR} and distributes PU to Server.
    - Sever encrypts message M using client’s public key {PU}.
    - Client decrypts the message sent by server using its private key {PR} */

/* Client Program */

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

int randInRange(int low, int high) // excluding high and low
{
    return rand()%(high-(low+1)) + (low+1) ;
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
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

// M = C^d mod n
int decrypt(int C, int PR[2])
{
    return powermod(C, PR[0], PR[1]);
}

int main()
{
    char ip[50];
    int port;
    cout << "\nEnter server's IP address: "; cin >> ip;
    cout << "Enter port : ";                 cin >> port;
    int sock = connectToServer(ip, port);

    int p,q; 
    cout << "\nEnter two prime numbers : "; cin >> p >> q;
    int n = p * q ;
    int phi = (p-1) * (q-1);

    srand(time(NULL));
    int e, d;
    do{ e = randInRange(1, phi); } while(gcd(e,phi) != 1);
    
    for(d=1; d<phi; d++)
    {
        if((d*e)%phi == 1) break;
    }
    
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