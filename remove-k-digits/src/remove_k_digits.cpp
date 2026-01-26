#include "remove_k_digits.hpp"

#include <ng-log/logging.h>

#include <cstddef>
#include <stdexcept>

std::string RemoveKDigits::removeKdigits(const std::string& num, int k)
{
    LOG(INFO) << "RemoveKDigits::removeKdigits num.size=" << num.size() << " k=" << k;

    if (k < 0)
    {
        throw std::invalid_argument("k must be non-negative");
    }
    if (num.empty() || static_cast<size_t>(k) >= num.size())
    {
        return "0";
    }
    if (k == 0)
    {
        // Normalize any leading zeros just in case.
        const size_t first_non_zero = num.find_first_not_of('0');
        return (first_non_zero == std::string::npos) ? "0" : num.substr(first_non_zero);
    }

    std::string st;
    st.reserve(num.size());

    for (const char c : num)
    {
        while (k > 0 && !st.empty() && st.back() > c)
        {
            st.pop_back();
            --k;
        }
        st.push_back(c);
    }

    while (k > 0 && !st.empty())
    {
        st.pop_back();
        --k;
    }

    const size_t first_non_zero = st.find_first_not_of('0');
    if (first_non_zero == std::string::npos)
    {
        return "0";
    }
    return st.substr(first_non_zero);
}
