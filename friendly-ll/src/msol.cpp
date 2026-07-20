#include "msol.hpp"
#include "node.hpp"

#include "ng-log/logging.h"

auto MSol::Clone(Node* root) -> Node*
{
    if (root == nullptr)
    {
        LOG(ERROR) << "Error: root is nullptr";
        return nullptr;
    }

    LOG(INFO) << "Begin: " << root;

    // Phase 1: interleave each cloned node immediately after its original.
    for (auto r = root; r != nullptr; r = r->next->next)
    {
        auto cr = new Node{r->value + 10, r->next, nullptr};
        r->next = cr;
    }
    LOG(INFO) << "Phase 1: " << root;

    // Phase 2: a cloned friend is one hop after the original friend's node.
    for (auto r = root; r != nullptr; r = r->next->next)
    {
        if (r->afriend != nullptr)
        {
            r->next->afriend = r->afriend->next;
        }
    }
    LOG(INFO) << "Phase 2: " << root;

    auto croot = root->next;

    // Phase 3: detach the interleaved list into original and cloned lists.
    for (auto r = root, ctmp = croot; r != nullptr; r = r->next, ctmp = ctmp->next)
    {
        r->next = ctmp->next;
        ctmp->next = r->next == nullptr ? nullptr : r->next->next;
    }

    LOG(INFO) << "Phase 3:";
    LOG(INFO) << "root: " << root;
    LOG(INFO) << "croot: " << croot;
    return croot;
}
