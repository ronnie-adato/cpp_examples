#include "list_utils.hpp"

#include "msol.hpp"
#include "node.hpp"

#include <gtest/gtest.h>
#include <memory>

// Test case for the Clone function
TEST(MCloneTest, DeepCopy) {
  // Create a linked list: 1 -> 2 -> 3, with afriend pointers: 1->3, 2->1, 3->2
  Node *root = CreateLinkedList({1, 2, 3}, {2, 0, 1});

  // Clone the linked list
  std::unique_ptr<Solution> solution = std::make_unique<MSol>();
  Node *cloned_root = solution->Clone(root);

  // Verify the cloned list is a deep copy
  Node *original = root;
  Node *cloned = cloned_root;
  while (original != nullptr && cloned != nullptr) {
    EXPECT_NE(original, cloned); // Ensure different memory addresses
    EXPECT_EQ(original->value + 10,
              cloned->value); // Ensure values are the same
    if (original->afriend) {
      EXPECT_NE(original->afriend,
                cloned->afriend); // Ensure afriend is deep copied
      EXPECT_EQ(original->afriend->value + 10,
                cloned->afriend->value); // Ensure afriend values match
    } else {
      EXPECT_EQ(cloned->afriend, nullptr);
    }
    original = original->next;
    cloned = cloned->next;
  }

  // Ensure both lists end at the same time
  EXPECT_EQ(original, nullptr);
  EXPECT_EQ(cloned, nullptr);

  // Clean up
  DeleteLinkedList(root);
  DeleteLinkedList(cloned_root);
}
