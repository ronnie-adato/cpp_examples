#include "rsol.hpp"
#include "node.hpp"

#include "ng-log/logging.h"

auto RSol::Clone(Node *root) -> Node *
{
    if (root == nullptr)
    {
        LOG(ERROR) << "Error: root is nullptr";
        return nullptr;
    }

    LOG(INFO) << "Original list: " << root;

    Node *cloned_root = nullptr;

    for (Node *node = root, *cloned_node = nullptr; node != nullptr; node = cloned_node->next)
    {
        cloned_node = new Node{node->value + 10, node->next, nullptr};
        if (cloned_root == nullptr)
        {
            cloned_root = cloned_node;
        }
        node->next = cloned_node;
    }
    LOG(INFO) << "phase 1, Original list: " << root;

    for (Node *node = root, *cloned_node = cloned_root; node != nullptr;
         node = cloned_node->next, cloned_node = node == nullptr ? nullptr : node->next)
    {
        if (node->afriend != nullptr)
        {
            cloned_node->afriend = node->afriend->next;
        }
    }
    LOG(INFO) << "phase 2, Original list: " << root;

    for (Node *node = root, *cloned_node = cloned_root; node != nullptr;
         node = node->next, cloned_node = cloned_node->next)
    {
        node->next = cloned_node->next;
        cloned_node->next = node->next == nullptr ? nullptr : node->next->next;
    }

    LOG(INFO) << "phase 3, Original list: " << root;
    LOG(INFO) << "phase 3, Cloned list: " << cloned_root;

    return cloned_root;
}
