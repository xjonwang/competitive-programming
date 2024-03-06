#include <iostream>
 
enum COLOR { RED, BLACK };
 
struct Node {
  int val;
  COLOR color;
  Node *left, *right, *parent;
};

Node root = NULL;
 
// check if node is left child of parent
bool left(Node *node) { return node == node->parent->left; }

Node *uncle(Node *node) {
  if (node->parent == NULL or node->parent->parent == NULL)
    return NULL;
  if (left(node->parent))
    return parent->parent->right;
  else
    return parent->parent->left;
}

Node *sibling(Node *node) {
  if (node->parent == NULL)
    return NULL;
  if (left(node))
    return parent->right;
  else
    return parent->left;
}

void movedown(Node *node, Node *newpar) {
  if (node == root)
    root = newpar;
  if (node->parent != NULL) {
    if (left(node)) {
      parent->left = newpar;
    } else {
      parent->right = newpar;
    }
  }
  newpar->parent = node->parent;
  node->parent = newpar;
}

bool redchild(Node *node) {
  return (node->left != NULL && node->left->color == RED) || (node->right != NULL && node->right->color == RED);
}
 
 
  void leftrotate(Node *root, Node *x) {
    Node *newpar = x->right;
    movedown(x, newpar);
    x->right = newpar->left;
    if (newpar->left != NULL)
      newpar->left->parent = x;
    newpar->left = x;
  }
 
  void rightrotate(Node *x) {
    Node *newpar = x->left;
    movedown(x, newpar);
    x->left = newpar->right;
    if (newpar->right != NULL)
      newpar->right->parent = x;
    newpar->right = x;
  }
 
  void swapcolor(Node *x1, Node *x2) {
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }
 
  void swapValues(Node *x1, Node *x2) {
    int temp;
    temp = x1->val;
    x1->val = x2->val;
    x2->val = temp;
  }
 
  // fix red red at given node
  void fixrr(Node *root, Node *x) {
    if (x == root) {
      x->color = BLACK;
      return;
    }
    while (x != root && x->parent->color == RED) {
      Node *parent = x->parent, *grandparent = parent->parent, *uncle = uncle(x);
  
      if (parent->color != BLACK) {
        if (uncle != NULL && uncle->color == RED) {
          parent->color = BLACK;
          uncle->color = BLACK;
          grandparent->color = RED;
          x = grandparent;
        } else {
          if (parent->isOnLeft()) {
            if (x->isOnLeft()) {
              swapColors(parent, grandparent);
            } else {
              leftRotate(parent);
              swapColors(x, grandparent);
            }
            rightRotate(grandparent);
          } else {
            if (x->isOnLeft()) {
              rightRotate(parent);
              swapColors(x, grandparent);
            } else {
              swapColors(parent, grandparent);
            }
            leftRotate(grandparent);
          }
        }
      }
    }
  }
 
  // find node that do not have a left child
  // in the subtree of the given node
  Node *successor(Node *x) {
    Node *suc = x;
    while (suc->left != NULL)
      suc = suc->left;
    return suc;
  }
 
  // find node that replaces a deleted node in BST
  Node *replace(Node *x) {
    if (x->left != NULL and x->right != NULL)
      return successor(x->right);
    else if (x->left != NULL)
      return x->left;
    else if (x->right != NULL)
      return x->right;
    else
      return NULL;
  }
 
  // deletes the given node
  void deletenode(Node *x) {
    for (;;) {
      Node *y = replace(x);
  
      bool xyb = (y == NULL || y->color == BLACK) && (x->color == BLACK);
      Node *parent = x->parent;
  
      if (y == NULL) {
        if (x == root) {
          root = NULL;
        } else {
          if (xyb) {
            fixbb(x);
          } else {
            if (sibling(x) != NULL)
              sibling(x)->color = RED;
          }
  
          if (left(x)) {
            parent->left = NULL;
          } else {
            parent->right = NULL;
          }
        }
        delete x;
        return;
      }
  
      if (x->left == NULL || x->right == NULL) {
        if (x == root) {
          x->val = y->val;
          x->left = x->right = NULL;
          delete y;
        } else {
          if (left(x))
            parent->left = y;
          else
            parent->right = y;
          delete x;
          y->parent = parent;
          if (xyb)
            fixbb(y);
          else
            y->color = BLACK;
        }
        return;
      }
  
      swapValues(x, y);
      x = y;
    }
  }
 
  void fixbb(Node *x) {
    if (x == root)
      return;
 
    Node *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
      // No sibling, double black pushed up
      fixDoubleBlack(parent);
    } else {
      if (sibling->color == RED) {
        // Sibling red
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        // Sibling black
        if (sibling->hasRedChild()) {
          // at least 1 red children
          if (sibling->left != NULL and sibling->left->color == RED) {
            if (sibling->isOnLeft()) {
              // left left
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rightRotate(parent);
            } else {
              // right left
              sibling->left->color = parent->color;
              rightRotate(sibling);
              leftRotate(parent);
            }
          } else {
            if (sibling->isOnLeft()) {
              // left right
              sibling->right->color = parent->color;
              leftRotate(sibling);
              rightRotate(parent);
            } else {
              // right right
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              leftRotate(parent);
            }
          }
          parent->color = BLACK;
        } else {
          // 2 black children
          sibling->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }
 
public:
  // constructor
  // initialize root
  RBTree() { root = NULL; }
 
  Node *getRoot() { return root; }
 
  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)
  Node *search(int n) {
    Node *temp = root;
    while (temp != NULL) {
      if (n < temp->val) {
        if (temp->left == NULL)
          break;
        else
          temp = temp->left;
      } else if (n == temp->val) {
        break;
      } else {
        if (temp->right == NULL)
          break;
        else
          temp = temp->right;
      }
    }
 
    return temp;
  }
 
  // inserts the given value to tree
  void insert(int n) {
    Node *newNode = new Node(n);
    if (root == NULL) {
      // when root is null
      // simply insert value at root
      newNode->color = BLACK;
      root = newNode;
    } else {
      Node *temp = search(n);
 
      if (temp->val == n) {
        // return if value already exists
        return;
      }
 
      // if value is not found, search returns the node
      // where the value is to be inserted
 
      // connect new node to correct node
      newNode->parent = temp;
 
      if (n < temp->val)
        temp->left = newNode;
      else
        temp->right = newNode;
 
      // fix red red violation if exists
      fixRedRed(newNode);
    }
  }
 
  // utility function that deletes the node with given value
  void deleteByVal(int n) {
    if (root == NULL)
      // Tree is empty
      return;
 
    Node *v = search(n), *u;
 
    if (v->val != n) {
      cout << "No node found to delete with value:" << n << endl;
      return;
    }
 
    deleteNode(v);
  }
 
  // prints inorder of the tree
  void printInOrder() {
    cout << "Inorder: " << endl;
    if (root == NULL)
      cout << "Tree is empty" << endl;
    else
      inorder(root);
    cout << endl;
  }
 
  // prints level order of the tree
  void printLevelOrder() {
    cout << "Level order: " << endl;
    if (root == NULL)
      cout << "Tree is empty" << endl;
    else
      levelOrder(root);
    cout << endl;
  }
};
 
int main() {
  RBTree tree;
  
}