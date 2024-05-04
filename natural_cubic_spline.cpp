/**
    input : N, x[0], x[1], ..., x[N], f(x[0]), f(x[1]), ..., f(x[N])
    output : a[i], b[i], c[i], d[i] ( i : 0 -> n-1 )

    spline of [ x[i], x[i+1] ] = a[i] + b[i] * (x - x[i]) + c[i] * (x - x[i])^2 + d[i] * (x - x[i])^3 , x[i] <= x <= x[i+1]
*/
#include <bits/stdc++.h>

using namespace std;

signed main(){
    int N;
    cout << "Number of distinct numbers N : "; cin >> N;

    vector<double> x, y, h, a(N, 0.0), b(N, 0.0), c(N, 0.0), d(N, 0.0);

    for(int i = 0;i <= N;i ++){
        double xi;
        cout << "x[" << i << "] : "; cin >> xi;

        x.push_back(xi);

        if(i > 0){
            h.push_back(x[i] - x[i-1]); /// h[i] = x[i+1] - x[i]
        }
    }

    for(int i = 0;i <= N;i ++){
        double yi;
        cout << "y[" << i << "] = f(x[" << i << "]): "; cin >> yi;

        y.push_back(yi);
        a[i] = yi;
    }

    vector<double> alpha(N+1, 0.0), l(N+1, 0.0), muy(N+1, 0.0), z(N+1, 0.0);

    for(int i = 1;i < N;i ++){
        alpha[i] =  3.0 / h[i] * (a[i+1] - a[i]) - 3.0 / h[i-1] * (a[i] - a[i-1]);
    }

    l[0] = 1.0;

    for(int i = 1;i < N;i ++){
        l[i] = 2.0 * (x[i+1] - x[i-1]) - h[i-1] * muy[i-1];
        muy[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
    }

    l[N] = 1.0;

    for(int j = N-1;j >= 0;j --){
        c[j] = z[j] - muy[j] * c[j+1];
        b[j] = (a[j+1] - a[j]) / h[j] - h[j] * (c[j+1] + 2.0 * c[j]) / 3;
        d[j] = (c[j+1] - c[j]) / (3.0 * h[j]);
    }

    for(int i = 0;i < N;i ++){
        cout << setprecision(7) << fixed << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << "\n";
    }

    double X;
    cout << "X : "; cin >> X;

    for(int i = 0;i < N;i ++){
        if(x[i] <= X && X <= x[i+1]){
            double ans = a[i] + b[i] * (X - x[i]) + c[i] * (X - x[i]) * (X - x[i]) + d[i] * (X - x[i]) * (X - x[i]) * (X - x[i]);

            cout << "P(" << setprecision(7) << fixed << X << ") : " << ans ;
            return 0;
        }
    }

    cout << "chiu roi :v";

    return 0;
}
