#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "console.h"
#include "cookie.h"
#include "notification.h"
#include "logo.h"
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "Node.h"

using namespace std;

struct ConfirmBoxConfig {
	string title = "CONFIRM BOX";
	string body = "Are you sure you want to continue with your action?";
	string button1 = "BACK";
	string text1 = " Cancel";
	string spliter = "  |  ";
	string button2 = "ENTER";
	string text2 = " Continue";
	string footer = "You might not be able to undo!";
};

// TODO
// 1. live visualization of linked lists
// 2. optional input from file or from console
// 3. what is size_t as type
// 4. visualizer settings using cookies better to be implemented
// 5. head also needs to be freed as well as node in from matrix and from string
// 6. i wanted to write in golang not c++
// 7. coefs to string precision in settings
// 8. remove first sign to string prints
// 9. for negetive coefs includes fix bugs

namespace intro {
	void keyBinder(string key) {
		setConsoleColor(3599);
		cout << BLINKERSTART << key << BLINKEREND;
	}
	void printHelp(string key, string info, int color = YELLOW, string ending = "\n\n") {
		keyBinder(key);

		setConsoleColor(color);

		cout << " \t " << info << ending;
		setConsoleColor(WHITE);
	}
	template <class T>
	void _dataLine(string name, T value, int nameLen, int valueLen, string key = "") {
		setConsoleColor(LIGHTGREY);
		cout << left << setw(nameLen) << name;

		setConsoleColor(WHITE);
		cout << left << setw(valueLen) << value;

		cout << "";
		setConsoleColor(LIGHTRED);
		if (key != "")
			intro::keyBinder(key);
		else
			cout << "0";
		setConsoleColor(YELLOW);
		cout << " to change\n\n";
		setConsoleColor(WHITE);
	}
	
	void header(string page = "Home", string pageLabel = "Page") {
		clearConsole();

		/*while (!ensureConsoleSize())
		{
			string toShow = "Your window size doesn't match our requirements";
			int xPos = (getConsoleColumns() - toShow.length()) / 2;
			int yPos = (getConsoleRows()) / 2 - 2;
			gotoxy(xPos, yPos);
			cout << toShow;

			toShow = "Expand window little bit or zoom out";
			xPos = (getConsoleColumns() - toShow.length()) / 2;
			yPos = (getConsoleRows()) / 2 - 1;
			gotoxy(xPos, yPos);
			setConsoleColor(LIGHTCYAN);
			cout << toShow;
			setConsoleColor(WHITE);

			toShow = "Must be at least 130 X 32";
			xPos = (getConsoleColumns() - toShow.length()) / 2;
			yPos = (getConsoleRows()) / 2;
			gotoxy(xPos, yPos);
			cout << toShow;

			toShow = "Yours is " + to_string(getConsoleColumns()) + " X " + to_string(getConsoleRows());
			xPos = (getConsoleColumns() - toShow.length()) / 2;
			yPos = (getConsoleRows()) / 2 + 1;
			gotoxy(xPos, yPos);
			cout << "Yours is ";
			if (getConsoleColumns() >= 130)
				setConsoleColor(LIGHTGREEN);
			else
				setConsoleColor(LIGHTRED);
			cout << getConsoleColumns();

			setConsoleColor(WHITE);
			cout << " X ";

			if (getConsoleRows() >= 32)
				setConsoleColor(LIGHTGREEN);
			else
				setConsoleColor(LIGHTRED);
			cout << getConsoleRows();

			setConsoleColor(WHITE);
			Sleep(500);
			clearConsole();
		}*/

		setConsoleColor(CYAN);
		cout << "Polynomials";
		setConsoleColor(WHITE);
		cout << " | " << pageLabel << " -> " << page;
		showNotif();
	}
	void home() {
		header();
		
		printHelp("KEY 1", "Profiles!");
		printHelp("KEY 2", "Visualize!", DARKGREY);
		printHelp("KEY 3", "Print!", DARKGREY);
		printHelp("KEY 4", "Get Depth!", DARKGREY);
		printHelp("KEY 5", "Multiply by!", DARKGREY);

		printHelp("SPACE", "ADMIN PANEL!", LIGHTGREEN);
		printHelp("ESC", "EXIT!", LIGHTRED);
	}
}

namespace view {
	bool confirmBox(ConfirmBoxConfig config = ConfirmBoxConfig()) {
		clearConsole();
		int rows = getConsoleRows(), columns = getConsoleColumns();

		setConsoleColor(CYAN);
		gotoxy((columns - config.title.length()) / 2, rows / 2 - 4);
		cout << config.title;

		setConsoleColor(WHITE);
		gotoxy((columns - config.body.length()) / 2, rows / 2 - 2);
		cout << config.body;


		gotoxy((columns - (config.button1.length() + config.button2.length() + config.text1.length() + config.text2.length() + config.spliter.length())) / 2, rows / 2 - 0);
		setConsoleColor(3599);
		cout << BLINKERSTART << config.button1 << BLINKEREND;
		setConsoleColor(LIGHTRED);
		cout << config.text1;
		setConsoleColor(WHITE);
		cout << config.spliter;
		setConsoleColor(3599);
		cout << BLINKERSTART << config.button2 << BLINKEREND;
		setConsoleColor(LIGHTGREEN);
		cout << config.text2;

		setConsoleColor(DARKGREY);
		gotoxy((columns - config.footer.length()) / 2, rows / 2 + 2);
		cout << config.footer;

		while (true)
		{
			int cc = getKey();

			switch (cc)
			{
			case VK_RETURN:
				return true;
				break;

			case VK_BACK:
			case VK_ESCAPE:
				return false;
				break;
			}
		}
	}
	void home() {
		while (true)
		{
			intro::home();
			int cc = getKey();
			switch (cc)
			{
			case VK_ESCAPE:
				if (confirmBox())
					exit(0);
				else
					setNotif("warning", "Action canceled!");
				break;
			case VK_BACK:
				setNotif("warning", "Return back is unavailable!");
				break;
			case VK_KEY1:
				//signin();
				break;
			case VK_KEY2:
				//signout();
				break;
			case VK_KEY3:
				//profile();
				break;
			case VK_KEY4:
				//explore();
				break;
			default:
				setNotif("error", "Unknown Command!!!");
				break;
			}
		}
	}
}

int main()
{
	//logo::getAnimation();
	//view::home();

	int i;
	cin >> i;
	Node* tree = Node::fromFile();
	//Node* tree2 = Node::fromFile("in2.txt");

	//Node* tree = Node::fromString("10xyz");
	//tree->print(true);
	/*cout << tree->toString() << "\n\n";
	tree->multiply(2);
	cout << tree->toString();*/
	//consoleColorTest();
	//cout << tree->getDepth();
	//cout << (tree->includes(tree2) ? "TRUE" : "FALSE");
	cout << tree->calculate();
}

