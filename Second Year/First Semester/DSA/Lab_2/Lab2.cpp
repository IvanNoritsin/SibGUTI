#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 26;

struct trie {
	struct trie* children[N];
	bool isEndOfWord;
	int value;
};

trie* trie_create() {
	trie* node = new trie;
	node->isEndOfWord = false;
	node->value = 0;
	for (int i = 0; i < N; i++)
		node->children[i] = NULL;
	return node;
}

int trie_lookup(trie* root, string key) {
	trie* currentNode = root;
	for (int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		if (!currentNode->children[index]) {
			return -1;
		}
		currentNode = currentNode->children[index];
	}
	if (currentNode->isEndOfWord) {
		return currentNode->value;
	}
	return -1;
}

void trie_insert(trie* root, string key, int value) {
	trie* currentNode = root;
	for (int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		if (!currentNode->children[index]) {
			currentNode->children[index] = trie_create();
		}
		currentNode = currentNode->children[index];
	}
	currentNode->isEndOfWord = true;
	currentNode->value = value;
}

void trie_delete(trie* root, string key) {
	trie* currentNode = root;
	for (int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		if (!currentNode->children[index]) {
			return;
		}
		currentNode = currentNode->children[index];
	}
	currentNode->isEndOfWord = false;
}

void print_trie(trie* node, string prefix = "") {
	if (node->isEndOfWord) {
		cout << prefix << " (" << node->value << ")" << endl;
	}
	for (int i = 0; i < N; i++) {
		if (node->children[i]) {
			char ch = i + 'a';
			print_trie(node->children[i], prefix + ch);
		}
	}
}


int main() {
	trie* root = trie_create();

	trie_insert(root, "there", 32);
	trie_insert(root, "their", 5);
	trie_insert(root, "this", 74);
	trie_insert(root, "that", 57);
	trie_insert(root, "does", 23);
	trie_insert(root, "did", 98);
	trie_insert(root, "omega",48);

	print_trie(root);

	cout << "--------------------------" << endl;
	cout << "Lookup before deletion" << endl << "Found value is: ";
	if (trie_lookup(root, "this") != -1) {
		cout << trie_lookup(root, "this");
	}
	else {
		cout << "Not found";
	}

	cout << endl << endl;

	trie_delete(root, "this");

	cout << "Lookup after deletion" << endl << "Found value is: ";
	if (trie_lookup(root, "this") != -1) {
		cout << trie_lookup(root, "this");
	}
	else {
		cout << "Not found";
	}

	cout << endl;





	return 0;
}
