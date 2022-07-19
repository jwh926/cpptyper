#ifndef __TYPING_SYSTEM_H__
#define __TYPING_SYSTEM_H__
#include "Header.h"
#include "User.h"

class TypingSystem {
private:
	std::vector<std::string> sentences;
	User* currentUser = nullptr;
	void loadData();
public:
	void printData();
	void init();
	void printMenu();
	char getChar();
	std::string getString();
	void typingStart(int t);
};

#endif // !__TYPING_SYSTEM_H__
