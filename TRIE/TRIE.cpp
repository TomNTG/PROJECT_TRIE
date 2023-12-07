#include <iostream>
#include <string>
#include <stack>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
    Node* Child[ALPHABET_SIZE];
    bool isEnd; //Kiem tra ket thuc tu
    Node() { //Khoi tao node
        for (int i = 0; i < ALPHABET_SIZE; i++) Child[i] = NULL;
        isEnd = false;
    }
};

bool isEmpty(Node* root) {
    if (root == NULL) return true;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->Child[i] != NULL) return false;
    return true;
}

void Insert(Node*& root, string key) {
    if (root == NULL) root = new Node();
    Node* p = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (p->Child[index] == NULL)
            p->Child[index] = new Node();
        p = p->Child[index];
    }
    p->isEnd = true;
}

//void Insert(Node*& root, string key, int index = 0) {
//    if (root == NULL) root = new Node();
//    if (index == key.length()) {
//        root->isEnd = true;
//        return;
//    }
//    int childIndex = key[index] - 'a';
//    if (root->Child[childIndex] == NULL)
//        root->Child[childIndex] = new Node();
//    Insert(root->Child[childIndex], key, index + 1);
//}

void Delete(Node*& root, string key, int index = 0) {
    if (root == NULL) return;
    if (index == key.length()) {
        if (root->isEnd == true) root->isEnd = false;
        if (isEmpty(root)) {
            delete root;
            root = NULL;
        }
        return;
    }

    int childIndex = key[index] - 'a';
    Delete(root->Child[childIndex], key, index + 1);

    if (isEmpty(root) && root->isEnd == false) {
        delete root;
        root = NULL;
    }
}

//void Delete(Node*& root, string key) {
//    stack<Node*> st;
//    Node* p = root;
//    for (int i = 0; i < key.length(); i++) {
//        int index = key[i] - 'a';
//        if (p == NULL) return;
//        st.push(p);
//        p = p->Child[index];
//    }
//    if (p == NULL) return;
//    p->isEnd = false;
//    while (!st.empty()) {
//        Node* cur = st.top();
//        st.pop();
//        if (isEmpty(cur) && cur->isEnd == false) {
//            delete cur;
//            cur = NULL;
//        }
//        else {
//            while (!st.empty()) st.pop();
//            return;
//        }
//    }
//}

bool Search(Node* root, string key) {
    if (root == NULL) return false;
    Node* p = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (p->Child[index] == NULL) return false;
        p = p->Child[index];
    }
    return (p != NULL && p->isEnd);
}

//bool Search(Node* root, string key, int index = 0) {
//    if (root == NULL) return false;
//    if (index == key.length())
//        return root->isEnd;
//    int childIndex = key[index] - 'a';
//    if (root->Child[childIndex] == NULL) return false;
//    else return Search(root->Child[childIndex], key, index + 1);
//}

int main() {
    string keys[] = { "hello", "one", "he", "people", "the", "a", "there", "answer", "any", "by",
                      "bye", "their", "hero", "heroplane" };
    int n = sizeof(keys) / sizeof(keys[0]);
    Node* root = new Node();

    for (int i = 0; i < n; i++)
        Insert(root, keys[i]);

    for (int i = 0; i < n; i++) cout << keys[i] << ' ';
    cout << '\n';

    string output[] = { "NO", "YES" };

    cout << "the" << " --- " << output[Search(root, "the")] << '\n';
    cout << "these" << " --- " << output[Search(root, "these")] << '\n';
    cout << "their" << " --- " << output[Search(root, "their")] << '\n';
    cout << "heroplane" << " --- " << output[Search(root, "heroplane")] << '\n';
    cout << "one" << " --- " << output[Search(root, "one")] << '\n';

    Delete(root, "heroplane");
    Delete(root, "one");

    cout << "\nDelete: heroplane one\n";
    cout << "hero" << " --- " << output[Search(root, "hero")] << '\n';
    cout << "heroplane" << " --- " << output[Search(root, "heroplane")] << '\n';
    cout << "one" << " --- " << output[Search(root, "one")] << '\n';
    return 0;
}