/**
    A = LU => Ax = B <=> LUx = B => Ly = B and Ux = y

    L = [ 1       0       0 ...       0 ]       l[1][1] = l[2][2] = l[3][3] = ... = l[n][n] = 1
        [ l[2][1] 1       0...        0 ]       l[i][j] = 0 ( i : 1 -> n, j > i )
        [ l[3][1] l[3][2] 1 ...       0 ]
        ...
        [ l[n][1] l[n][2] l[n][3] ... 1 ]

    U = [ u[1][1] u[1][2] ... u[1][n] ]         u[i][j] = 0 ( i : 1 -> n, j < i )
        [ 0       u[2][2] ... u[2][n] ]
        ...
        [ 0       0 ...       u[n][n] ]
*/
#include <bits/stdc++.h>

using namespace std;

signed main(){
    int N;

    cout << "Size of matrix N : " ; cin >> N;
    cout << "Matrix :\n";

    vector<double> arr[N], L[N], U[N];

    for(int i = 0;i < N;i ++){
        for(int j = 0;j <= N;j ++){
            double aij; cin >> aij;

            arr[i].push_back(aij);

            if(j == N) continue;

            L[i].push_back((i == j) ? 1.0 : 0.0);
            U[i].push_back(0.0);
        }
    }

    if(arr[0][0] == 0.0){
        cout << "Factorization impossible";
        return 0;
    }

    U[0][0] = arr[0][0] / L[0][0];

    for(int i = 1;i < N;i ++){
        U[0][i] = arr[0][i] / L[0][0];  /// first row of U
        L[i][0] = arr[i][0] / U[0][0];  /// first column of L
    }

    for(int i = 1;i < N;i ++){
        double A = arr[i][i];
        for(int k = 0;k < i;k ++){
            A -= L[i][k] * U[k][i];
        }

        if(i+1 < N && A == 0.0){
            cout << "Factorization impossible";
            return 0;
        }

        U[i][i] = A / L[i][i];

        for(int j = i+1;j < N;j ++){
            A = arr[i][j];
            for(int k = 0;k < i;k ++){
                A -= L[i][k] * U[k][j];
            }

            U[i][j] = A / L[i][i];  /// i-th row of U
            ///------------------------------------------
            A = arr[j][i];
            for(int k = 0;k < i;k ++){
                A -= L[j][k] * U[k][i];
            }

            L[j][i] = A / U[i][i];  /// i-th column of L
        }
    }

    /// solve
    /**
        Ax = B <-> LUx = B -> Ly = B and Ux = y
    */
    vector<double> y(N, 0.0), x(N, 0.0);
    for(int i = 0;i < N;i ++){
        double A = arr[i][N];   /// B[i]

        for(int j = 0;j < i;j ++){
            A -= L[i][j] * y[j];
        }

        y[i] = A / L[i][i];
    }

    for(int i = N-1;i >= 0;i --){
        double A = y[i];

        for(int j = i+1;j < N;j ++){
            A -= U[i][j] * x[j];
        }

        x[i] = A / U[i][i];
    }

    /// output
    cout << "solution : \n";
    for(int i = 0;i < N;i ++){
        cout << "x[" << i+1 << "] : " << setprecision(4) << fixed << x[i] << "\n";
    }

    return 0;
}
