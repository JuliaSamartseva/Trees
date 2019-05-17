#include <fstream>
#include <iostream>


struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

struct BinarySearchTree {
	Node* head = NULL;
	int NodesNumber = 0;

	void insertNode(int key) {
		int i = 0;
		Node* x = head;
		Node* element = new Node(key);

		if (head == NULL) head = element; else {
			while (true) {
				if (x->data >= element->data) i = -1;
				else i = 1;
				if (i < 0) {
					if (x->left == NULL) {
						x->left = element;
						break;
					}
					else x = x->left;
				}
				else { // i > 0
					if (x->right == NULL) {
						x->right = element;
						break;
					}
					else x = x->right;
				}
			}
		}
		NodesNumber++;
	}

	Node* minValueNode(Node* element) {
		Node* x = element;
		// find the leftmost node
		while (x->left != NULL) x = x->left;
		return x;
	}

	void deleteNode(int key) {
		Node* x = head;
		head = deleteNode_recur(x, key);
		NodesNumber--;
	}

	Node* deleteNode_recur(Node * node, int key) {
		if (node == NULL) return node;
		if (key < node->data) node->left = deleteNode_recur(node->left, key); //find the right node to delete
		else if (key > node->data) node->right = deleteNode_recur(node->right, key);
		else { // node with this key has been founded
			if (node->left == NULL) // with one or no child
			{
				Node* temp = node->right;
				free(node);
				return temp;
			}
			else if (node->right == NULL)
			{
				Node* temp = node->left;
				free(node);
				return temp;
			}
			// with two children 
			Node* temp = minValueNode(node->right);
			node->data = temp->data;
			node->right = deleteNode_recur(node->right, temp->data);
		}
		return node;
	}

	void printInorder() {
		Node* x = head;
		printInorder_recur(x);
	}

	void printInorder_recur(Node * node) {
		if (node == NULL) return;
		printInorder_recur(node->left);
		std::cout << node->data << " ";
		printInorder_recur(node->right);
	}

	void createInorderArray(Node * node, int* nodes, int& i) {
		if (node == NULL) return;
		createInorderArray(node->left, nodes, i);
		nodes[i] = node->data;
		i++;
		createInorderArray(node->right, nodes, i);
	}

	void balanceBinaryTree() {
		Node* x = head;
		int* nodes = new int[NodesNumber];
		int i = 0;
		createInorderArray(x, nodes, i);
		head = balanceBinaryTree_recur(nodes, 0, NodesNumber - 1);
	}

	Node* balanceBinaryTree_recur(int* nodes, int start, int end) {
		if (start > end)
			return NULL;
		int mid = (start + end) / 2;
		Node * x = new Node(nodes[mid]);
		x->left = balanceBinaryTree_recur(nodes, start, mid - 1);
		x->right = balanceBinaryTree_recur(nodes, mid + 1, end);
		return x;
	}
};

int main()
{
	BinarySearchTree x;
	x.insertNode(50);
	x.insertNode(40);
	x.insertNode(70);
	x.insertNode(60);
	x.insertNode(80);
	x.printInorder();
	x.deleteNode(50);
	x.printInorder();
}