#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"

#define LogoWidth 50

using namespace std;

// TODO
// 1. make use if cursor at char in logo

//char cursorCharRead()
//{
//	char buf[BUFSIZ];
//	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
//	COORD pos = csbiInfo.dwCursorPosition; //set pos to current cursor location
//	TCHAR strFromConsole[1];    //need space to only one char
//	DWORD dwChars;
//	ReadConsoleOutputCharacter(
//		hConsole,
//		strFromConsole, // Buffer where store symbols
//		1, // Read 1 char to strFormConsole
//		pos, // Read from current cursor position
//		&dwChars); // How many symbols stored
//	char c = strFromConsole[0];
//	return c;
//}
namespace logo {
	const char* X =
		"                                                  \n"
		"                                                  \n"
		"                                                  \n"
		"=@@@@@@@@@@@@@@@=                     +@@@@@@%:   \n"
		" .#@@@@@@@@@@@@@@#.                 -@@@@@@@=     \n"
		"   =@@@@@+...:%@@@@=              :%@@@@@@+       \n"
		"    .#@@@@#.   +@@@@#.          .#@@@@@@#.        \n"
		"      -@@@@@=   :%@@@@=        +@@@@@@%:          \n"
		"        *@@@@#.   +@@@@#.    =@@@@@@@=            \n"
		"         -@@@@@=   :%@@@@= -%@@@@@@+              \n"
		"           *@@@@%.   +@@@@@@@@@@@*.               \n"
		"            -%@@@@+ L .%@@@@@@@%:                 \n"
		"              *@@@@%: O =@@@@@+                   \n"
		"               :%@@@@+ A .%@@@@+                  \n"
		"                 +@@@@%: D =@@@@%:                \n"
		"                  #@@@@@* I .#@@@@+               \n"
		"                =@@@@@@@@%: N =@@@@%:             \n"
		"              :%@@@@@@%@@@@* G .#@@@@+            \n"
		"            .#@@@@@@#. =@@@@@-   =@@@@%:          \n"
		"           +@@@@@@%:    .#@@@@*   .#@@@@+         \n"
		"         =@@@@@@@=        =@@@@@-   =@@@@%:       \n"
		"       :%@@@@@@+           .#@@@@#.  .#@@@@*      \n"
		"     .*@@@@@@#.              -@@@@@=   =@@@@%:    \n"
		"    +@@@@@@%:                  *@@@@#***#@@@@@*   \n"
		"  -@@@@@@@=                     -@@@@@@@@@@@@@@%: \n"
		"                                                  \n"
		"                                                  \n";
	const char* last =
		"                   D O N E                        \n";

	void getLogo(const char* logo = X, int color = DARKGREY) {
		stringstream ss(X);
		string token;
		int num = (getConsoleColumns() - LogoWidth) / 2;
		int i = 0;
		gotoxy(num, i);
		i++;
		setConsoleColor(color);
		while (getline(ss, token, '\n'))
		{
			cout << token << '\n';
			Sleep(25);
			/*if (i % 6 == 0)
			{
				Sleep(60);
			}
			if (i % 10 == 0)
			{
				Sleep(80);
			}*/
			gotoxy(num, i);
			i++;
		}
		/*stringstream ss2(X);
		i = 0;
		setConsoleColor(WHITE);
		while (getline(ss2, token, '\n'))
		{
			gotoxy(num, i);
			cout << token << '\n';
			i++;
		}*/
	}
	void getAnimation() {
		getLogo(X, YELLOW);
		getLogo(X, LIGHTRED);
		getLogo(X, LIGHTCYAN);
		cout << last;
		getLogo(X, BLACK);
		//Sleep(400);
	}
}