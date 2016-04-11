/*
 * Example from Page 466 of SS Rao
 * Calculating the minimum of f(x1, x2) = (x1 + 1)**3/3 + x2
 * subject to g1(x1, x2) = 1 - x1 <= 0
 * and g2(x1, x2) = -x2 <= 0
 * using the Exterior penalty method
 */
#include<iostream>
#include<cmath>
#include<math.h>
using namespace std;

double max(double x1, double x2)
{
    return (x1 < x2)?x2:x1;
}

double diff(double x1, double x2, double r, int n)
{
    if(n==1){
        return (x1 + 1)*(x1 + 1) - 2*r*max(0, 1 - x1);
    }
    else if(n==2){
        return 1 - 2*r*max(0, -x2);
    }
}

double penalty_eval(double x1, double x2, double r){
    return r*pow(max(0, 1 - x1), 2) + r*pow(max(0, -x2), 2);
}

double PolyEval(double x1, double x2){
    return (x1 + 1)*(x1 + 1)*(x1 + 1)/3 + x2;
}

double x_star_eval(double r, int n)
{
    if(n==1){
        return pow(r*r + 4*r, 0.5) - 1 - r;
    }
    else if(n==2){
        return -1/(2*r);
    }
}

int main(int argc, char const *argv[])
{
    double x1, x2, phi, f;
    double r = 0.001;

    /* It will have 7 iterations
     */

    while(r < 100000){
        x1 = x_star_eval(r, 1);
        x2 = x_star_eval(r, 2);
        f = PolyEval(x1, x2);
        phi = f + penalty_eval(x1, x2, r);
        r = r*10;
    }
    cout << "The minimum value of functions occurs at (" << x1 << ", " << x2 << ")" << endl;
    cout << "The minimum value of function is f(x1, x2) = " << f << endl;
}
