#include "msol.hpp"
#include "node.hpp"

#include "ng-log/logging.h"

auto MSol::Clone(Node *root) -> Node * {
  if (root == nullptr) {
    LOG(ERROR) << "Error: root is nullptr";
    return nullptr;
  }

  LOG(INFO) << "Begin: " << root;

  for (auto r = root; r != nullptr; r = r->next->next) {
    auto cr = new Node{r->value + 10, r->next, nullptr};
    r->next = cr;
  }
  LOG(INFO) << "Phase 1: " << root;

  for (auto r = root; r != nullptr; r = r->next->next) {
    if (r->afriend != nullptr) {
      r->next->afriend = r->afriend->next;
    }
  }
  LOG(INFO) << "Phase 2: " << root;

  auto croot = root->next;
  
  for (auto r = root, ctmp = croot; r != nullptr; r = r->next, ctmp = ctmp->next) {
    r->next = ctmp->next;
    ctmp->next = r->next == nullptr ? nullptr : r->next->next;
  }
  
  LOG(INFO) << "Phase 3:";
  LOG(INFO) << "root: " << root;
  LOG(INFO) << "croot: " << croot;
  return croot;
}
