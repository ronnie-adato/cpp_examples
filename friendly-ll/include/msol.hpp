#pragma once

#include "solution.hpp"

class MSol : public Solution
{
   public:
    // Map-free clone implementation using interleaved original/clone nodes.
    Node* Clone(Node* root) override;
};
