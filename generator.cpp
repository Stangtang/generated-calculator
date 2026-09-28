#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

std::string get_indentation(unsigned int num_indents) {
    std::string result = "";
    while (num_indents--) {
        result += "    ";
    }
    return result;
}

void write_conditions(char op, std::ofstream& output) {
    output << get_indentation(1) << "if (op == '" << op << "') {\n";
    for (unsigned int i = 0; i <= 100; i++) {
        for (unsigned int j = 0; j <= 100; j++) {
            std::string answer;
            switch(op) {
                case '+':
                    answer = std::to_string(i + j);
                    break;
                case '-':
                    answer = std::to_string(i - j);
                    break;
                case '*':
                    answer = std::to_string(i * j);
                    break;
                case '/':
                    if (j == 0) {
                        answer = "Cannot divide by 0.";
                    } else {
                        answer = std::to_string(static_cast<double>(i) / j);
                    }
                    break;
            }
            output << get_indentation(2) << "if (num1 == " << i << " && num2 == " << j << ") {\n";
            output << get_indentation(3) << "std::cout << \"" << answer << "\" << '" << "\\n" << "'" << ";\n";
            output << get_indentation(2) << "}\n";
        }
    }
    output << get_indentation(1) << "}\n";
}

int main() {
    std::filesystem::path output_path = "output/calculator.cpp";
    std::filesystem::create_directories(output_path.parent_path());
    std::ofstream output(output_path);

    std::ifstream boilerplate("boilerplate.txt");
    output << boilerplate.rdbuf();

    write_conditions('+', output);
    write_conditions('-', output);
    write_conditions('*', output);
    write_conditions('/', output);

    output << "}\n";
}