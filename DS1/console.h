#pragma once
#include <Windows.h>
#include <conio.h>

// color codes
#define BLACK        0
#define BLUE         1
#define GREEN        2
#define CYAN         3
#define RED          4
#define MAGENTA      5
#define BROWN        6
#define LIGHTGREY    7
#define DARKGREY     8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define WHITE        15
#define BLINKERSTART "\033[5m"
#define BLINKEREND   "\033[0m"

#define VK_KEY0 0x30
#define VK_KEY1 0x31
#define VK_KEY2 0x32
#define VK_KEY3 0x33
#define VK_KEY4 0x34
#define VK_KEY5 0x35
#define VK_KEY6 0x36
#define VK_KEY7 0x37
#define VK_KEY8 0x38
#define VK_KEY9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

using namespace std;

int getConsoleRows() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int getConsoleColumns() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearConsole() {
	system("cls");
}

void setConsoleColor(int foreground, int background = BLACK) {
	/*if (foreground < 0 || foreground > 15 || background < 0 || background > 15)
		error("Invalid color code!", "Foreground and background must be in the range 0-15.", __FILE__, __LINE__);*/


	// Combine foreground and background
	int colorCode = (background << 4) | foreground;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}

void consoleColorTest(int n = 16, string text = "This example text") {
	for (int i = 0; i < n; i++)
	{
		setConsoleColor(i);
		cout << text << " " << i << "\n";
	}
}

bool ensureConsoleSize() {
	bool check1 = false, check2 = false;
	if (getConsoleRows() >= 32)
		check1 = true;
	if (getConsoleColumns() >= 130)
		check2 = true;
	return check1 && check2;
}

void error(string msg = "An error acquired!", string help = "No information provided", string file = "NOT PROVIDDED", int line = -1, bool end = true) {
	setConsoleColor(LIGHTRED);
	cout << msg << '\n';
	setConsoleColor(LIGHTGREY);
	cout << help << '\n';
	setConsoleColor(BROWN);
	cout << "Location: " << file << ":" << line << '\n';
	setConsoleColor(WHITE);

	if (end)
		exit(-1);
}

int getKey() {
	while (true)
	{
		if (GetAsyncKeyState(VK_KEY0) || GetAsyncKeyState(VK_NUMPAD0))
		{
			while (GetAsyncKeyState(VK_KEY0) || GetAsyncKeyState(VK_NUMPAD0));
			return VK_KEY0;
		}
		if (GetAsyncKeyState(VK_KEY1) || GetAsyncKeyState(VK_NUMPAD1))
		{
			while (GetAsyncKeyState(VK_KEY1) || GetAsyncKeyState(VK_NUMPAD1));
			return VK_KEY1;
		}
		if (GetAsyncKeyState(VK_KEY2) || GetAsyncKeyState(VK_NUMPAD2))
		{
			while (GetAsyncKeyState(VK_KEY2) || GetAsyncKeyState(VK_NUMPAD2));
			return VK_KEY2;
		}
		if (GetAsyncKeyState(VK_KEY3) || GetAsyncKeyState(VK_NUMPAD3))
		{
			while (GetAsyncKeyState(VK_KEY3) || GetAsyncKeyState(VK_NUMPAD3));
			return VK_KEY3;
		}
		if (GetAsyncKeyState(VK_KEY4) || GetAsyncKeyState(VK_NUMPAD4))
		{
			while (GetAsyncKeyState(VK_KEY4) || GetAsyncKeyState(VK_NUMPAD4));
			return VK_KEY4;
		}
		if (GetAsyncKeyState(VK_KEY5) || GetAsyncKeyState(VK_NUMPAD5))
		{
			while (GetAsyncKeyState(VK_KEY5) || GetAsyncKeyState(VK_NUMPAD5));
			return VK_KEY5;
		}
		if (GetAsyncKeyState(VK_KEY6) || GetAsyncKeyState(VK_NUMPAD6))
		{
			while (GetAsyncKeyState(VK_KEY6) || GetAsyncKeyState(VK_NUMPAD6));
			return VK_KEY6;
		}
		if (GetAsyncKeyState(VK_KEY7) || GetAsyncKeyState(VK_NUMPAD7))
		{
			while (GetAsyncKeyState(VK_KEY7) || GetAsyncKeyState(VK_NUMPAD7));
			return VK_KEY7;
		}
		if (GetAsyncKeyState(VK_KEY8) || GetAsyncKeyState(VK_NUMPAD8))
		{
			while (GetAsyncKeyState(VK_KEY8) || GetAsyncKeyState(VK_NUMPAD8));
			return VK_KEY8;
		}
		if (GetAsyncKeyState(VK_KEY9) || GetAsyncKeyState(VK_NUMPAD9))
		{
			while (GetAsyncKeyState(VK_KEY9) || GetAsyncKeyState(VK_NUMPAD9));
			return VK_KEY9;
		}


		if (GetAsyncKeyState(VK_SPACE))
		{
			while (GetAsyncKeyState(VK_SPACE));
			return VK_SPACE;
		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			while (GetAsyncKeyState(VK_ESCAPE));
			return VK_ESCAPE;
		}
		if (GetAsyncKeyState(VK_DELETE))
		{
			while (GetAsyncKeyState(VK_DELETE));
			return VK_DELETE;
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			while (GetAsyncKeyState(VK_RETURN));
			return VK_RETURN;
		}
		if (GetAsyncKeyState(VK_BACK))
		{
			while (GetAsyncKeyState(VK_BACK));
			return VK_BACK;
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			while (GetAsyncKeyState(VK_LEFT));
			return VK_LEFT;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			while (GetAsyncKeyState(VK_UP));
			return VK_UP;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			while (GetAsyncKeyState(VK_RIGHT));
			return VK_RIGHT;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			while (GetAsyncKeyState(VK_DOWN));
			return VK_DOWN;
		}

		//ignorance
		if (GetAsyncKeyState(VK_A))
		{
			while (GetAsyncKeyState(VK_A));
		}
		if (GetAsyncKeyState(VK_B))
		{
			while (GetAsyncKeyState(VK_B));
		}
		if (GetAsyncKeyState(VK_C))
		{
			while (GetAsyncKeyState(VK_C));
		}
		if (GetAsyncKeyState(VK_D))
		{
			while (GetAsyncKeyState(VK_D));
		}
		if (GetAsyncKeyState(VK_E))
		{
			while (GetAsyncKeyState(VK_E));
		}
		if (GetAsyncKeyState(VK_F))
		{
			while (GetAsyncKeyState(VK_F));
		}
		if (GetAsyncKeyState(VK_G))
		{
			while (GetAsyncKeyState(VK_G));
		}
		if (GetAsyncKeyState(VK_H))
		{
			while (GetAsyncKeyState(VK_H));
		}
		if (GetAsyncKeyState(VK_I))
		{
			while (GetAsyncKeyState(VK_I));
		}
		if (GetAsyncKeyState(VK_J))
		{
			while (GetAsyncKeyState(VK_J));
		}
		if (GetAsyncKeyState(VK_K))
		{
			while (GetAsyncKeyState(VK_K));
		}
		if (GetAsyncKeyState(VK_L))
		{
			while (GetAsyncKeyState(VK_L));
		}
		if (GetAsyncKeyState(VK_M))
		{
			while (GetAsyncKeyState(VK_M));
		}
		if (GetAsyncKeyState(VK_N))
		{
			while (GetAsyncKeyState(VK_N));
		}
		if (GetAsyncKeyState(VK_O))
		{
			while (GetAsyncKeyState(VK_O));
		}
		if (GetAsyncKeyState(VK_P))
		{
			while (GetAsyncKeyState(VK_P));
		}
		if (GetAsyncKeyState(VK_Q))
		{
			while (GetAsyncKeyState(VK_Q));
		}
		if (GetAsyncKeyState(VK_R))
		{
			while (GetAsyncKeyState(VK_R));
		}
		if (GetAsyncKeyState(VK_S))
		{
			while (GetAsyncKeyState(VK_S));
		}
		if (GetAsyncKeyState(VK_T))
		{
			while (GetAsyncKeyState(VK_T));
		}
		if (GetAsyncKeyState(VK_U))
		{
			while (GetAsyncKeyState(VK_U));
		}
		if (GetAsyncKeyState(VK_V))
		{
			while (GetAsyncKeyState(VK_V));
		}
		if (GetAsyncKeyState(VK_W))
		{
			while (GetAsyncKeyState(VK_W));
		}
		if (GetAsyncKeyState(VK_X))
		{
			while (GetAsyncKeyState(VK_X));
		}
		if (GetAsyncKeyState(VK_Y))
		{
			while (GetAsyncKeyState(VK_Y));
		}
		if (GetAsyncKeyState(VK_Z))
		{
			while (GetAsyncKeyState(VK_Z));
		}
	}
}

void _handleNumKeyPress(string& output, int key1, int key2, char letter, bool preview) {
	while (GetAsyncKeyState(key1) || GetAsyncKeyState(key2));
	output += letter;
	if (preview)
		cout << letter;
	else
		cout << '*';
}

void _handleAlphaKeyPress(string& output, int key, char letter, bool preview, bool caps = false) {


	if (caps)
		letter = toupper(letter);

	while (GetAsyncKeyState(key));
	output += letter;
	if (preview)
		cout << letter;
	else
		cout << '*';
}

string getString(bool preview = true) {
	string output = "";

	bool caps = false;
	//if ((GetAsyncKeyState(VK_CAPITAL) & 0x0001) == 0) // caps lock on
	//    caps = true;
	//if (GetAsyncKeyState(VK_SHIFT)) // shift is being held
	//    caps = !caps;

	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			while (GetAsyncKeyState(VK_RETURN));
			cout << '\n';
			return output;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			while (GetAsyncKeyState(VK_SPACE));
			output += " ";
		}
		if (GetAsyncKeyState(VK_BACK))
		{
			while (GetAsyncKeyState(VK_BACK));
			if (output.length() > 0)
			{
				output = output.substr(0, output.length() - 1);
				cout << '\b' << ' ' << '\b';
			}
		}

		// num
		if (GetAsyncKeyState(VK_KEY1) || GetAsyncKeyState(VK_NUMPAD1))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY1, VK_NUMPAD1, '!', preview);
			else
				_handleNumKeyPress(output, VK_KEY1, VK_NUMPAD1, '1', preview);
		}
		if (GetAsyncKeyState(VK_KEY2) || GetAsyncKeyState(VK_NUMPAD2))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY2, VK_NUMPAD2, '@', preview);
			else
				_handleNumKeyPress(output, VK_KEY2, VK_NUMPAD2, '2', preview);
		}
		if (GetAsyncKeyState(VK_KEY3) || GetAsyncKeyState(VK_NUMPAD3))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY3, VK_NUMPAD3, '#', preview);
			else
				_handleNumKeyPress(output, VK_KEY3, VK_NUMPAD3, '3', preview);
		}
		if (GetAsyncKeyState(VK_KEY4) || GetAsyncKeyState(VK_NUMPAD4))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY4, VK_NUMPAD4, '$', preview);
			else
				_handleNumKeyPress(output, VK_KEY4, VK_NUMPAD4, '4', preview);
		}
		if (GetAsyncKeyState(VK_KEY5) || GetAsyncKeyState(VK_NUMPAD5))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY5, VK_NUMPAD5, '%', preview);
			else
				_handleNumKeyPress(output, VK_KEY5, VK_NUMPAD5, '5', preview);
		}
		if (GetAsyncKeyState(VK_KEY6) || GetAsyncKeyState(VK_NUMPAD6))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY6, VK_NUMPAD6, '^', preview);
			else
				_handleNumKeyPress(output, VK_KEY6, VK_NUMPAD6, '6', preview);
		}
		if (GetAsyncKeyState(VK_KEY7) || GetAsyncKeyState(VK_NUMPAD7))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY7, VK_NUMPAD7, '&', preview);
			else
				_handleNumKeyPress(output, VK_KEY7, VK_NUMPAD7, '7', preview);
		}
		if (GetAsyncKeyState(VK_KEY8) || GetAsyncKeyState(VK_NUMPAD8))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY8, VK_NUMPAD8, '*', preview);
			else
				_handleNumKeyPress(output, VK_KEY8, VK_NUMPAD8, '8', preview);
		}
		if (GetAsyncKeyState(VK_KEY9) || GetAsyncKeyState(VK_NUMPAD9))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY9, VK_NUMPAD9, '(', preview);
			else
				_handleNumKeyPress(output, VK_KEY9, VK_NUMPAD9, '9', preview);
		}
		if (GetAsyncKeyState(VK_KEY0) || GetAsyncKeyState(VK_NUMPAD0))
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleNumKeyPress(output, VK_KEY0, VK_NUMPAD0, ')', preview);
			else
				_handleNumKeyPress(output, VK_KEY0, VK_NUMPAD0, '0', preview);
		}

		// Alpha
		if (GetAsyncKeyState(VK_A))
		{
			_handleAlphaKeyPress(output, VK_A, 'a', preview, caps);
		}
		if (GetAsyncKeyState(VK_B))
		{
			_handleAlphaKeyPress(output, VK_B, 'b', preview, caps);
		}
		if (GetAsyncKeyState(VK_C))
		{
			_handleAlphaKeyPress(output, VK_C, 'c', preview, caps);
		}
		if (GetAsyncKeyState(VK_D))
		{
			_handleAlphaKeyPress(output, VK_D, 'd', preview, caps);
		}
		if (GetAsyncKeyState(VK_E))
		{
			_handleAlphaKeyPress(output, VK_E, 'e', preview, caps);
		}
		if (GetAsyncKeyState(VK_F))
		{
			_handleAlphaKeyPress(output, VK_F, 'f', preview, caps);
		}
		if (GetAsyncKeyState(VK_G))
		{
			_handleAlphaKeyPress(output, VK_G, 'g', preview, caps);
		}
		if (GetAsyncKeyState(VK_H))
		{
			_handleAlphaKeyPress(output, VK_H, 'h', preview, caps);
		}
		if (GetAsyncKeyState(VK_I))
		{
			_handleAlphaKeyPress(output, VK_I, 'i', preview, caps);
		}
		if (GetAsyncKeyState(VK_J))
		{
			_handleAlphaKeyPress(output, VK_J, 'j', preview, caps);
		}
		if (GetAsyncKeyState(VK_K))
		{
			_handleAlphaKeyPress(output, VK_K, 'k', preview, caps);
		}
		if (GetAsyncKeyState(VK_L))
		{
			_handleAlphaKeyPress(output, VK_L, 'l', preview, caps);
		}
		if (GetAsyncKeyState(VK_M))
		{
			_handleAlphaKeyPress(output, VK_M, 'm', preview, caps);
		}
		if (GetAsyncKeyState(VK_N))
		{
			_handleAlphaKeyPress(output, VK_N, 'n', preview, caps);
		}
		if (GetAsyncKeyState(VK_O))
		{
			_handleAlphaKeyPress(output, VK_O, 'o', preview, caps);
		}
		if (GetAsyncKeyState(VK_P))
		{
			_handleAlphaKeyPress(output, VK_P, 'p', preview, caps);
		}
		if (GetAsyncKeyState(VK_Q))
		{
			_handleAlphaKeyPress(output, VK_Q, 'q', preview, caps);
		}
		if (GetAsyncKeyState(VK_R))
		{
			_handleAlphaKeyPress(output, VK_R, 'r', preview, caps);
		}
		if (GetAsyncKeyState(VK_S))
		{
			_handleAlphaKeyPress(output, VK_S, 's', preview, caps);
		}
		if (GetAsyncKeyState(VK_T))
		{
			_handleAlphaKeyPress(output, VK_T, 't', preview, caps);
		}
		if (GetAsyncKeyState(VK_U))
		{
			_handleAlphaKeyPress(output, VK_U, 'u', preview), caps;
		}
		if (GetAsyncKeyState(VK_V))
		{
			_handleAlphaKeyPress(output, VK_V, 'v', preview), caps;
		}
		if (GetAsyncKeyState(VK_W))
		{
			_handleAlphaKeyPress(output, VK_W, 'w', preview), caps;
		}
		if (GetAsyncKeyState(VK_X))
		{
			_handleAlphaKeyPress(output, VK_X, 'x', preview), caps;
		}
		if (GetAsyncKeyState(VK_Y))
		{
			_handleAlphaKeyPress(output, VK_Y, 'y', preview), caps;
		}
		if (GetAsyncKeyState(VK_Z))
		{
			_handleAlphaKeyPress(output, VK_Z, 'z', preview), caps;
		}


		// Special ones
		if (GetAsyncKeyState(VK_OEM_1)) // ;:
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_1, ':', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_1, ';', preview);
		}
		if (GetAsyncKeyState(VK_OEM_2)) // /?
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_2, '?', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_2, '/', preview);
		}
		if (GetAsyncKeyState(VK_OEM_3)) // `~
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_3, '~', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_3, '`', preview);
		}
		if (GetAsyncKeyState(VK_OEM_4)) // [{
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_4, '{', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_4, '[', preview);
		}
		if (GetAsyncKeyState(VK_OEM_5)) // \|
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_5, '|', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_5, '\\', preview);
		}
		if (GetAsyncKeyState(VK_OEM_6)) // \|
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_6, '}', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_6, ']', preview);
		}
		if (GetAsyncKeyState(VK_OEM_7)) // '"
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_7, '"', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_7, '\'', preview);
		}

		if (GetAsyncKeyState(VK_OEM_COMMA)) // ,<
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_COMMA, '<', preview);
			/*else      COMMA IS BLOCKED
				_handleAlphaKeyPress(output, VK_OEM_COMMA, ',', preview);*/
		}
		if (GetAsyncKeyState(VK_OEM_MINUS)) // -_
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_MINUS, '_', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_MINUS, '-', preview);
		}
		if (GetAsyncKeyState(VK_OEM_PLUS)) // =+
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_PLUS, '+', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_PLUS, '=', preview);
		}
		if (GetAsyncKeyState(VK_OEM_PERIOD)) // .>
		{
			if (GetAsyncKeyState(VK_SHIFT))
				_handleAlphaKeyPress(output, VK_OEM_PERIOD, '>', preview);
			else
				_handleAlphaKeyPress(output, VK_OEM_PERIOD, '.', preview);
		}


		// ignorance
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			while (GetAsyncKeyState(VK_ESCAPE));
		}
		if (GetAsyncKeyState(VK_DELETE))
		{
			while (GetAsyncKeyState(VK_DELETE));
		}
	}
}

// not checked with negetive numbers probably not working with that
bool is_number(const std::string& s)
{
	if (s == "")
		return false;

	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}