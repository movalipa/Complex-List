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
	static Node* generateFromFile(string fileName);
	static Node* generateFromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n);
	void addExpression(char var, int exp, float coef);
	static bool isEqual(Node* a, Node* b);
	static Node* sum(Node* a, Node* b);
};

int blockWitdh = 33, blockHeight = 9;

template <class T>
void printLine(string label, T data, int color, int baseColor, int& line, int depth, string ending = "") {
	gotoxy(depth * blockWitdh, line++);

	setConsoleColor(baseColor);
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
	setConsoleColor(baseColor);
	cout << "|";

	setConsoleColor(WHITE);
	cout << ending << "\n";
}

void printLineSeprator(int baseColor, int& line, int depth, bool linked = false) {
	gotoxy(depth * blockWitdh, line++);

	setConsoleColor(baseColor);
	if (linked)
		cout << "--------------V-------------\n";
	else
		cout << "----------------------------\n";
	setConsoleColor(WHITE);
}

void printCustomLine(int& line, int depth, string text) {
	gotoxy(depth * blockWitdh, line++);
	setConsoleColor(WHITE);
	cout << text;
}


Node::Node(char var, Node* link = NULL) : type(1), var(var), link(link) {}

Node::Node(Node* dlink, int exp, Node* link = NULL) : type(2), dlink(dlink), exp(exp), link(link) {}

Node::Node(float coef, int exp, Node* link = NULL) : type(3), coef(coef), exp(exp), link(link) {}


int Node::print(bool printAll = false, int line = 0, int depth = 0, int skipLine = 0) {
	if (this == NULL) return 0;

	int baseColor = WHITE;
	/*switch (type)
	{
	case 1:
		baseColor = GREEN;
		break;
	case 2:
		baseColor = LIGHTRED;
		break;
	case 3:
		baseColor = CYAN;
		break;
	}*/

	int count = 1;

	bool hasDlink = dlink != NULL;

	printLineSeprator(baseColor, line, depth);
	printLine("Address", this, BROWN, baseColor, line, depth, ((hasDlink) ? "   --" : ""));
	printLine("Type", type, WHITE, baseColor, line, depth, ((hasDlink) ? "  / " : ""));
	printLine("Dlink", dlink, BROWN, baseColor, line, depth, ((hasDlink) ? "--" : ""));
	printLine("Var", var, WHITE, baseColor, line, depth);
	printLine("Exp", exp, WHITE, baseColor, line, depth);
	printLine("Coef", coef, WHITE, baseColor, line, depth);
	printLine("Link", link, BROWN, baseColor, line, depth);
	printLineSeprator(baseColor, line, depth, link != NULL);

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

Node* Node::generateFromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n)
{
	return new Node('z', new Node(new Node('y', new Node(new Node('x', new Node(4, 1, new Node(3, 0))), 2, new Node(1, 1))), 2, new Node(new Node('y', new Node(new Node('x', new Node(-2, 1)), 1, new Node(new Node('x', new Node(-3, 1)), 0))), 1)));

	Node* head = new Node('x');

	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			char var = variables[j - 1];
			int exp = matrix[i][j];
			float coef = matrix[i][0];

			//if (j == n - 1) // last item
			//	head->addExpression(var, exp, coef); // coef on last element
			//else
			//	head->addExpression(var, exp);
		}
	}
	return head;
}

void Node::addExpression(char var, int exp, float coef = NULL)
{
	Node* p = this;
	Node* node = new Node(var);
	while (p)
	{
		if (p->type == 1 && p->var == var)
		{

		}
		p = p->link;
	}
}

bool Node::isEqual(Node* a, Node* b)
{
	// both null
	if (a == NULL && b == NULL) return true;

	// one of them null
	if ((a == NULL && b != NULL) ||
		(a != NULL && b == NULL)) return false;

	// neither null
	return
		a->type == b->type &&
		a->var == b->var &&
		a->exp == b->exp &&
		a->coef == b->coef;
}

Node* Node::sum(Node* a, Node* b)
{
	while (a || b)
	{
		if (Node::isEqual(a, b))
		{

		}
	}
}





// darft
/*
void List::readFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file)
	{
		cout << "Error opening file!" << endl;
		return;
	}

	int numVariables, numTerms;
	file >> numVariables >> numTerms;

	for (int i = 0; i < numTerms; i++)
	{
		int coef;
		file >> coef;

		Node* first = nullptr;
		Node* help_link = head;
		for (int j = 0; j < numVariables; j++)
		{
			int exp;
			file >> exp;
			string var = "x" + to_string(j + 1);
			if (help_link && help_link->getLink())
			{
				help_link = Find_Variable(exp, help_link);
			}
			if (help_link && help_link->getLink())
				continue;

			Node* node1 = new Node();
			Node* node2 = new Node();
			node1->setVariable(var);
			node1->setTag(1);
			node2->setExp(exp);
			node2->setTag(2);
			if (j == numVariables - 1)
			{
				node2->setCoef(coef);
				node2->setTag(3);
			}
			node1->setLink(node2);

			if (!first)
			{
				first = node1;
			}
			else
			{
				Node* temp = first;
				while (temp->getLink() || temp->getDlink())
					temp = (temp->getDlink()) ? temp->getDlink() : temp->getLink();

				temp->setDlink(node1);
			}
		}
		if (!head)
			head = first;
		else
			help_link->setLink(first->getLink());
	}
}
Node* List::Find_Variable(int exp, Node* link)
{
	Node* temp = link;
	while (temp)
	{
		if (temp->getTag() != 1 && temp->getExp() == exp)
			return (temp->getDlink()) ? temp->getDlink() : temp;

		if (temp->getLink())
			temp = temp->getLink();
		else
			break;
	}

	return temp;
}

*/


