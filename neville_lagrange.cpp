#include <bits/stdc++.h>

using namespace std;

signed main(){
    int N;
    cout << "Number of distinct numbers N : "; cin >> N;

    double X;
    cout << "X : "; cin >> X;

    vector<double> x, y;
    vector<vector<double> > Q(N+1, vector<double>(N+1, 0.0));

    for(int i = 0;i <= N;i ++){
        double xi;
        cout << "x[" << i << "] : "; cin >> xi;

        x.push_back(xi);
    }

    for(int i = 0;i <= N;i ++){
        double yi;
        cout << "y[" << i << "] = f(x[" << i << "]): "; cin >> yi;

        y.push_back(yi);
        Q[0][i] = yi;
    }

    for(int i = 1;i <= N;i ++){
        for(int j = i;j <= N;j ++){ /// Q[i][j] = P_(j-i)(j-i+1)...(j)
            Q[i][j] = ( ( X - x[j-i] ) * Q[i-1][j] - ( X - x[j] ) * Q[i-1][j-1] ) / ( x[j] - x[j-i] );
        }
    }

    cout << "P(" << setprecision(7) << fixed << X << ") : " << Q[N][N];

    return 0;
}
