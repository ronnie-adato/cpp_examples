#pragma once

#include <string>

class DecodeString
{
   public:
    // Decodes bracketed repeat expressions such as "3[a2[c]]".
    std::string decodeString(const std::string& s);
};
