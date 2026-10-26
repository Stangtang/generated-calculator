#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

constexpr unsigned int max_operand = 100;

void write_conditions(char op, std::string& generated,
                      const std::array<std::string, max_operand + 1>& numbers) {
    generated.append("    if (op == '");
    generated.push_back(op);
    generated.append("') {\n");

    for (unsigned int i = 0; i <= max_operand; ++i) {
        for (unsigned int j = 0; j <= max_operand; ++j) {
            std::string answer;
            switch (op) {
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
                    answer =
                        j == 0 ? "Cannot divide by 0." : std::to_string(static_cast<double>(i) / j);
                    break;
            }

            generated.append("        if (num1 == ");
            generated.append(numbers[i]);
            generated.append(" && num2 == ");
            generated.append(numbers[j]);
            generated.append(") {\n            std::cout << \"");
            generated.append(answer);
            generated.append("\" << '\\n';\n        }\n");
        }
    }
    generated.append("    }\n");
}

int main() {
    std::ifstream boilerplate("boilerplate.txt");
    if (!boilerplate) {
        std::cerr << "Unable to open boilerplate.txt\n";
        return 1;
    }

    const std::filesystem::path output_path = "output/calculator.cpp";
    std::filesystem::create_directories(output_path.parent_path());
    std::ofstream output(output_path);
    if (!output) {
        std::cerr << "Unable to open " << output_path << '\n';
        return 1;
    }
    output << boilerplate.rdbuf();

    std::array<std::string, max_operand + 1> numbers;
    for (unsigned int i = 0; i <= max_operand; ++i) {
        numbers[i] = std::to_string(i);
    }

    std::string generated;
    generated.reserve(1'000'000);
    for (char op : {'+', '-', '*', '/'}) {
        generated.clear();
        write_conditions(op, generated, numbers);
        output.write(generated.data(), static_cast<std::streamsize>(generated.size()));
    }
    output << "}\n";
    if (!output) {
        std::cerr << "Unable to write " << output_path << '\n';
        return 1;
    }
}
