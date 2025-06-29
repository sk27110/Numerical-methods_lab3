#include "coef.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

void DragCoefficientFitter::prepareData(const std::vector<double>& M, 
                                      const std::vector<double>& cD,
                                      std::vector<double>& x, 
                                      std::vector<double>& y) {
    if (M.size() != cD.size()) {
        throw std::invalid_argument("M and cD vectors must have the same size");
    }
    
    for (size_t i = 0; i < M.size(); ++i) {
        if (M[i] <= 1.1 || cD[i] <= 0.0) continue;
        
        double denominator = M[i]*M[i] - 1.0;
        if (denominator <= 0) continue;
        
        x.push_back(std::log(denominator));
        y.push_back(std::log(cD[i]));
    }
    
    if (x.size() < 2) {
        throw std::invalid_argument("Insufficient valid data points for regression");
    }
}

void DragCoefficientFitter::calculateRegression(const std::vector<double>& x, const std::vector<double>& y) {
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0;
    const size_t n = x.size();

    for (size_t i = 0; i < n; ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    double denominator = n * sumX2 - sumX * sumX;
    if (std::abs(denominator) < std::numeric_limits<double>::epsilon()) {
        throw std::runtime_error("Singular matrix in regression calculation");
    }
    double slope = (n * sumXY - sumX * sumY) / denominator;
    double intercept = (sumY - slope * sumX) / n;

    b = -slope;
    a = std::exp(intercept);
    
    coefficientsCalculated = true;
}

DragCoefficientFitter::DragCoefficientFitter(const std::vector<double>& M, 
                                           const std::vector<double>& cD) 
    : a(0.0), b(0.0), coefficientsCalculated(false) {
    std::vector<double> x, y;
    prepareData(M, cD, x, y);
    calculateRegression(x, y);
}

double DragCoefficientFitter::cD(double M) const {
    if (!coefficientsCalculated) {
        throw std::logic_error("Regression coefficients not calculated");
    }
    if (M <= 1.1) {
        throw std::invalid_argument("Function defined only for M > 1.1");
    }
    double denominator = std::pow(M*M - 1.0, b);
    return a / denominator;
}

void DragCoefficientFitter::printCoefficients() const {
    if (!coefficientsCalculated) {
        std::cout << "Coefficients not calculated\n";
        return;
    }
    std::cout << "Regression coefficients:\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
}