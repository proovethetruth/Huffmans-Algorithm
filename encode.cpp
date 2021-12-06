
#include "Haffman Algorithm.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <bitset>
#include <sstream>

Node* addNode(char ch, int freq, Node* left, Node* right) {
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

void build_tree(std::string& text, std::string& name) {
	std::unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	std::cout << "\n\n Found characters frequency: ";
	for (auto& it : freq) {
		std::cout << "\n " << it.first;
		std::cout << " " << it.second;
	}

	std::priority_queue<Node*, std::vector<Node*>, comp> pq;
	for (auto pair : freq) {
		pq.push(addNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1) {
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();

		pq.push(addNode('\0', (left->freq + right->freq), left, right));
	}

	Node* root = pq.top();

	std::unordered_map<char, std::string> huffmanCode;
	encode(root, "", huffmanCode);

	std::cout << "\n\n Huffman Codes are :";
	for (auto pair : huffmanCode) {
		std::cout << "\n " << pair.first << " " << pair.second;
	}

	std::string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	std::string base_name;
	for (int i = 0; i < 4; i++)
		name.pop_back();
	base_name = name + " - encoded.txt";
	std::ofstream outfile(base_name);

	str = bin_to_hex(outfile, str);
	reverse(str.begin(), str.end());
	outfile << str;
	outfile.close();

	//base_name = name + "'s tree.txt";
	//std::fstream outfile(base_name);
	//outfile.open();
	//save_tree(outfile, root);
	//outfile.close();
}

void encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode) {
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

std::string bin_to_hex(std::ofstream& file, std::string& str) {
	std::stringstream tmp;

	while (str.size() % 4 != 0) {
		str = "0" + str;
	}
	reverse(str.begin(), str.end());

	std::bitset<4> set;
	std::cout << "\n";
	while (str.size() != 0) {
		for (std::size_t i = 0; i < 4; i++) {
			set[i] = str[i] - '0';
			std::cout << set[i];
		}
		std::cout << " - ";
		tmp << std::hex << set.to_ulong();
		std::cout << " - " << std::hex << set.to_ulong() << std::endl;
		str.erase(0, 4);
	}
	return tmp.str();
}