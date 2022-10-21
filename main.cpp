#include"RBTree.h"

int main() {
    RBTree<int, int> rb;
    std::vector<int> v = {1,5,74,-34,235,6,8,344,213,0,-1,-2,-3,-4,-5};
    for(int i = 0; i < v.size(); i++)
    {
        rb.insert(std::make_pair(v[i],v[i]));
    }
    rb.PreOrder();
    cout<<rb.isBalance()<<std::endl;
    return 0;
}
