// Shahil Chaudhari - ME21M038
/*
One-dimensional diffusion equation
Assume that there is a source term S = 8x, and that the diffusion 
coefficient Γ = 1 is constant.
Discretize the domain into five uniform cells with ∆x = 1.
Let the boundary values of φ be φ A = 100 and φ B = 600.
*/

#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;


double gaussSeidel(double phiE,double phiW,double nodeDistance){
    double phiP;
    phiP = (phiE+phiW+8*nodeDistance)/2;
    return phiP;
}

int main(){
    /// number of cells
    int n = 5;
    double length =5;
    double* sol = new double[n];
    double* nodeDistance = new double[n];
    // creating temporary array to update solution array
    double* xnew= new double[n];

    // variable to compare accuracy
    double dummy;

    /// initial conditions for internal nodes
    double phiA = 100,phiB = 600;
    for(int i=0;i<n;i++){
        sol[i]=(phiA+phiB)/2;
        nodeDistance[i]=i*(length/n)+length/(n*2);
    }
    
    do{
       /// updating values with previos iteration
        for(int i =0;i<n;i++){
            xnew[i]=sol[i];
        }
        /// performing guuss seidel iterative method
        /// node 1 
        xnew[0]=(xnew[1]+phiA*2+8*0.5)/3;
        sol[0]=xnew[0];

        // Internal nodes 2,3,4
        for(int i=1;i<=n-2;i++){
            xnew[i]=gaussSeidel(xnew[i-1],xnew[i+1],(i+0.5));
            sol[i]=xnew[i];
        }
        dummy = xnew[n-1];
        // node 5
        xnew[n-1]=(xnew[n-2]+phiB*2+8*(n-0.5))/3;
        sol[n-1]=xnew[n-1];

    }while(abs(xnew[n-1]-dummy)>pow(10,-9));

    // Printing solution array 
    for(int i=0;i<n;i++){
        printf("(Phi)%d  %.10f\n",i+1,sol[i]);
    }

    return 0;
}