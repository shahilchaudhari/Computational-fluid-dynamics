#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

//int const n = 4;
double const L = 3;

int main(){

    int n;

    cout<<"Enter the grid size"<<endl;
    cin>>n;

    int i,j=0;
    double phiWest = 0;
    double phiSouth = 1;
    double phiSource = 0.5;
    double density = 2;
    double gamma = 3;
    double x,y,dx,dy;

    dx = L/n;
    dy = L/n;

    // defining velocity at faces
    double** u = new double* [n+1];
    double** v = new double* [n+1];

    for(i=0;i<n+1;i++){
        u[i]=new double[n+1];
        v[i]=new double[n+1];
    }

    cout<<endl;
    //cout<<"-------------------u and v---------------------"<<endl;
    for(i=0;i<n+1;i++){
        for(j=0;j<n+1;j++){
            u[i][j]=1+pow(j*dy,2);
            v[i][j]=1+pow(i*dx,2);
            //cout<<u[i][j]<<"  "<<v[i][j]<<"          ";
        }
        //cout<<endl;
    }

    // centroid of the cells and source term
    double** phi = new double* [n];
    double** xc = new double* [n];
    double** yc = new double* [n];
    double** s = new double* [n];

    for(i=0;i<n;i++){
        phi[i]=new double[n];
        xc[i]= new double[n];
        yc[i]=new double[n];
        s[i]=new double[n];
    }

    
    cout<<endl;
    //3cout<<"---------------Source terms---------------------"<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            xc[i][j] = dx*j + dx/2;
            yc[i][j] = dx*i + dy/2;
            phi[i][j] = 0.5;
            s[i][j] = 4 * (xc[i][j]+yc[i][j])*phiSource*dx*dy;
            //cout<<xc[i][j]<<"  "<<yc[i][j]<<" "
            //cout<<s[i][j]<<"       ";
        }
        //cout<<endl;
    }
    
    double xw,xe,yn,ys;

    double** Fe = new double*[n];
    double** Fw = new double*[n];
    double** Fn = new double*[n];
    double** Fs = new double*[n];
    double** De = new double*[n];
    double** Dw = new double*[n];
    double** Ds = new double*[n];
    double** Dn = new double*[n];

    for(i=0;i<n;i++){
        Fn[i]= new double[n];
        Fs[i]= new double[n];
        Fw[i]= new double[n];
        Fe[i]= new double[n];
        De[i]= new double[n];
        Dw[i]= new double[n];
        Dn[i]= new double[n];
        Ds[i]= new double[n];
    }

    cout<<endl;
    //cout<<"------------Fe Fw Fn Fs         De Dw Dn Ds --------------------------------"<<endl;
    for(i = 0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==0 & j==0){
                xw=dx/2;
                ys=dy/2;
                xe = dx;
                yn = dy;

                //cout<< density*u[i][j+1]*dy<<endl;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            else if(i==0 & j!=n-1){
                xw=dx;
                ys=dy/2;
                xe = dx;
                yn = dy;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            else if(i==0 & j==n-1){
                xw=dx;
                ys=dy/2;
                xe = dx/2;
                yn = dy;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            else if(i==n-1 & j == 0){
                xw=dx/2;
                ys=dy;
                xe = dx;
                yn = dy/2;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            else if(i==n-1 & j!=n-1){
                xw=dx;
                ys=dy;
                xe = dx;
                yn = dy/2;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }
        

            else if(i==n-1 & j==n-1){
                xw=dx;
                ys=dy;
                xe = dx/2;
                yn = dy/2;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            else if(j==0 & i>0 & i<n-1){
                xw=dx/2;
                ys=dy;
                xe = dx;
                yn = dy;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            else if (j==n-1 & i>0 & i<n-1){
                xw=dx;
                ys=dy;
                xe = dx/2;
                yn = dy;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            else{
                xw=dx;
                ys=dy;
                xe = dx;
                yn = dy;

                Fe[i][j] = density*u[i][j+1]*dy;
                Fw[i][j] = density*u[i][j]*dy;
                Fs[i][j] = density*v[i][j]*dy;
                Fn[i][j] = density*v[i+1][j]*dy;

                De[i][j] = gamma*dy/xe;
                Dw[i][j] = gamma*dy/xw;
                Dn[i][j] = gamma*dx/yn;
                Ds[i][j] = gamma*dx/ys;
            }

            //cout<<Fe[i][j]<<"  "<<Fw[i][j]<<"  "<<Fn[i][j]<<"  "<<Fs[i][j]<<"      ";
            //cout<<De[i][j]<<"  "<<Dw[i][j]<<"  "<<Dn[i][j]<<"  "<<Ds[i][j]<<"       ";
        }
        //cout<<"\n";
    }

    double** ae = new double*[n];
    double** aw = new double*[n];
    double** an = new double*[n];
    double** as = new double*[n];
    double** ap = new double*[n];

    for(i=0;i<n;i++){
        ae[i]=new double[n];
        aw[i]=new double[n];
        an[i]=new double[n];
        as[i]=new double[n];
        ap[i]=new double[n];
    }
    //cout<<endl;
    //cout<<"------------------Ae Aw An As Ap-------------"<<endl;

    for(i =0;i<n;i++){
        for(j=0;j<n;j++){

            if(i!=n-1 & j==n-1){
                
                ae[i][j] = 0;
                aw[i][j] = Dw[i][j]+Fw[i][j];
                an[i][j] = Dn[i][j];
                as[i][j] = Ds[i][j]+Fs[i][j];
                ap[i][j] = Fe[i][j]+Dw[i][j]+Fn[i][j]+Dn[i][j]+Ds[i][j];
                
            }

            else if(i==n-1 & j!=n-1){
                ae[i][j] = De[i][j];
                aw[i][j] = Dw[i][j] + Fw[i][j];
                an[i][j] = 0;
                as[i][j] = Ds[i][j] + Fs[i][j];
                ap[i][j] = Fe[i][j]+De[i][j]+Dw[i][j]+Fn[i][j]+Ds[i][j];
            }

            else if(i==n-1 & j==n-1){
                ae[i][j] = 0;
                aw[i][j] = Dw[i][j] + Fw[i][j];
                an[i][j] = 0;
                as[i][j] = Ds[i][j] + Fs[i][j];
                ap[i][j] = Fe[i][j]+Dw[i][j]+Fn[i][j]+Ds[i][j];
            }

            else{
                ae[i][j] = De[i][j];
                aw[i][j] = Dw[i][j]+Fw[i][j];
                an[i][j] = Dn[i][j];
                as[i][j] = Ds[i][j] + Fs[i][j];
                ap[i][j] = De[i][j]+Fe[i][j]+Dw[i][j]+Dn[i][j]+Fn[i][j]+Ds[i][j];
            }

            //cout<<ap[i][j]<<"  ";
        //cout<<ae[i][j]<<"    "<<aw[i][j]<<"  "<<an[i][j]<<"  "<<as[i][j]<<"  "<<ap[i][j]<<"      ";
        }
        //cout<<endl;
    }


    cout<<endl;

    double precision = 1;
    double dummy = 0.5;
    while(precision<1500){
        //cout<<endl;
        //cout<<" Iteration : "<<precision<<endl;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){

                double source  = 0,dump = 1;
                
                if((i>1 & i<n-2) & (j>1 & j<n-2)){

                    while(abs(source-dump)>pow(10,-3)){
                        source = s[i][j] - Fe[i][j]*((-1/4)*phi[i][j]+3/8*phi[i][j+1]-1/8*phi[i][j-1])+ Fw[i][j]*((-1/4)*phi[i][j-1]+3/8*phi[i][j]-1/8*phi[i][j-2]) - Fn[i][j]*((-1/4)*phi[i][j]+3/8*phi[i+1][j]-1/8*phi[i-1][j]) + Fs[i][j]*((-1/4)*phi[i-1][j]+3/8*phi[i][j]-1/8*phi[i-2][j]);
                        
                        phi[i][j] = (ae[i][j]*phi[i][j+1]+aw[i][j]*phi[i][j-1]+an[i][j]*phi[i+1][j]+as[i][j]*phi[i-1][j]+source)/ap[i][j];
                        dump = s[i][j] - Fe[i][j]*((-1/4)*phi[i][j]+3/8*phi[i][j+1]-1/8*phi[i][j-1])+ Fw[i][j]*((-1/4)*phi[i][j-1]+3/8*phi[i][j]-1/8*phi[i][j-2]) - Fn[i][j]*((-1/4)*phi[i][j]+3/8*phi[i+1][j]-1/8*phi[i-1][j]) + Fs[i][j]*((-1/4)*phi[i-1][j]+3/8*phi[i][j]-1/8*phi[i-2][j]);
                    }
                }


                else if((i==1 & j!=0 & j!=n-1) || (j==1 & i!=n-1 & i!=0) || (i==n-2 & j!=0 & j!=n-1) || (j==n-2 & i!=n-1 & i!=0)){
                    phi[i][j] = (ae[i][j]*phi[i][j+1]+aw[i][j]*phi[i][j-1]+an[i][j]*phi[i+1][j]+as[i][j]*phi[i-1][j]+s[i][j])/ap[i][j];
                }
                
                else if(i==0){
                    if(j==0){
                        phi[i][j] = (ae[i][j]*phi[i][j+1]+aw[i][j]*phiWest+an[i][j]*phi[i+1][j]+as[i][j]*phiSouth+s[i][j])/ap[i][j];
                    }
                    else if(j==n-1){
                        phi[i][j] = (aw[i][j]*phi[i][j-1]+an[i][j]*phi[i+1][j]+as[i][j]*phiSouth+s[i][j])/ap[i][j];
                    }
                    else{
                        phi[i][j] = (ae[i][j]*phi[i][j+1]+aw[i][j]*phi[i][j-1]+an[i][j]*phi[i+1][j]+as[i][j]*phiSouth+s[i][j])/ap[i][j];
                    }
                }

                else if(i==n-1){
                    if(j==0){
                        phi[i][j] = (ae[i][j]*phi[i][j+1]+aw[i][j]*phiWest+as[i][j]*phi[i-1][j]+s[i][j])/ap[i][j];
                    }
                    else if(j==n-1){
                        phi[i][j] = (aw[i][j]*phi[i][j-1]+as[i][j]*phi[i-1][j]+s[i][j])/ap[i][j];
                    }
                    else{
                        phi[i][j] = (ae[i][j]*phi[i][j+1]+aw[i][j]*phi[i][j-1]+as[i][j]*phi[i-1][j]+s[i][j])/ap[i][j];
                    }
                }
    
                else if(i!=0 & i!=n-1){
                    if(j==0){
                        phi[i][j] = (ae[i][j]*phi[i][j+1]+aw[i][j]*phiWest+an[i][j]*phi[i+1][j]+as[i][j]*phi[i-1][j]+s[i][j])/ap[i][j];
                    }
                    else if(j==n-1){
                        phi[i][j] = (aw[i][j]*phi[i][j-1]+an[i][j]*phi[i+1][j]+as[i][j]*phi[i-1][j]+s[i][j])/ap[i][j];
                    }
                
                }
    
            }
        }
        precision=precision+1;
        //precision = abs(dummy-phi[n/2][n/2]);
        //dummy = phi[n/2][n/2];
    }
    cout<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
           // cout<<phi[i][j]<<"   ";
        }
        //cout<<endl;
    }
    cout<<endl;
    
    for(i=0;i<n;i++){
       cout<<phi[(n-1)/2][i]<<endl;
    }
    

    ofstream file1;
    file1.open("QUICK50.csv");

    for(i=0;i<n;i++){
        file1<<xc[(n-1)/2][i]<<","<<phi[(n-1)/2][i]<<endl;
    }
    file1.close();

    return 0;
}