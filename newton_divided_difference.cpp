#include <bits/stdc++.h>

using namespace std;

signed main(){
    int N;
    cout << "Number of distinct numbers N : "; cin >> N;

    double X;
    cout << "X : "; cin >> X;

    vector<double> x, y;
    vector<vector<double> > F(N+1, vector<double>(N+1, 0.0));

    for(int i = 0;i <= N;i ++){
        double xi;
        cout << "x[" << i << "] : "; cin >> xi;

        x.push_back(xi);
    }

    for(int i = 0;i <= N;i ++){
        double yi;
        cout << "y[" << i << "] = f(x[" << i << "]): "; cin >> yi;

        y.push_back(yi);
        F[0][i] = yi;
    }

    for(int i = 1;i <= N;i ++){
        for(int j = i;j <= N;j ++){ /// F[i][j] = f[ x(j-i), x(j-i+1), ..., x(j) ]
            F[i][j] = ( F[i-1][j] - F[i-1][j-1] ) / ( x[j] - x[j-i] );
        }
    }

    double ans = F[0][0], tich = 1.0; /// newton tien , tich = (X - x[0]) * (X - x[1]) * ... * (X - x[n])

    for(int i = 1;i <= N;i ++){
        tich *= (X - x[i-1]);

        ans += tich * F[i][i];
    }

    ans += tich * (X - x[N]) * F[N][N];

    cout << "P(" << setprecision(7) << fixed << X << ") : " << ans;

    return 0;
}

