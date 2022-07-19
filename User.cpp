#include "User.h"

User::User(std::string username) {
	FILE* fp = fopen(username.c_str(), "r");
	bool exists = fp != nullptr;

	if (exists) fclose(fp);

	if (exists) {
		clear();
		putStringOnPosition(6, 4, "loading");
		this->username = username;
		load();
//		putStringOnPosition(6, 5, "press enter to continue");
//		fseek(stdin, 0, SEEK_END);
//		fgetc(stdin);
	}
	else {
		clear();
		putStringOnPosition(6, 4, username + " does not exist. create new one? (y/n): ");
		char ans;
		fseek(stdin, 0, SEEK_END);
		scanf("%c", &ans);
		if (ans == 'y') {
			this->username = username;
			save();
			clear();
			putStringOnPosition(6, 4, username + " created. press enter to continue");
			fseek(stdin, 0, SEEK_END);
			fgetc(stdin);
		}
		else {
			this->username = "";
			clear();
			putStringOnPosition(6, 4, "aborted. press enter to continue");
			fseek(stdin, 0, SEEK_END);
			fgetc(stdin);
		}
	}
}

void User::save() {
	FILE* out = fopen(username.c_str(), "w");
	fprintf(out, "%.1lf\n", avgSpeed);
	fprintf(out, "%d", typingCount);
	fclose(out);
}

void User::load() {
	FILE* in = fopen(username.c_str(), "r");
	fscanf(in, "%lf", &avgSpeed); fgetc(in);
	fscanf(in, "%d", &typingCount); fgetc(in);
	fclose(in);
}

void User::printUserInfo() {
	char avgSpeed[20], count[50];
	sprintf(avgSpeed, "%f", this->avgSpeed);
	sprintf(count, "%d", this->typingCount);

	putStringOnPosition(6, 6, avgSpeed);
	putStringOnPosition(6, 7, count);
	putStringOnPosition(6, 8, "press any key to continue");
	fseek(stdin, 0, SEEK_END);
	fgetc(stdin);
}

std::string User::getUsername() {
	return username;
}
