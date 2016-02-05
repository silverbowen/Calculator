# include <iostream>
# include <string>
# include <stdexcept>

inline void error(const std::string& input);

int main()
{
    int lvalue, rvalue;
    char operation;

    std::cout << "Please enter expression (using +, -, *, and /): ";
    std::cin >> lvalue;
    if (!std::cin)  error("No first operand!\n");

    for (char operation; std::cin >> operation;)
    {
        if (operation != 'x') std::cin >> rvalue;
        if (!std::cin) error("No second operand!\n");
        if (operation == '+') lvalue += rvalue ;
        if (operation == '-') lvalue -= rvalue ;
        if (operation == '*') lvalue *= rvalue ;
        if (operation == '/') lvalue /= rvalue ;
        if (operation == 'x')
            std::cout << "Result: " << lvalue << "\n";
    }
}

inline void error(const std::string& input)
{
    throw std::runtime_error(input);
}
