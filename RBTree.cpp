//
//  main.cpp
//  RBTree
//
#include <iostream>
#include <utility>
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
        
        

    }
    
private:
    Node* _root;
};

int main() {
    
    return 0;
}
