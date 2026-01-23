#include "decode_string.hpp"

#include <ng-log/logging.h>
#include <cstddef>
#include <stack>
#include <string>
#include <variant>

std::string DecodeString::decodeString(const std::string& s)
{
    LOG(INFO) << "DecodeString::decodeString input=" << s;

    std::string decoded = "";
    using Element = std::variant<std::monostate, size_t, std::string>;
    std::stack<Element> stack;
    Element element;
    for (auto ch : s)
    {
        if (!std::holds_alternative<size_t>(element) && !std::holds_alternative<std::string>(element))
        {
            if ('0' <= ch && ch <= '9')
            {
                element = static_cast<size_t>(ch - '0');
            }
            else
            {
                element = std::string(1, ch);
            }
            continue;
        }
        if (std::holds_alternative<size_t>(element))
        {
            if ('0' <= ch && ch <= '9')
            {
                element = std::get<size_t>(element) * 10 + static_cast<size_t>(ch - '0');
            }
            else
            {
                stack.push(element);
                element = "";
            }
        }
        else
        {
            if ('0' <= ch && ch <= '9')
            {
                stack.push(element);
                element = static_cast<size_t>(ch - '0');
            }
            else if (ch == ']')
            {
                size_t repeat = std::get<size_t>(stack.top());
                stack.pop();
                std::string word = "";
                for (size_t i = 0; i < repeat; ++i)
                {
                    word += std::get<std::string>(element);
                }
                if (!stack.empty())
                {
                    word = std::get<std::string>(stack.top()) + word;
                    stack.pop();
                }
                element = word;
            }
            else
            {
                element = std::get<std::string>(element) + ch;
            }
        }
    }
    if (!stack.empty())
    {
        decoded = std::get<std::string>(stack.top());
        stack.pop();
    }
    else
    {
        if (std::holds_alternative<size_t>(element))
        {
            decoded = std::get<std::string>(element);
        }
        else if (std::holds_alternative<std::string>(element))
        {
            decoded = std::get<std::string>(element);
        }
    }

    return decoded;
}
