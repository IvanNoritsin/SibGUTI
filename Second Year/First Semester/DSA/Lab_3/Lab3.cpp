#include <iostream>
#include <cmath>

using namespace std;

struct fibheap {
    fibheap* parent;
    fibheap* child;
    fibheap* left;
    fibheap* right;
    int key;
    string value;
    bool mark;
    int degree;
};

class FH {
private:
    fibheap* minNode;
    int nnodes;

    fibheap* fibheap_create(int key, string value) {
        fibheap* node = new fibheap();
        node->key = key;
        node->value = value;
        node->degree = 0;
        node->mark = false;
        node->parent = NULL;
        node->child = NULL;
        node->left = node;
        node->right = node;
        return node;
    }

    void insertNode(fibheap* root, fibheap* node) {
        node->left = root;
        node->right = root->right;
        root->right->left = node;
        root->right = node;
    }

    void removeNode(fibheap* node) {
        node->left->right = node->right;
        node->right->left = node->left;
    }

    void consolidate() {
        int maxDegree = log(nnodes) / log(2) + 1;
        fibheap** degreeTable = new fibheap * [maxDegree];
        for (int i = 0; i < maxDegree; i++) {
            degreeTable[i] = NULL;
        }

        fibheap* current = minNode;
        while (true) {
            int degree = current->degree;
            while (degreeTable[degree] != NULL) {
                fibheap* other = degreeTable[degree];
                if (current->key > other->key) {
                    swap(current, other);
                }
                link(other, current);
                degreeTable[degree] = NULL;
                degree++;
            }
            degreeTable[degree] = current;
            current = current->right;
            if (current == minNode) {
                break;
            }
        }

        minNode = NULL;
        for (int i = 0; i < maxDegree; i++) {
            if (degreeTable[i] != NULL) {
                if (minNode == NULL) {
                    minNode = degreeTable[i];
                }
                else {
                    insertNode(minNode, degreeTable[i]);
                    if (degreeTable[i]->key < minNode->key) {
                        minNode = degreeTable[i];
                    }
                }
            }
        }
        delete[] degreeTable;
    }

    void link(fibheap* child, fibheap* parent) {
        removeNode(child);
        child->parent = parent;
        child->mark = false;
        if (parent->child == NULL) {
            parent->child = child;
            child->left = child;
            child->right = child;
        }
        else {
            insertNode(parent->child, child);
        }
        parent->degree++;
    }

    void cut(FH& heap, fibheap* node, fibheap* parent) {
        node->left->right = node->right;
        node->right->left = node->left;

        parent->degree--;

        if (parent->child == node) {
            parent->child = node->right;
        }

        node->left = heap.minNode;
        node->right = heap.minNode->right;
        heap.minNode->right = node;
        node->right->left = node;

        node->parent = NULL;

        node->mark = false;
    }

    void cascading_cut(FH& heap, fibheap* node) {
        fibheap* parent = node->parent;

        if (parent != NULL) {
            if (node->mark) {
                cut(heap, node, parent);
                cascading_cut(heap, parent);
            }
            else {
                node->mark = true;
            }
        }
    }

public:
    FH() {
        minNode = NULL;
        nnodes = 0;
    }

    fibheap* fibheap_insert(int key, string value) {
        fibheap* node = fibheap_create(key, value);
        if (minNode == NULL) {
            minNode = node;
        }
        else {
            insertNode(minNode, node);
            if (node->key < minNode->key) {
                minNode = node;
            }
        }
        nnodes++;
        return node;
    }

    fibheap* fibheap_min() {
        if (minNode == NULL) {
            cout << "Heap is empty" << endl;
        }
        return minNode;
    }

    void fibheap_delete_min() {
        if (minNode == NULL) {
            cout << "Heap is empty" << endl;
        }
        else {
            fibheap* temp = minNode;
            fibheap* pntr;
            pntr = minNode;
            fibheap* x = NULL;
            if (temp->child != NULL) {
                x = temp->child;
                do {
                    pntr = x->right;
                    (minNode->left)->right = x;
                    x->right = minNode;
                    x->left = minNode->left;
                    minNode->left = x;
                    if (x->key < minNode->key)
                        minNode = x;
                    x->parent = NULL;
                    x = pntr;
                } while (pntr != temp->child);
            }
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            minNode = temp->right;
            if (temp == temp->right && temp->child == NULL)
                minNode = NULL;
            else {
                minNode = temp->right;
                consolidate();
            }
            nnodes--;
        }

    }

    void fibheap_union(FH& heap1, FH& heap2) {
        if (heap1.minNode == NULL) {
            heap1.minNode = heap2.minNode;
        }
        else if (heap2.minNode != NULL) {
            fibheap* heap1Min = heap1.minNode;
            fibheap* heap2Min = heap2.minNode;
            fibheap* heap1MinRight = heap1Min->right;
            fibheap* heap2MinLeft = heap2Min->left;

            heap1Min->right = heap2Min;
            heap2Min->left = heap1Min;
            heap1MinRight->left = heap2MinLeft;
            heap2MinLeft->right = heap1MinRight;

            if (heap2Min->key < heap1Min->key) {
                heap1.minNode = heap2Min;
            }
        }
        heap1.nnodes += heap2.nnodes;
        heap2.minNode = NULL;
        heap2.nnodes = 0;
    }

    void fibheap_decrease_key(FH& heap, fibheap* node, int newKey) {
        if (newKey > node->key) {
            cout << "New key is greater than current key";
            return;
        }

        node->key = newKey;
        fibheap* parent = node->parent;

        if (parent != NULL && node->key < parent->key) {
            cut(heap, node, parent);
            cascading_cut(heap, parent);
        }

        if (node->key < heap.minNode->key) {
            heap.minNode = node;
        }
    }

    fibheap* fibheap_find(fibheap* root, int key) {
        fibheap* node = root;
        if (node == NULL) {
            return NULL;
        }

        do {
            if (node->key == key) {
                return node;
            }

            fibheap* foundNode = fibheap_find(node->child, key);
            if (foundNode != NULL) {
                return foundNode;
            }

            node = node->right;
        } while (node != root);

        return NULL;
    }

    void fibheap_delete(FH& heap, fibheap* x, int key) {
        fibheap* find = fibheap_find(x, key);
        fibheap_decrease_key(heap, find, -1000000);
        fibheap_delete_min();
    }

    void fibheap_print(FH& heap) {
        if (heap.minNode == NULL) {
            cout << "Heap is empty" << endl;
            return;
        }

        cout << "Fibonacci Heap:" << endl;

        fibheap* current = heap.minNode;
        do {
            cout << "Key: " << current->key << ", Value: " << current->value << endl;

            if (current->child != NULL) {
                printChild(current->child, 1);
            }

            current = current->right;
        } while (current != heap.minNode);

        cout << endl;
    }

    void printChild(fibheap* node, int level) {
        fibheap* current = node;
        do {
            for (int i = 0; i < level; i++) {
                cout << "  ";
            }
            cout << "Key: " << current->key << ", Value: " << current->value << endl;

            if (current->child != NULL) {
                printChild(current->child, level + 1);
            }

            current = current->right;
        } while (current != node);
    }

};


int main() {
    FH fh1;
    FH fh2;

    fibheap* fheap1;
    fibheap* fheap2;

    fheap1 = fh1.fibheap_insert(271, "Sunderland");
    fheap1 = fh1.fibheap_insert(347, "Ely");
    fheap1 = fh1.fibheap_insert(457, "Plymouth");
    fheap1 = fh1.fibheap_insert(4, "Chichester");
    fheap1 = fh1.fibheap_insert(52, "Cambridge");


    fheap2 = fh2.fibheap_insert(135, "Oxford");
    fheap2 = fh2.fibheap_insert(122, "Peterborough");
    fheap2 = fh2.fibheap_insert(187, "York");
    fheap2 = fh2.fibheap_insert(184, "Lincoln");
    fheap2 = fh2.fibheap_insert(38, "Chelmsford");
    fheap2 = fh2.fibheap_insert(487, "Bristol");
    fheap2 = fh2.fibheap_insert(347, "Liverpool");
    fheap2 = fh2.fibheap_insert(24, "Sheffield");


    fh1.fibheap_print(fh1);
    fh2.fibheap_print(fh2);

    fh1.fibheap_union(fh1, fh2);

    fh1.fibheap_print(fh1);

    cout << "============================================" << endl;

    int kmin1;
    string vmin1;

    kmin1 = fh1.fibheap_min()->key;;
    vmin1 = fh1.fibheap_min()->value;

    cout << "Minimum node in heap: " << endl << "Key: " << kmin1 << endl << "Value: " << vmin1 << endl;
    cout << "============================================" << endl;

    fh1.fibheap_delete_min();

    kmin1 = fh1.fibheap_min()->key;
    vmin1 = fh1.fibheap_min()->value;

    cout << "Minimum node in heap after del: " << endl << "Key: " << kmin1 << endl << "Value: " << vmin1 << endl;
    cout << "============================================" << endl;

    fh1.fibheap_print(fh1);

    cout << "============================================" << endl;

    fibheap* find = fh1.fibheap_find(fheap1, 487);
    fh1.fibheap_decrease_key(fh1, find, 350);

    fh1.fibheap_print(fh1);

    cout << "============================================" << endl;

    return 0;
}

