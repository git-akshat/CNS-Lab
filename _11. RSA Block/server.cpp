# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int connectToClient(const char* ip)
{
    struct sockaddr_in addr;
 
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); 
    addr.sin_addr.s_addr = inet_addr(ip);

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
    int sock = connectToClient("127.0.0.1");

    int PU[2];
    recv(sock, &PU, sizeof(PU), 0); // receive public key from client
    cout << "\nPublic key received from client : {" << PU[0] << ", " << PU[1] << "}" << endl;

    String msg; // plaintext message
    cout << "\nEnter message to encrypt : "; cin >> M;

    // string m1 = msg[itr++];
    //     string m2 = msg[itr++];
    //     string temp1 = (msg[itr]-97 < 10) ? ("0" + msg[itr++]-97) : (msg[itr++]-97);
    //     string temp2 = (msg[i+1]-97 < 10) ? ("0" + msg[i+1]-97) : (msg[i]-97);
    if(msg.length()% 2 != 0) msg += "x";
    for(int i=0; i<msg.length()-1; i+=2)
    { 
        int M = (msg[i]-'a')*100 + msg[i+1]-'a';
        int C = encrypt(M, PU);
        cout << "\nEncrypted Text : " << C << endl;
        send(sock, &C, sizeof(C), 0); // send ciphertext to client
    }
    send(sock, -1, sizeof(C), 0);
    cout << "\nSent ciphertext to client." << endl << endl;
}

/* 
akshat@pop-os:~/Desktop$ g++ server.cpp -o s.out
akshat@pop-os:~/Desktop$ ./s.out

Server Online. Waiting for client....
Connection Established.

Public key received from client : {3, 391}

Enter message(M<391) to encrypt : 231

Encrypted Text : 116

Sent ciphertext to client.
*/