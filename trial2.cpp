#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <chrono>

using namespace std::chrono;

// Add your name and blazer id here
std::string name = "Kajal Jadhav";
std::string blazer_id = "kjadhav";

/* For all questions, please do not hard-code your algorithms for testing inputs.
You code should work with any input with arbitrary sizes. If you hard-code your algorithms, 10 points
will be deduced per question.
*/

/*
Question 1 (50 points): Implement a priority queue data structure using max-heap.
Do not modify the given function signatures. You are free to add helper functions or variables inside class.
*/
class PriorityQueue
{
public:
  std::vector<int> data;
  int maximum_size;
  int actual_size;

  PriorityQueue(int maximum_size)
  {
    data = std::vector<int>(maximum_size, 0);
    this->maximum_size = maximum_size;
    actual_size = 0;
  }

  // Question 1.1 (20 points): Build the priority queue given a list of element
  void BuildQueue(std::vector<int> input)
  {
    // Put your implementation here...
    if (input.size() > maximum_size)
    {
      std::cerr << "Input size exceeds the maximum size of the priority queue." << std::endl;
      return;
    }

    // Copy input elements to the data vector
    actual_size = static_cast<int>(input.size());
    for (int i = 0; i < actual_size; ++i)
    {
      data[i] = input[i];
    }

    // Heapify the data vector to maintain the max-heap property
    for (int i = actual_size / 2 - 1; i >= 0; --i)
    {
      Heapify(i);
    }
  }

  // Question 1.2 (15 points): Add a key into the priority queue
  void Enqueue(int x)
  {
    // Put your implementation here...
    if (actual_size == maximum_size)
    {
      std::cerr << "Priority queue is full. Cannot enqueue more elements." << std::endl;
      return;
    }

    // Insert the new element at the end of the vector
    int index = actual_size;
    data[index] = x;
    actual_size++;

    // Perform up-heap (swim) to maintain the max-heap property
    while (index > 0 && data[parent(index)] < data[index])
    {
      std::swap(data[index], data[parent(index)]);
      index = parent(index);
    }
  };

  // Question 1.3 (15 points): Remove a highest priority (largest) key from the priority queue
  int Dequeue()
  {

    if (actual_size == 0)
    {
      std::cerr << "Priority queue is empty. Cannot dequeue." << std::endl;
      return 0;
    }
    if (actual_size == 1)
    {
      --actual_size;
      return data[0];
    }
    // Extract the root (maximum element) from the max-heap
    int max_value = data[0];

    // Move the last element to the root
    data[0] = data[actual_size - 1];
    actual_size--;

    // Perform down-heap (sink) to maintain the max-heap property
    Heapify(0);

    return max_value;
  }

private:
  // Helper function to get the index of the parent of a node
  int parent(int i)
  {
    return (i - 1) / 2;
  }

  // Function to perform heapify operation
  void Heapify(int index)
  {
    int largest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if (left_child < actual_size && data[left_child] > data[largest])
    {
      largest = left_child;
    }

    if (right_child < actual_size && data[right_child] > data[largest])
    {
      largest = right_child;
    }

    if (largest != index)
    {
      // Swap elements and recursively heapify the affected subtree
      std::swap(data[index], data[largest]);
      Heapify(largest);
    }
  }
};

/*
Question 2 (70 points): Implement a binary search tree data structure
Do not modify the given function signatures. You are free to add helper functions or variables inside class.

*/

class TreeNode
{
public:
  int key = 0;
  TreeNode *parent = nullptr;
  TreeNode *leftchild = nullptr;
  TreeNode *rightchild = nullptr;
};

class BinarySearchTree
{
public:
  TreeNode *root = nullptr;

  // Question 2.1 (10 points): Add an key into the BST. You can assume that there will be no duplicated keys
  void Insert(int x)
  {
    TreeNode *newNode = new TreeNode();
    newNode->key = x;

    TreeNode *y = nullptr;
    TreeNode *z = root;

    while (z != nullptr)
    {
      y = z;
      if (x < z->key)
        z = z->leftchild;
      else
        z = z->rightchild;
    }

    newNode->parent = y;
    if (y == nullptr)
      root = newNode;
    else if (x < y->key)
      y->leftchild = newNode;
    else
      y->rightchild = newNode;
  }

  // Question 2.2 (10 points): Search for a key in the BST. Return true/false t indicate if the key exist or not
  TreeNode* SearchRecursive(TreeNode* node, int value){
    if(node == nullptr || node->key == value){
      return node;
    }
    if(value < node->key)
      return SearchRecursive(node->leftchild, value);
    return SearchRecursive(node->rightchild, value);
  }

  bool Search(int x)
  {
    return SearchRecursive(root, x); // Put your implementation here...
  }

  // Question 2.3 (10 points): Delete a key in the BST. The key may or may not exsit in the BST before deletion.
  void Transplant(TreeNode* u, TreeNode* v){
    if(u->parent == nullptr){
      root = v;
    }else if(u == u->parent->leftchild){
      u->parent->leftchild = v;
    }else{
      u->parent->rightchild = v;
    }

    if(v != nullptr){
      v->parent = u->parent;
    }
  }
  
  void Delete(int x)
  {
    // Put your implementation here...
    TreeNode* node = SearchRecursive(root, x);
    if(node->leftchild == nullptr){
      Transplant(node, node->rightchild);
    }else if(node->rightchild == nullptr){
      Transplant(node, node->leftchild);
    }else{
      TreeNode* y = GetMinimum(node->rightchild);
      if(y->parent != node){
        Transplant(y, y->rightchild);
        y->rightchild = node->rightchild;
        y->rightchild->parent = y;
      }
      Transplant(node, y);
      y->leftchild = node->leftchild;
      y->leftchild->parent = y;
    }
  }

  // Question 2.4 (10 points): Find the minimum key in the BST.

  TreeNode* GetMinimum(TreeNode* node){
    while(node->leftchild != nullptr)
      node = node->leftchild;
    return node;
  }

  int Minimum()
  {
    // Put your implementation here...
    if(root == nullptr)
      return 0;
    else
      return GetMinimum(root)->key; 
  }
  // Question 2.5 (10 points): Find the maximum key in the BST.

  TreeNode* GetMaximum(TreeNode* node){
    while(node->rightchild != nullptr)
      node = node->rightchild;
    return node;
  }

  int Maximum()
  {
    // Put your implementation here...
    if(root == nullptr)
      return 0;
    else
      return GetMaximum(root)->key; 
  }
  // Question 2.6 (10 points): Find the successor of a key in the BST. If the successor does not exist, return -1.
  int Successor(int x)
  {
    // Put your implementation here...
    TreeNode* node = SearchRecursive(root, x);
    if(node != nullptr && node->rightchild != nullptr){
      return GetMinimum(node->rightchild)->key;
    }
    TreeNode* y = node->parent;
    while(y != nullptr && node == y->rightchild){
      node = y;
      y = y->parent;
    }

    if(y != nullptr){
      return y->key;
    }else{
      return -1;
    }
  }

  // Question 2.7 (10 points): Find the predcessor of a key in the BST. If the predcessor does not exist, return -1.
  int Predcessor(int x)
  {
    // Put your implementation here...
    TreeNode* node = SearchRecursive(root, x);
    if(node != nullptr && node->leftchild != nullptr){
      return GetMaximum(node->leftchild)->key;
    }
    TreeNode* y = node->parent;
    while(y != nullptr && node == y->leftchild){
      node = y;
      y = y->parent;
    }

    if(y != nullptr){
      return y->key;
    }else{
      return -1;
    }
  }
};

/************ Do not modify code below this line ***************/

bool verify_array(std::vector<int> a, std::vector<int> b, int size)
{
  if (a.size() < size || b.size() < size)
    return false;
  for (int i = 0; i < size; i++)
  {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

int subtree_max_value(TreeNode *root)
{
  if (root == nullptr)
  {
    return std::numeric_limits<int>::min();
  }
  int children_max = std::max(subtree_max_value(root->leftchild), subtree_max_value(root->rightchild));
  return std::max(root->key, children_max);
}

int subtree_min_value(TreeNode *root)
{
  if (root == nullptr)
  {
    return std::numeric_limits<int>::max();
  }
  int children_min = std::min(subtree_min_value(root->leftchild), subtree_min_value(root->rightchild));
  return std::min(root->key, children_min);
}

bool verify_tree(TreeNode *root)
{
  if (root == nullptr)
  {
    return true;
  }
  if (root->leftchild != nullptr && root->key <= subtree_max_value(root->leftchild))
  {
    return false;
  }
  if (root->rightchild != nullptr && root->key >= subtree_min_value(root->rightchild))
  {
    return false;
  }
  return verify_tree(root->leftchild) && verify_tree(root->rightchild);
}

int main()
{

  std::vector<int> result = {16, 15, 14, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  bool pass;

  std::cout << "Name: " << name << " Blazer ID: " << blazer_id << "\n";

  std::cout << "---------- Priority Queue ---------\n";
  PriorityQueue pq(15);
  pq.BuildQueue({4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
  pass = verify_array(pq.data, {16, 14, 10, 8, 7, 9, 3, 2, 4, 1}, 10);
  std::cout << "BuildQueue: " << (pass ? "Pass" : "No Pass") << std::endl;
  pq.Enqueue(12);
  pass = verify_array(pq.data, {16, 14, 10, 8, 12, 9, 3, 2, 4, 1, 7}, 11);
  std::cout << "Enqueue(12): " << (pass ? "Pass" : "No Pass") << std::endl;
  pq.Enqueue(5);
  pass = verify_array(pq.data, {16, 14, 10, 8, 12, 9, 3, 2, 4, 1, 7, 5}, 12);
  std::cout << "Enqueue(5): " << (pass ? "Pass" : "No Pass") << std::endl;
  pq.Enqueue(15);
  pass = verify_array(pq.data, {16, 14, 15, 8, 12, 10, 3, 2, 4, 1, 7, 5, 9}, 13);
  std::cout << "Enqueue(15): " << (pass ? "Pass" : "No Pass") << std::endl;
  pq.Enqueue(6);
  pass = verify_array(pq.data, {16, 14, 15, 8, 12, 10, 6, 2, 4, 1, 7, 5, 9, 3}, 14);
  std::cout << "Enqueue(6): " << (pass ? "Pass" : "No Pass") << std::endl;
  pq.Enqueue(11);
  pass = verify_array(pq.data, {16, 14, 15, 8, 12, 10, 11, 2, 4, 1, 7, 5, 9, 3, 6}, 15);
  std::cout << "Enqueue(11): " << (pass ? "Pass" : "No Pass") << std::endl;
  for (int i = 0; i < 15; i++)
  {
    int x = pq.Dequeue();
    pass = x == result[i];
    std::cout << "Dequeue current max " << result[i] << ": " << (pass ? "Pass" : "No Pass") << std::endl;
  }

  std::cout << "---------- Binary Search Tree ---------\n";
  BinarySearchTree bst;
  std::vector<int> input = {5, 3, 8, 1, 4, 6, 9, 2, 0, 7, 10, 11, 12};
  for (int i = 0; i < input.size(); i++)
  {
    bst.Insert(input[i]);
    pass = verify_tree(bst.root);
    std::cout << "Insert key " << input[i] << ": " << (pass ? "Pass" : "No Pass") << std::endl;
  }
  for (int i = 0; i < input.size(); i++)
  {
    pass = bst.Search(input[i]);
    std::cout << "Search key " << input[i] << ": " << (pass ? "Pass" : "No Pass") << std::endl;
  }
  for (int i = 13; i < 20; i++)
  {
    pass = !bst.Search(i);
    std::cout << "Search key " << i << ": " << (pass ? "Pass" : "No Pass") << std::endl;
  }
  pass = bst.Minimum() == 0;
  std::cout << "Minimum key: " << (pass ? "Pass" : "No Pass") << std::endl;
  pass = bst.Maximum() == 12;
  std::cout << "Maximum key: " << (pass ? "Pass" : "No Pass") << std::endl;
  for (int i = 0; i < input.size() - 1; i++)
  {
    pass = bst.Successor(input[i]) == input[i] + 1;
    std::cout << "Successor of key " << input[i] << ": " << (pass ? "Pass" : "No Pass") << std::endl;
  }
  for (int i = 1; i < input.size(); i++)
  {
    pass = bst.Predcessor(input[i]) == input[i] - 1;
    std::cout << "Predcessor of key " << input[i] << ": " << (pass ? "Pass" : "No Pass") << std::endl;
  }
  for (int i = 0; i < input.size(); i++)
  {
    bst.Delete(input[i]);
    pass = !bst.Search(input[i]);
    std::cout << "Delete key " << input[i] << ": " << (pass ? "Pass" : "No Pass") << std::endl;
  }

  return 0;
}