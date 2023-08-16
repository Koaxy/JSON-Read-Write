#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <minwindef.h>
#include <vadefs.h>
#include <bitset>
#include <shlobj.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <stack>
#include "json.h"

#define _CRT_SECURE_NO_WARNINGS

using namespace tiny;




namespace KoaxyUtils
{
	std::string Path;

	std::string get_path() {
		wchar_t folder[1024];
		HRESULT result = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, folder);
		if (SUCCEEDED(result)) {
			char string[1024];
			wcstombs(string, folder, 1023);
			return string;
		}
		else return "";
	}

	std::string path = "C:/YourPath";

	std::filesystem::path m_path{};
	std::ofstream m_file{};

	void MagicFunc(std::string JSON)
	{
		m_path.append(path);
                // Write to path.
		m_file.open(m_path, std::ios_base::out | std::ios_base::trunc);
		m_file << JSON;
		m_file.close();
	}

	std::string ReadFile(const std::string& path)//http://0x80.pl/notesen/2019-01-07-cpp-read-file.html
	{
		auto close_file = [](FILE* f) {fclose(f); };
		auto holder = std::unique_ptr<FILE, decltype(close_file)>(fopen(path.c_str(), "rb"), close_file);
		if (!holder)
			return "";
		FILE* f = holder.get();
		if (fseek(f, 0, SEEK_END) < 0)
			return "";
		const long size = ftell(f);
		if (size < 0)
			return "";
		if (fseek(f, 0, SEEK_SET) < 0)
			return "";
		std::string res;
		res.resize(size);
		fread(const_cast<char*>(res.data()), 1, size, f);
		return res;
	}

}
namespace KoaxyJSON
{
	TinyJson rjson;
	TinyJson readJsonA;

	enum JSONType
	{
		STRING,
		INT_,
		BOOLEAN_
	};

	TinyJson JSON;
	TinyJson subjson;

	template <typename T>
	void WriteValue(const std::string& key, T value) {
		JSON[key].Set(value);
		std::string Written = JSON.WriteJson();
		KoaxyUtils::MagicFunc(Written);
		std::cout << Written << std::endl;
	}

	template <typename T>
	void ReadValue(const std::string& key, T value) {
		std::string fileToRead = KoaxyUtils::ReadFile(KoaxyUtils::path);
		TinyJson jsonRead;
		jsonRead.ReadJson(fileToRead);

		if (value == JSONType::STRING) { // 0
			jsonRead.Get<std::string>(key);
			std::cout << jsonRead.Get<std::string>(key) << std::endl;
		}
		if (value == JSONType::BOOLEAN_) { // 2
			jsonRead.Get<bool>(key);
			std::cout << jsonRead.Get<bool>(key) << std::endl;
		}
		if (value == JSONType::INT_) { // 1
			jsonRead.Get<int>(key);
			std::cout << jsonRead.Get<int>(key) << std::endl;
		}
	}
}
