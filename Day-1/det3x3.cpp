#include <iostream>
#include<cmath>

using namespace std;

int main()
{
    int mat[3][3];
    int det;

    cout << "Enter 3X3 matrix" << endl;

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cin >> mat[i][j];
        }
    }

    det = (mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]))-(mat[0][1]*(mat[1][0]*mat[2][2]-mat[1][2]*mat[2][0]))+(mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]));

    cout << "Determinant = " << det << endl;
}
