/* Author : AKSHAT AGARWAL 

4. Write a program to perform encryption and decryption using 
   transposition technique with column permutation given as key.  */

#include<bits/stdc++.h>
using namespace std ;

string encrypt(string pt , string key)
{
    string ct = ""; // ciphertext
    int k = 0;      // plaintext iterator

    int num_row = ceil((float) pt.length()/key.length());
    int num_col = key.length();
    char mat[num_row][num_col];
    
    cout << "\nEncryption Matrix :" << endl;
    cout << "---------------------" << endl;
    for(int i=0; i<num_row ; i++)
    {
        for(int j=0; j<num_col; j++)
        {
            if(k < pt.length())
            {
                cout << (mat[i][j] = pt[k++]) << "  ";
            }
            else
            {
                cout << (mat[i][j] = 'x') << "  " ;
            }
        }
        cout << endl;
    }
    for(int i=0; i<num_col; i++)
    {
        for(int j=0; j<num_row; j++)
        {
            ct += mat[j][key.find(i+'1')];
        }
    }
    return ct;
}

string decrypt(string ct , string key)
{
    string pt = ""; // plaintext
    int k = 0; // ciptext iterator

    int num_row = ceil((float)ct.length() / key.length());
    int num_col = key.length();
    char mat[num_row][num_col];

    for(int i=0; i<num_col; i++)
    {
        for(int j=0; j<num_row; j++)
        {
             mat[j][key.find(i+'1')] = ct[k++];
        }
    }

    cout << "\nDecryption Matrix :" << endl;
    cout << "---------------------" << endl;
    for(int i=0; i<num_row ; i++)
    {
        for(int j=0; j<num_col; j++)
        {
            cout << mat[i][j] << "  ";
            pt += mat[i][j];
        }
        cout << endl;
    }
    return pt;
}

int main()
{
    string plaintext , key , ciphertext , decryptext;

    cout << "Enter text : ";
    cin >> plaintext;

    cout << "Enter key  : ";
    cin >> key;

    ciphertext = encrypt(plaintext , key);
    cout << "\nEncrypted text \t: " << ciphertext << endl;

    decryptext = decrypt(ciphertext , key);
    cout << "\nDecrypted text \t: " << decryptext << endl;
}

/*
Enter text : transpositioncipher
Enter key  : 4231

Encryption Matrix :
---------------------
t  r  a  n  
s  p  o  s  
i  t  i  o  
n  c  i  p  
h  e  r  x  

Encrypted text 	: nsopxrptceaoiirtsinh

Decryption Matrix :
---------------------
t  r  a  n  
s  p  o  s  
i  t  i  o  
n  c  i  p  
h  e  r  x  

Decrypted text 	: transpositioncipherx
*/