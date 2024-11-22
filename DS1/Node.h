#pragma once
#include "variables.h"
#include "configs.h"

#define InputFilePath "in.txt"
#define HighContrastConfigName "high_contrast_print"
#define AnimationConfigName "animation_print"

const int blockWitdh = 33, blockHeight = 9;
int backgroundColor = BLACK; // can be changed

class Node
{
private:
	char var = NULL;
	float coef = NULL;
	int exp = NULL, type = NULL;
	Node* link = NULL;
	Node* dlink = NULL;
public:
	Node(char var, Node* link = NULL); // type 1
	Node(Node* dlink, int exp, Node* link = NULL); // type 2
	Node(float coef, int exp, Node* link = NULL); // type 3

	static Node* fromFile(string fileName = InputFilePath);
	static Node* fromString(string input);
	static Node* fromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n);
	static bool isEqual(Node* a, Node* b, bool recursive = false);
	static Node* sum(Node* a, Node* b);

	int print(bool printAll = false, int line = 0, int depth = 0, int skipLine = 0);
	Node* copy(bool recursive = false);
	void free(bool recursive = false);
	string toString(string result = "");
	int getDepth();
	bool includes(Node* a);
	void multiply(float num);
	float calculate(int lastVar = 0);
};

// helper functions

template <class T>
void printLine(string label, T data, int& line, int depth, string ending = "") {
	gotoxy(depth * blockWitdh, line++);

	if (getConfig(AnimationConfigName))
		Sleep(60);

	setConsoleColor(WHITE);
	cout << "|";

	setConsoleColor(WHITE, backgroundColor);
	cout << left << setw(10) << label;
	if constexpr (std::is_same<T, Node*>::value)
	{
		if (data == NULL)
		{
			setConsoleColor(LIGHTRED, backgroundColor);
			cout << left << setw(16) << "Null";
		}
		else {
			setConsoleColor(BROWN, backgroundColor);
			cout << left << setw(16) << data;
		}
	}
	else
	{
		if (data == NULL)
		{
			setConsoleColor(LIGHTRED, backgroundColor);
			cout << left << setw(16) << "Null";
		}
		else
		{
			setConsoleColor(WHITE, backgroundColor);
			cout << left << setw(16) << data;
		}
	}
	setConsoleColor(WHITE);
	cout << "|";

	setConsoleColor(WHITE);
	cout << ending << "\n";
}

void printLineSeprator(int& line, int depth, bool linked = false) {
	gotoxy(depth * blockWitdh, line++);

	if (getConfig(AnimationConfigName))
		Sleep(40);

	setConsoleColor(WHITE);
	if (linked)
		cout << "--------------V-------------\n";
	else
		cout << "----------------------------\n";
	setConsoleColor(WHITE);
}

void printCustomLine(int& line, int depth, string text) {
	gotoxy(depth * blockWitdh, line++);

	if (getConfig(AnimationConfigName))
		Sleep(20);

	setConsoleColor(WHITE);
	cout << text;
}

string float2string(float num) {
	ostringstream oss;
	oss << fixed << setprecision(4);
	oss << abs(num);
	string numStr = oss.str();
	numStr.erase(numStr.find_last_not_of('0') + 1, string::npos);
	if (numStr.back() == '.')
		numStr.pop_back();

	return numStr;
}

// constructor functions

Node::Node(char var, Node* link) : type(1), var(var), link(link) {}

Node::Node(Node* dlink, int exp, Node* link) : type(2), dlink(dlink), exp(exp), link(link) {}

Node::Node(float coef, int exp, Node* link) : type(3), coef(coef), exp(exp), link(link) {}

// static functions

Node* Node::fromFile(string fileName)
{
	float matrix[MaxFileLines][MaxFileLines] = { 0 };
	int i = 0, j = 0;

	string lines[MaxFileLines];
	int n = readFile(fileName, lines);

	string token;// helping string

	for (i = 0; i < n; i++)
	{
		// i + 1 to skip the first line
		stringstream ss(lines[i]);

		j = 0;
		while (getline(ss >> ws, token, ' '))
		{
			matrix[i][j++] = stof(token);
		}
	}

	return fromMatrix(matrix, i, j);
}

Node* Node::fromString(string input) {
	return NULL; // doesnt work
}

Node* Node::fromMatrix(float matrix[MaxFileLines][MaxFileLines], int m, int n)
{
	Node* head = NULL;

	for (int i = 0; i < m; i++) {
		Node* term = NULL;
		Node* p = NULL;
		float coef = matrix[i][0];

		if (coef == 0)
			continue;

		for (int j = 1; j < n; j++) {
			char var = variables[j - 1];
			int exp = matrix[i][j];

			if (!term)
				p = term = new Node(var, new Node(nullptr, exp));
			else
				p = p->dlink = new Node(var, new Node(nullptr, exp));

			p = p->link;
		}

		// useless for now
		if (!term)
			error("Polynomial syntax error!", "Only coef provided with zero exp variables", __FILE__, __LINE__);

		p->type = 3;
		p->coef = coef;

		// Add the term to the polynomial
		Node* temp = sum(head->copy(true), term);
		head->free(true);
		term->free(true);
		head = temp;
	}
	return head;
}

bool Node::isEqual(Node* a, Node* b, bool recursive)
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
		a->coef == b->coef &&
		(recursive ? isEqual(a->link, b->link, true) : true) &&
		(recursive ? isEqual(a->dlink, b->dlink, true) : true);
}

Node* Node::sum(Node* a, Node* b) {
	if (!a) return b->copy(true);
	if (!b) return a->copy(true);

	Node* result = nullptr;

	if (isEqual(a, b) && a->type != 3) {
		// Merge equal nodes
		result = a->copy();
		result->link = sum(a->link, b->link);
		result->dlink = sum(a->dlink, b->dlink);
	}
	else {
		if (a->type == 3 && b->type == 3 && a->exp == b->exp)
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
				result->dlink = a->dlink->copy(true);
			}
			else {
				result = b->copy();
				result->link = sum(a, b->link);
				result->dlink = b->dlink->copy(true);
			}
		}
		else {
			// Fallback for other types
			result = a->copy();
			result->link = sum(a->link, b);
			result->dlink = a->dlink->copy();
		}
	}

	return result;
}

// methods

int Node::print(bool printAll, int line, int depth, int skipLine) {
	if (this == NULL) return 0;

	if (getConfig(HighContrastConfigName))
		switch (type)
		{
		case 1:
			backgroundColor = RED;
			break;
		case 2:
			backgroundColor = LIGHTBLUE;
			break;
		case 3:
			backgroundColor = GREEN;
			break;
		}

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
	//cout << "\n";
	return count;
}

Node* Node::copy(bool recursive) {
	if (!this) return NULL;

	Node* node = new Node('x'); // Variable doesn't matter
	node->type = type;
	node->coef = coef;
	node->var = var;
	node->exp = exp;
	node->link = recursive ? link->copy(true) : NULL;
	node->dlink = recursive ? dlink->copy(true) : NULL;

	return node;
}

void Node::free(bool recursive) {
	if (!this) return;

	if (recursive) {
		if (link) {
			link->free(true);
			link = NULL;
		}
		if (dlink) {
			dlink->free(true);
			dlink = NULL;
		}
	}
	delete this;
}

string Node::toString(string result) {
	if (this == NULL)
		return "";

	string newResult = "";
	string expo = (exp <= 1 ? "" : "^" + to_string(exp));
	string coefs = (coef == 1 || coef == -1 ? "" : float2string(coef));
	string flag = (coef >= 0 ? " + " : " - ");

	switch (type)
	{
	case 1:
		newResult = result + var;
		return link->toString(newResult);
	case 2:
		if (exp == 0) // removing lastest var from string
			newResult = result.substr(0, result.size() - 1);
		else
			newResult = result + expo;

		return dlink->toString(newResult) + link->toString(result);
	case 3:
		if (exp == 0) // removing lastest var from string
			newResult = flag + coefs + result.substr(0, result.size() - 1);
		else
			newResult = flag + coefs + result + expo;

		return newResult + link->toString(result);
	}
}

int Node::getDepth()
{
	if (this == NULL)
		return -1;

	int count = 0;

	if (link)
		count = max(link->getDepth(), count);
	if (dlink)
		count = max(dlink->getDepth() + 1, count);

	return count;
}

bool Node::includes(Node* a) {
	if (a == NULL)
		return true;

	if (this == NULL)
		return false;

	bool coefo;
	switch (type) {
	case 1:
		if (isEqual(this, a))
			return (link ? link->includes(a->link) : a->link == NULL);

		break;
	case 2:
		if (isEqual(this, a))
			return (dlink ? dlink->includes(a->dlink) : a->dlink == NULL) &&
			(link ? link->includes(a->link) : a->link == NULL);

		break;
	case 3:
		//if (coef >= 0) // + +
		//	coefo = coef >= a->coef;
		//else
		//	coefo = abs(coef) >= abs(a->coef);

		// TODO

		//coefo = abs(coef) >= abs(a->coef);
		//if (a->type == 3 && exp == a->exp && coef >= a->coef)
		if (isEqual(this, a))
			return (link ? link->includes(a->link) : a->link == NULL);

		break;
	}

	// no direct match -> checking link for indirect matches
	return link->includes(a);
}

void Node::multiply(float num)
{
	if (this == NULL)
		return;

	if (type == 3)
		coef *= num;

	dlink->multiply(num);
	link->multiply(num);
}

float Node::calculate(int lastVar)
{
	if (this == NULL)
		return 0;

	switch (type)
	{
	case 1:
		return link->calculate(getVar(var));
	case 2:
		if (dlink)
			return pow(lastVar, exp) * dlink->calculate() + link->calculate(lastVar);

		return pow(lastVar, exp) + link->calculate(lastVar);
	case 3:
		return coef * pow(lastVar, exp) + link->calculate(lastVar);
	}
}



