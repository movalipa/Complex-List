#pragma once
#include "cookie.h"

#define VarCookiePrefix "var:"

char variables[] = {
	 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i', 'j',
	 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
};
const int MAX_VARIABLES = 26;

bool isVariableValid(char name) {
	for (int i = 0; i < MAX_VARIABLES; ++i) {
		if (variables[i] == name) {
			return true;
		}
	}
	return false;
}

bool setVar(char name, int value) {
	if (!isVariableValid(name))
		return false;

	setCookie(VarCookiePrefix + string(&name, &name + 1), to_string(value));
	return true;
}

int getVar(char name) {
	string tmp = getCookie(VarCookiePrefix + string(&name, &name + 1));

	if (tmp == "")
		error("Variables not initialized!", "Initialize manualy in cookies", __FILE__, __LINE__);

	return stoi(tmp);
}

bool unsetVar(char name) {
	if (!isVariableValid(name))
		return false;

	setCookie(VarCookiePrefix + string(&name, &name + 1), "0");
	return true;
}


bool isRangeDefined(int index) {
	if (index < 0 || index >= MAX_VARIABLES)
		return false;

	for (int i = 0; i < index; i++)
		if (getVar(variables[i]) == 0)
			return false;

	return true;
}