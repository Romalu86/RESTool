	#pragma once
	#include "stdafx.h"
	#include <Windows.h>
	#include <fstream>
	#include <iostream>
	#include <vector>
	#include <string>
	#include <sstream>
	using namespace std;

	// File Functions
	char bufferrn[64];
	FILE* OpenFile(char* name)
	{
		FILE* file = fopen(name, "rb");
		return file;
	}
	int ReadByte(FILE* file)
	{
		char number;
		fread(&number, 1, 1, file);
		return number;
	}

	int ReadInt(FILE* file)
	{
		int number;
		fread(&number, 1, 4, file);
		return number;
	}

	float ReadFloat(FILE* file)
	{
		float number;
		fread(&number, 1, sizeof(float), file);
		return number;
	}

	// Name & VidName strings function
	char* ReadString(FILE* file, FILE* out, char* name)
	{
		char buffer[256]; // 256 Limit for new games.
		int stringsize = 0;
		char msgbuffer[128];
		fread(buffer, sizeof(char), sizeof(buffer) - 1, file);

		for (int i = 0; i < sizeof(buffer) - 1; ++i)
		{
			stringsize++;
			if (buffer[i] == 0x00)
			{
				fseek(file, (ftell(file) - (sizeof(buffer) - 1) + stringsize), SEEK_SET);
				//printf("OK: Cursor pos %i \n", (ftell(file) - (sizeof(buffer) - 1) + stringsize));
				break;
			}
		}

		sprintf(msgbuffer, "%s", buffer);

		// Динамическое выделение памяти и копирование содержимого buffer
		char* result = (char*)malloc((stringsize + 1) * sizeof(char)); // +1 для нулевого символа окончания строки
		strcpy(result, buffer);

		fprintf(out, "%s=%s\n", name, buffer);

		return result;
	}

		// SFX & ForceFeedback strings function
		std::string ReadStringNoRTN(FILE* file) {
		int stringsize = 0;
		char ch;
		std::string buffer;

		while (fread(&ch, sizeof(char), 1, file) == 1) {
			if (ch == 0x00) {
				break;
			}
			buffer += ch;
			stringsize++;
		}

		return buffer;
		}

		// Функция для считывания заданного количества строк из файла и формирования строки с путями
		std::string readPathsFromFile(FILE* file, int numStrings) {
		std::vector<std::string> paths;
		std::string path;

		// Считываем заданное количество строк для путей до файлов
		for (int i = 0; i < numStrings; ++i) {
			if (!feof(file)) {
				path = ReadStringNoRTN(file);
				paths.push_back(path);
			}
		}

		// Формируем строку с путями до файлов
		std::string buffer;
		for (const std::string& p : paths) {
			buffer += p + " ";
		}

		return buffer;
		}

	// Copy Header to Output files function
	void copyFileContent(const string& sourceFilename, const string& destinationFilename) {
		ifstream sourceFile(sourceFilename); // Open file (Read)
		ofstream destinationFile(destinationFilename, ios::out | ios::app); // Open file (Write)

		if (!sourceFile.is_open())
		{
			std::cerr << "WARNING: Failed to open file " << sourceFilename << std::endl;
			std::cerr << "WARNING: The output file will be created without a compiler header!" << endl;
		}

		if (!destinationFile.is_open())
		{
			std::cerr << "ERROR: Failed to open file " << destinationFilename << std::endl;
			std::cerr << "Press Enter to exit..." << std::endl;
			std::cin.ignore();
			exit(1);
		}

		string line;

		// Copy file "sourceFilename" in file "destinationFilename"
		while (getline(sourceFile, line))
		{
			destinationFile << line << endl; // New line
		}
		sourceFile.close();
		destinationFile.close();
	}

	// Remove quotes from path to file
	string removeQuotes(string str)
	{
		size_t firstQuote = str.find_first_of("\"");
		size_t lastQuote = str.find_last_of("\"");
		if (firstQuote != string::npos && lastQuote != string::npos && firstQuote < lastQuote)
		{
			return str.substr(firstQuote + 1, lastQuote - firstQuote - 1);
		}
		return str;
	}

	// Clear Previous Results confirmation func
	void ClearPreviousResults()
	{
		wchar_t currentPath[MAX_PATH];
		GetCurrentDirectoryW(MAX_PATH, currentPath);

		std::wstring folderPath = std::wstring(currentPath) + L"\\unpacked_inis";

		std::wcout << L"To avoid problems with unpacking, it is recommended to clear the previous results in the 'unpacked_inis' folder. Do you want to remove them? (y/n): ";
		std::wstring response;
		std::getline(std::wcin, response);
		std::wcout << std::endl;

		if (response == L"y" || response == L"Y")
		{
			if (CreateDirectoryW(folderPath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
			{
				std::wstring searchPath = folderPath + L"\\*.*";
				WIN32_FIND_DATAW findData;
				HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);

				if (hFind != INVALID_HANDLE_VALUE)
				{
					do
					{
						if (findData.cFileName[0] != L'.')
						{
							std::wstring filePath = folderPath + L"\\" + findData.cFileName;

							if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
							{
								std::wstring subFolderPath = folderPath + L"\\" + findData.cFileName;

								std::wstring subSearchPath = subFolderPath + L"\\*.*";
								WIN32_FIND_DATAW subFindData;
								HANDLE hSubFind = FindFirstFileW(subSearchPath.c_str(), &subFindData);

								if (hSubFind != INVALID_HANDLE_VALUE)
								{
									do
									{
										if (subFindData.cFileName[0] != L'.')
										{
											std::wstring subFilePath = subFolderPath + L"\\" + subFindData.cFileName;
											DeleteFileW(subFilePath.c_str());
										}
									} while (FindNextFileW(hSubFind, &subFindData) != 0);

									FindClose(hSubFind);
								}

								RemoveDirectoryW(subFolderPath.c_str());
							}
							else
							{
								DeleteFileW(filePath.c_str());
							}
						}
					} while (FindNextFileW(hFind, &findData) != 0);

					FindClose(hFind);
				}

				if (RemoveDirectoryW(folderPath.c_str()))
				{
					std::wcout << L"Folder 'unpacked_inis' deleted successfully." << std::endl;
					std::wcout << std::endl;
				}
				else
				{
					std::wcout << L"Failed to delete folder 'unpacked_inis'." << std::endl;
					std::wcout << L"Error code: " << GetLastError() << std::endl;
					std::wcout << std::endl;
				}
			}
		}
	}

	// Working with float`s
	std::string processFloatValues(const float* arrayf, int numValues, bool useTabulation = true)
	{
		std::vector<std::string> values;
		for (int i = 0; i < numValues; ++i)
		{
			std::string str = std::to_string(arrayf[i]);
			str.erase(str.find_last_not_of('0') + 1, std::string::npos);
			str.erase(str.find_last_not_of('.') + 1, std::string::npos);
			values.push_back(str);
		}

		std::ostringstream oss;
		for (const auto& value : values)
		{
			if (useTabulation)
				oss << value << "\t\t";
			else
				oss << value << " ";
		}

		std::string formattedResult = oss.str();
		formattedResult.pop_back(); // Delete last tabulation or space

		return formattedResult;
	}

	// Working with int`s
	std::string processIntValues(const int* arrayi, int numValues, bool useTabulation = true)
	{
		std::ostringstream oss;
		for (int i = 0; i < numValues; ++i)
		{
			if (useTabulation)
				oss << arrayi[i] << "\t\t";
			else
				oss << arrayi[i] << " ";
		}

		std::string formattedResult = oss.str();
		formattedResult.pop_back(); // Delete last tabulation or space

		return formattedResult;
	}

	// Headers errors
	void showError(const std::string& errorMessage)
	{
		std::cout << "ERROR: " << errorMessage << std::endl;
		std::cout << "Press Enter to exit..." << std::endl;
		std::cin.ignore();
		exit(1);
	}

	// checkDictionary function
	void checkDictionary()
	{
		std::ifstream file("data/constants.ini");

		if (!file)
		{
			std::cout << "WARNING: Failed to open file data/constants.ini" << std::endl;
			std::cout << "WARNING: Description of object properties will be unavailable!" << std::endl;
		}
		else
		{
			std::cout << "OK: Constants file loaded" << std::endl;
		}
	}
	// End of File Functions