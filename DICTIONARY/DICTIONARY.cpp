#include <iostream>
#include <string>
#include <list>
#include <fstream>
using namespace std;

const int ALPHABET_SIZE = 27; //Them dau cach

struct Node {
    Node* Child[ALPHABET_SIZE];
    bool isEnd;
    string meaning;
    Node() {
        for (int i = 0; i < ALPHABET_SIZE; i++) Child[i] = NULL;
        isEnd = false;
        meaning = "";
    }
};

bool isEmpty(Node* root) {
    if (root == NULL) return true;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->Child[i] != NULL) return false;
    return true;
}

void Insert(Node*& root, string& key, string& mean) {
    if (root == NULL) root = new Node();
    Node* p = root;
    for (int i = 0; i < key.length(); i++) {
        int index = (key[i] == ' ') ? 26 : key[i] - 'a';
        if (p->Child[index] == NULL)
            p->Child[index] = new Node();
        p = p->Child[index];
    }
    p->isEnd = true;
    p->meaning = mean;
}

void Delete(Node*& root, string key, int index = 0) {
    if (root == NULL) return;
    if (index == key.length()) {
        if (root->isEnd == true) {
            root->isEnd = false;
            root->meaning = "";
        }
        if (isEmpty(root)) {
            delete root;
            root = NULL;
        }
        return;
    }

    int childIndex = (key[index] == ' ') ? 26 : key[index] - 'a';
    Delete(root->Child[childIndex], key, index + 1);

    if (isEmpty(root) && root->isEnd == false) {
        delete root;
        root = NULL;
    }
}

string lowerString(string s) {
    for (int i = 0; i < s.length(); i++) s[i] = tolower(s[i]);
    return s;
}

void printAll(Node* root, char str[], int level, list<pair<string, string>>& List) {
    if (root == NULL) return;
    if (root->isEnd == true) {
        str[level] = '\0';
        List.push_back({ str,root->meaning });
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->Child[i] != NULL) {
            str[level] = (i == 26) ? ' ' : i + 'a';
            printAll(root->Child[i], str, level + 1, List);
        }
}

string Search(Node* root, string key) {
    if (root == NULL) return "Empty!";
    Node* p = root;
    for (int i = 0; i < key.length(); i++) {
        int index = (key[i] == ' ') ? 26 : key[i] - 'a';
        if (index < 0 || index > 26) return "Empty!";
        if (p->Child[index] == NULL) return "Empty!";
        p = p->Child[index];
    }
    if (p != NULL && p->isEnd) return p->meaning;
    return "Empty!";
}

void inputDictionary(Node*& root) {
    fstream f;
    f.open("Dictionary.txt", ios::in);
    if (!f.is_open()) return;
    while (!f.eof()) {
        string st;
        getline(f, st);
        if (st == "") continue;
        int pos = st.find("  ");
        string Key = st.substr(0, pos);
        string Mean = st.substr(pos + 2);
        Key = lowerString(Key);
        Insert(root, Key, Mean);
    }
    f.close();
}

void outputDictionary(Node*& root) {
    fstream f;
    f.open("Dictionary.txt", ios::out);
    if (!f.is_open()) return;
    char st[100];
    list<pair<string, string>> l;
    printAll(root, st, 0, l);
    for (auto st : l)
        f << st.first << "  " << st.second << "\n\n";
    f.close();
}

void menu() {
	cout << "\n---------- Menu ------------\n";
	cout << "1. Search\n";
	cout << "2. Insert\n";
	cout << "3. Delete\n";
	cout << "0. Exit\n";
}

void load_menu() {
    Node* root = new Node();
    inputDictionary(root);
	int k = 0;
	do {
		system("cls");
		menu();

		cout << "Enter your choice: "; cin >> k;
		switch (k) {
		case 1:
		{
            system("cls");
            string Key;
            cout << "->: ";
            cin.ignore();
            getline(cin, Key);
            Key = lowerString(Key);
            cout << "Meaning: " << Search(root, Key);
            cout << '\n';
            system("pause");
            break;
		}
		case 2:
		{
            system("cls");
            string Key, Mean;
            cout << "->: ";
            cin.ignore();
            getline(cin, Key);
            cout << "Meaning: ";
            getline(cin, Mean);
            Key = lowerString(Key);
            Mean = lowerString(Mean);
            Insert(root, Key, Mean);
            outputDictionary(root);
            system("pause");
			break;
		}
		case 3:
		{
            system("cls");
            string Key;
            cout << "->: ";
            cin.ignore();
            getline(cin, Key);
            Key = lowerString(Key);
            Delete(root, Key);
            outputDictionary(root);
            system("pause");
			break;
		}
		case 0: {
			system("cls");
			return;
		}
		default: {
			cout << "Error!\n";
			system("pause");
		}
		}
	} while (true);
}

int main() {
    load_menu();
    return 0;
}
