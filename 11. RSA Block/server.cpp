/* Author: Akshat Agarwal

11. Implement RSA algorithm to process blocks of plaintext (refer Figure 9.7 of the text book), where plaintext is a string of characters and let the block size be two characters. (Note: assign a unique code to each plain text character i.e., a=00, A=26). The program should support the following.
    - Accept string of characters as plaintext.
    - Encryption takes plaintext and produces ciphertext characters.
    - Decryption takes ciphertext characters obtained in step ii and produces corresponding plaintext characters
    - Display the result after each step  */

/* Server Program */

# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int createServer(int port)  // TCP connection
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

// a=00, b=01, ... A=26, B=27...
int toInt(char c)
{
    return (c < 'a') ? (c-'A'+26) : (c-'a');
}

int main()
{
    int port;
    cout << "Enter port : "; cin >> port;
    int sock = createServer(port);

    int PU[2];
    recv(sock, &PU, sizeof(PU), 0); // receive public key from client
    cout << "\nPublic key received from client : {" << PU[0] << ", " << PU[1] << "}" << endl;

    string msg; // plaintext message
    cout << "\nEnter message to encrypt : "; cin >> msg;
    
    if(msg.length()% 2 != 0) msg+="x";

    for(int i=0; i<msg.length(); i+=2) // increment by 2 for block
    { 
        int M = toInt(msg[i])*100 + toInt(msg[i+1]); // block consist of two msg character 
        cout << "\nPlaintext block : " << M << endl;

        int C = encrypt(M, PU);
        cout << "Encrypted text  : " << C << endl;
        send(sock, &C, sizeof(C), 0); // send ciphertext to client
    }
    int stop = -1; // at end send -1 to tell client to stop
    send(sock, &stop, sizeof(stop), 0); //at end send stop to client
    cout << "\nSent ciphertext to client." << endl << endl;
}

/* 
Enter port : 1234

Server Online. Waiting for client....
Connection Established.

Public key received from client : {1007, 13231}

Enter message to encrypt : cryptographylab

Plaintext block : 217
Encrypted text  : 9189

Plaintext block : 2415
Encrypted text  : 4027

Plaintext block : 1914
Encrypted text  : 10957

Plaintext block : 617
Encrypted text  : 534

Plaintext block : 15
Encrypted text  : 2422

Plaintext block : 724
Encrypted text  : 7387

Plaintext block : 1100
Encrypted text  : 8051

Plaintext block : 123
Encrypted text  : 9570

Sent ciphertext to client.
*/