#include "msol.hpp"
#include "node.hpp"

#include "ng-log/logging.h"

auto MSol::Clone(Node *root) -> Node * {
  if (root == nullptr) {
    LOG(ERROR) << "Error: root is nullptr";
    return nullptr;
  }

  LOG(INFO) << "Begin: " << root;

  auto r = root;
  while (r != nullptr) {

    auto cr = new Node();
    cr->value = r->value + 10;
    cr->next = r->next;
    r->next = cr;
    r = r->next->next;
  }
  LOG(INFO) << "Phase 1: " << root;

  r = root;
  while (r != nullptr) {
    r->next->afriend = r->afriend->next;
    r = r->next->next;
  }
  LOG(INFO) << "Phase 2: " << root;

  auto croot = root->next;
  auto ctmp = croot;
  r = root;
  
  while (ctmp->next != nullptr) {
    r->next = ctmp->next;
    ctmp->next = ctmp->next->next;
    r = r->next;
    ctmp = ctmp->next;
  }
  r->next = nullptr;
  
  LOG(INFO) << "Phase 3:";
  LOG(INFO) << "root: " << root;
  LOG(INFO) << "croot: " << croot;
  return croot;
}
