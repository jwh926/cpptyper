#include "TypingSystem.h"

void TypingSystem::loadData() {
	FILE* infile = fopen("sentences.txt", "r");
	while (true) {
		if (feof(infile) == 1) break;
		char line[512] = { 0, };
		fscanf(infile, "%511[^\n]s", line);
		fgetc(infile);
		sentences.push_back(line);
	}

	fclose(infile);
}

void TypingSystem::printData() {
	for (auto& i : sentences) {
		printf("%s\n", i.c_str());
	}
}

void TypingSystem::init() {
	loadData();
	while (true) {
		clear();
		printMenu();
		char input = getChar();
		if (input == '1' && currentUser == nullptr) {
			clear();
			putStringOnPosition(6, 4, "username: ");
			std::string uname = getString();
			currentUser = new User(uname);
			if (currentUser->getUsername() == "") {
				delete currentUser;
				currentUser = nullptr;
			}
		}
		else if (input == '1' && currentUser != nullptr) {
			delete currentUser;
			currentUser = nullptr;
		}
		else if (input == '2' && currentUser != nullptr) {
			clear();
			int t = 0;
			putStringOnPosition(6, 4, "times: ");
			fseek(stdin, 0, SEEK_END);
			scanf("%d", &t);
			typingStart(t);
		}
		else if (input == '3' && currentUser != nullptr) {
			clear();
			currentUser->printUserInfo();
		}
		else if (input == 'x' || input == 'X') {
			putStringOnPosition(0, 13, "quit");
			break;
		}
	}
}

void TypingSystem::printMenu() {
	if (currentUser == nullptr) {
		putStringOnPosition(6, 3, "1. login");
	}
	else if (currentUser != nullptr) {
		putStringOnPosition(6, 3, "1. logout");
		putStringOnPosition(6, 4, "2. start typing");
		putStringOnPosition(6, 5, "3. user stats");
		putStringOnPosition(0, 8, "currentUser: " + currentUser->getUsername());
	}
	putStringOnPosition(0, 10, "input: ");
}

char TypingSystem::getChar() {
	fseek(stdin, 0, SEEK_END);
	char c;
	scanf("%c", &c);
	return c;
}

std::string TypingSystem::getString() {
	char input[100];
	fseek(stdin, 0, SEEK_END);
	scanf("%99[^\n]s", input);
	return input;
}

void TypingSystem::typingStart(int t) {
	float types_per_min = 0.0f;
	for (int i = 0; i < t; i++) {
		clear();
		char buff[128];
		sprintf(buff, "%d / %d", i, t);
		putStringOnPosition(6, 6, buff);
		sprintf(buff, "%.1f", types_per_min);
		putStringOnPosition(6, 5, buff);

		int target = rand() % sentences.size();
		sprintf(buff, "sentence: %s", sentences[target].c_str());
		putStringOnPosition(6, 3, buff);
		putStringOnPosition(6, 4, "input: ");

		float start = (float)clock() / CLOCKS_PER_SEC;
		std::string input = getString();
		float end = (float)clock() / CLOCKS_PER_SEC;
		float delta = end - start;

		types_per_min = sentences[target].size() / delta * 60;
		currentUser->typingCount++;
		currentUser->avgSpeed = (currentUser->avgSpeed * ((double)currentUser->typingCount - 1.0) + types_per_min) / (double)currentUser->typingCount;
	}
	currentUser->save();
}
