#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build BST from level-order array
TreeNode* buildTree(const vector<int>& arr) {
    if (arr.empty()) return nullptr;
    
    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    
    while (!q.empty() && i < arr.size()) {
        TreeNode* node = q.front();
        q.pop();
        
        // Left child
        if (i < arr.size()) {
            node->left = new TreeNode(arr[i]);
            q.push(node->left);
        }
        i++;
        
        // Right child
        if (i < arr.size()) {
            node->right = new TreeNode(arr[i]);
            q.push(node->right);
        }
        i++;
    }
    
    return root;
}

// Reverse in-order traversal (right-root-left) to get descending order
int kthLargest(TreeNode* root, int& cnt) {
    if (root == nullptr) return -1;
    
    // Visit right subtree first
    int result = kthLargest(root->right, cnt);
    if (result != -1) return result;
    
    // Visit current node
    cnt--;
    if (cnt == 0) return root->val;
    
    // Visit left subtree
    return kthLargest(root->left, cnt);
}

int findKthLargest(TreeNode* root, int k) {
    int cnt = k;
    return kthLargest(root, cnt);
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<int> arr;
    int val;
    
    // Read 7 integers for the BST nodes
    for (int i = 0; i < 7; i++) {
        cin >> val;
        arr.push_back(val);
    }
    
    // Read cnt
    int cnt;
    cin >> cnt;
    
    // Build tree and find result
    TreeNode* root = buildTree(arr);
    int result = findKthLargest(root, cnt);
    cout << result << endl;
    
    // Clean up
    deleteTree(root);
    
    return 0;
}
