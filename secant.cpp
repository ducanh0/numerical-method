/**
    phuong phap day cung, bien the nho cua phuong phap newton
    dung cach nay thi khong can tinh dao ham cua f(x)

    thay f'(x) = ( f(x) - f(d) ) / (x - d) , (d - x -> 0)

    p(n) = p(n-1) - ( f(p(n-1)) * (p(n-1) - p(n-2) ) / ( f(p(n-1) - f(p(n-2) )

     input : initial approximation p0, p1; tolerance TOL; maximum number of iterations N
     output : approximate solution p or message of failure
*/
#include <bits/stdc++.h>

using namespace std;

const double minVal = -1e18;
const double maxVal = 1e18; /// avoid fault when calculate number
const double eps = 1e-18;

/**
    calculate p^n
*/

double cal_pow(double p, int n){
    if(n == 0) return 1.0;

    if(n < 0){
        double d = cal_pow(p, -n);

        if(d == maxVal || d == minVal) return 0.0;

        if(abs(d) < eps){
            return maxVal;
        }

        return 1.0 / d;
    }

    double d = cal_pow(p, n / 2);

    if(d == maxVal || d == minVal) return d;

    if(d > maxVal / d) return maxVal;
    if(d < minVal / d) return minVal;

    double ans = d * d;

    if(n % 2){
        if(ans > maxVal / p) return maxVal;
        if(ans < minVal / p) return minVal;

        ans = ans * p;
    }

    return ans;
}

/// f(x) = x^3 + 4 * x^2 - 10
double f(double p){ /// return f(p)
    return cal_pow(p, 3) + 4.0 * cal_pow(p, 2) - 10.0;
}

signed main(){
    double p0, p1, TOL;
    int N;

    cout << "Initial approximation p0 : "; cin >> p0;
    cout << "Initial approximation p1 : "; cin >> p1;
    cout << "Tolerance TOL : "; cin >> TOL;
    cout << "Maximum number of iterations N : "; cin >> N;

    for(int i = 0;i < N;i ++){
        double p = p1 - f(p1) / (f(p1) - f(p0)) * (p1 - p0); /// tranh tran so

        if(abs(p - p1) < TOL){
            cout << "Approximate solution p : " << setprecision(9) << fixed << p;
            return 0;
        }

        p0 = p1; p1 = p;
    }
    cout << "Fail to find solution after " << N << " iterations";

    return 0;
}
