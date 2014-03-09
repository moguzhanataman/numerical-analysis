/*
    Author: Mehmet Oguzhan Ataman
	
	Numerical Analysis Homework #1
	
	Implementation of 5 differnet methods for finding roots of given
	mathematical function. Numerical methods that used in this homework are:
	
	1- Bisection
	2- False-Position
	3- One-Point Iteration
	4- Newton-Raphion
	5- Secant Method
	
	They all working except One-point iteration method. This method don't work
	with this mathematical function.
*/

/* === Include Statements === */
#include <stdio.h>
#include <math.h>

/* === Constant Macros === */
#define ERROR_TOLERANCE  0.0001
#define MAX_ITERATION    100
#define DIFF_SENSITIVITY 0.0001

/* === Function Prototypes === */
/* NOTE: Comments about functions made on top of each function's implementation.
   Not in prototypes section. */
double TheFunction(double);
int SignOfDouble(double);
void TestSignOfDouble();
double Bisection(double, double);
void TestBisection();
double FalsePosition(double, double);
void TestFalsePosition();
double OnePointIteration(double);
void TestOnePointIteration();
double NewtonRaphson(double);
void TestNewtonRaphson();
double NumericalDifferantiation(double);
void TestNumericalDifferantiation();
double Secant(double, double);
void TestSecant(); 
void TestAll();
void PrintMenu();
void SelectMethod(int);

/* === Main Method === */
int main() {
	printf("Aciklama: One-point iteration harici fonksiyonlar pozitif degerler verildiginde calisiyor.\n\n");
	TestAll();
}

/* === Function Implementations === */
/* Our mathematical function */
double TheFunction(double n) {
	return (
		( (-3000) * pow(1.2, n) ) / ( pow(1.2, n) - 1 )
		+ 175.0*n / ( pow(1.2, n) - 1 )
		+ 5000
	);
}

/* Finds sign of function */
int SignOfDouble(double value) {
	int result;
	if(value == 0.0)
		result = 0;
	else if(value < 0.0)
		result = -1;
	else if(value > 0.0)
		result = 1;
	return result;
}

/* Tests sign checking function */
void TestSignOfDouble() {
	if(SignOfDouble(-15.0) == -1)
		printf("Test SignOfDouble: PASSED for -15.0\n");
	else
		printf("Test SignOfDouble: FAILED for -15.0\n");
		
	if(SignOfDouble(56.0) == 1)
		printf("Test SignOfDouble: PASSED for 56.0\n");
	else
		printf("Test SignOfDouble: FAILED for 56.0\n");
		
	if(SignOfDouble(0.0) == 0)
		printf("Test SignOfDouble: PASSED for 0.0\n");
	else
		printf("Test SignOfDouble: FAILED for 0.0\n");
	
}

/*
 * Bisection method implementation
 * 
 * a,b: start and end points for an interval
 */
double Bisection(double a, double b) {
	// Maximum iteration number for avoiding infinite loops
	int maxIterationNumber = MAX_ITERATION,
		n = 1;
		
	// Middle value
	double c;
	
	while (n <= maxIterationNumber) {
		//printf("a: %lf, b: %lf, c: %lf\n", a, b, c);
		c = (a+b) / 2.0;
		
		if(TheFunction(c) == 0.0 || (b-a) / 2.0 < ERROR_TOLERANCE) {
			return c;
		}
		
		// is sign of a and c are equal?
		if(SignOfDouble(TheFunction(c)) == SignOfDouble(TheFunction(a))) {
			a = c;
		} else {
			b = c;
		}
		
		n++;
	}
}

/* Tests Bisection method */
void TestBisection() {
	printf("Test Bisection: for a=0.1, b=10.0; root = %lf\n", Bisection(0.1, 10.0));
}

/*
 * False Position Method implementation
 * a,b: start and end points for an interval
 */
double FalsePosition(double a, double b) {
	int maxIterationNumber = MAX_ITERATION,
		n = 1;
	
	double c, fa, fb, fc, nonChangingPoint;
	
	while (n <= maxIterationNumber) {
		
		fa = TheFunction(a);
		fb = TheFunction(b);

		c = b-((fb*(a-b))/(fa-fb));
		fc = TheFunction(c);

		if(c < 0) {
			a = c;
			nonChangingPoint = b;
		} else {
			b = c;
			nonChangingPoint = a;
		}
		
		if (fabs(nonChangingPoint-c) < ERROR_TOLERANCE) {
				return c;
		}
		++n;
	}
	return c;
}

/* Tests False position method */
void TestFalsePosition() {
	printf("Test False Position: a=2.0, b=1000.0; root = %lf\n", FalsePosition(2.0, 1000.0));
}

/*
 * One Point Iteration
 *
 * x: Start point
 */
double OnePointIteration (double x) {
	int maxIterationNumber = MAX_ITERATION,
		n = 1;
	
	double xNext;
	
	while (n <= maxIterationNumber) {
		xNext = TheFunction(x);
		
		//printf("x: %lf, xNext: %lf\n", x, xNext);
		
		if( fabs((xNext - x) / xNext) < ERROR_TOLERANCE ) {
			return xNext;
		} else {
			x = xNext;
		}
		
		++n;
	}
}

/* Test code for one point iteration */
void TestOnePointIteration () {
	printf("Test One Point Iteration: for x=3.0; root = %lf\n", OnePointIteration(3.0));
}

/*
 * Newton-Raphson method implementation
 *
 * x: Start point
 */
double NewtonRaphson (double x) {
	int maxIterationNumber = MAX_ITERATION,
		n = 1;
	
	double xNext, fx, fprimex;
	while (n <= maxIterationNumber) {
		
		fx = TheFunction(x);
		fprimex = NumericalDifferantiation(x);
		xNext = x - fx/fprimex;
		
		if (fabs((xNext - x) / xNext) * 100 < ERROR_TOLERANCE) {
			return xNext;
		} else {
			x = xNext;
		}
		//printf("x: %lf, fx: %lf, fprimex: %lf, xNext: %lf\n", x, fx, fprimex, xNext);
		n++;
	}
	
	/* Reached max. iteration limit and must be leave with
	   error bigger than ERROR_TOLERANCE */
	return xNext;
}

/* Test code for Newton-Raphson */
void TestNewtonRaphson () {
	printf("Test Newton-Raphson method: root = %lf\n", NewtonRaphson(6.0));
}

/* Gets numerical differantiation of the function */
double NumericalDifferantiation (double x) {
	return (TheFunction(x+DIFF_SENSITIVITY) - TheFunction(x)) / DIFF_SENSITIVITY;
}

/* Test code for numerical differantiation */
void TestNumericalDifferantiation () {
	printf("Numerical Diff for x = 1, %lf (Must be 16326.8 theoretically)\n", NumericalDifferantiation(1.0));
}

/*
 * Secant method implementation
 * 
 * a, b: start and end point
 */
double Secant (double a, double b) {
	int maxIterationNumber = MAX_ITERATION,
		n = 1;
	
	double x, fa, fb;
	
	while (n <= maxIterationNumber) {
		fa = TheFunction(a);
		fb = TheFunction(b);
		x = b - (a-b)*fb / (fa - fb);
		
		if (fabs(x-b) < ERROR_TOLERANCE) {
			return x;
		} else {
			a = b;
			b = x;
		}
	}
	
	/* Reached max. iteration limit and must be leave with
	   error bigger than ERROR_TOLERANCE */
	return x;
}

/* Test function for secant */
void TestSecant () {
	printf("Test Secant: for a=3.2, b=8.98; root = %lf\n", Secant(3.2, 8.98));
}

/* Tests all methods */
void TestAll () {
	int choice;
	do {
		PrintMenu();
		scanf("%d", &choice);
		if(choice != 0)
			SelectMethod(choice);
	} while (choice != 0);
}

/* Prints menu to screen */
void PrintMenu () {
	printf("----------------------------------------------\n");
	printf("1: Bisection Method\n");
	printf("2: False Position Method\n");
	printf("3: One-Point Iteration Method\n");
	printf("4: Newton-Raphson Method\n");
	printf("5: Secant Method\n");
	printf("6: Run each method with predefined test values\n");
	printf("----------------------------------------------\n");
	printf("0: EXIT\n");
}

/* Using in TestAll method to selecting which method users prefer and gets values
 * then uses in functions
 * 
 * choice: User selected option
 */
void SelectMethod (int choice) {
	double a,b,x;
	
	// Get a, b or x value
	switch (choice) {
		case 3:
		case 4:
			// One point iteration and Newton-Raphson methods takes
			// one parameters
			printf("Enter x value: ");
			scanf("%lf", &x);
			printf("\n");
			break;
		case 1:
		case 2:
		case 5:
			printf("Enter starting point: ");
			scanf("%lf", &a);
			printf("Enter ending point: ");
			scanf("%lf", &b);
			break;
		case 6:
			printf("======== TEST ALL METHODS =========\n");
			TestBisection();
			TestFalsePosition();
			TestOnePointIteration();
			TestNewtonRaphson();
			TestSecant();
			printf("===================================\n");
			break;
	}
	
	switch (choice) {
		case 1:
			printf("Bisection method, root = %lf\n", Bisection(a, b));
			break;
		case 2:
			printf("Bisection method, root = %lf\n",FalsePosition(a, b));
			break;
		case 3:
			printf("Bisection method, root = %lf\n",OnePointIteration(x));
			break;
		case 4:
			printf("Bisection method, root = %lf\n",NewtonRaphson(x));
			break;
		case 5:
			printf("Bisection method, root = %lf\n",Secant(a, b));
			break;
	}
}
