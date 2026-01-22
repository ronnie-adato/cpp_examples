#include "decode_string.hpp"

#include <cctype>
#include <stack>
#include <string>

std::string DecodeString::decodeString(const std::string &s)
{
    std::stack<size_t> repeat_stack;
    std::stack<std::string> prefix_stack;

    size_t repeat = 0;
    std::string current;

    for (char ch : s) {
        const unsigned char uch = static_cast<unsigned char>(ch);
        if (std::isdigit(uch) != 0) {
            repeat = repeat * 10 + static_cast<size_t>(ch - '0');
            continue;
        }

        if (ch == '[') {
            repeat_stack.push(repeat);
            prefix_stack.push(current);
            repeat = 0;
            current.clear();
            continue;
        }

        if (ch == ']') {
            const size_t k = repeat_stack.top();
            repeat_stack.pop();

            std::string expanded = prefix_stack.top();
            prefix_stack.pop();

            expanded.reserve(expanded.size() + current.size() * k);
            for (size_t i = 0; i < k; ++i) {
                expanded += current;
            }
            current = std::move(expanded);
            continue;
        }

        current += ch;
    }

    return current;
}
