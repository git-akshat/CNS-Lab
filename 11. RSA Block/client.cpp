/* Author: Akshat Agarwal

11. Implement RSA algorithm to process blocks of plaintext (refer Figure 9.7 of the text book), where plaintext is a string of characters and let the block size be two characters. (Note: assign a unique code to each plain text character i.e., a=00, A=26). The program should support the following.
    - Accept string of characters as plaintext.
    - Encryption takes plaintext and produces ciphertext characters.
    - Decryption takes ciphertext characters obtained in step ii and produces corresponding plaintext characters
    - Display the result after each step  */
    
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

// a=00, b=01, ... A=26, B=27...
char toChar(int n)
{
    return (n >= 26) ? (n+'A'-26) : (n+'a');
}

int main()
{
    char ip[50];
    int port;
    cout << "Enter Server's IP address: "; cin >> ip;
    cout << "Enter port : "; cin >> port;
    int sock = connectToServer(ip, port);

    int p,q; 
    cout << "\nEnter two large prime numbers(>100) : "; cin >> p >> q;
    int n = p * q ; // should be greater than 5151 (since ZZ=5151)
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

    string msg = "";
    while (true)
    {
        int C; // ciphertext
        recv(sock, &C, sizeof(C), 0); 
        if(C == -1)   break; // at the end -1 will be received 
        cout << "\nCiphertext received from server : " << C << endl;

        int M = decrypt(C,PR);
        cout << "Decrypted Text : " << M << endl;
        msg += toChar(M/100); // first char in block
        msg += toChar(M%100); // second char in block
    }
    cout << "\nDecrypted message : " << msg << endl << endl; 
}

/*
Enter Server's IP address: 192.168.224.74
Enter port : 1234

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

/* Note: give p and q values such that p*q > 5151 (since ZZ=5151) */