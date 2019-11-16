#include <iostream>
#include<cmath>

using namespace std;

int main()
{
    int mat[2][2];
    int det;

    cout << "Enter 2X2 matrix" << endl;

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            cin >> mat[i][j];
        }
    }

    det = ( mat[0][0] * mat[1][1] ) - ( mat[1][0] * mat[0][1]);

    cout << "Determinant = " << det << endl;
}
