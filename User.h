#ifndef __USER_H__
#define __USER_H__

#include "Header.h"

class User {
public:
	std::string username = "";
	double avgSpeed = 0.0;
	int typingCount = 0;
	User(std::string username);
	void save();
	void load();
	void printUserInfo();
	std::string getUsername();
};

#endif // !__USER_H__
