#include <fstream>
#include <iostream>

struct Node {
	int data;
	Node* next;
	Node(int data)
	{
		this->data = data;
		this->next = NULL;
	}
};

struct AdjacencyList {
	Node** head;

	AdjacencyList(int vertices) {
		head = new Node * [vertices];
		for (int i = 0; i < vertices; i++) head[i] = NULL;
	}

	void Add(int source, int destination) {
		if (head[source] == NULL) head[source] = new Node(destination);
		else {
			Node* temp = head[source];
			head[source] = new Node(destination);
			head[source]->next = temp;
		}
	}
};

struct AdjacencyMatrix {
	int** adjacencyMatrix = NULL;
	int VerticesNumber = 0;

	AdjacencyMatrix() {
		std::fstream file;
		std::string word, filename;
		filename = "file.txt";
		file.open(filename.c_str());
		int n;
		if (file.is_open())
		{
			file >> n;
			adjacencyMatrix = new int* [n];
			for (int i = 0; i < n; i++) adjacencyMatrix[i] = new int[n];
			for (int i = 0; i < n; i++) // reading matrix from file
				for (int j = 0; j < n; j++) file << adjacencyMatrix[i][j];
		}
		file.close();
		VerticesNumber = n;
	}
};

struct Graph {
	int Vertices;
	AdjacencyList* list = NULL;

	Graph(int v) // read graph from a list of edges
	{
		Vertices = v;
		list = new AdjacencyList(Vertices);
		std::fstream file;
		std::string filename;
		int source, destination, number;

		filename = "file3.txt";
		file.open(filename.c_str());

		if (file.is_open()) {
			int i = 1;
			while ((file >> number)) {
				if (i == 1) {
					source = number;
					i++;
				}
				else {
					destination = number;
					AddEdge(source, destination);
					AddEdge(destination, source);
					i = 1;
				}
			}
		}
		file.close();
	}


	void AddEdge(int source, int destination) {
		list->Add(source, destination);
	}

};

int main()
{
	Graph* q = new Graph(10); // 10 - number of vertices
}

