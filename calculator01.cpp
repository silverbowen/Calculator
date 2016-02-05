# include "TokenStream.h"

inline void error(const std::string& input);

double expression(TokenStream& tokenstream);
double term(TokenStream& tokenstream);
double primary(TokenStream& tokenstream);


int main()
{
    TokenStream tokenstream;
    double result = 0.0;

    try
    {
        while (std::cin)
        {
            Token token = tokenstream.getToken();
            if (token.kind == 'q') return 0;      // 'q' for quit
            if (token.kind == '=')                // '=' for "print now"
                std::cout << result << '\n';
            else                                  // anything else
            {
                tokenstream.setToken(token);      // reset token into tokenstream
                result = expression(tokenstream); // set result to value of expression
            }
        }
    }

    catch (std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    catch (...)
    {
        std::cerr << "exception \n";
        return 2;
    }
}

double expression(TokenStream& tokenstream)
{
    double result = term(tokenstream);       // set result to value of term
    Token token = tokenstream.getToken();  // get next token from tokenstream

    while (true)
    {
        if (token.kind == '+')
        {
            result += term(tokenstream);      // evaluate term and add to result
            token = tokenstream.getToken(); // get next token from tokenstream
        }

        if (token.kind == '-')
        {
            result -= term(tokenstream);      // evaluate term and subtract from result
            token = tokenstream.getToken(); // get next token from tokenstream
        }

        if (token.kind != '+' && token.kind != '-')
        {
            tokenstream.setToken(token);    // reset token into token stream
            return result;                    // return result
        }
    }
}
double term(TokenStream& tokenstream)
{
    double result = primary(tokenstream);   // set result to value of primary
    Token token = tokenstream.getToken(); // get next token from tokenstream

    while (true)
    {
        if (token.kind == '*')
        {
            result *= primary(tokenstream);   // evaluate primary and multiply with result
            token = tokenstream.getToken(); // get next token from tokenstream
        }

        if (token.kind == '/')
        {
            double divisor = primary(tokenstream);     // set divisor to value of primary
            if (divisor == 0) error("divide by zero"); // check for error
            result /= divisor;                           // divide result by divisor
            token = tokenstream.getToken();      // get next token from tokenstream
        }

        if (token.kind != '*' && token.kind != '/')
        {
            tokenstream.setToken(token); // put token back into the Token stream
            return result;                 // return result
        }
    }
}

double primary(TokenStream& tokenstream)
{
    Token token = tokenstream.getToken();

    if (token.kind == '(') // handle ‘(‘ expression ‘)’
    {
        double result = expression(tokenstream);           // set result to value of expression
        token = tokenstream.getToken();               // get next token from tokenstream
        if (token.kind != ')') error("')' expected"); // check for error
        return result;                                     // return divisor
    }
    if (token.kind == '8')  // we use ‘8’ to represent a number
        return token.value; // return the number’s value
    if (token.kind != '(' && token.kind != '8') // check for error
        error("primary expected");
}

inline void error(const std::string& input)
{
    throw std::runtime_error(input);
}
