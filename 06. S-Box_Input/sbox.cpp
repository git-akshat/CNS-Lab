/* Author : AKSHAT AGARWAL 

6. Given 64-bit output of (i-1)th round of DES, 48-bit ith round key Ki and E table, find the 48-bit input for S-box.	*/

#include <bits/stdc++.h>
using namespace std;

int expPermute[] = {
	32, 1 , 2 , 3 , 4 , 5 ,
	4 , 5 , 6 , 7 , 8 , 9 ,
	8 , 9 , 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1 };

string expansionPermute(string input)
{
	string res = "";
	for(int i=0; i<48; i++)
	{
		res += input[expPermute[i]-1];
	}
	return res;
}

string XOR(string input1, string input2)
{
	string res = "";
	for(int i=0; i<input1.length(); i++)
	{
		res += (input1[i] == input2[i]) ? "0" : "1";
	}
	return res;
}

int main()
{
	int i; // round i
	unsigned long long hexInput;
	string Ki; // ith round key
	ifstream fin;

	cout << "\nEnter Round number (i) : ";
	cin >> i;

	cout << "Enter 64-bit (i-1)th round output in hex: " ;
	cin >> hex >> hexInput;
	string input = bitset<64>(hexInput).to_string();

	fin.open("keygen.txt");
	for(int j=1; j<=i; j++)
	{
		fin >> Ki;
	}

	// ---- To insert key manually uncomment below lines ---
	// unsigned long long hexKey;
	// cout << "Enter 48 bit key for ith round: " ;
	// cin >> hex >> hexKey;
	// Ki = bitset<48>(hexKey).to_string();

	if(Ki.length() == 0)
	{
		cout << "\nkeygen.txt not found !!! \n" << endl;
		exit(1);
	}

	cout << "\n64-bit Binary Input = " << input << endl ;
	cout << "key for ith round (Ki) = " << Ki << endl ;

	string Ri_1 = input.substr(32,32); // 32 bit Right half of input R[i-1]
	cout << "\nRight half of 64-bit input, Ri_1 = " << Ri_1 << endl;

	string R48 = expansionPermute(Ri_1);
	cout << "Ri_1 after expansion permutation = " << R48 << endl;

	string sBoxInput = XOR(R48, Ki);
	cout << "\nInput to s-box : " << sBoxInput << endl << endl;
}

/******************************* Output-1 ******************************************
Enter Round number (i) : 1
Enter 64-bit (i-1)th round output in hex: cc00ccfff0aaf0aa

64-bit Binary Input = 1100110000000000110011001111111111110000101010101111000010101010
key for ith round (Ki) = 000110110000001011101111111111000111000001110010

Right half of 64-bit input, Ri_1 = 11110000101010101111000010101010
Ri_1 after expansion permutation = 011110100001010101010101011110100001010101010101

Input to s-box : 011000010001011110111010100001100110010100100111
************************************************************************************/