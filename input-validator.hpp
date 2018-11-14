//
// Created by krutna on 16.09.18.
//

#ifndef PROGRAM_INPUT_VALIDATOR_HPP
#define PROGRAM_INPUT_VALIDATOR_HPP

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

class InputValidator {
public:
    int getDimension();
    std::vector<std::vector<double>> validateFile(char* fileName);
    std::vector<std::vector<double>> validateInput(char* input);
};


#endif //PROGRAM_INPUT_VALIDATOR_HPP
