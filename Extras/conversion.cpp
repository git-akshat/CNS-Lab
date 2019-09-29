string DecToBin(int dec)
{
    string bin = ""; // binary
    for(int i=0; i<4; i++) // to generate 4-bit binary
    {
        bin += (char) (dec%2 + '0');
        dec = dec/2;
    }
    reverse(bin.begin(), bin.end()); // inbuilt function
    return bin;
}

int BinToDec(string bin)
{
    int dec = 0; // decimal
    int base = 1; // power of 2 variable

    for(int i = bin.length()-1 ; i>=0 ; i--)
    {
        if(bin[i] == '1')
        {
            dec += base;
        }
        base = base * 2;
    }
    return dec;
}