#pragma once
#include "cookie.h"

#define VarCookiePrefix "var:"

void setVar(char name, int value) {
	setCookie(VarCookiePrefix + name, to_string(value));
}

int getVar(char name) {
	string tmp = getCookie(VarCookiePrefix + string(&name, &name + 1));

	if (tmp == "")
		error("Variables not initialized!", "Initialize manualy in cookies", __FILE__, __LINE__);

	return stoi(tmp);
}

void unsetVar(char name) {
	setCookie(VarCookiePrefix + name, "0");
}