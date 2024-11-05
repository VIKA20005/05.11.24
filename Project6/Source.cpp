#include <iostream>
#include <string>
#include <limits>

using namespace std;


struct Node {
    string english_word; 
    string russian_word; 
    int count; 
    Node* left;  
    Node* right; 

    Node(string eng, string rus) : english_word(eng), russian_word(rus), count(0), left(nullptr), right(nullptr) {}
};


class BinaryTree {
private:
    Node* root;

    
    Node* insert(Node* node, const string& english_word, const string& russian_word) {
        if (node == nullptr) {
            return new Node(english_word, russian_word);
        }

        if (english_word < node->english_word) {
            node->left = insert(node->left, english_word, russian_word);
        }
        else if (english_word > node->english_word) {
            node->right = insert(node->right, english_word, russian_word);
        }
        else {
            node->count++; 
        }
        return node;
    }

    Node* find(Node* node, const string& english_word) {
        if (node == nullptr || node->english_word == english_word) {
            return node;
        }

        if (english_word < node->english_word) {
            return find(node->left, english_word);
        }
        else {
            return find(node->right, english_word);
        }
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->english_word << " - " << node->russian_word << " (Visits: " << node->count << ")\n";
            inOrder(node->right);
        }
    }

    Node* minNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* maxNode(Node* node) {
        Node* current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    Node* remove(Node* node, const string& english_word) {
        if (node == nullptr) return node;

        if (english_word < node->english_word) {
            node->left = remove(node->left, english_word);
        }
        else if (english_word > node->english_word) {
            node->right = remove(node->right, english_word);
        }
        else { // Ќайдено слово
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minNode(node->right);
            node->english_word = temp->english_word;
            node->russian_word = temp->russian_word;
            node->count = temp->count;
            node->right = remove(node->right, temp->english_word);
        }
        return node;
    }

    
    void findPopular(Node* node, Node*& popular, Node*& leastPopular) {
        if (node != nullptr) {
            if (popular == nullptr || node->count > popular->count) {
                popular = node;
            }
            if (leastPopular == nullptr || node->count < leastPopular->count) {
                leastPopular = node;
            }
            findPopular(node->left, popular, leastPopular);
            findPopular(node->right, popular, leastPopular);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    
    void insert(const string& english_word, const string& russian_word) {
        root = insert(root, english_word, russian_word);
    }

    
    string find(const string& english_word) {
        Node* node = find(root, english_word);
        if (node != nullptr) {
            node->count++;
            return node->russian_word;
        }
        return "—лово не найдено!";
    }

   
    void display() {
        inOrder(root);
    }

   
    void remove(const string& english_word) {
        root = remove(root, english_word);
    }

    
    void displayPopularAndLeastPopular() {
        Node* popular = nullptr;
        Node* leastPopular = nullptr;
        findPopular(root, popular, leastPopular);

        if (popular != nullptr) {
            cout << "—амое попул€рное слово: " << popular->english_word << " (Visits: " << popular->count << ")\n";
        }
        else {
            cout << "ѕопул€рные слова не найдены.\n";
        }

        if (leastPopular != nullptr) {
            cout << "—амое непопул€рное слово: " << leastPopular->english_word << " (Visits: " << leastPopular->count << ")\n";
        }
        else {
            cout << "Ќепопул€рные слова не найдены.\n";
        }
    }
};

int main() {
    BinaryTree dict;

    dict.insert("apple", "€блоко");
    dict.insert("banana", "банан");
    dict.insert("cherry", "вишн€");

    cout << "¬ведите слово дл€ поиска: ";
    string word;
    cin >> word;
    cout << "ѕеревод: " << dict.find(word) << endl;

    dict.display();

    cout << "\n—амое попул€рное и непопул€рное слово:\n";
    dict.displayPopularAndLeastPopular();

    cout << "\n”далим слово 'banana'.\n";
    dict.remove("banana");
    dict.display();

    return 0;
}