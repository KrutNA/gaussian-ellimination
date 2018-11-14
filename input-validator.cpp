//
// Created by krutna on 16.09.18.
//

#include "input-validator.hpp"

static std::regex intRegex ("[1-9][0-9]*");
static std::regex dblRegex ("[+-]?[0-9]+(\\.[0-9]*)?");
static std::regex matrixLineRegex ("^[|]?([\\s\t]*[+-]?[0-9]+(\\.[0-9]*)?)*[\\s\t]*[\n]?$");
static std::regex valueRegex ("^[\\s\t]*([1][0-9]{9})|(2[01][0-4][0-6][0-9]{6})|([1-9][0-9]{0,8})[\\s\t]*$");
static int dimension;

int InputValidator::getDimension() {
    return dimension;
}

std::vector<std::vector<double>> InputValidator::validateFile(char* fileName) {
    std::string value;
    std::vector<std::vector<double>> result;
    std::vector<std::vector<double>> matrix;
    std::ifstream file (fileName);
    if (!file.is_open()) {
        std::cout << "Can't read file: " <<  fileName << std::endl;
    }
    std::cout << "Reading file...\n";
    if (!getline(file, value)) {
        std::cout << "File is clear!";
        goto resultLabel;
    }
    if (!std::regex_match(value, valueRegex) || value.length() > 9) {
        std::cout << "On first line you must write positive integer value!\n";
        goto resultLabel;
    }
    dimension = std::stoi((*std::sregex_iterator(value.begin(), value.end(), intRegex))[0]);
    if (dimension > 20 || dimension < 1) {
        std::cout << "Value is " << dimension << ". But must be less then 21." << std::endl
                  << "Line: 1." << std::endl;
        goto resultLabel;
    }
    std::cout << "Dimension: " << dimension << std::endl;
    for (int i = 0; i < dimension; ++i) {
        if (!getline(file, value)) {
            std::cout << "Can't read file on line " << i + 2 << std::endl;
            goto resultLabel;
        }
        auto arrStart = std::sregex_iterator(value.begin(), value.end(), dblRegex);
        auto arrEnd = std::sregex_iterator();
        if (!std::regex_match(value, matrixLineRegex) || dimension+1 != std::distance(arrStart, arrEnd)) {
            std::cout << "Error on parsing line " << i + 2 << std::endl;
            goto resultLabel;
        }
        matrix.emplace_back();
        for (std::sregex_iterator j = arrStart; j != arrEnd; ++j) {
            std::smatch match = *j;
            std::string match_str = match.str();
            matrix[i].push_back(std::stof(match_str));
        }
    }
    if (getline(file, value)) {
       std::cout << "Error: file has more lines, then " << dimension+1 << std::endl;
        goto resultLabel;
    }
    result = matrix;
resultLabel:
    if (file.is_open()) file.close();
    return result;
};

std::vector<std::vector<double>> InputValidator::validateInput(char* parameter) {
    std::string value = parameter;
    std::vector<std::vector<double>> result;
    std::vector<std::vector<double>> matrix;
    if (!std::regex_match(value, valueRegex)) {
        std::cout << "You must write positive value!" << std::endl;
        goto resultLabel;
    }
    dimension = std::stoi(value);
    if (dimension > 20 || dimension < 1) {
        std::cout << "Value is " << dimension << ". But must be less then 21." << std::endl;
        goto resultLabel;
    }
    std::cout << "Matrix:\n";
    for (int i = 0; i < dimension; i++) {
        std::cout << "| ";
        std::getline(std::cin, value);
        auto arrStart = std::sregex_iterator(value.begin(), value.end(), dblRegex);
        auto arrEnd = std::sregex_iterator();
        if (!std::regex_match(value, matrixLineRegex) || dimension+1 != std::distance(arrStart, arrEnd)) {
            std::cout << "Error on parsing line" << std::endl;
            goto resultLabel;
        }
        matrix.emplace_back();
        for (std::sregex_iterator j = arrStart; j != arrEnd; ++j) {
            std::smatch match = *j;
            std::string match_str = match.str();
            matrix[i].push_back(std::stof(match_str));
        }
    }
    result = (matrix);
resultLabel:
    return result;
}
