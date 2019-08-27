#include <bits/stdc++.h>
using namespace std;

typedef struct{
	int row;
	int col;
}position;

char mat[5][5]; // Global Variable

void generateMatrix(string key)
{
    /* to keep tacks of letters that are filled in matrix */
	/* flag = 0 -> letter not present in matrix */
	/* flag = 1 -> letter present in matrix */
    int flag[26] = {0}; 
	int x = 0, y = 0;

    /* Add all characters present in the key */
    for(int i=0; i<key.length(); i++)
    {
        if(key[i] == ' ') continue;
        if(key[i] == 'j') key[i] = 'i'; // i and j are filled at same position 

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

    /* Add remaining characters */
    for(char ch = 'a'; ch <= 'z'; ch++)
    {
        if(ch == 'j') continue; 

        if(flag[ch - 'a'] == 0)
        {
            mat[x][y++] = ch;
            flag[ch - 'a'] = 1 ;
        }

        if(y==5)
		{
			x++;
			y=0;
		}
    }
}

/* function to add filler letter('x') */
string formatMessage(string message)
{
    for(int i=0; i<message.length(); i++)
    {
        if(message[i] == ' ')
        {
            message = message.replace(i, 1, ""); // remove spaces
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

/* Returns the position of the character */
position getPosition(char c)
{
    for(int i=0; i<5; i++)
	{
        for(int j=0; j<5; j++)
		{
            if(c == mat[i][j])
			{
				position p = {i, j};
                return p;
			}
		}
	}
}

string encrypt(string message)
{
    string ctext;
    for(int i=0; i<message.length(); i+=2)    // i is incremented by 2 inorder to group by two two characters
    {
		position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row;
        int x2 = p2.row;
        int y1 = p1.col;
        int y2 = p2.col;

        if( x1 == x2 )
        {
            ctext.append(1, mat[x1][(y1+1)%5]);
            ctext.append(1, mat[x2][(y2+1)%5]);
        }

        else if( y1 == y2 )
        {
            ctext.append(1, mat[ (x1+1)%5 ][ y1 ]);
            ctext.append(1, mat[ (x2+1)%5 ][ y2 ]);
        }

        else
        {
            ctext.append(1, mat[ x1 ][ y2 ]);
            ctext.append(1, mat[ x2 ][ y1 ]);
        }
    }
    return ctext;
}


string Decrypt(string message)
{
    string msg;
    for(int i=0; i<message.length(); i+=2)
    {
        position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row;
        int x2 = p2.row;
        int y1 = p1.col;
        int y2 = p2.col;

        if( x1 == x2 )
        {
            msg.append(1, mat[x1][ --y1<0 ? 4: y1 ]);
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

    cout << "Enter message : ";
    getline(cin, plaintext);

    cout << "Enter number of keys : ";
    cin >> n;
    cin.get();

    string key[n];

    for(int i=0; i<n; i++)
    {
        cout<< "\nEnter key " << i+1 << " : " << key[i];
        getline(cin, key[i]);

        generateMatrix(key[i]);

        cout << "Key " << i+1 << " Matrix:" << endl;
        for(int k=0;k<5;k++)
        {
            for(int j=0;j<5;j++)
            {
                cout << mat[k][j] << "  ";
            }
            cout << endl;
        }
    
        cout << "Actual Message \t\t: " << plaintext << endl;

        string fmsg = formatMessage(plaintext);
        cout << "Formatted Message \t: " << fmsg << endl;

        string ciphertext = encrypt(fmsg);
        cout << "Encrypted Message \t: " << ciphertext << endl;

        string decryptmsg = Decrypt(ciphertext);
        cout<< "Decrypted Message \t: " << decryptmsg << endl;
    }
}

/****************************** OUTPUT *********************************

Enter message : balloon
Enter number of keys : 2

Enter key 1 : monarchy
Key 1 Matrix:
m  o  n  a  r
c  h  y  b  d
e  f  g  i  k
l  p  q  s  t
u  v  w  x  z
Actual Message          : balloon
Formatted Message       : balxloon
Encrypted Message       : ibsupmna
Decrypted Message       : balxloon

Enter key 2 : playfair
Key 2 Matrix:
p  l  a  y  f
i  r  b  c  d
e  g  h  k  m
n  o  q  s  t
u  v  w  x  z
Actual Message          : balloon
Formatted Message       : balxloon
Encrypted Message       : hbyvrvqo
Decrypted Message       : balxloon

*********************************************************************/