#pragma once
#include "Node.h"

struct Profile {
	string name = "";
	Node* data = NULL;
};

Profile available_profiles[MaxFileLines];
int profiles_count = 0;

Profile SelectedProfile;

bool existsProfile(string name) {
	for (int i = 0; i < profiles_count; i++)
		if (available_profiles[i].name == name)
			return true;

	return false;
}

Node* getProfile(string name) {
	for (int i = 0; i < profiles_count; i++)
		if (available_profiles[i].name == name)
			return available_profiles[i].data;

	return NULL;
}

bool addProfile(string name, Node* data) {
	// name already exists
	if (existsProfile(name))
		return false;

	available_profiles[profiles_count].name = name;
	available_profiles[profiles_count].data = data;
	profiles_count++;

	return true;
}

bool removeProfile(int index) {
	if (index < 0 || index >= profiles_count)
		return false;


	if (available_profiles[index].data != nullptr) {
		delete available_profiles[index].data;
		available_profiles[index].data = nullptr;
		available_profiles[index].name = "";
	}

	// Shift remaining profiles to fill the gap
	for (int i = index; i < profiles_count - 1; i++)
		available_profiles[i] = available_profiles[i + 1];

	available_profiles[profiles_count - 1] = Profile();

	profiles_count--;

	return true;
}

bool removeProfile(string name) {
	for (int i = 0; i < profiles_count; i++)
		if (available_profiles[i].name == name)
			return removeProfile(i);

	return false;
}

bool setActiveProfile(int index) {
	return false;
}


