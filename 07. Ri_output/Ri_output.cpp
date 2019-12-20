/* Author : AKSHAT AGARWAL 

7. Given 48-bit input to S-box and permutation table P, 
   find the 32-bit output Ri of ith round of DES algorithm.    */

#include <bits/stdc++.h>
using namespace std;

unsigned int sBoxes[8][4][16] = {
   {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},

    {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},

    {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},

    {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},

    {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},

    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,},

    {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},

    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
};

int permTable[] = {
    16, 7 , 20, 21, 29, 12, 28, 17,
    1 , 15, 23, 26, 5 , 18, 31, 10,
    2 , 8 , 24, 14, 32, 27, 3 , 9 ,
    19, 13, 30, 6 , 22, 11, 4 , 25 };

string substitution(string input)
{
    string res = ""; // to store final s-box output
    for(int i=0; i<8; i++)
    {
        string sInput = input.substr(6*i, 6) ;
        int row = bitset<2>( sInput.substr(0,1) + sInput.substr(5,1) ).to_ulong() ;
        int col = bitset<4>( sInput.substr(1,4) ).to_ulong() ;
        res += bitset<4>(sBoxes[i][row][col]).to_string() ;

        // To display individual s-box input and output un-comment this block
        // string value = "";
        // value = bitset<4>(sBoxes[i][row][col]).to_string() ;
        // cout << "sbox-" << i+1 <<  ": \t" << sInput << "\t\t" << value << endl;
    }
    return res;
}

string permute(string input)
{
    string res = "";
    for(int i=0; i<32; i++)
    {
        res += input[permTable[i]-1];
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
    unsigned long long hexSBoxInput, hexInput;

    cout << "\nEnter 48-bit input for S-Box in hex(12-digits)      : " ;
    cin >> hex >> hexSBoxInput;

    cout << "Enter 64-bit (i-1)th round output in hex(16-digits) : " ;
    cin >> hex >> hexInput;

    string sBoxinput = bitset<48>(hexSBoxInput).to_string();
    cout << "\nS-Box Input       : " << sBoxinput << endl;

    string input = bitset<64>(hexInput).to_string();
    cout << " Round(i-1) output : " << input << endl;

    string Li_1 = input.substr(0,32);
    cout << "\nLi_1              : " << Li_1 << endl;

    string sBoxOutput = substitution(sBoxinput);
    cout << "\nS-Box output    = " << sBoxOutput << endl;

    string P = permute(sBoxOutput);
    cout << "Permuted output = " << P << endl;

    string Ri = XOR(P, Li_1); // P is permuted string and Li_1 is left half output of (i-1)th round
    cout << "\nOutput of ith round (Ri) = " << Ri << endl << endl;
}

/******************************* Output-1 ******************************************
Enter 48 bit input for S-Box in hex(12-digits)      : 6117ba866527
Enter 64-bit (i-1)th round output in hex(16-digits) : cc00ccfff0aaf0aa

S-Box Input       : 011000010001011110111010100001100110010100100111
Round(i-1) output : 1100110000000000110011001111111111110000101010101111000010101010
Li_1              : 11001100000000001100110011111111

S-Box output    = 01011100100000101011010110010111
Permuted output = 00100011010010101010100110111011

Output of ith round (Ri) = 11101111010010100110010101000100
***********************************************************************************/
