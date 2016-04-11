/*
	Calculating minimum of a function using Gradient descent algorithm
	example 
	we will use iterative formula
	X(i+1) = X(i) - lambda*(grad(f))

	Here function is f(x1,x2) = x1 - x2 + 2(x1)^2 + 2(x1)(x2) + (x2)^2
	Solution is x1 = -1.0, x2 = 1.5;


	at each stage we will make simultaneous two updates for x1 and x2;
	i.e.
		x1(i+1) = x1(i) - lambda*(partial derivative of f wrt to x1)
		x2(i+1) = x2(i) - lambda*(partial derivative of f wrt to x2)

		Here note that simultaneous updates are to be made correctly i.e.
		store values of x1(i+1) and x2(i+1) in two seperate variables and at the end of iteration assign it
		so it would not use updated value of x1 for calculation fo x2(i+1)
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

double grad(double x1, double x2,int n){
	//partial derivative with respect to xi will depend on n
	//i.e. n = 1 means wrt 1
	if(n==1){
		return 1 + (4*x1) + (2*x2);
	}
	else if(n==2){
		return -1 + (2*x1) + (2*x2);
	}
}

double f_eval(double x1,double x2){
	return x1 - x2 + (2*x1*x1) + (2*x1*x2) + (x2*x2);
}

int main(int argc, char const *argv[]){
	int n;
	double x1=0,x2=0,temp1,temp2,lambda,e1,e2;
	double s1=0,s2=0;
	int count=0;
	while(1){
		cout<<"----------------------------------------------------------\n";
		// to evaluate s1 and s2
		s1 = -grad(x1,x2,1);
		s2 = -grad(x1,x2,2);

		//Print statements to debug the code
		printf("In the %d loop s1 = %lf and s2 = %lf\n",++count,s1,s2);

		lambda = -2.0;
		double f_min = f_eval(x1,x2);
		double temp,final_lambda=lambda;
		for (int i = 0; i < 5000; ++i)
		{
			lambda += 0.01;
			temp = f_eval((x1+lambda*s1),(x2+lambda*s2));
			if(temp < f_min){
				final_lambda = lambda;
				f_min = temp;
				
			}
		}
		
		
		temp1 = x1 + (final_lambda)*s1;
		temp2 = x2 + (final_lambda)*s2;
		printf("Optimal value of lambda = %lf\n",final_lambda);
		printf("old x1 = %lf and old x2 = %lf\n",x1,x2);
		printf("new x1 = %lf and new x2 = %lf\n",temp1,temp2);
		
		e1 = grad(temp1,temp2,1);
		e2 = grad(temp1,temp2,2);

		e1 = abs(e1);
		e2 = abs(e2);

		if((e1 <= 0.000001)  && (e2 <= 0.00001)){
			x1 = temp1;
			x2 = temp2;
			printf("|E1| = %lf and |E2| = %lf\n",e1,e2);
			printf("Terminating criteria is achieved!\n");
			break;
		}
		else{
			x1 = temp1;
			x2 = temp2;
			printf("Values of |E1| = %lf and |E2| = %lf\n",e1,e2);
		}

		cout<<endl;
	}
	cout<<"-----------------------------------------\n";
	printf(" x1* = %lf and x2* = %lf\n",x1,x2);
	return 0;
}


