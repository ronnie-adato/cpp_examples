#pragma once

#include "solution.hpp"

class RSol : public Solution
{
   public:
    // Alternative map-free clone implementation using explicit node cursors.
    Node* Clone(Node* root) override;
};
