#pragma once
#include "stdafx.h"
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
	if (!file)
	{
		printf("ERROR: Could not open %s! \n", name);
	}
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
// считываем пути до аудио в SFX секции
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

// копируем содержимое файла в конечный результат (заголовки)
void copyFileContent(const string& sourceFilename, const string& destinationFilename) {
    ifstream sourceFile(sourceFilename); // Открываем файл для чтения
    ofstream destinationFile(destinationFilename, ios::out | ios::app); // Открываем файл для записи (сохраняем текущее содержимое)

    if (!sourceFile.is_open()) {
        cout << "ERROR: Failed to open file " << sourceFilename << endl;
        return;
    }

    if (!destinationFile.is_open()) {
        cout << "ERROR: Failed to open file " << destinationFilename << endl;
        return;
    }

    string line;

    // Копирование содержимого файла sourceFilename в файл destinationFilename
    while (getline(sourceFile, line)) {
        destinationFile << line << endl; // Добавляем символ новой строки в конец строки
    }

    sourceFile.close();
    destinationFile.close();
}

// удаляем все содержимое папки unpacked_inis
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

// Функция для удаления кавычек из строки
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
	formattedResult.pop_back(); // Удаление последнего пробела

	return formattedResult;
}

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
	formattedResult.pop_back(); // Удаление последнего пробела

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
// End of File Functions