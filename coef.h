#pragma once
#include <vector>

class DragCoefficientFitter {
private:
    double a;
    double b;
    bool coefficientsCalculated;

    void prepareData(const std::vector<double>& M, 
                    const std::vector<double>& cD,
                    std::vector<double>& x, 
                    std::vector<double>& y);
    
    void calculateRegression(const std::vector<double>& x, const std::vector<double>& y);

public:
    DragCoefficientFitter(const std::vector<double>& M, 
                         const std::vector<double>& cD);
    
    double cD(double M) const;
    void printCoefficients() const;
    
    double getA() const { return a; }
    double getB() const { return b; }
    bool isCalculated() const { return coefficientsCalculated; }
};