#include "../../header/file/filesystem.h"

std::vector<char> elm::file::ReadFile(const char* path) {
	std::ifstream file(path, std::ios::binary);
	std::istreambuf_iterator<char> beg(file), end;
	std::vector<char> data(beg, end);
	file.close();
	return data;
}

int elm::file::WriteFile(std::vector<char> data, const char* path)
{
	std::ofstream file(path, std::ios::binary);
	std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(file));
	file.close();
	return EXIT_SUCCESS;
}

bool elm::file::Exist(const char* path)
{
	struct stat buffer;
	return stat(path, &buffer) == 0;
}

std::vector<char> elm::file::CompressData(std::vector<char> data)
{
	std::vector<char> compressedData(LZ4_compressBound(data.size()));
	int size = LZ4_compress_default(data.data(), compressedData.data(), data.size(), compressedData.size());
	compressedData.resize(size);
	return compressedData;
}

int elm::file::DecompressData(std::vector<char>& in, std::vector<char>& out)
{
	return LZ4_decompress_safe(in.data(), out.data(), in.size(), out.size());
}

elm::thread::Task<std::vector<char>, const char*> elm::file::ReadFileAsync(const char* path)
{
	elm::thread::Task<std::vector<char>, const char*> task = ReadFile;
	task(path);
	return task;
}

elm::thread::Task<int, std::vector<char>, const char*> elm::file::WriteFileAsync(std::vector<char> data, const char* path)
{
	elm::thread::Task<int, std::vector<char>, const char*> task = WriteFile;
	task(data, path);
	return task;
}
