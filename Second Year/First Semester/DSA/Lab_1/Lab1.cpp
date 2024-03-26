#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class AVL {
	struct avltree {
		int key;
		string value;
		int height;
		bool deleted;
		struct avltree* left;
		struct avltree* right;
	};

	avltree* root;
	avltree* new_root;

	void avltree_free(struct avltree* tree) {
		if (tree == NULL)
			return;
		
		avltree_free(tree->left);
		avltree_free(tree->right);
		delete tree;
	}

	avltree* avltree_create(int key, avltree* node, string value) {
		node = new avltree;
		if (node != NULL) {
			node->key = key;
			node->value = value;
			node->deleted = false;
			node->left = NULL;
			node->right = NULL;
			node->height = 0;
		}
		return node;
	}

	avltree* avltree_add(int key, avltree* tree, string value) {
		if (tree == NULL) {
			return avltree_create(key, tree, value);
		}

		if (key < tree->key) {
			tree->left = avltree_add(key, tree->left, value);
			if (avltree_height(tree->left) - avltree_height(tree->right) == 2) {
				if (key < tree->left->key) {
					tree = right_rotate(tree);
				}
				else {
					tree = double_right_rotate(tree);
				}
			}
		}

		else if (key > tree->key) {
			tree->right = avltree_add(key, tree->right, value);
			if (avltree_height(tree->right) - avltree_height(tree->left) == 2) {
				if (key > tree->right->key) {
					tree = left_rotate(tree);
				}
				else {
					tree = double_left_rotate(tree);
				}
			}
		}

		tree->height = max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
		return tree;
	}

	avltree* right_rotate(avltree* &tree) {
		avltree* l = tree->left;
		tree->left = l->right;
		l->right = tree;
		tree->height = max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
		l->height = max(avltree_height(tree->left), tree->height) + 1;
		return l;
	}

	avltree* left_rotate(avltree*& tree) {
		avltree* r = tree->right;
		tree->right = r->left;
		r->left = tree;
		tree->height = max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
		r->height = max(avltree_height(tree->right), tree->height) + 1;
		return r;
	}

	avltree* double_right_rotate(avltree*& tree) {
		tree->left = left_rotate(tree->left);
		return right_rotate(tree);
	}

	avltree* double_left_rotate(avltree*& tree) {
		tree->right = right_rotate(tree->right);
		return left_rotate(tree);
	}

	int del_count = 0;
	int max_del = 5;

	void avltree_delete(int key, string new_value) {
		avltree* node = avltree_lookup(root, key);
		if (node != NULL) {
			if (!node->deleted) {
				node->deleted = true;
				del_count++;
				node->value = new_value;
			}
		}
		if (del_count >= max_del) {
			create_new_tree();
		}
	}

	void create_new_tree() {
		new_root = NULL;
		copy_tree(root);
		avltree_free(root);
		root = new_root;
		del_count = 0;
	}

	void copy_tree(avltree* tree) {
		if (tree == NULL) {
			return;
		}
		if (tree->deleted == false) {
			avltree* new_node = avltree_create(tree->key, tree ,tree->value);
			new_node->left = tree->left;
			new_node->right = tree->right;
			new_root = avltree_add(new_node->key, new_root, new_node->value);
		}
		copy_tree(tree->left);
		copy_tree(tree->right);
	}

	avltree* avltree_lookup(avltree* tree, int key) {
		while (tree != NULL) {
			if (key == tree->key && !tree->deleted) {
				return tree;
			}
			else if (key < tree->key) {
				tree = tree->left;
			}
			else {
				tree = tree->right;
			}
		}
		return tree;
	}

	avltree* avltree_min(avltree* tree) {
		if (tree == NULL) {
			return NULL;
		}
		else if (tree->left == NULL) {
			return tree;
		}
		else {
			return avltree_min(tree->left);
		}
	}

	avltree* avltree_max(avltree* tree) {
		if (tree == NULL) {
			return NULL;
		}
		else if (tree->right == NULL) {
			return tree;
		}
		else{
			return avltree_max(tree->right);
		}
	}


	int avltree_height(avltree* tree) {
		return (tree == NULL ? -1 : tree->height);
	}


	int avltree_balance(avltree* tree) {
		if (tree == NULL) {
			return 0;
		}
		else {
			return avltree_height(tree->left) - avltree_height(tree->right);
		}
	}

	void avltree_print(avltree* tree, string indent, bool last) {
		if (tree != NULL) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "     ";
			}
			else {
				cout << "L----";
				indent += "|    ";
			}

			cout << tree->key << "(" << tree->value << ")" << endl;

			avltree_print(tree->left, indent, false);
			avltree_print(tree->right, indent, true);
		}
	}

public:
	AVL() {
		root = NULL;
	}

	void avltree_free() {
		avltree_free(root);
	}

	void avltree_add(int key, string value) {
		root = avltree_add(key, root, value);
	}

	void avltree_delete(int key) {
		avltree_delete(key, root->value);
	}

	string avltree_lookup(int key) {
		avltree* node = avltree_lookup(root, key);
		if (node != NULL) {
			return node->value;
		}
		else {
			return "Not found";
		}
	}

	string avltree_min() {
		avltree* node = avltree_min(root);
		if (node != NULL) {
			return node->value;
		}
	}

	string avltree_max() {
		avltree* node = avltree_max(root);
		if (node != NULL) {
			return node->value;
		}
	}

	void avltree_print() {
		avltree_print(root, "", true);
	}

	int avltree_height() {
		return avltree_height(root);
	}

	int avltree_balance() {
		return avltree_balance(root);
	}

};




int main() {
	AVL avl;

	avl.avltree_add(50, "Cat");
	avl.avltree_add(55, "Dog");
	avl.avltree_add(63, "Parrot");
	avl.avltree_add(69, "Turtle");
	avl.avltree_add(86, "Frog");
	avl.avltree_add(18, "Monkey");
	avl.avltree_add(99, "Horse");
	avl.avltree_add(74, "Lion");
	avl.avltree_add(1, "Tiger");
	avl.avltree_add(77, "Butterfly");
	avl.avltree_add(9, "Fox");
	avl.avltree_add(5, "Shark");
	avl.avltree_add(98, "Cow");
	avl.avltree_add(48, "Wolf");
	avl.avltree_add(13, "Snake");

	avl.avltree_print();
	cout << endl << "-------------------------------------------" << endl;

	string min = avl.avltree_min();
	string max = avl.avltree_max();
	cout << "Minimum value is: " << min << endl;
	cout << "Maximum value is: " << max << endl;
	cout << "-------------------------------------------" << endl;

	string found = avl.avltree_lookup(77);
	cout << "Search before deletion:" << endl;
	cout << "Found value is: " << found << endl;

	avl.avltree_delete(77);
	found = avl.avltree_lookup(77);
	cout << endl << "Search after deletion:" << endl;
	cout << "Found value is: " << found << endl;
	cout << "-------------------------------------------" << endl << endl;

	avl.avltree_delete(55);
	avl.avltree_delete(99);
	avl.avltree_delete(5);
	avl.avltree_delete(48);

	avl.avltree_print();
	cout << endl << "-------------------------------------------" << endl;

	AVL avl2;

	ifstream inputKeys("keys.txt");
	ifstream inputValues("values.txt");

	int key, count = 0, h;
	string value;
	while (inputKeys >> key && inputValues >> value) {
		avl2.avltree_add(key, value);
		count++;
		if (count % 5000 == 0) {
			h = avl2.avltree_height();
			cout << "Number of elements: " << count << endl << "Tree height: " << h << endl << "Height using the logarithm: " << log2(count) << endl;
			cout << "-----------------------------------" << endl;
		}
	}
	inputKeys.close();
	inputValues.close();
	

	return 0;

}
