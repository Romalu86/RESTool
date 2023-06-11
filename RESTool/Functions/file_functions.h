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

uint32_t ReadUInt(FILE* file)
{
	uint32_t number;
	fread(&number, sizeof(uint32_t), 1, file);
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

// // SFX & ForceFeedback strings function
char* ReadStringNoRTN(FILE* file)
{
	int stringsize = 0;
	char* buffer = NULL;
	char ch;
	while (fread(&ch, sizeof(char), 1, file) == 1)
	{
		if (ch == 0x00)
		{
			break;
		}
		char* temp = (char*)realloc(buffer, (stringsize + 1) * sizeof(char));
		if (temp == NULL)
		{
			// Обработка ошибки выделения памяти
			// Можно вернуть NULL или предпринять другие действия
			free(buffer);
			return NULL;
		}
		buffer = temp;
		buffer[stringsize] = ch;
		stringsize++;
	}
	char* result = (char*)realloc(buffer, (stringsize + 1) * sizeof(char));
	if (result != NULL)
	{
		result[stringsize] = '\0';
	}
	return result;
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

// Delete files and folder unpacked_inis
void RemoveAllFilesInDirectory(const std::string& directory)
{
	std::string searchPath = directory + "\\*.*";
	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.cFileName[0] != '.')
			{
				std::string filePath = directory + "\\" + findData.cFileName;

				if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					RemoveAllFilesInDirectory(filePath);
					RemoveDirectory(filePath.c_str());
				}
				else
				{
					DeleteFile(filePath.c_str());
				}
			}
		} while (FindNextFile(hFind, &findData) != 0);

		FindClose(hFind);
	}
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
	cout << endl;
	std::cout << "Press Enter to exit..." << std::endl;
	std::cin.ignore();
	exit(1);
}

// Clear previous results
void ClearPreviousResults()
{
	char currentPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentPath);

	std::string folderPath = std::string(currentPath) + "\\unpacked_inis";

	std::cout << "To avoid problems with unpacking, it is recommended to clear the previous results in the 'unpacked_inis' folder. Do you want to remove them? (y/n): ";
	std::string response;
	std::getline(std::cin, response);
	std::cout << std::endl;

	if (response == "y" || response == "Y")
	{
		if (CreateDirectory(folderPath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
		{
			RemoveAllFilesInDirectory(folderPath);

			if (RemoveDirectory(folderPath.c_str()))
			{
				std::cout << "Folder 'unpacked_inis' deleted successfully." << std::endl;
				std::cout << std::endl;
			}
			else
			{
				std::cout << "Failed to delete folder 'unpacked_inis'." << std::endl;
				std::cout << "Error code: " << GetLastError() << std::endl;
				std::cout << std::endl;
			}
		}
	}
}
// End of File Functions