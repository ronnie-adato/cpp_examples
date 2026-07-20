#include "node.hpp"

#include <vector>

auto CreateLinkedList(const std::vector<int>& values, const std::vector<int>& afriend_indices) -> Node*
{
    if (values.empty())
    {
        return nullptr;
    }

    std::vector<Node*> nodes(values.size(), nullptr);
    // Keep raw pointers in a side array so afriend indexes can be resolved
    // after the next chain has been constructed.
    for (size_t i = 0; i < values.size(); ++i)
    {
        nodes[i] = new Node{values[i], nullptr, nullptr};
        if (i > 0)
        {
            nodes[i - 1]->next = nodes[i];
        }
    }

    for (size_t i = 0; i < afriend_indices.size(); ++i)
    {
        if (afriend_indices[i] >= 0 && afriend_indices[i] < static_cast<int>(nodes.size()))
        {
            nodes[i]->afriend = nodes[afriend_indices[i]];
        }
    }

    return nodes[0];
}

void DeleteLinkedList(Node* root)
{
    while (root)
    {
        Node* temp = root;
        root = root->next;
        delete temp;
    }
}
