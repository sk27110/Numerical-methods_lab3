#include "coef.h"
#include <iostream>

int main() {
    std::vector<double> MachNumbers = {1.4, 1.6, 2.0, 3.2};
    std::vector<double> dragCoefficients = {0.35, 0.3, 0.25, 0.20};
    
    DragCoefficientFitter fitter(MachNumbers, dragCoefficients);
    fitter.printCoefficients();
        
    std::cout << "\nCalculated drag coefficients:\n";
    for (double M : MachNumbers) {
        std::cout << "M = " << M << ": cD = " << fitter.cD(M) << "\n";
    }
        
    std::cout << "\nAdditional points:\n";
    std::cout << "M = 3.5: cD = " << fitter.cD(3.5) << "\n";
    std::cout << "M = 6.0: cD = " << fitter.cD(6.0) << "\n";
    return 0;
}