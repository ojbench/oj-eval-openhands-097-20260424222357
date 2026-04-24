#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build BST from level-order array
TreeNode* buildTree(const vector<int>& arr) {
    if (arr.empty() || arr[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    
    while (!q.empty() && i < arr.size()) {
        TreeNode* node = q.front();
        q.pop();
        
        // Left child
        if (i < arr.size() && arr[i] != -1) {
            node->left = new TreeNode(arr[i]);
            q.push(node->left);
        }
        i++;
        
        // Right child
        if (i < arr.size() && arr[i] != -1) {
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
    string line;
    
    // Read the entire input
    string input = "";
    while (getline(cin, line)) {
        input += line + " ";
    }
    
    // Parse input
    vector<int> arr;
    int cnt = 0;
    
    // Find root array
    size_t start = input.find('[');
    size_t end = input.find(']');
    if (start != string::npos && end != string::npos) {
        string arrStr = input.substr(start + 1, end - start - 1);
        stringstream ss(arrStr);
        string token;
        while (getline(ss, token, ',')) {
            // Trim whitespace
            token.erase(0, token.find_first_not_of(" \t\n\r"));
            token.erase(token.find_last_not_of(" \t\n\r") + 1);
            if (!token.empty() && token != "null") {
                arr.push_back(stoi(token));
            } else {
                arr.push_back(-1); // Use -1 to represent null
            }
        }
    }
    
    // Find cnt value
    size_t cntPos = input.find("cnt");
    if (cntPos != string::npos) {
        size_t equalPos = input.find('=', cntPos);
        if (equalPos != string::npos) {
            string cntStr = input.substr(equalPos + 1);
            // Extract number
            stringstream ss(cntStr);
            ss >> cnt;
        }
    }
    
    // Build tree and find result
    TreeNode* root = buildTree(arr);
    int result = findKthLargest(root, cnt);
    cout << result << endl;
    
    // Clean up
    deleteTree(root);
    
    return 0;
}
