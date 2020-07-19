#include <sstream>
#include <iostream>

#include "game.h"
#include "mem.h"
#include "offsets.h"
#include "globalsettings.h"

bool Game::getAddrs() {
	uint64_t gweled_base_address = Mem::getModuleStart("gweled");
	std::cout << "gweled is @ " << std::hex << gweled_base_address << std::endl;

	base_address = gweled_base_address;

	return true;
}

bool Game::changeScore(int score) {
	std::vector<int> buf;
	buf.push_back(score);

	Mem::writeToAddr((void*) (base_address + gi_score), buf);
	Mem::writeToAddr((void*) (base_address + gi_current_score), buf);

	return true;
}

bool Game::readScore() {
	int lifeScore = Mem::readFromAddr((void*) (base_address + gi_score), sizeof(int))[0];

	std::cout << "score => " << std::dec << (lifeScore) << std::endl;
	return true;
}
