#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

constexpr int max_operand = 1000;

void write_conditions(char op, std::ostream& output,
                      const std::array<std::string, max_operand + 1>& numbers) {
    output << "    if (op == '" << op << "') {\n";

    std::string generated;
    generated.reserve((max_operand + 1) * 128);
    for (int i = 0; i <= max_operand; ++i) {
        generated.clear();
        for (int j = 0; j <= max_operand; ++j) {
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
        output.write(generated.data(), static_cast<std::streamsize>(generated.size()));
        if (!output) {
            return;
        }
    }
    output << "    }\n";
}

int main() {
    std::ifstream source_template("calculator_template.cpp.in");
    if (!source_template) {
        std::cerr << "Unable to open calculator_template.cpp.in\n";
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(source_template)),
                       std::istreambuf_iterator<char>());
    const std::string marker = "@MAX_OPERAND@";
    const auto marker_position = source.find(marker);
    if (marker_position == std::string::npos) {
        std::cerr << "Template is missing " << marker << '\n';
        return 1;
    }
    source.replace(marker_position, marker.size(), std::to_string(max_operand));

    const std::filesystem::path output_path = "output/calculator.cpp";
    std::error_code directory_error;
    std::filesystem::create_directories(output_path.parent_path(), directory_error);
    if (directory_error) {
        std::cerr << "Unable to create output directory: " << directory_error.message() << '\n';
        return 1;
    }
    std::ofstream output(output_path);
    if (!output) {
        std::cerr << "Unable to open " << output_path << '\n';
        return 1;
    }
    output << source;

    std::array<std::string, max_operand + 1> numbers;
    for (int i = 0; i <= max_operand; ++i) {
        numbers[i] = std::to_string(i);
    }

    for (char op : {'+', '-', '*', '/'}) {
        write_conditions(op, output, numbers);
        if (!output) {
            std::cerr << "Unable to write " << output_path << '\n';
            return 1;
        }
    }
    output << "}\n";
    output.close();
    if (!output) {
        std::cerr << "Unable to write " << output_path << '\n';
        return 1;
    }
}
