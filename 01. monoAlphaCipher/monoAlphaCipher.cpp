/* Author : Natesh */
/******************************************************************************
1. Perform encryption and decryption using mono-alphabetic cipher.The program 
   should support the following:
i.  Construct an input file named plaintext.txt (consisting of 1000 alphabets,
	without any space or special characters)
ii. Compute key space (Permutation of set of all letters appeared in plaintext.txt:
	there are n! permutations of a set of n elements)
iii.Encrypt the characters of plaintext.txt using any one key from (ii)
	and store the corresponding ciphertext characters in ciphertext.txt
iv. Compute the frequency of occurrence of each alphabet in both plaintext.txt
	and ciphertext.txt and tabulate the results as follows
********************************************************************************/

#include<bits/stdc++.h>
using namespace std;

char uniqtext[26]; // Global variable

/* read plain text from plaintext.txt file */
string readPlainText()
{
	ifstream fin;
	string ptext;

	fin.open("plaintext.txt");
	fin >> ptext;
	fin.close();

	return ptext;
}

/* write cipher text to ciphertext.txt file */
void writecipherText(string ctext)
{
	ofstream fout;
	fout.open("ciphertext.txt");
	fout << ctext;
	fout.close();
}

/* function to find all possible permutation */
void permute(char a[], int l, int r, vector<string>& keyspace) // keyspace is passed by reference
{
	if(l == r)
	{
		keyspace.push_back(a);
	}
	else
	{
		for(int i = l; i <= r; i++)
		{
			swap(a[l], a[i]); //inbuilt swap function
			permute(a, l+1, r, keyspace);
			swap(a[l], a[i]);
		}
	}
}

vector<string> genKeySpace(string plaintext)
{
	set<char> uniqSet;
	vector<string> keyspace; // contains all possible permutation of letters in plaintext
	int count = 0;

	/* store all the unique letters of plain text in uniqSet */
	for(int i=0; i < plaintext.length(); i++)
	{
		uniqSet.insert(plaintext[i]);
	}

	/* copy uniqSet to uniqtext char array */
	for(set<char>::iterator it = uniqSet.begin(); it != uniqSet.end(); it++)
	{
		uniqtext[count++] = (*it);
	}

	permute(uniqtext, 0, strlen(uniqtext)-1, keyspace);
	return keyspace;
}

/* create cipher text using key */
string encrypt(string unique, string key)
{
	string plaintext = readPlainText();
	string ciphertext = "";

	for(int i=0; i < plaintext.length(); i++)
	{
		int idx = unique.find(plaintext[i]);
		ciphertext += key[idx];
	}
	return ciphertext;
}

/* frequency = (no of occurance of a character / length of plaintext) */
/* show frequency of all characters of plain text and cipher text */
void showFrequency(string pt , string ct)
{
	map<char , int > mPlain ;
	map<char , int > mCipher ;

	for(int i =0 ;i < pt.length() ; i++)
	{
		mPlain[pt[i]]++ ;
		mCipher[ct[i]]++ ;
	}
	cout<<"\nFrequency\t\tPlaintext Character\t\tCiphertext character" <<endl;
	cout<<"=========\t\t===================\t\t====================" <<endl;
	for(int i=0 ; i<pt.length() ; i++)
	{
		cout<< (float)mPlain[pt[i]]/pt.length() << "\t\t\t\t" << pt[i] << "\t\t\t\t" << ct[i] << endl ;
	}
}

int main()
{
	srand(time(NULL)) ;

	string plaintext = readPlainText() ;
	cout<<"Plain text = \t" << plaintext << endl;

	vector<string> keyspace = genKeySpace(plaintext);
	string key = keyspace[rand()%keyspace.size()];

	cout<<"Unique chars = \t" << uniqtext <<endl;
	cout<<"Chosen key = \t" << key <<endl;

	string ciphertext = encrypt(uniqtext , key) ;
	writecipherText(ciphertext) ; // write ciphertext to file
	showFrequency(plaintext , ciphertext) ;
}


/****************************** OUTPUT-1 ****************************************
Plain text =    HelloWorld
Unique chars =  HWdelor
Chosen key =    WHoedrl

Frequency               Plaintext Character             Ciphertext character
=========               ===================             ====================
0.1                             H                               W
0.1                             e                               e
0.3                             l                               d
0.3                             l                               d
0.2                             o                               r
0.1                             W                               H
0.2                             o                               r
0.1                             r                               l
0.3                             l                               d
0.1                             d                               o

/****************************** OUTPUT-2 ****************************************
Plain text =    workisworship
Unique chars =  hikoprsw
Chosen key =    rphskowi

Frequency               Plaintext Character             Ciphertext character
=========               ===================             ====================
0.153846                                w                               i
0.153846                                o                               s
0.153846                                r                               o
0.0769231                               k                               h
0.153846                                i                               p
0.153846                                s                               w
0.153846                                w                               i
0.153846                                o                               s
0.153846                                r                               o
0.153846                                s                               w
0.0769231                               h                               r
0.153846                                i                               p
0.0769231                               p                               s
***********************************************************************************/