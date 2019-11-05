# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int createServer(int port)
{
    struct sockaddr_in addr;
 
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); 
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "\nServer Online. Waiting for client...." << endl;

    listen(sersock, 5);
    int sock = accept(sersock, NULL, NULL);
    cout << "Connection Established." << endl;

    return sock;
}

// C = M^e mod n
int encrypt(int M, int PU[2])
{
    int C=1;
    for(int i=1; i<=PU[0]; i++)
    {
        C = (C * M) % PU[1];
    }
    return C;
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

    for(int i=0; i<msg.length(); i+=2)
    { 
        int M = (tolower(msg[i])-'a')*100 + tolower(msg[i+1])-'a'; // block consist of two msg character 
        cout << "\nPlaintext block : " << M << endl;

        int C = encrypt(M, PU);
        cout << "Encrypted text  : " << C << endl;
        send(sock, &C, sizeof(C), 0); // send ciphertext to client
    }
    int stop = -1;
    send(sock, &stop, sizeof(stop), 0); //at end send -1 to client
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