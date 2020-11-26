#include "test.h"
#include "timer.h"
#include <iostream>
#include <iomanip>

const int Ntests=100000000;
int main()
{
    static int A[Ntests];
    bool v[Nval];
    
    for(int i=0; i<Ntests; ++i){
        A[i]=rand()%Nval;
    }
    for(int i=0; i<Nval; ++i){
        v[i]=rand()%2;
    }
    
    //alignas(Align) Vbool4 tab;
    Vbool6 tab(Nval);
    for(int i=0; i<Nval; ++i){
        tab[i]=v[i];
    }
    
    Timer t;
    int n;
    for(int i=0; i<Ntests; ++i){
        if(tab[A[i]])n++;
    }
    
    auto time = t.elapsed();
    std::cout << "Time taken: " << time << '\n';
    std::cout << "    Result: " << n << " of true (" << std::setprecision(3) << (double)n/Ntests*100 << "%)\n";
    std::cout << "  Speed is: " << std::setprecision(3) << (double)Ntests/time/1.0e6 << " MHz" <<'\n';
}
