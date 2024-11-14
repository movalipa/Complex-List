#pragma once
// linked list

#include <iostream>
#include <sstream>
#include <string>
#include "file.h"
#include "Node.h"

#define InputFilePath "in.txt"

using namespace std;

char vars[] = {
	'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w'
};

float inputMatrix[MaxFileLines][MaxFileLines] = { 0 };
int inputI = 0, inputJ = 0;

Node* tree = NULL;

void fetchFile() {
	string lines[MaxFileLines];
	int n = readFile(InputFilePath, lines);

	string token;// helping string

	int i = 0, j = 0;
	for (i = 0; i < n - 1; i++)
	{
		// i + 1 to skip the first line
		stringstream ss(lines[i + 1]);

		j = 0;
		while (getline(ss >> ws, token, ' '))
		{
			inputMatrix[i][j++] = stof(token);
		}
	}
	inputI = i;
	inputJ = j;
}

void generateTree() {
	// test
	tree = new Node('a', new Node(new Node(new Node(new Node('h'), 11, new Node('o')), 22, new Node(new Node('p', new Node('j')), 77)), 2, new Node('c')));


}

namespace test {
	void printMatrix() {
		for (int i = 0; i < inputI; i++)
		{
			for (int j = 0; j < inputJ; j++)
			{
				cout << inputMatrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
}




