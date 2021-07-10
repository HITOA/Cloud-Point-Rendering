#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <lz4.h>
#include <sys/stat.h>

#include "../thread/task.h"
#include "filestruct.h"

namespace elm::file {
	std::vector<char> ReadFile(const char* path);
	int WriteFile(std::vector<char> data, const char* path);
	bool Exist(const char* path);

	std::vector<char> CompressData(std::vector<char> data);
	int DecompressData(std::vector<char>& in, std::vector<char>& out);

	elm::thread::Task<std::vector<char>, const char*> ReadFileAsync(const char* path);
	elm::thread::Task<int, std::vector<char>, const char*> WriteFileAsync(std::vector<char> data, const char* path);
}