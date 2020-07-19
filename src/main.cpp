#include <iostream>
#include <sys/uio.h>
#include <vector>

#include "globalsettings.h"
#include "game.h"
#include "util.h"

using namespace std;

pid_t PID;
unsigned int gi_score = 0x187E8;
unsigned int gi_current_score = 0x18800;
uint64_t base_address;

int main() {
	cout << "loading...." << endl;

	PID = Util::getPID();
	std::cout << "GWELED Process PID: " << PID << std::endl;

	Game::getAddrs();

	if (Game::changeScore(450))
		std::cout << "Successfully change score!" << std::endl;
	else
		std::cout << "Error change score!" << std::endl;

	Game::readScore();

	return 0;
}

