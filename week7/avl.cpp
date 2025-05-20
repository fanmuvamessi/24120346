#include <iostream>
#include <algorithm>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data)
{
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    p->height = 1;
    return p;
}
int getHeight(NODE* node)
{
    if (node)
        return node->height;
    else
        return 0;
}

int getBalance(NODE* node)
{
    if (node)
        return getHeight(node->p_left) - getHeight(node->p_right);
    else
        return 0;
}

void updateHeight(NODE* node) {
    if (node)
        node->height = 1 + max(getHeight(node->p_left), getHeight(node->p_right));
}

NODE* rightRotate(NODE* y)
{
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    x->p_right = y;
    y->p_left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

NODE* leftRotate(NODE* x)
{
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    y->p_left = x;
    x->p_right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

void Insert(NODE* &pRoot, int x)
{
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return;
    updateHeight(pRoot);
    int balance = getBalance(pRoot);
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rightRotate(pRoot);
    else if (balance < -1 && x > pRoot->p_right->key)
        pRoot = leftRotate(pRoot);
    else if (balance > 1 && x > pRoot->p_left->key)
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    else if (balance < -1 && x < pRoot->p_right->key)
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

NODE* findMin(NODE* node)
{
    while (node->p_left)
        node = node->p_left;
    return node;
}

void Remove(NODE* &pRoot, int x)
{
    if (!pRoot)
        return;
    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else
    {
        if (!pRoot->p_left || !pRoot->p_right)
        {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else
        {
            NODE* temp = findMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
    if (!pRoot)
        return;
    updateHeight(pRoot);
    int balance = getBalance(pRoot);
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rightRotate(pRoot);
    else if (balance > 1 && getBalance(pRoot->p_left) < 0)
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = leftRotate(pRoot);
    else if (balance < -1 && getBalance(pRoot->p_right) > 0)
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

bool isAVL(NODE* pRoot)
{
    if (!pRoot)
        return true;
    int balance = getBalance(pRoot);
    if (abs(balance) > 1)
        return false;
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
