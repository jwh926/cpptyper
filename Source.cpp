#include "Header.h"
#include "TypingSystem.h"

int main() {
	TypingSystem* system = new TypingSystem();
	system->init();


	delete system;
	return 0;
}