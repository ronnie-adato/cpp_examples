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
    auto cr = new Node();
    cr->value = r->value + 10;
    cr->next = r->next;
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
  auto ctmp = croot;

  for (auto r = root; ctmp->next != nullptr; r = r->next->next, ctmp = ctmp->next) {
    r->next = ctmp->next;
    ctmp->next = ctmp->next->next;
  }

  LOG(INFO) << "root: " << root;
  LOG(INFO) << "croot: " << croot;
  return croot;
}
