#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct ttree {
	int value;
	ttree* left;
	ttree* right;
};

ttree* ttree_create(int value) {
	ttree* newNode = new ttree;
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

ttree* ttree_build(vector<int>& players, int start, int end) {
	if (start == end) {
		return ttree_create(players[start]);
	}

	int mid = (start + end) / 2;
	ttree* left = ttree_build(players, start, mid);
	ttree* right = ttree_build(players, mid + 1, end);
	ttree* winner = ttree_create(max(left->value, right->value));
	winner->left = left;
	winner->right = right;

	return winner;
}

int ttree_find_winner(ttree* root) {
	return root->value;
}

int ttree_find_second_best_player(ttree* root) {
	if (root->left->value == root->value) {
		return ttree_find_winner(root->right);
	}
	else {
		return ttree_find_winner(root->left);
	}
}

void ttree_delete(ttree* root) {
	if (root == NULL) {
		return;
	}

	ttree_delete(root->left);
	ttree_delete(root->right);
	delete root;
}

void printTournamentTree(ttree* root, int level) {
	if (root == nullptr) {
		return;
	}
	printTournamentTree(root->right, level + 1);
	for (int i = 0; i < level; i++) {
		cout << "\t";
	}
	cout << root->value << std::endl;
	printTournamentTree(root->left, level + 1);
}



int main() {
	vector<int> players = { 136, 39, 124, 29, 181, 103, 192, 105, 44, 41, 182, 26, 11, 165, 127, 173 };
	ttree* root = ttree_build(players, 0, players.size() - 1);

	printTournamentTree(root, 0);
	cout << endl;

	cout << "The winner is: " << ttree_find_winner(root) << endl;
	cout << "The second best player is: " << ttree_find_second_best_player(root) << endl;

	ttree_delete(root);

	return 0;
}