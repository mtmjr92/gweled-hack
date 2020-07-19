#include <sys/uio.h> // iovec
#include <iostream>
#include <sstream>

#include "mem.h"
#include "globalsettings.h"
#include "util.h"

uint64_t Mem::getModuleStart(std::string module) {
	uint64_t moduleStart = -1;
	std::string cmd = "cat /proc/" + std::to_string(Util::getPID())
			+ "/maps | grep " + module + " | head -n1 | cut -d '-' -f1";
	std::string output = Util::exec(cmd.c_str());

	if (output.length() == 0) {
		std::cerr << "Error getting GWELED memory map" << std::endl;
		exit(1);
	}

	// convert stirng to uint64_t
	std::stringstream ss;
	ss << std::hex << output.c_str();
	ss >> moduleStart;

	return moduleStart;
}

bool Mem::readmem(void *address, void *buf, size_t size) {
	if (PID == 0 || size == 0)
		return false;

	iovec iovLocalAddressSpace;
	iovec iovRemoteAddressSpace;

	iovLocalAddressSpace.iov_base = buf;
	iovLocalAddressSpace.iov_len = size;

	iovRemoteAddressSpace.iov_base = address;
	iovRemoteAddressSpace.iov_len = size;

	ssize_t bytes_count_read = process_vm_readv(PID,
			&iovLocalAddressSpace,
			1, //Size of the local iovec array
			&iovRemoteAddressSpace, //Remote iovec array
			1,                      //Size of the remote iovec array
			0);                     //Flags, unused

	return (bytes_count_read == (ssize_t) size);
}

bool Mem::writemem(void *address, void *buf, size_t size) {
    if (PID == 0 || size == 0)
        return false;

    iovec iovLocalAddressSpace;
    iovec iovRemoteAddressSpace;

    iovLocalAddressSpace.iov_base = buf;
    iovLocalAddressSpace.iov_len = size;

    iovRemoteAddressSpace.iov_base = address;
    iovRemoteAddressSpace.iov_len = size;

    ssize_t bytes_count_write = process_vm_writev(PID,
                                                  &iovLocalAddressSpace,  //Local iovec array
                                                  1,                      //Size of the local iovec array
                                                  &iovRemoteAddressSpace, //Remote iovec array
                                                  1,                      //Size of the remote iovec array
                                                  0);                     //Flags, unused

    return (bytes_count_write == (ssize_t)size);
}

std::vector<int> Mem::readFromAddr(void *address, size_t size) {
	int buffer[size] = { 0 };
	if (!Mem::readmem(address, buffer, size)) {
		std::cerr << "Couldn't read from " << std::hex << address << std::endl;
		exit(1);
	}
	std::vector<int> res(buffer, buffer + size);
	return res;
}

bool Mem::writeToAddr(void *address, std::vector<int> buffer) {
    return Mem::writemem(address, reinterpret_cast<int *>(buffer.data()), sizeof(int));
}
