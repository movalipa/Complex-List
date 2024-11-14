#pragma once

#include <iostream>
using namespace std;

#define InputFilePath "in.txt"

char variables[] = {
	'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w'
};



class Node
{
private:
	char var = NULL;
	float coef = NULL;
	int exp = NULL, type = NULL;
	Node* link = NULL;
	Node* dlink = NULL;
public:
	Node(char var, Node* link); // type 1
	Node(Node* dlink, int exp, Node* link); // type 2
	Node(float coef, int exp, Node* link); // type 3
	int print(bool printAll, int line, int depth, int skipLine);
	int getDepth();
	static Node* generateFromFile(string fileName);
	static Node* generateFromMatrix(float inputMatrix[MaxFileLines][MaxFileLines], int i, int j);
};

int blockWitdh = 33, blockHeight = 9;

template <class T>
void printLine(string label, T data, int color, int& line, int depth, string ending = "") {
	gotoxy(depth * blockWitdh, line++);

	cout << "|";
	setConsoleColor(WHITE);
	cout << left << setw(10) << label;
	if (data == NULL)
	{
		setConsoleColor(LIGHTRED);
		cout << left << setw(16) << "Null";
	}
	else
	{
		setConsoleColor(color);
		cout << left << setw(16) << data;
	}
	setConsoleColor(WHITE);
	cout << "|" << ending << "\n";
}

void printLineSeprator(int& line, int depth, bool linked = false) {
	gotoxy(depth * blockWitdh, line++);

	if (linked)

		cout << "--------------V-------------\n";
	else
		cout << "----------------------------\n";
}

void printCustomLine(int& line, int depth, string text) {
	gotoxy(depth * blockWitdh, line++);

	cout << text;
}


Node::Node(char var, Node* link = NULL) : type(1), var(var), link(link) {}

Node::Node(Node* dlink, int exp, Node* link = NULL) : type(2), dlink(dlink), exp(exp), link(link) {}

Node::Node(float coef, int exp, Node* link = NULL) : type(3), coef(coef), exp(exp), link(link) {}


int Node::print(bool printAll = false, int line = 0, int depth = 0, int skipLine = 0) {
	if (this == NULL) return 0;

	int count = 1;

	bool hasDlink = dlink != NULL;

	printLineSeprator(line, depth);
	printLine("Address", this, BROWN, line, depth, ((hasDlink) ? "   --" : ""));
	printLine("Type", type, WHITE, line, depth, ((hasDlink) ? "  / " : ""));
	printLine("Dlink", dlink, BROWN, line, depth, ((hasDlink) ? "--" : ""));
	printLine("Var", var, WHITE, line, depth);
	printLine("Exp", exp, WHITE, line, depth);
	printLine("Coef", coef, WHITE, line, depth);
	printLine("Link", link, BROWN, line, depth);
	printLineSeprator(line, depth, link != NULL);

	int prevLine = line;
	if (printAll)
	{
		int a = dlink->print(printAll, line - blockHeight, depth + 1);
		if (a > 1) count += a - 1;

		for (int i = prevLine; link != NULL && i < line + (count - 1) * blockHeight;)
			printCustomLine(i, depth, "              |             \n");

		count += link->print(printAll, line + (count - 1) * blockHeight, depth);
	}
	cout << "\n";
	return count;
}

int Node::getDepth()
{
	if (this == NULL) return -1;

	// TODO 

	int depth = 0;
}

Node* Node::generateFromFile(string fileName = InputFilePath)
{
	float matrix[MaxFileLines][MaxFileLines] = { 0 };
	int i = 0, j = 0;

	string lines[MaxFileLines];
	int n = readFile(InputFilePath, lines);

	string token;// helping string

	for (i = 0; i < n - 1; i++)
	{
		// i + 1 to skip the first line
		stringstream ss(lines[i + 1]);

		j = 0;
		while (getline(ss >> ws, token, ' '))
		{
			matrix[i][j++] = stof(token);
		}
	}

	return generateFromMatrix(matrix, i, j);
}

Node* Node::generateFromMatrix(float inputMatrix[MaxFileLines][MaxFileLines], int i, int j)
{
	return  new Node('a', new Node(new Node(new Node(new Node('h'), 11, new Node('o')), 22, new Node(new Node('p', new Node('j')), 77)), 2, new Node('c')));
	// TODO
}








