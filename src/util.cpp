#include <array>
#include <memory>

#include "util.h"

std::string Util::exec(const char *cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

	if (!pipe)
		throw std::runtime_error("popen() failed!");

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();

	return result;
}

pid_t Util::getPID() {
	std::string output = Util::exec("pidof gweled");

	if (output.length() == 0) {
		std::cerr << "Error getting GWELED PID" << std::endl;
		exit(1);
	}

	pid_t PID = (pid_t) atoi(&output[5]);

	return PID;
}
