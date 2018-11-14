#include <iostream>
#include "input-validator.hpp"
#include "system-of-linear-equations.hpp"
#include <cmath>

struct argument {
    std::string command;
    bool hasArgument;
    std::string description;
    bool isUsed;
};

int main(int argc, char* argv[]) {
    int result = 1, dimension;
    bool isMatrixSetted = false;
    char* args[2];
    std::ofstream outFile;
    std::vector<std::vector<double>> matrix;
    SystemOfLinearEquations system;
    InputValidator validator;
    argument arguments[] {
            {"-f", true, "Opens and reading matrix from file", false},
            {"-c", true, "Dimension of matrix", false},
            {"-o", true, "Save to file", false},
            {"er", false, "Error", true}
    };
    for (int i = 1; i < argc; i++) {
        argument arg =
                arguments[0].command == argv[i] ? arguments[0] :
                arguments[1].command == argv[i] ? arguments[1] :
                arguments[2].command == argv[i] ? arguments[2] :
                arguments[3];
        if (arg.command == "er") {
            std::cout << "Error occurred on parsing arguments!" << std::endl;
            goto returnLabel;
        }
        if ((argv[i] == arguments[0].command && arguments[0].isUsed) ||
            (argv[i] == arguments[1].command && arguments[1].isUsed) ||
            (argv[i] == arguments[2].command && arguments[2].isUsed)) {
            std::cout << "Multiple argument initialization" << std::endl;
            goto returnLabel;
        }
        if (argv[i] == arguments[0].command && !isMatrixSetted &&
            !arguments[0].isUsed && !arguments[1].isUsed && argc > i+1) {
            isMatrixSetted = true;
            arguments[0].isUsed = true;
            args[0] = argv[++i];
        } else if (argv[i] == arguments[1].command && !isMatrixSetted &&
                  !arguments[1].isUsed && !arguments[0].isUsed && argc > i+1) {
            isMatrixSetted = true;
            arguments[1].isUsed = true;
            args[0] = argv[++i];
        } else if (argv[i] == arguments[2].command && !arguments[2].isUsed && argc > i+1) {
            arguments[2].isUsed = true;
            args[1] = argv[++i];
            outFile.open(args[1], std::ofstream::ate);
            if (!outFile.is_open()) {
                std::cout << "Can't open file " << args[1] << " for writing" << std::endl;
                goto returnLabel;
            }
        } else {
            std::cout << "Error occurred on parsing arguments" << std::endl;
            goto returnLabel;
        }
    }
    if (!arguments[0].isUsed && !arguments[1].isUsed) {
        std::cout << R"(Didn't initialized matrix in arguments, use "-c" for value or "-f" for file!)" << std::endl;
        goto returnLabel;
    }
    matrix = arguments[0].isUsed ?
            validator.validateFile(args[0]) :
            validator.validateInput(args[0]);
    if (matrix.empty()) goto returnLabel;

    dimension = validator.getDimension();
    system.executeMethod(&matrix, dimension, &outFile);
    result = 0;
returnLabel:
    return result;
}
