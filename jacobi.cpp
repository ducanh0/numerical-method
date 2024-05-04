/**
    phuong phap lap jacobi

    b1 : check dieu kien hoi tu
    b2 : tao ma tran B, D
    b3 : tinh q = chuan vo cung cua ma tran B
    b4 : cthuc lap la X(n+1) = B * X(n) + D
    b5 : dung cthuc tien nghiem / hau nghiem de tinh so buoc lap

-----------------------------------------------------------------------------

    input : size of matrix N, a[i][j] ( i , j : 1 -> n ) , b[i] ( i : 1 -> n ), x0[i] ( i : 1 -> n ), tolerance TOL, maximum number of iterations N0

    output : approximate solution or message that the number of iterations was exceeded

*/
#include <bits/stdc++.h>

using namespace std;

signed main(){
    int N;
    cout << "Size of matrix : " ; cin >> N;

    vector<vector<double> > arr(N, vector<double>(N, 0.0));
    cout << "Matrix A :\n";

    for(int i = 0;i < N;i ++){
        for(int j = 0;j < N;j ++){
            double aij; cin >> aij;

            arr[i][j] = aij;
        }
    }

    vector<double> b(N, 0.0);
    cout << "Matrix B :\n";

    for(int i = 0;i < N;i ++){
        double bi; cin >> bi;

        b[i] = bi;
    }

    vector<double> X0(N, 0.0);
    cout << "Matrix X[0] :\n";

    for(int i = 0;i < N;i ++){
        double bi; cin >> bi;

        X0[i] = bi;
    }

    double TOL;
    cout << "tolerance TOL : "; cin >> TOL;

    int N0;
    cout << "Number of maximum iterations N0 : "; cin >> N0;

    /**
        || X[n] - X* || <= q / (1 - q) * || X[n] - X[n-1] || <= eps -> || X[n] - X[n-1] || <= eps * (1 - q) / q
    */

    /// find q
    double q = -1e18;
    for(int i = 0;i < N;i ++){
        /// find idx : arr[i][idx] = max( arr[i][j] )
        /// q = max( ( sigma( abs(arr[i][j]) ) - abs(arr[i][idx]) ) / abs(arr[i][idx]) )
        double sum = 0.0;
        int idx = -1;

        for(int j = 0;j < N;j ++){
            sum += abs(arr[i][j]);

            if(idx == -1 || abs(arr[i][idx]) < abs(arr[i][j])){
                idx = j;
            }
        }

        q = max( q, ( sum - abs(arr[i][idx]) ) / abs(arr[i][idx]) );
    }

    TOL = TOL * (1.0 - q) / q;

    vector<double> X(N, 0.0);   /// nghiem , X dong vai tro la X[n], X0 dong vai tro la X[n-1], dung lai khi || X[n] - X[n-1] || < TOL
    for(int i = 0;i < N0;i ++){
        for(int j = 0;j < N;j ++){
            double B = b[j];

            for(int k = 0;k < N;k ++){
                if(k == j) continue;

                B -= X0[k] * arr[j][k];
            }

            X[j] = B / arr[j][j];
        }

        double cvc = -1e18;
        for(int j = 0;j < N;j ++){
            cvc = max(cvc, abs(X[j] - X0[j]));
        }

        if(cvc < TOL){
            cout << "appriximate solution :\n";
            for(int i = 0;i < N;i ++){
                cout << "x[" << i+1 << "] : " << setprecision(4) << fixed << X[i] << "\n";
            }

            return 0;
        }

        for(int j = 0;j < N;j ++){
            X0[j] = X[j];
        }
    }

    cout << "Maximum number of iterations exceeded";

    return 0;
}
