#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data)
{
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}

vector<int> NLR(NODE* pRoot)
{
    vector<int> ans;
    if (pRoot == nullptr)
        return ans;
    ans.push_back(pRoot->key);
    vector<int> left = NLR(pRoot->p_left);
    vector<int> right = NLR(pRoot->p_right);
    ans.insert(ans.end(), left.begin(), left.end());
    ans.insert(ans.end(), right.begin(), right.end());
    return ans;
}

vector<int> LNR(NODE* pRoot)
{
    vector<int> ans;
    if (pRoot == nullptr)
        return ans;
    vector<int> left = LNR(pRoot->p_left);
    ans.insert(ans.end(), left.begin(), left.end());
    ans.push_back(pRoot->key);
    vector<int> right = LNR(pRoot->p_right);
    ans.insert(ans.end(), right.begin(), right.end());
    return ans;
}

vector<int> LRN(NODE* pRoot)
{
    vector<int> ans;
    if (pRoot == nullptr) return ans;
    vector<int> left = LRN(pRoot->p_left);
    vector<int> right = LRN(pRoot->p_right);
    ans.insert(ans.end(), left.begin(), left.end());
    ans.insert(ans.end(), right.begin(), right.end());
    ans.push_back(pRoot->key);
    return ans;
}

vector<vector<int>> LevelOrder(NODE* pRoot)
{
    vector<vector<int>> ans;
    if (pRoot == nullptr) return ans;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; ++i)
        {
            NODE* node = q.front(); q.pop();
            level.push_back(node->key);
            if (node->p_left)
                q.push(node->p_left);
            if (node->p_right)
                q.push(node->p_right);
        }
        ans.push_back(level);
    }
    return ans;
}

int countNode(NODE* pRoot)
{
    if (pRoot == nullptr)
        return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot)
{
    if (pRoot == nullptr)
        return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int findHeight(NODE* node)
{
    if (!node)
        return -1;
    return 1 + max(findHeight(node->p_left), findHeight(node->p_right));
}

int heightNode(NODE* pRoot, int value)
{
    if (pRoot == nullptr)
        return -1;
    if (pRoot->key == value)
        return findHeight(pRoot);
    int left = heightNode(pRoot->p_left, value);
    if (left != -1)
        return left;
    return heightNode(pRoot->p_right, value);
}

int Level(NODE* pRoot, NODE* p) {
    if (pRoot == nullptr)
        return -1;
    queue<pair<NODE*, int>> q;
    q.push({pRoot, 0});
    while (!q.empty()) {
        auto [node, level] = q.front(); q.pop();
        if (node == p)
            return level;
        if (node->p_left)
            q.push({node->p_left, level + 1});
        if (node->p_right)
            q.push({node->p_right, level + 1});
    }
    return -1;
}

int countLeaf(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
        return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}


