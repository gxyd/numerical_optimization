/*
Calculating the minimum of function f(x) = 0.65 - (0.75/(1+(x*x))) - (0.65*x*atan(1/x)), in interval (0,3) with 0.01
From comparision table we know that for e = 0.01, we have n>=9  so we fix n = 10
*/
#include <iostream>
#include <cmath>
using namespace std;


//Function takes the value of x and returns f(x)
double PolyEval(double x){
	return 0.65 - (0.75/(1+(x*x))) - (0.65*x*atan(1/x));
}


// Calculates Fibonacci number
int F(int n){
	int f[20];
	f[0] = 0;
	f[1] = 1;
	for(int i=2;i<20;i++){
		f[i] = f[i-1] + f[i-2];
	}
	//cout<<"\nHey I am F and for "<<n<<" I am returning "<<f[n]<<endl;
	return f[n+1];
}

/*
	Variables defined:-
		n = N the total number of iterations
		e = epsilon(tolerance value)
		A = left point of intial interval
		B = right end point of initial interval
		left = left end point of current interval of uncertainity
		right = right end point of current interval of uncertainity
		l2_star = L2*,
*/



int main(int argc, char const *argv[]){
	int n;
	double e,A,B,left,right;
	
	A = 0;
	B = 3;
	left = A; right = B;
	n = 10;
	//Value of n can be changed considering the tolerance value

	//calulating L2* = F(n-2)/F(n)*L(0)
	double L2_star = (F(n-2)*(B-A)/F(n));

	double L1,x1,x2; 
	
	for(int i=2; i<n; i++){
		L1 = B - A;

		if(L2_star > (L1/2)){
			x1 = B - L2_star;
			x2 = A + L2_star;
		}
		else{
			x1 = A + L2_star;
			x2 = B - L2_star;
		}
		//calculating f1 and f2;
		double f1 = PolyEval(x1);
		double f2 = PolyEval(x2);

		//cout<<"Values of F1 and F2 are "<<f1<<"\t"<<f2<<endl;

		if(f1 > f2){
			A = x1;
			L2_star = F(n-i)*L1/F(n-i+2);
			cout<<"I am in the f1>f2 in the "<<i<<"th loop\n";
		}
		else if(f1 < f2){
			B = x2;
			L2_star = F(n-i)*L1/F(n-i+2);
			cout<<"I am in the f1<f2 in the "<<i<<"th loop\n";
		}
		else{
			A = x1;
			B = x2;
			L2_star = F(n-i)*(B-A)/F(n-i+2);
			i++;
			cout<<"I am in the f1==f2 in the "<<i<<"th loop\n";
		}
	}
	//final values for interval of uncertainity is [A,B]
	double L_final = B-A;
	double x_optimal = (B+A)/2;
	double f_optimal = PolyEval(x_optimal);
	cout<<"Final value for interval of uncertainity is ["<<A<<","<<B<<"] and x = "<<x_optimal<<", f(x) = "<<f_optimal<<"\n";
	return 0;
}