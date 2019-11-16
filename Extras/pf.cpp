/* playfair with multi level encrption */
#include <bits/stdc++.h>
using namespace std;

char mat[5][5];

void generateMatrix(string key)
{
    int flag[26] = {0}; //to store occurrance of a character
    int x = 0, y = 0;

    // Add all characters present in a given key
    for(int i=0; i<key.length(); i++)
    {
        if(key[i]==' ') continue;
        if(key[i]=='j') key[i] = 'i';

        if(flag[key[i]-'a'] == 0)
        {
            mat[x][y++] = key[i];
            flag[key[i]-'a'] = 1;
        }

        if(y==5)
        {
            x++;
            y=0;
        }
    }

    // Add all other characters
    for(int i=0; i<26; i++)
    {
        if(i==9)    continue; // 'i' - 'a' = 9
        if(key[i] == 'j')   key[i]='i';

        if(flag[i] == 0)
        {
            mat[x][y++] = i + 'a';
            flag[i] = 1 ;
        }

        if(y==5)
        {
            x++;
            y=0;
        }
    }
}

string formatMessage(string message)
{
    for(int i=0; i<message.length(); i++)
    {
        if(message[i] == ' ')   // add conditions here for any other special characters
        {
            message = message.replace(i, 1, "");
        }

        if(message[i] == 'j')
        {
            message[i] = 'i';
        }
    }

    for(int i=1; i<message.length(); i+=2)
    {
        if(message[i-1] == message[i])
        {
            message = message.insert(i, "x");
        }
    }

    if(message.length()%2 != 0)
    {
        message += "x";
    }

    return message;
}

// Returns the row position of the given character in a mat
int getRow(char c)
{
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(c==mat[i][j])
                return i;
}

int getColumn(char c)
{
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(c==mat[i][j])
                return j;
}

string encrypt(string message)
{
    string ctext;
    for(int i=0;i<message.length();i+=2)    // i is incremented by 2 inorder to group by two two characters
    {
        int x1 = getRow(message[i]);
        int y1 = getColumn(message[i]);
        int x2 = getRow(message[i+1]);
        int y2 = getColumn(message[i+1]);

        if( x1 == x2 )
        {
            ctext.append(1, mat[x1][(y1+1)%5]);
            ctext.append(1, mat[x2][(y2+1)%5]);
        }

        else if( y1 == y2 )
        {
            ctext.append(1, mat[(x1+1)%5][y1]);
            ctext.append(1, mat[(x2+1)%5][y2]);
        }

        else
        {
            ctext.append(1, mat[ x1 ][ y2 ]);
            ctext.append(1, mat[ x2 ][ y1 ]);
        }
    }
    return ctext;
}

string decrypt(string message)
{
    string msg;
    for(int i=0; i<message.length(); i+=2)
    {
        int x1 = getRow(message[i]);
        int y1 = getColumn(message[i]);
        int x2 = getRow(message[i+1]);
        int y2 = getColumn(message[i+1]);

        if( x1 == x2 )
        {
            msg.append(1, mat[x1][ --y1<0 ? 4: y1 ]);   // to handle negative modlus  if(negative) 4 else num-1
            msg.append(1, mat[x2][ --y2<0 ? 4: y2 ]);
        }

        else if( y1 == y2 )
        {
            msg.append(1, mat[ --x1<0 ? 4: x1 ][y1]);
            msg.append(1, mat[ --x2<0 ? 4: x2 ][y2]);
        }

        else
        {
            msg.append(1, mat[ x1 ][ y2 ]);
            msg.append(1, mat[ x2 ][ y1 ]);
        }
    }
    return msg;
}


int main()
{
    int n; // number of keys
    string plaintext;

    cout << "Enter the number of keys : ";
    cin >> n;
    cin.get();

    string key[n];
    for(int i=0; i<n; i++)
    {
        cout << "key" <<i+1 <<" : ";
        getline(cin, key[i]);
    }

    cout << "Enter message to be encrypted : ";
    getline(cin, plaintext);

    string ciphertext = plaintext;

    for(int i=0; i<n; i++)
    {
        string fmsg = formatMessage(ciphertext);
        generateMatrix(key[i]);
        cout<<"----------------------------"<<endl;
        cout<<"Using key"<<i+1<<": "<<key[i]<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"Key Matrix: "<<endl;
        for(int k=0;k<5;k++)
        {
            for(int j=0;j<5;j++)
            {
                cout<<mat[k][j]<<" ";
            }
            cout<<endl;
        }

        cout << "Actual Message : "<< ciphertext << endl;

        cout << "Formatted Message : "<< fmsg << endl;

        ciphertext = encrypt(fmsg);

        cout << "Encrypted Message : " << ciphertext << endl;


    }


    cout << "\n-->To Decrypt back the message press 'ENTER' key" <<endl;
    cin.get();

    string dmsg = ciphertext;
    for(int i=n-1; i>=0; i--)
    {
        generateMatrix(key[i]);
        cout<<"----------------------------"<<endl;
        cout<<"Using key"<<i+1<<": "<<key[i]<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"Key Matrix: "<<endl;
        for(int k=0;k<5;k++)
        {
            for(int j=0;j<5;j++)
            {
                cout<<mat[k][j]<<" ";
            }
            cout<<endl;
        }

        cout << "Message to be decrypted: "<< dmsg << endl;

        dmsg = decrypt(dmsg);
        cout << "Decrypted Message : " << dmsg << endl;
    }
}

/********************** Output ********************************
Enter the number of keys : 2
key1 : monarchy
key2 : playfair
Enter message to be encrypted : balloon
----------------------------
Using key1: monarchy
----------------------------
Key Matrix:
m o n a r
c h y b d
e f g i k
l p q s t
u v w x z
Actual Message : balloon
Formatted Message : balxloon
Encrypted Message : ibsupmna
----------------------------
Using key2: playfair
----------------------------
Key Matrix:
p l a y f
i r b c d
e g h k m
n o q s t
u v w x z
Actual Message : ibsupmna
Formatted Message : ibsupmna
Encrypted Message : rcnxfeqp

-->To Decrypt back the message press 'ENTER' key

----------------------------
Using key2: playfair
----------------------------
Key Matrix:
p l a y f
i r b c d
e g h k m
n o q s t
u v w x z
Message to be decrypted: rcnxfeqp
Decrypted Message : ibsupmna
----------------------------
Using key1: monarchy
----------------------------
Key Matrix:
m o n a r
c h y b d
e f g i k
l p q s t
u v w x z
Message to be decrypted: ibsupmna
Decrypted Message : balxloon
********************************************************************/
