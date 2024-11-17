#pragma once

#include <iostream>
using namespace std;

#define InputFilePath "in.txt"

char variables[] = {
	 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i', 'j',
	 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
};
int varCount = 26;

int indexOfVariable(char var) {
	for (int i = 0; i < varCount; i++)
		if (var == variables[i])
			return i;

	return -1;
}

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
	static Node* fromFile(string fileName);
	static Node* fromString(string input);
	static Node* fromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n);
	static bool isEqual(Node* a, Node* b);
	static Node* sum(Node* a, Node* b);
	Node* copy();
	void free(bool recursive);
};

int blockWitdh = 33, blockHeight = 9;
int blockBorderColor = WHITE;

template <class T>
void printLine(string label, T data, int& line, int depth, string ending = "") {
	gotoxy(depth * blockWitdh, line++);

	setConsoleColor(blockBorderColor);
	cout << "|";

	setConsoleColor(WHITE);
	cout << left << setw(10) << label;
	if constexpr (std::is_same<T, Node*>::value)
	{
		if (data == NULL)
		{
			setConsoleColor(LIGHTRED);
			cout << left << setw(16) << "Null";
		}
		else {
			setConsoleColor(BROWN);
			cout << left << setw(16) << data;
		}
	}
	else
	{
		if (data == NULL)
		{
			setConsoleColor(LIGHTRED);
			cout << left << setw(16) << "Null";
		}
		else
		{
			setConsoleColor(WHITE);
			cout << left << setw(16) << data;
		}
	}
	setConsoleColor(blockBorderColor);
	cout << "|";

	setConsoleColor(WHITE);
	cout << ending << "\n";
}

void printLineSeprator(int& line, int depth, bool linked = false) {
	gotoxy(depth * blockWitdh, line++);

	setConsoleColor(blockBorderColor);
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


int Node::print(bool printAll = true, int line = 0, int depth = 0, int skipLine = 0) {
	if (this == NULL) return 0;

	/*switch (type)
	{
	case 1:
		blockBorderColor = GREEN;
		break;
	case 2:
		blockBorderColor = LIGHTRED;
		break;
	case 3:
		blockBorderColor = CYAN;
		break;
	}*/

	int count = 1;

	bool hasDlink = dlink != NULL;

	printLineSeprator(line, depth);
	printLine("Address", this, line, depth, ((hasDlink) ? "   --" : ""));
	printLine("Type", type, line, depth, ((hasDlink) ? "  / " : ""));
	printLine("Dlink", dlink, line, depth, ((hasDlink) ? "--" : ""));
	printLine("Var", var, line, depth);
	printLine("Exp", exp, line, depth);
	printLine("Coef", coef, line, depth);
	printLine("Link", link, line, depth);
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

Node* Node::fromFile(string fileName = InputFilePath)
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

	return fromMatrix(matrix, i, j);
}

Node* Node::fromString(string input) {
	stringstream ss(input);
	string token;
	Node* head = nullptr;

	while (getline(ss, token, '+')) {
		float coef = 1.0;
		int exp = 0;
		char var = '\0';

		// Find the variable in the token
		int varPos = -1;
		for (int i = 0; i < varCount; ++i) {
			if (token.find(variables[i]) != string::npos) {
				varPos = i;
				var = variables[i];
				break;
			}
		}

		if (varPos != -1) { // Variable found
			// Parse coefficient
			string coefPart = token.substr(0, token.find(var));
			if (!coefPart.empty()) {
				coef = stof(coefPart);
			}

			// Parse exponent
			int expPos = token.find('^');
			if (expPos != -1) {
				exp = stoi(token.substr(expPos + 1));
			}
			else {
				exp = 1; // Assume exponent is 1 if not provided
			}
		}
		else {
			// No variable; parse as constant
			coef = stof(token);
		}

		// Create the term node
		Node* term = new Node(coef, exp, nullptr);
		if (var != '\0') {
			term = new Node(var, term);
		}

		// Add to polynomial
		head = sum(head, term);
	}
	return head;
}


Node* Node::fromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n)
{
	// test
	//return new Node('z', new Node(new Node('y', new Node(new Node('x', new Node(4, 1, new Node(3, 0))), 2, new Node(1, 1))), 2, new Node(new Node('y', new Node(new Node('x', new Node(-2, 1)), 1, new Node(new Node('x', new Node(-3, 1)), 0))), 1)));

	Node* head = NULL;

	for (int i = 0; i < m; i++) {
		Node* node = NULL;
		Node* p = NULL;
		float coef = matrix[i][0];
		for (int j = 1; j < n; j++) {
			char var = variables[j - 1];
			int exp = matrix[i][j];

			if (!node) {
				p = node = new Node(var, new Node(nullptr, exp));
			}
			else {
				p = p->dlink = new Node(var, new Node(nullptr, exp));
			}

			p = p->link;
		}

		if (!node) {
			error("Polynomial syntax error!", "Only coef provided with zero exp variables", __FILE__, __LINE__);
			continue;
		}

		p->type = 3;
		p->coef = coef;

		// Add the term to the polynomial
		head = sum(head, node);
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

Node* Node::sum(Node* a, Node* b) {
	if (!a) return b;
	if (!b) return a;

	Node* result = nullptr;

	if (isEqual(a, b)) {
		// Merge equal nodes
		result = a->copy();
		result->link = sum(a->link, b->link);
		result->dlink = sum(a->dlink, b->dlink);
	}
	else {
		if (a->type == 3 && b->type == 3)
		{
			// adding coefs togheder
			result = a->copy();
			result->coef += b->coef;
			result->link = sum(a->link, b->link);
		}
		else if (a->type == 2 && b->type == 2) {
			// Sort by exponent
			if (a->exp < b->exp) {
				result = a->copy();
				result->link = sum(a->link, b);
			}
			else {
				result = b->copy();
				result->link = sum(a, b->link);
			}
		}
		else {
			// Fallback for other types
			result = a->copy();
			result->link = sum(a->link, b);
		}
	}

	return result;
}

Node* Node::copy() {
	Node* node = new Node('x'); // Variable doesn't matter
	node->type = type;
	node->coef = coef;
	node->var = var;
	node->exp = exp;
	node->link = link ? link->copy() : nullptr;
	node->dlink = dlink ? dlink->copy() : nullptr;
	return node;
}

void Node::free(bool recursive) {
	if (!this) return;

	if (recursive) {
		if (link) {
			link->free(true);
			delete link;
			link = nullptr;
		}
		if (dlink) {
			dlink->free(true);
			delete dlink;
			dlink = nullptr;
		}
	}

	delete this;
}




