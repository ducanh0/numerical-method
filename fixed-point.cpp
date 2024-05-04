/**
    input : initial approximation p0, tolerance TOL, maximum number of iterations N
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

/**
        there're many ways to find g(x) such as x = g(x) and x = g(x) <=> f(x) = 0
        but we choose g(x) such as abs(g'(x)) < 1 , x in [a, b]
*/

double g(double p){ /// f(x) = x^3 + 4 * x^2 - 10 = 0 => x = sqrt(10 - x^3) / 2 = g(x)
    return sqrt(10.0 - cal_pow(p, 3)) /  2;
}

signed main(){
    double p0, TOL;
    int N;

    cout << "Initial approximation p0 : "; cin >> p0;
    cout << "Tolerance TOL : "; cin >> TOL;
    cout << "Maximum number of iterations N : "; cin >> N;

    for(int i = 0;i < N;i ++){
        double p = g(p0);

        if(abs(p - p0) < TOL){
            cout << "Approximate solution p : " << setprecision(9) << fixed << p;
            return 0;
        }

        p0 = p;
    }
    cout << "Fail to find solution after " << N << " iterations";

    return 0;
}
