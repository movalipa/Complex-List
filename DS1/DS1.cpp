#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "console.h"
#include "cookie.h"
#include "notification.h"
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "configs.h"
#include "profiles.h"

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
// 10. default profile imports
// 11. export svaing profiles as cookie or file

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

	void renderProfiles(int& page, int limit = 5) {
		int n = profiles_count;

		setConsoleColor(LIGHTGREY);
		cout << left << setw(5) << "ID";
		cout << left << setw(22) << "Name";
		cout << left << setw(20) << "Expression";
		setConsoleColor(WHITE);
		cout << "\n";

		if (page <= 0)
			page = 1;
		page = min(ceil((float)n / limit), page);
		int start = ((page - 1) * limit >= 0) ? (page - 1) * limit : 0;
		int end = min(start + limit, n);
		for (int i = start; i < end; i++)
		{
			string strEq = available_profiles[i].data->toString();
			setConsoleColor(BROWN);
			cout << left << setw(5) << "#" + to_string(i + 1);
			setConsoleColor(YELLOW);
			cout << left << setw(22) << available_profiles[i].name.substr(0, 18);
			cout << left << setw(20) << (strEq == "" ? "0" : strEq.substr(1));

			setConsoleColor(WHITE);
			cout << "\n";
		}
		int totalPageCount = ceil((float)n / limit);
		setConsoleColor(WHITE);
		if (totalPageCount == 0)// no data at all
			setConsoleColor(LIGHTRED);

		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << "\n";
		cout << "                                                                    Page " << page << " of " << totalPageCount << "\n\n";
		setConsoleColor(WHITE);
	}
	void renderVariables(int& page, int limit = 6) {
		int n = MAX_VARIABLES;

		setConsoleColor(LIGHTGREY);
		cout << left << setw(5) << "Var";
		cout << left << setw(5) << "";
		cout << left << setw(10) << "Value";
		setConsoleColor(WHITE);
		cout << "\n";

		if (page <= 0)
			page = 1;
		page = min(ceil((float)n / limit), page);
		int start = ((page - 1) * limit >= 0) ? (page - 1) * limit : 0;
		int end = min(start + limit, n);
		for (int i = start; i < end; i++)
		{
			setConsoleColor(BROWN);
			cout << left << setw(1) << " ";
			cout << left << setw(4) << ::variables[i];
			setConsoleColor(DARKGREY);
			cout << left << setw(7) << "-->";

			int varValue = getVar(::variables[i]);
			if (varValue == 0)
				setConsoleColor(LIGHTRED);
			else
				setConsoleColor(YELLOW);
			cout << left << setw(10) << varValue;

			setConsoleColor(WHITE);
			cout << "\n";
		}
		int totalPageCount = ceil((float)n / limit);
		setConsoleColor(WHITE);
		if (totalPageCount == 0)// no data at all
			setConsoleColor(LIGHTRED);

		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << "\n";
		cout << "                                                                    Page " << page << " of " << totalPageCount << "\n\n";
		setConsoleColor(WHITE);
	}
	void renderSettings(int& page, int limit = 6) {
		int n = MAX_CONFIGS;

		setConsoleColor(LIGHTGREY);
		cout << left << setw(5) << "ID";
		cout << left << setw(30) << "Config";
		cout << left << setw(10) << "Status";
		setConsoleColor(WHITE);
		cout << "\n";

		if (page <= 0)
			page = 1;
		page = min(ceil((float)n / limit), page);
		int start = ((page - 1) * limit >= 0) ? (page - 1) * limit : 0;
		int end = min(start + limit, n);
		for (int i = start; i < end; i++)
		{
			setConsoleColor(BROWN);
			cout << left << setw(5) << "#" + to_string(i + 1);
			setConsoleColor(YELLOW);
			cout << left << setw(30) << available_configs[i];

			bool value = getConfig(available_configs[i]);
			if (value)
				setConsoleColor(GREEN);
			else
				setConsoleColor(LIGHTRED);
			cout << left << setw(10) << (value ? "ON" : "OFF");

			setConsoleColor(WHITE);
			cout << "\n";
		}
		int totalPageCount = ceil((float)n / limit);
		setConsoleColor(WHITE);
		if (totalPageCount == 0)// no data at all
			setConsoleColor(LIGHTRED);

		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << "\n";
		cout << "                                                                    Page " << page << " of " << totalPageCount << "\n\n";
		setConsoleColor(WHITE);
	}

	void sizePrompt(int rows = 32, int columns = 130) {
		clearConsole();
		while (!ensureConsoleSize(rows, columns))
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

			toShow = "Must be at least " + to_string(columns) + " X " + to_string(rows);
			xPos = (getConsoleColumns() - toShow.length()) / 2;
			yPos = (getConsoleRows()) / 2;
			gotoxy(xPos, yPos);
			cout << toShow;

			toShow = "Yours is " + to_string(getConsoleColumns()) + " X " + to_string(getConsoleRows());
			xPos = (getConsoleColumns() - toShow.length()) / 2;
			yPos = (getConsoleRows()) / 2 + 1;
			gotoxy(xPos, yPos);
			cout << "Yours is ";
			if (getConsoleColumns() >= columns)
				setConsoleColor(LIGHTGREEN);
			else
				setConsoleColor(LIGHTRED);
			cout << getConsoleColumns();

			setConsoleColor(WHITE);
			cout << " X ";

			if (getConsoleRows() >= rows)
				setConsoleColor(LIGHTGREEN);
			else
				setConsoleColor(LIGHTRED);
			cout << getConsoleRows();

			setConsoleColor(WHITE);
			Sleep(500);
			clearConsole();
		}
	}
	void header(string page = "Home", string pageLabel = "Page") {
		clearConsole();

		//sizePrompt();

		setConsoleColor(CYAN);
		cout << "Polynomials";
		setConsoleColor(WHITE);
		cout << " | " << pageLabel << " -> " << page;
		showNotif();
	}
	void profiles(int& page) {
		header("Profiles");

		renderProfiles(page);

		printHelp("ENTER", "Select Profile!", BROWN);
		printHelp("SPACE", "Import Profile!", BROWN);
		//printHelp("NONE", "Export Profile!", DARKGREY);
		printHelp("DEL", "Remove Profile!", BROWN);

		printHelp("KEY 1", "Equality Check!");
		printHelp("KEY 2", "Subset Check!");
		printHelp("KEY 3", "Addition!");
		printHelp("KEY 4", "Subtraction!");
		printHelp("KEY 5", "Exclude!");

		printHelp("UP", "Previous Page!", CYAN);
		printHelp("DOWN", "Next Page!", CYAN);

		printHelp("BACK", "RETURN!", LIGHTCYAN);
		printHelp("ESC", "EXIT!", LIGHTRED);
	}
	void visualizer(string name, Node* data) {
		sizePrompt(80, 450); // stops program until size matches

		header(name, "Visualizer");

		data->print(true, 2);

		cout << "\n\n";

		printHelp("KEY 1", "Repaint!");

		printHelp("BACK", "RETURN!", LIGHTCYAN);
		printHelp("ESC", "EXIT!", LIGHTRED);
	}
	void profile(string name, Node* data) {
		header(name, "Profile");

		setConsoleColor(LIGHTGREY);
		cout << "String Equivilant: ";
		setConsoleColor(YELLOW);
		cout << (data->toString() == "" ? " 0" : data->toString().substr(1)) << "\n\n";

		setConsoleColor(LIGHTGREY);
		cout << "Nodes max depth: ";
		setConsoleColor(YELLOW);
		cout << data->getDepth() << "\n\n";

		setConsoleColor(LIGHTGREY);
		cout << "Calculated result: ";
		setConsoleColor(YELLOW);
		cout << data->calculate() << "  ";

		if (!isRangeDefined(data->getDepth() + 1))
		{
			setConsoleColor(BLACK, BROWN);
			cout << "WARNING: Some variables are not defined or set to zero!";
		}

		setConsoleColor(WHITE);
		cout << "\n\n";

		cout << "\n";

		printHelp("KEY 1", "Visualizer!");
		printHelp("KEY 2", "Multiply!");
		printHelp("KEY 3", "Devide!");
		printHelp("KEY 4", "Inverse!");
		printHelp("KEY 5", "Save as profile!");

		printHelp("BACK", "RETURN!", LIGHTCYAN);
		printHelp("ESC", "EXIT!", LIGHTRED);
	}
	void variables(int& page) {
		header("Variables");

		renderVariables(page);

		printHelp("ENTER", "Update variable!");
		printHelp("DEL", "Delete variable!");

		printHelp("UP", "Previous Page!", CYAN);
		printHelp("DOWN", "Next Page!", CYAN);

		printHelp("BACK", "RETURN!", LIGHTCYAN);
		printHelp("ESC", "EXIT!", LIGHTRED);
	}
	void settings(int& page) {
		header("Settings");

		renderSettings(page);

		printHelp("ENTER", "Toggle config!");

		printHelp("UP", "Previous Page!", CYAN);
		printHelp("DOWN", "Next Page!", CYAN);

		printHelp("BACK", "RETURN!", LIGHTCYAN);
		printHelp("ESC", "EXIT!", LIGHTRED);
	}
	void home() {
		header();

		printHelp("KEY 1", "Profiles!");
		printHelp("KEY 2", "Variables!");
		printHelp("KEY 3", "Settings!");

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

	void visualizer(string name, Node* data) {
		while (true)
		{
			intro::visualizer(name, data);
			int cc = getKey();
			string name, file;
			switch (cc)
			{
			case VK_ESCAPE:
				if (confirmBox())
					exit(0);
				else
					setNotif("warning", "Action canceled!");
				break;
			case VK_BACK:
				return;
				break;
			case VK_KEY1:
				break;
			default:
				setNotif("error", "Unknown Command!!!");
				break;
			}
		}
	}
	void profile(string name, Node* data) {
		while (true)
		{
			intro::profile(name, data);
			int cc = getKey();
			string tmp;
			switch (cc)
			{
			case VK_ESCAPE:
				if (confirmBox())
					exit(0);
				else
					setNotif("warning", "Action canceled!");
				break;
			case VK_BACK:
				return;
				break;
			case VK_KEY1:
				visualizer(name, data);
				break;
			case VK_KEY2:
				cout << "Enter a number to multiply by: ";
				tmp = getString();
				if (!is_number(tmp))
				{
					setNotif("error", "Provide a valid number!");
					break;
				}
				data->multiply(stoi(tmp));
				setNotif("success", "Profile multiplied successfully!");
				break;
			case VK_KEY3:
				cout << "Enter a number to devide by: ";
				tmp = getString();
				if (!is_number(tmp) || tmp == "0")
				{
					setNotif("error", "Provide a valid number!");
					break;
				}
				data->multiply(1.0 / stoi(tmp));
				setNotif("success", "Profile devided successfully!");
				break;
			case VK_KEY4:
				data->multiply(-1);
				setNotif("success", "Profile inversed successfully!");
				break;
			case VK_KEY5:
				cout << "Enter profile name to save: ";
				tmp = getString();
				if (existsProfile(tmp))
				{
					setNotif("error", "This profile name is alread taken!");
					break;
				}
				addProfile(tmp, data->copy(true));
				setNotif("success", "New profile added successfully!");
				return;
				break;
			default:
				setNotif("error", "Unknown Command!!!");
				break;
			}
		}
	}

	void profiles() {
		int page = 1;
		while (true)
		{
			intro::profiles(page);
			int cc = getKey();
			string name, name2, file;
			Node* result, * tmp;
			switch (cc)
			{
			case VK_ESCAPE:
				if (confirmBox())
					exit(0);
				else
					setNotif("warning", "Action canceled!");
				break;
			case VK_BACK:
				return;
				break;
			case VK_RETURN:
				cout << "Enter profile name to select: ";
				name = getString();
				if (!existsProfile(name))
				{
					setNotif("error", "This name doesnt exist as a profile!");
					break;
				}
				profile(name, getProfile(name));
				break;
			case VK_SPACE:
				cout << "Enter new profile name: ";
				name = getString();
				if (name.size() == 0 || existsProfile(name))
				{
					setNotif("error", "This name is already taken or it's invalid!");
					break;
				}
				cout << "Enter matrix file name: ";
				file = getString();
				if (!fileExists(file))
				{
					setNotif("error", "Invalid file name!");
					break;
				}
				addProfile(name, Node::fromFile(file));
				setNotif("success", "Profile imported successfully!");
				break;
			case VK_KEY1:
				cout << "Enter first profile name: ";
				name = getString();
				if (!existsProfile(name))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				cout << "Enter second profile name: ";
				name2 = getString();
				if (!existsProfile(name2))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				if (Node::isEqual(getProfile(name), getProfile(name2), true))
				{
					setConsoleColor(BLACK, LIGHTGREEN);
					cout << "They are equal!";
				}
				else
				{
					setConsoleColor(WHITE, LIGHTRED);
					cout << "They are not equal!";
				}
				setConsoleColor(WHITE);
				cout << "\n";
				cout << "press enter to continue...";
				getKey();
				break;
			case VK_KEY2:
				cout << "Enter base profile name: ";
				name = getString();
				if (!existsProfile(name))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				cout << "Enter sample profile name: ";
				name2 = getString();
				if (!existsProfile(name2))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				if (getProfile(name)->includes(getProfile(name2)))
				{
					setConsoleColor(BLACK, LIGHTGREEN);
					cout << name2 << " is a subset of " << name;
				}
				else
				{
					setConsoleColor(WHITE, LIGHTRED);
					cout << name2 << " is not a subset of " << name;
				}
				setConsoleColor(WHITE);
				cout << "\n";
				cout << "press enter to continue...";
				getKey();
				break;
			case VK_KEY3:
				cout << "Enter first profile name: ";
				name = getString();
				if (!existsProfile(name))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				cout << "Enter second profile name: ";
				name2 = getString();
				if (!existsProfile(name2))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				result = Node::sum(getProfile(name), getProfile(name2));
				profile("Addition(" + name + "+" + name2 + ")", result);
				result->free(true);
				break;
			case VK_KEY4:
				cout << "Enter first profile name: ";
				name = getString();
				if (!existsProfile(name))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				cout << "Enter second profile name: ";
				name2 = getString();
				if (!existsProfile(name2))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				//inversing second profile then add
				tmp = getProfile(name2)->copy(true);
				tmp->multiply(-1);

				result = Node::sum(getProfile(name), tmp);
				profile("Subtraction(" + name + "-" + name2 + ")", result);
				result->free(true);
				tmp->free(true);
				break;
			case VK_KEY5:
				cout << "Enter first profile name: ";
				name = getString();
				if (!existsProfile(name))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				cout << "Enter second profile name: ";
				name2 = getString();
				if (!existsProfile(name2))
				{
					setNotif("error", "Profile doesnt exist!");
					break;
				}
				result = Node::exclude(getProfile(name), getProfile(name2));
				profile("Excluded(" + name + "-" + name2 + ")", result);
				result->free(true);
				break;
			case VK_DELETE:
				cout << "Enter profile name to remove: ";
				name = getString();
				if (removeProfile(name))
					setNotif("success", "Profile removed successfully!");
				else
					setNotif("error", "This name doesnt exist as a profile!");
				break;
			case VK_UP:
				page--;
				break;
			case VK_DOWN:
				page++;
				break;
			default:
				setNotif("error", "Unknown Command!!!");
				break;
			}
		}
	}

	void variables() {
		int page = 1;
		while (true)
		{
			intro::variables(page);
			int cc = getKey();
			char varName;
			string varValue;
			switch (cc)
			{
			case VK_ESCAPE:
				if (confirmBox())
					exit(0);
				else
					setNotif("warning", "Action canceled!");
				break;
			case VK_BACK:
				return;
				break;
			case VK_RETURN:
				cout << "Enter variable name to update: ";
				varName = getString()[0];
				cout << "Enter new value: ";
				varValue = getString();
				if (!is_number(varValue))
				{
					setNotif("error", "Value you provided is not a valid number!");
					break;
				}

				if (setVar(varName, stoi(varValue)))
					setNotif("success", "Variable updated successfully!");
				else
					setNotif("error", "Couldnt find variable!");

				break;
			case VK_DELETE:
				cout << "Enter variable name to delete: ";
				varName = getString()[0];
				if (unsetVar(varName))
					setNotif("success", "Variable deleted successfully!");
				else
					setNotif("error", "Couldnt find variable!");
				break;
			case VK_UP:
				page--;
				break;
			case VK_DOWN:
				page++;
				break;
			default:
				setNotif("error", "Unknown Command!!!");
				break;
			}
		}
	}
	void settings() {
		int page = 1;
		while (true)
		{
			intro::settings(page);
			int cc = getKey();
			string configID;
			switch (cc)
			{
			case VK_ESCAPE:
				if (confirmBox())
					exit(0);
				else
					setNotif("warning", "Action canceled!");
				break;
			case VK_BACK:
				return;
				break;
			case VK_RETURN:
				cout << "Enter config ID to toggle: ";
				configID = getString();

				if (is_number(configID) && toggleConfig(available_configs[stoi(configID) - 1]))
					setNotif("success", "Config updated successfully!");
				else
					setNotif("error", "Couldnt find config ID provided by you!");

				break;
			case VK_UP:
				page--;
				break;
			case VK_DOWN:
				page++;
				break;
			default:
				setNotif("error", "Unknown Command!!!");
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
				profiles();
				break;
			case VK_KEY2:
				variables();
				break;
			case VK_KEY3:
				settings();
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
	addProfile("main", Node::fromFile("main.txt"));
	addProfile("helper", Node::fromFile("helper.txt"));

	view::home();

	// palyground

	int i;
	cin >> i;
	Node* tree = Node::fromFile();
	Node* tree2 = Node::fromFile("helper.txt");
	Node* res = Node::exclude(tree, tree2);


	cout << tree->toString() << "\n\n";
	cout << tree2->toString() << "\n\n";
	cout << res->toString() << "\n\n";

	//res->print(true);

	//cout << Node::isEqual(tree, tree2, true);

	//Node* tree = Node::fromString("10xyz");
	//tree->print(true);
	/*cout << tree->toString() << "\n\n";
	tree->multiply(2);
	cout << tree->toString();*/
	//consoleColorTest();
	//cout << tree->getDepth();
	//cout << (tree->includes(tree2) ? "TRUE" : "FALSE");
	//cout << tree->calculate();

}

