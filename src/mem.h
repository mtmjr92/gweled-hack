#include <string>
#include <vector>

#ifndef MEM_H_
#define MEM_H_

class Mem {
public:
	static uint64_t getModuleStart(std::string module);
	static bool readmem(void *address, void *buf, size_t size);
	static bool writemem(void *address, void *buf, size_t size);
	static std::vector<int> readFromAddr(void *address, size_t size);
	static bool writeToAddr(void *address, std::vector<int> buffer);
};

#endif /* MEM_H_ */
