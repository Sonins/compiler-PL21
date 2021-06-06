#include "SyntaxTree.hpp"

vector<SyntaxTreeNode> SyntaxTreeNode::getChildren() {
    return this->childNodes;
}

Item SyntaxTreeNode::getItem() {
    return this->componentItem;
}

SyntaxTreeNode SyntaxTree::getroot() {
    return this->root;
}