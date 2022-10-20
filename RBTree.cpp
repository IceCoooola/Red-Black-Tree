//
//  main.cpp
//  RBTree
//
#include <iostream>
#include <utility>
#include<vector>
using std::pair;
using std::cout;
using std::cin;

enum color
{
    RED,
    BLACK
};

template<class K, class V>
struct RBTreeNode
{
    RBTreeNode<K,V>* _left;
    RBTreeNode<K,V>* _right;
    RBTreeNode<K,V>* _parent;
    
    color _col;
    std::pair<K,V> _kv;
    
    RBTreeNode(const pair<K,V> kv ):_left(nullptr),_right(nullptr),_parent(nullptr),_col(RED),_kv(kv){}
};

template<class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;
public:
    RBTree():_root(nullptr){}
    bool insert(const pair<K, V>& kv)
    {
        if(_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK;
            return true;
        }
        Node* cur = _root;
        Node* parent = _root;
        while(cur)
        {
            if(kv.first < cur->_kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if(kv.first > cur->_kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                cout<<"data exist."<<std::endl;
            }
        }
        
        //insert new node
        cur = new Node(kv);
        cur->_col = RED;
        Node* newnode = cur;
        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
            cur->_parent = parent;
        }
        else
        {
            parent->_left = cur;
            cur->_parent = parent;
        }
        
        while(parent && parent->_col == RED)
        {
            Node* grandParent = parent->_parent;
            if(parent == grandParent->_left)
            {
                Node* uncle = parent->_parent->_right;
                //if uncle exist and is red color. renew uncle && parent's color
                if(uncle && uncle->_col == RED)
                {
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                }
                else//if uncle doesn't exist or uncle is black. means unbalance need to rotate
                {
                    if(cur == parent->_left)
                    {
                        RotateR(grandParent);
                    }
                    else
                    {
                        RotateL(parent);
                        RotateR(grandParent);
                    }
                }
            }
            else if(parent == grandParent->_right)
            {
                Node* uncle = parent->_parent->_left;
                //if uncle exist and is red color. renew uncle && parent's color
                if(uncle && uncle->_col == RED)
                {
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                }
                else//if uncle doesn't exist or uncle is black. means unbalance need to rotate
                {
                    if(cur == parent->_right)
                    {
                        RotateL(grandParent);
                    }
                    else
                    {
                        RotateR(parent);
                        RotateL(grandParent);
                    }
                }
            }
            cur = grandParent;
            cur->_col = RED;
            parent = cur->_parent;
        }
        _root->_col = BLACK;
        return true;
    }
    
    void PreOrder()
    {
        _preOrder(_root);
    }
    
private:
    Node* _root;
    void _preOrder(Node* root)
    {
        if(!root)
            return;
        _preOrder(root->_left);
        cout<<root->_kv.first<<"->"<<root->_kv.second<<std::endl;
        _preOrder(root->_right);
    }
    void RotateR(Node* parent)
    {
        //left side have more nodes, rorate to the right
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        Node* grandparent = parent->_parent;
        parent->_left = subLR;
        subL->_right = parent;
        parent->_parent = subL;
        if (subLR)
        {
            subLR->_parent = parent;
        }


        if (parent == _root)
        {
            _root = subL;
            _root->_parent = nullptr;
        }
        else
        {
            if (grandparent->_left == parent)
            {
                grandparent->_left = subL;
            }
            else
            {
                grandparent->_right = subL;
            }

            subL->_parent = grandparent;
        }

    }

    void RotateL(Node* parent)
    {
        //right side have more nodes, rorate to the left

        Node* grandparent = parent->_parent;
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        parent->_right = subRL;
        subR->_left = parent;
        parent->_parent = subR;
        if (subRL)
        {
            subRL->_parent = parent;
        }

        if (parent == _root)
        {
            _root = subR;
            _root->_parent = nullptr;
        }
        else
        {
            if (grandparent->_left == parent)
            {
                grandparent->_left = subR;
            }
            else
            {
                grandparent->_right = subR;
            }

            subR->_parent = grandparent;
        }
    }
};

int main() {
    RBTree<int, int> rb;
    std::vector<int> v = {1,5,74,-34,235,6,8,344,213,0};
    for(int i = 0; i < v.size(); i++)
    {
        rb.insert(std::make_pair(v[i],v[i]));
    }
    rb.PreOrder();
    return 0;
}
