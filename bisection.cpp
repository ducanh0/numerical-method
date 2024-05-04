/**
    input : endpoints a, b; tolerance TOL; maximum number of iterations N
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
    f : function that need to find solution x such as f(x) = 0
    return :
        -1 if f(x) < 0
        0 if f(x) = 0
        1 if f(x) > 0
*/

int sign_f(double p){
    double val = cal_pow(p, 3) + 4.0 * cal_pow(p, 2) - 10.0; /// f(x) = x^3 + 4 * x^2 - 10

    if(abs(val) < eps) return 0;

    return ((val > 0.0) ? 1 : -1);
}

signed main(){
    double a, b, TOL;
    int N;

    cout << "endpoint a : " ; cin >> a;
    cout << "endpoint b : "; cin >> b;
    cout << "tolerance TOL : "; cin >> TOL;
    cout << "maximum number of iterations N : "; cin >> N;

    int sign_a = sign_f(a), sign_p = 0;

    for(int i = 0;i < N;i ++){
        double p = (a + b) / 2;
        int sign_p = sign_f(p);

        if(sign_p == 0 || abs(a - b) / 2 < TOL){ /// find solution success
            cout << "Approximate solution p = " << setprecision(9) << fixed << p;
            return 0;
        }

        if(sign_a * sign_p > 0){ /// [a, b]_new = [p, b]_old
            a = p;
            sign_a = sign_p;
        } else { /// [a, b]_new = [a, p]_old
            b = p;
        }
    }
    cout << "Fail to find solution after " << N << " iterations";

    return 0;
}
