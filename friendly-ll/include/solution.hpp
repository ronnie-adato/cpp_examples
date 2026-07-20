#pragma once

struct Node;

class Solution
{
   public:
    // Clones a linked list that contains both next and friend pointers.
    virtual Node* Clone(Node* root) = 0;
};
