#include "node.hpp"

#include <ostream>

auto operator<<(std::ostream& os, const Node& node) -> std::ostream&
{
    // Print friend by value to avoid recursively walking arbitrary friend
    // cycles while still showing the next chain.
    os << "[Value: " << node.value;
    if (node.afriend)
    {
        os << ", afriend: " << node.afriend->value;
    }
    else
    {
        os << ", afriend: nullptr";
    }
    os << "] --> " << node.next;
    return os;
}

auto operator<<(std::ostream& os, const Node* node) -> std::ostream&
{
    if (node)
    {
        os << *node;
    }
    else
    {
        os << "nullptr";
    }
    return os;
}
