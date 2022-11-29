#include <iostream>
#include <fstream>
#include <deque>
using namespace std;
const int x = 1000;
struct Node{
    int key = 0;
    int dst = 0;
    bool visited = false;
    Node* left = nullptr;
    Node* right = nullptr;
    Node * next = nullptr;
    Node(int x): key(x) , left(nullptr), right(nullptr) , next(nullptr),visited(false),dst(0),visited_p(false){}
    bool visited_p = false;
};
ostream& operator<<(ostream& out, const Node* zet){
    if(zet != nullptr){
        out << zet->key << '\n';
        return out;
    }
    out << "NULL" << '\n';
    return out;
}
template <typename T>
struct queue{
    T * arr;
    int cap;
    int sz;
    int first;
    queue(int n): arr(new T[n]), cap(n), sz(0),first(n/3){}
    bool empty(){
        return !static_cast<bool>(sz);
    }
    T& operator[](int x){
        return arr[first + x];
    }
    T& back(){

        return *(arr + first + sz - 1);
    }
    T& front(){
        return *(arr + first);
    }
    void pop_back(){
        sz--;
    }

    void push_back(T x){
        arr[first + sz++] = x;
    }

    void push_front(T x){
        arr[first--] = x;
        sz++;
    }

    void pop_front(){
        first++;
        sz--;
    }
    ~queue(){
        delete[] arr;
    }
};

void bfs_bts(Node * root){
    queue<Node*> q(x);
    q.push_back(root);
    while(!q.empty()){
        Node * tmp = q.front();
        q.pop_front();
        if(tmp->left != nullptr && !tmp->left->visited){
            q.push_back(tmp->left);
            q.back()->visited = true;
            q.back()->dst = tmp->dst+1;
        }
        if(tmp->right != nullptr && !tmp->right->visited){
            q.push_back(tmp -> right);
            q.back()->visited = true;
            q.back()->dst = tmp->dst + 1;
        }
        if(q.sz > 1 && q[0]->dst == q[1]->dst)
            q[0]->next = q[1];
//        if(q.sz == 2){
//            q.arr[q.first]
//        }
    }
}
void print_bfs_bts(Node * root){
    queue<Node*> q(x);
    q.push_back(root);
    while(!q.empty()){
        Node * tmp = q.front();
        q.pop_front();
        if(tmp->left != nullptr && !tmp->left->visited_p){
            q.push_back(tmp->left);
            q.back()->visited_p = true;
            q.back()->dst = tmp->dst+1;
        }
        if(tmp->right != nullptr && !tmp->right->visited_p){
            q.push_back(tmp -> right);
            q.back()->visited_p = true;
            q.back()->dst = tmp->dst + 1;
        }
        cout << tmp->next;
    }
}


//Node * create_tree(const vector<int>& keys, const vector<char>& directions){
//}

void destruct(Node* root){
    if(root->left != nullptr)
        destruct(root->left);
    if(root->right != nullptr)
        destruct(root->right);
    if(root->left == nullptr && root->right == nullptr)
        delete root;
}
//      1
//     /  \
//    2    3
//      \   \
//       4   7

//Node * construct(vector<vector<int>>& a){
//    Node * root = new Node(a[0]);
//    for(int i = 0; i < a.size();++i){
//
//    }
//}

int main() {
    enum{l, r};
    fstream f;
    f.open("input.txt");
    using pii = pair<int,int>;
    deque<Node*> pool;
    int x; cin >> x;
    for (int i = 0; i < x; ++i) {
        int key; cin >> key;
        pool.push_back(new Node(key));
    }
    int adj[x][2];
    for(int i = 0; i < x; ++i){
       adj[i][l] = adj[i][r] = -1;
    }
    for(int i = 0; i < x; ++i){
        cin >> adj[i][l];
        cin >> adj[i][r];
    }
    for (int i = 0; i < x; ++i) {
        if(adj[i][l] > -1)
            pool[i]->left = pool[adj[i][l]];
        if(adj[i][r] > -1){
            pool[i]->right = pool[adj[i][r]];
        }
    }
    bfs_bts(pool[0]);
    print_bfs_bts(pool[0]);
    return 0;
}
