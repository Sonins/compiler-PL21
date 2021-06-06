#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <vector>

#include "Item.hpp"

using std::vector;

class SyntaxTreeNode {
  public:
  SyntaxTreeNode(Item item);

  Item getItem();
  vector<SyntaxTreeNode> getChildren();
  
  private:
    Item componentItem;
    vector<SyntaxTreeNode> childNodes;
};

class SyntaxTree {
  public:
  SyntaxTree();
  ~SyntaxTree();
  
  SyntaxTreeNode getroot();

  private:
    SyntaxTreeNode root;  // 아마 prog이 되지 않을까
};

#endif