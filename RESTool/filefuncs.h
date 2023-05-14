#pragma once
#include "stdafx.h"
#include <iostream>

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
	char buffer[256]; // �������� ����� � 64 �� 256. ���� ����������� ����������� ������.
	int stringsize = 0;
	char msgbuffer[128];
	fread(buffer, sizeof(char), sizeof(buffer) - 1, file); // ������ � �����

	for (int i = 0; i < sizeof(buffer) - 1; ++i) // ��������� ������� �����
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

	// ������������ ��������� ������ � ����������� ����������� buffer
	char* result = (char*)malloc((stringsize + 1) * sizeof(char)); // +1 ��� �������� ������� ��������� ������
	strcpy(result, buffer);

	fprintf(out, "%s=%s\n", name, buffer);

	return result;
}

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
			// ��������� ������ ��������� ������
			// ����� ������� NULL ��� ����������� ������ ��������
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
// End of File Functions

