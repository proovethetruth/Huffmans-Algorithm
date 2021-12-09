#ifndef HAFFMAN_ALGORITHM_H
#define HAFFMAN_ALGORITHM_H

#include <string>
#include <unordered_map>

struct Node {
	char ch = 0;
	int freq = 0;
	Node* left = nullptr, * right = nullptr;

	Node() {}
	Node(char val) {
		ch = val;
	}

	Node(char ch, Node* left, Node* right) {
		Node* node = new Node();

		node->ch = ch;
		node->freq = 0;
		node->left = left;
		node->right = right;
	}
};

struct comp {
	bool operator()(Node* l, Node* r) {
		return l->freq > r->freq;
	}
};

// Utility Functions
int check_task(char* argv[]);
std::string gen_filename(std::string original);
int parse_file(std::string& name, std::string& text, int task);
float show_efficiency(float before, float after);
void save_in_binary(std::string& str, std::ofstream& outfile);

Node* addNode(char ch, int freq, Node* left, Node* right);

// Huffman's Algorithm
void build_tree(std::string& text, std::string& name);
void encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode);
std::string bin_to_hex(std::string& str);

void decode(Node* root, int& index, std::string str);

void writeBinaryTree(Node* node, std::string& result);
Node readBinaryTree(std::string& str, int& index);

#endif
