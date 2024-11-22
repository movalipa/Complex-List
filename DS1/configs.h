#pragma once
#include "cookie.h"

#define ConfigCookiePrefix "config:"

const string available_configs[] = {"high_contrast_print", "animation_print"};
const int MAX_CONFIGS = 2;

bool isConfigValid(string name) {
	for (int i = 0; i < MAX_CONFIGS; ++i) {
		if (available_configs[i] == name) {
			return true;
		}
	}
	return false;
}

bool setConfig(string name, bool value) {
	if (!isConfigValid(name))
		return false;

	setCookie(ConfigCookiePrefix + name, value ? "1" : "0");
	return true;
}

bool getConfig(string name) {
	return getCookie(ConfigCookiePrefix + name) == "1";
}

bool toggleConfig(string name) {
	return setConfig(name, !getConfig(name));
}

