// NOTE: the code is extracted from:
// https://eli.thegreenplace.net/2011/05/17/the-curiously-recurring-template-pattern-in-c
// great article
#include <print>
struct TreeNode {
  enum Kind { RED, BLUE };

  TreeNode(Kind kind_, TreeNode *left_ = nullptr, TreeNode *right_ = nullptr)
      : kind(kind_), left(left_), right(right_) {}

  Kind kind;
  TreeNode *left, *right;
};

template <typename Derived> class GenericVisitor {
public:
  void visit_preorder(TreeNode *node) {
    if (node) {
      dispatch_node(node);
      visit_preorder(node->left);
      visit_preorder(node->right);
    }
  }

  void visit_inorder(TreeNode *node) {
    if (node) {
      visit_inorder(node->left);
      dispatch_node(node);
      visit_inorder(node->right);
    }
  }

  void visit_postorder(TreeNode *node) {
    if (node) {
      visit_postorder(node->left);
      visit_postorder(node->right);
      dispatch_node(node);
    }
  }

  void handle_RED(TreeNode *node) { std::print("Generic handle RED\n"); }

  void handle_BLUE(TreeNode *node) { std::print("Generic handle BLUE\n"); }

private:
  // Convenience method for CRTP
  //
  Derived &derived() { return *static_cast<Derived *>(this); }

  void dispatch_node(TreeNode *node) {
    switch (node->kind) {
    case TreeNode::RED:
      derived().handle_RED(node);
      break;
    case TreeNode::BLUE:
      derived().handle_BLUE(node);
      break;
    default:
      std::print("-------\n");
      break;
    }
  }
};
class SpecialVisitor : public GenericVisitor<SpecialVisitor> {
public:
  void handle_RED(TreeNode *node) { std::print("RED is special\n"); }
};
// NOTE: extracted from Fluent cpp
// https://www.fluentcpp.com/2017/05/16/what-the-crtp-brings-to-code/
template <typename T> class Amount {
public:
  double getValue() const { return static_cast<T const &>(*this).getValue(); }
};
class Constant42 : public Amount<Constant42> {
public:
  double getValue() const { return 42; }
};

class Variable : public Amount<Variable> {
public:
  explicit Variable(int value) : value_(value) {}
  double getValue() const { return value_; }

private:
  int value_;
};
template<typename T>
void print_crtp(Amount<T> const& amount)
{
	std::println("{}", amount.getValue());
}
int main() {
  SpecialVisitor s;
  TreeNode *t = new TreeNode(TreeNode::Kind::BLUE);
  TreeNode *left = new TreeNode(TreeNode::Kind::RED);
  TreeNode *right = new TreeNode(TreeNode::Kind::BLUE);

  t->left = left;
  t->right = right;
  s.visit_preorder(t);

  delete left;
  delete right;
  delete t;

  Constant42 c42;
  print_crtp(c42);
  Variable v(43);
  print_crtp(v);

  return 0;
}
