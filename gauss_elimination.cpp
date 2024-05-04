/**
    a[1][1] * x[1] + a[1][2] * x[2] + ... + a[1][n] * x[n] = a[1][n+1] = b[1]
    a[2][1] * x[1] + a[2][2] * x[2] + ... + a[2][n] * x[n] = a[2][n+1] = b[2]
    ...
    a[n][1] * x[1] + a[n][2] * x[2] + ... + a[n][n] * x[n] = a[n][n+1] = b[n]

    input : N, a[i][j], i : 1 -> N, j : 1 -> N+1
    output : x[1...n] or message of has no unique solution
*/
#include <bits/stdc++.h>

using namespace std;

signed main(){
    int N;

    cout << "Size of matrix N : "; cin >> N;
    cout << "Matrix :\n";

    vector<double> arr[N];

    for(int i = 0;i < N;i ++){
        for(int j = 0;j <= N;j ++){
            double aij; cin >> aij;

            arr[i].push_back(aij);
        }
    }

    for(int j = 0;j + 1 < N;j ++){
        int idx = -1;

        for(int i = j;i < N && idx == -1;i ++){
            if(arr[i][j] != 0.0) {
                idx = i;
                break;
            }
        }

        if(idx == -1){
            cout << "no enique solution exists";
            return 0;
        }

        if(idx != j){ /// swap row idx <-> row j
            for(int i = 0;i <= N;i ++){
                double tmp = arr[j][i];
                arr[j][i] = arr[idx][i];
                arr[idx][i] = tmp;
            }
        }

        for(int i = j + 1;i < N;i ++){
            double d = arr[i][j] / arr[j][j];

            for(int k = j;k <= N;k ++){
                arr[i][k] -= d * arr[j][k];
            }
        }
    }

    if(arr[N-1][N-1] == 0.0){
        cout << "no enique solution exists";
        return 0;
    }

    vector<double> X(N, 0.0);

    for(int i = N-1;i >= 0;i --){
        for(int j = i+1;j < N;j ++){
            arr[i][N] -= arr[i][j] * X[j];
        }

        X[i] = arr[i][N] / arr[i][i];
    }

    cout << "solution is :\n";
    for(int i = 0;i < N;i ++){
        cout << "x[" << i+1 << "] : " << setprecision(4) << fixed <<  X[i] << "\n";
    }

    return 0;
}

