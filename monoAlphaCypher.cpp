/*Perform encryption and decryption using mono-alphabetic cipher. The program should support the following:
i.	Construct an input file named plaintext.txt (consisting of 1000 alphabets, without any space or special characters) 
ii.	Compute key space (Permutation of set of all letters appeared in plaintext.txt: there are n! permutations of a set of n elements)
iii.Encrypt the characters of plaintext.txt using any one key from (ii) and store the corresponding ciphertext characters in ciphertext.txt
iv.	Compute the frequency of occurrence of each alphabet in both plaintext.txt and ciphertext.txt and tabulate the results as follows	*/

#include<bits/stdc++.h>

using namespace std;

char uniq[26]; // Global variable

string readPlainText(const char* fname="plaintext.txt")
{
	ifstream fin;
	string ptext;

	fin.open(fname);
	fin >> ptext;
	fin.close();

	return ptext;
}

void writeCypherText(string ctext, const char*  fname="cyphertext.txt")
{
	ofstream fout;

	fout.open(fname);
	fout << ctext;
	fout.close();
}

//function to find all possible permutation
void permute(char a[], int l, int r, vector<string>& keyspace)
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
	set<char> uniqText;
	vector<string> keyspace; // contains all possible permutation of letters in plaintext
	int count = 0;

	// store all the letters of plain text in uniqtext
	for(int i=0; i < plaintext.length(); i++)
	{
		uniqText.insert(plaintext[i]);
	}


	//copy uniqtext set to a string utext
	for(set<char>::iterator it = uniqText.begin(); it != uniqText.end(); it++)
	{
		uniq[count++] = (*it);
	}


	cout << "unique letters of plain text : " << string(uniq) << endl;

	permute(uniq, 0, uniqText.size() - 1, keyspace);

	return keyspace;
}

string encrypt(string unique, string key)
{
	string plaintext = readPlainText();
	string cyphertext = "";

	for(int i=0; i < plaintext.length(); i++)
	{
		int idx = unique.find(plaintext[i]);
		cyphertext += key[idx];
	}

	return cyphertext;
}



void showFrequency(string pt , string ct){
	map<char , char > mPlain ;
	map<char , char > mCipher ;

	for(int i =0 ;i < pt.length() ; i++){
		mPlain[pt[i]]++ ;
		mCipher[ct[i]]++ ;
	}

	cout<<"Frequency\t\tPlaintext Character\t\tCiphertext character" <<endl;
	cout<<"=========\t\t===================\t\t====================" <<endl;
	for(int i =0 ;i < pt.length() ; i++){
		cout<< (float)mPlain[pt[i]]/pt.length() << "\t\t\t" << pt[i] << "\t\t\t" << ct[i] << endl ;
	}
}

int main()
{
	srand(time(NULL)) ;

	string plaintext = readPlainText() ;
	cout<<"Plain text = \t" << plaintext << endl;

	vector<string> keyspace = genKeySpace(plaintext);

	string key = keyspace[rand()%keyspace.size()];

	cout<<"Unique chars = \t" << uniq <<endl;
	cout<<"Chosen key = \t" << key <<endl;

	string cyphertext = encrypt(uniq , key) ;
	writeCypherText(cyphertext) ;
	showFrequency(plaintext , cyphertext) ;
}


