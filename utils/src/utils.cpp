
#include "utils.hpp"
#include <numeric>
#include <iterator>

namespace utils {

std::string join(const std::vector<std::string>& args) {
    if (args.empty()) {
        return "";
    }
    return std::accumulate(std::next(args.begin()), args.end(), args[0], [](const std::string& a, const std::string& b) {
        return a + " " + b;
    });
}

} // namespace utils
