# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int connectToServer(const char* ip)
{
    struct sockaddr_in addr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr(ip);

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
    int sock = connectToServer("127.0.0.1");

    int p,q; 
    cout << "\nEnter two large prime numbers : "; cin >> p >> q;
    int n = p * q ;
    int phi = (p-1) * (q-1);

    srand(time(NULL));
    int e, d;
    do{ e = rand()%(phi-2)+2; } while(gcd(e,phi) != 1);
    
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
    string msg = "";
    while (true)
    {
        int C; // ciphertext
        recv(sock, &C, sizeof(C), 0); 
        if(C == -1)   break; // at end -1 will be received 
        cout << "\nCiphertext received from server : " << C << endl;

        int M = decrypt(C,PR);
        cout << "Decrypted Text : " << M << endl;
        msg += char((M/100)+'a'); // first char in block
        msg += char((M%100)+'a'); // second char in block
    }
    cout << "\nDecrypted message : " << msg << endl << endl; 
}

/*
Client is connected to Server.

Enter two large prime numbers : 101 131

Public key , PU = {1007, 13231}
Private key, PR = {2143, 13231}

Sent Public key to server.

Ciphertext received from server : 9189
Decrypted Text : 217

Ciphertext received from server : 4027
Decrypted Text : 2415

Ciphertext received from server : 10957
Decrypted Text : 1914

Ciphertext received from server : 534
Decrypted Text : 617

Ciphertext received from server : 2422
Decrypted Text : 15

Ciphertext received from server : 7387
Decrypted Text : 724

Ciphertext received from server : 8051
Decrypted Text : 1100

Ciphertext received from server : 9570
Decrypted Text : 123

Decrypted message : cryptographylabx
*/

/* Note: large prime number should be provided such that their product should be greater than 2626 */