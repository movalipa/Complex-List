#pragma once

#include <iostream>
using namespace std;

#define InputFilePath "in.txt"

char variables[] = {
	 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm',
	 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w','x', 'y', 'z',
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
	static Node* FromFile(string fileName);
	static Node* FromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n);
	static bool isEqual(Node* a, Node* b);
	static Node* sum(Node* a, Node* b);
	Node* copy();
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

Node* Node::FromFile(string fileName = InputFilePath)
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

	return FromMatrix(matrix, i, j);
}

Node* Node::FromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n)
{
	//return new Node('z', new Node(new Node('y', new Node(new Node('x', new Node(4, 1, new Node(3, 0))), 2, new Node(1, 1))), 2, new Node(new Node('y', new Node(new Node('x', new Node(-2, 1)), 1, new Node(new Node('x', new Node(-3, 1)), 0))), 1)));

	Node* head = NULL;

	for (int i = 0; i < m; i++)
	{
		Node* node = NULL;
		Node* p = NULL;
		float coef = matrix[i][0];
		for (int j = 1; j < n; j++)
		{
			char var = variables[j - 1];
			int exp = matrix[i][j];

			if (exp == 0) continue;

			if (node == NULL)
				p = node = new Node(var, new Node((Node*)NULL, exp));
			else
				p = p->dlink = new Node(var, new Node((Node*)NULL, exp));

			p = p->link;
		}
		if (p == NULL)
			error("Polynomial syntax error!", "Only coef provided with zero exp variables", __FILE__, __LINE__);

		p->type = 3;
		p->coef = coef;

		head = sum(head, node);
		//head = node;
	}
	return head;
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
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	Node* node = NULL;

	if (isEqual(a, b))
	{
		node = a->copy(); // or b, they are same
		node->link = sum(a->link, b->link);
		node->dlink = sum(a->dlink, b->dlink);
	}
	else
	{
		if (a->type == 2 && b->type == 2)
		{
			Node* low = ((a->exp < b->exp) ? a : b);
			Node* high = ((a->exp > b->exp) ? a : b);

			node->link = 

		}
	}

	return node;
}

Node* Node::copy()
{
	Node* node = new Node('x');// var not important
	node->type = type;
	node->coef = coef;
	node->var = var;
	node->exp = exp;

	return node;
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


