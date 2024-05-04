/**
    A = L*L_T => Ax = B <=> LL_Tx = B => Ly = B and L_Tx = y

    A must satisfy some conditions to be factorize like that
    In case A is OK, we only need to find L, then L_T can be inferred from L
*/
#include <bits/stdc++.h>

using namespace std;

/// Function to create a sub-matrix (minor) excluding a row and column
vector<vector<double> > minor(vector<vector<double> > matrix, int n, int row, int col) {
      vector<vector<double> > newMatrix(n-1, vector<double>(n-1, 0.0));
      int k = 0, l = 0;

      for (int i = 0; i < n; i++) {
        if(i == row) continue;

        for (int j = 0; j < n; j++) {
            if(j == col) continue;

            newMatrix[k][l] = matrix[i][j];

            l++;
            if (l+1 >= n) {
              l = 0;
              k++;
            }
        }

      }

      return newMatrix;
}

double fDet(vector<vector<double> > matrix, int n) {
      /// Base cases
      if (n == 1) {
            return matrix[0][0];
      } else if (n == 2) {
            return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
      }

      /// Recursive case: calculate determinant using cofactor expansion
      double det = 0.0;
      for (int i = 0; i < n; i++) {
            double cofactor = fDet(minor(matrix, n, 0, i), n - 1);

            det += matrix[0][i] * cofactor * ((i % 2) ? -1.0 : 1.0);
      }

      return det;
}

signed main(){
    int N;

    cout << "Size of matrix N : " ; cin >> N;
    cout << "Matrix :\n";

    vector<double> arr[N];

    for(int i = 0;i < N;i ++){
        for(int j = 0;j <= N;j ++){
            double aij; cin >> aij;

            arr[i].push_back(aij);
        }
    }

    /// we need to check A first
    /// check A doi xung ? a[i][j] = a[j][i] ?
    for(int i = 0;i < N;i ++){
        for(int j = 0;j < N;j ++){
            if(arr[i][j] != arr[j][i]){
                cout << "cannot factorize A";
                return 0;
            }
        }
    }

    /// check A xac dinh duong ? -> moi det chinh deu > 0
    for(int i = 1;i <= N;i ++){
        vector<vector<double> > new_arr(i, vector<double>(i, 0.0));
        for(int j = 0;j < i;j ++){
            for(int k = 0;k < i;k ++){
                new_arr[j][k] = arr[j][k];
            }
        }

        double det = fDet(new_arr, i);

        if(det > 0.0) continue;

        cout << "cannot factorize A";
        return 0;
    }

    /// factorize matrix A
    vector<double> L[N];
    for(int i = 0;i < N;i ++){
        for(int j = 0;j < N;j ++){
           L[i].push_back(0.0);
        }
    }

    /// find L
    L[0][0] = sqrt(arr[0][0]);
    for(int i = 1;i < N;i ++){
        L[i][0] = arr[i][0] / L[0][0];  /// first column of L
    }

    for(int i = 1;i < N;i ++){
        double A = arr[i][i];
        for(int k = 0;k < i;k ++){
            A -= L[i][k] * L[i][k];
        }

        L[i][i] = sqrt(A);

        for(int j = i+1;j < N;j ++){
            A = arr[j][i];
            for(int k = 0;k < i;k ++){
                A -= L[j][k] * L[i][k];
            }

            L[j][i] = A / L[i][i];
        }
    }

    /// solve
    /**
        Ax = B <-> LL_Tx = B -> Ly = B and L_T x = y
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
            A -= L[j][i] * x[j];
        }

        x[i] = A / L[i][i];
    }

    /// output
    cout << "solution : \n";
    for(int i = 0;i < N;i ++){
        cout << "x[" << i+1 << "] : " << setprecision(4) << fixed << x[i] << "\n";
    }

    return 0;
}
