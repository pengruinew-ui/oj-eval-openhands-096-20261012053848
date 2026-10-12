#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct NodeInfo {
    int depth;
    int parent;
    NodeInfo() : depth(-1), parent(-1) {}
    NodeInfo(int d, int p) : depth(d), parent(p) {}
};

class Solution {
private:
    unordered_map<int, NodeInfo> nodeInfoMap;
    int index;
    
    TreeNode* buildTree(const vector<int>& preorder, int depth, int parent) {
        if (index >= static_cast<int>(preorder.size())) {
            return nullptr;
        }
        
        int val = preorder[index++];
        if (val == -1) {
            return nullptr;
        }
        
        TreeNode* node = new TreeNode(val);
        nodeInfoMap[val] = NodeInfo(depth, parent);
        
        node->left = buildTree(preorder, depth + 1, val);
        node->right = buildTree(preorder, depth + 1, val);
        
        return node;
    }
    
public:
    void solve() {
        int q;
        cin >> q;
        cin.ignore(); // Consume newline
        
        vector<pair<int, int>> queries;
        for (int i = 0; i < q; i++) {
            string line;
            getline(cin, line);
            istringstream iss(line);
            int x, y;
            iss >> x >> y;
            queries.push_back({x, y});
        }
        
        // Read the tree traversal
        string treeLine;
        getline(cin, treeLine);
        istringstream treeIss(treeLine);
        vector<int> preorder;
        int val;
        while (treeIss >> val) {
            preorder.push_back(val);
        }
        
        // Build tree and collect node information
        index = 0;
        TreeNode* root = buildTree(preorder, 0, -1);
        
        // Process queries
        for (const auto& query : queries) {
            int x = query.first;
            int y = query.second;
            
            if (nodeInfoMap.find(x) == nodeInfoMap.end() || 
                nodeInfoMap.find(y) == nodeInfoMap.end()) {
                cout << 0 << endl;
                continue;
            }
            
            const NodeInfo& infoX = nodeInfoMap[x];
            const NodeInfo& infoY = nodeInfoMap[y];
            
            // Cousins: same depth but different parents
            if (infoX.depth == infoY.depth && infoX.parent != infoY.parent) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
        
        // Clean up memory (optional for this problem)
        deleteTree(root);
    }
    
    void deleteTree(TreeNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

int main() {
    Solution sol;
    sol.solve();
    return 0;
}