//
// Created by krutna on 14.09.18.
//

#ifndef PROGRAM_SYSTEM_OF_LINEAR_EQUATIONS_HPP
#define PROGRAM_SYSTEM_OF_LINEAR_EQUATIONS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

class SystemOfLinearEquations {
public:
    bool executeMethod(std::vector<std::vector<double>>* matrix, int dimension, std::ofstream* outFile);
};


#endif //PROGRAM_SYSTEM_OF_LINEAR_EQUATIONS_HPP
