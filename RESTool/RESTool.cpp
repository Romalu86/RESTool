#include "stdafx.h"
#include <Windows.h>
#include "Functions\filefuncs.h"
#include "Functions\SpriteTypeParser.h"
#include "Functions\SpriteClassParser.h"
#include "Functions\DefaultBehaveParser.h"
#include "Functions\ObjectsPropertyParser.h"
#include "Functions\NWeaponPropertyParser.h"
#include "Functions\SFXPropertyParser.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	char currentPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentPath);

	std::string folderPath = std::string(currentPath) + "\\unpacked_inis";

	std::cout << "To avoid problems with unpacking, it is recommended to clear the previous results in the 'unpacked_inis' folder. Do you want to remove them? (y/n): ";
	std::string response;
	std::getline(std::cin, response);
	cout << endl;

	if (response == "y" || response == "Y")
	{
		if (CreateDirectory(folderPath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
		{
			RemoveAllFilesInDirectory(folderPath);

			if (RemoveDirectory(folderPath.c_str()))
			{
				std::cout << "Folder 'unpacked_inis' deleted successfully." << std::endl;
				cout << endl;
			}
			else
			{
				std::cout << "Failed to delete folder 'unpacked_inis'." << std::endl;
				std::cout << "Error code: " << GetLastError() << std::endl;
				cout << endl;
			}
		}
	}

	int out;
	float arrayf[17];
	int arrayi[17];
	char obuffer[65535];
	FILE* in;
	FILE* fout;
	string filename;
	string mode;

	bool fileOpened = false;

	cout << "RESTool 1.6 by Romalu86" << endl;
	cout << endl;
	cout << "File modes:" << endl;
	cout << "as1_engine - works with Alien Shooter 1, Alien Shooter 1 Last Hope, Alien Shooter - Lost World (Theseus Mobile) " << endl;
	cout << "theseus_pc - works with Theseus (PC Only)" << endl;
	cout << "as1world - works with Alien Shooter 1 - World" << endl;
	cout << "zs1 - works with Zombie Shooter 1 (PC Only)" << endl;
	cout << "zs1_mobile - works with Zombie Shooter 1 (Mobile)" << endl;
	cout << "as2_original - works with Gold and Vengeance editions" << endl;
	cout << "as2_addons - works with Reloaded, Conscription, Zombie Shooter 2 Teaser, Objects Extended Project (Old versions before 1.1.0.6)" << endl;
	cout << "zs2_engine - works with Zombie Shooter 2 / Alien Shooter: Revisited" << endl;
	cout << "as2legend_engine - works with Alien Shooter 2 Legend & TD (Steam and Mobile), Alien Shooter 2 New Era, Alien Shooter 2 Reloaded (Mobile)" << endl;
	cout << "oe_engine - works with Objects Extended Project (version 1.1.0.6+)" << endl;
	cout << endl;
	cout << "Alternative unpacking mode - required for unpacking data in case of incorrect section reading." << endl;
	cout << endl;

	bool activateCharPadFlag = true;

	while (!fileOpened)
	{
			// File name
			cout << "Enter the filename or path to file: ";
			getline(cin, filename);
			filename = removeQuotes(filename);

			// Alternative unpacking mode (char pad in weap section)
			cout << "Do you want to activate the alternative unpacking mode? (y/n): ";
			string activateCharPadMode;
			getline(cin, activateCharPadMode);

			if (activateCharPadMode == "y" || activateCharPadMode == "Y")
			{
				activateCharPadFlag = true;
			}
			else
			{
				activateCharPadFlag = false;
			}

			// File mode
			cout << "Enter file mode: ";
			getline(cin, mode);
			cout << endl;

		in = fopen(filename.c_str(), "rb");
		if (!in)
		{
			cout << "Failed to open file: " << filename << endl;
			cout << "Press Enter to try again or enter 'q' to quit...";
			cout << endl;
			string userInput;
			getline(cin, userInput);
			if (userInput == "q" || userInput == "Q")
				return 1;
			continue;
		}

		fileOpened = true;
	}

	bool validMode = false;
	while (!validMode)
	{
				// Alien Shooter 1 Engine
				if (mode == "as1_engine")
				{
				validMode = true;
				CreateDirectoryA("unpacked_inis", NULL);
				copyFileContent("data\\OBJ\\gen1_OBJ.ini", "unpacked_inis\\OBJ.ini");
			{
				// RES Header
				out = ReadInt(in);
				printf("OK: RES Header found\n", out);
				if (!out == 'RES ')
				{
					printf("ERROR: Could not find RES header! \n");
					fclose(in);
					return 1;
				}

				// RES File Size
				out = ReadInt(in);
				printf("OK: RES Size %d bytes\n", out);

				// DATA Header
				out = ReadInt(in);
				printf("OK: DATA Header found\n", out);
				if (!out == 'DATA')
				{
					printf("ERROR: Could not find DATA header! \n");
					fclose(in);
					return 1;
				}

				// OBJ Header
				out = ReadInt(in);
				printf("OK: OBJ Header found\n", out);
				if (!out == 'OBJ ')
				{
					printf("ERROR: Could not find OBJ header! \n");
					fclose(in);
					return 1;
				}

				out = ReadInt(in); // Section Size
				out = ReadInt(in); // unk1
				out = ReadInt(in); // unk2
				int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
				printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
				for (int _ = 0; _ < amountOfNVIDs; _++)
				{
					out = ReadInt(in); // NVid Size
					out = ReadInt(in); // NVid Number
					fout = fopen("unpacked_inis\\OBJ.ini", "a+");
					if (!fout)
					{
						printf("ERROR: Failed to open OBJ.ini file!\n");
						return 1;
					}
					fprintf(fout, ";------------------------- \n");
					fprintf(fout, "NVid=%i\n", out);
					// Name STRING
					ReadString(in, fout, "Name");
					// SpriteType DWORD
					out = ReadInt(in);
					string spriteTypeText = GetSpriteTypeText(out);
					if (!spriteTypeText.empty()) {
						fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
					}
					else {
						fprintf(fout, "SpriteType=%i\n", out);
					}
					// SpriteClass DWORD
					out = ReadInt(in);
					string spriteClassText = GetSpriteClassText(out);
					if (!spriteClassText.empty()) {
						fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
					}
					else {
						fprintf(fout, "SpriteClass=%i\n", out);
					}
					// Property DWORD
					out = ReadInt(in);
					string propertyText = GetObjectsPropertyText(out);
					if (!propertyText.empty()) {
						fprintf(fout, "Property=%s\n", propertyText.c_str());
					}
					else {
						fprintf(fout, "Property=0x%X\n", out);
					}
					// MoveMask DWORD
					out = ReadInt(in);
					fprintf(fout, "MoveMask=%i\n", out);
					// SizeXYZ FLOAT[3]
					for (int i = 0; i < 3; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 3);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "SizeXYZ=%s\n", obuffer);
					// MaxHP DWORD
					out = ReadInt(in);
					fprintf(fout, "MaxHP=%i\n", out);
					// MaxSpeed FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "MaxSpeed=%s\n", obuffer);
					// MaxZSpeed FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "MaxZSpeed=%s\n", obuffer);
					// Acceleration FLOAT[2]
					for (int i = 0; i < 2; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 2);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Acceleration=%s\n", obuffer);
					// RotationPeridod FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "RotationPeriod=%s\n", obuffer);
					// NWeapon DWORD
					out = ReadInt(in);
					fprintf(fout, "NWeapon=%i\n", out);
					// DeathRange FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "DeathRange=%s\n", obuffer);
					// DeathDamage DWORD
					out = ReadInt(in);
					fprintf(fout, "DeathDamage=%i\n", out);
					// LinkCoor FLOAT[3]
					for (int i = 0; i < 3; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 3);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "LinkCoor=%s\n", obuffer);
					// LinkVid DWORD
					out = ReadInt(in);
					fprintf(fout, "LinkVid=%i\n", out);
					// TopZ FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "TopZ=%s\n", obuffer);
					// ForMoveUpDownZ FLOAT[2]
					for (int i = 0; i < 2; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 2);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
					// LifeTime DWORD
					out = ReadInt(in);
					fprintf(fout, "LifeTime=%i\n", out);
					// Reserved CHAR[16]
					arrayf[0] = ReadFloat(in);
					arrayf[1] = ReadFloat(in);
					arrayf[2] = ReadFloat(in);
					arrayf[3] = ReadFloat(in);
					fprintf(fout, "Reserved=\n");
					// NoDir DWORD
					out = ReadInt(in);
					fprintf(fout, "NoDir=%i\n", out);
					// NoFrame DWORD[17]
					{
						for (int i = 0; i < 17; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "NoFrame=%s\n", obuffer);
					// SFX DWORD[17]
					{
						for (int i = 0; i < 17; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "SFX=%s\n", obuffer);
					// FrameSpeed DWORD[17]
					{
						for (int i = 0; i < 17; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "FrameSpeed=%s\n", obuffer);
					// ChildX FLOAT[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ChildX=%s\n", obuffer);
					// ChildY FLOAT[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ChildY=%s\n", obuffer);
					// ChildZ FLOAT[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ChildZ=%s\n", obuffer);
					// ChildVid DWORD[17]
					{
						for (int i = 0; i < 17; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ChildVid=%s\n", obuffer);
					// NoChild DWORD[17]
					{
						for (int i = 0; i < 17; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 17);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "NoChild=%s\n", obuffer);
					// GammaRGBA DWORD[4]
					{
						for (int i = 0; i < 4; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 4);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "GammaRGBA=%s\n", obuffer);
					// ScaleXYZ FLOAT[3]
					for (int i = 0; i < 3; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 3);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ScaleXYZ=%s\n", obuffer);
					// VidName STRING
					ReadString(in, fout, "VidName");
					fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
					fprintf(fout, "\n");
					fclose(fout); // Закрытие файла fout
				}

				// Read Weapon section
				copyFileContent("data\\WEAP\\gen1_WEAP.ini", "unpacked_inis\\WEAP.ini");
				//
				if (activateCharPadFlag)
				{
					char pad;
					fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
				}
				// WEAP Header
				out = ReadInt(in);
				printf("OK: WEAP Header found\n", out);
				if (!out == 'WEAP')
				{
					printf("ERROR: WEAP header not found! \n");
					return 1;
				}
				out = ReadInt(in); // Section size
				out = ReadInt(in); // unk1
				out = ReadInt(in); // unk2
				int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
				printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
				for (int i = 0; i < amountOfWEAPs; i++)
				{
					out = ReadInt(in); // NWeapon Size
					fout = fopen("unpacked_inis\\WEAP.ini", "a+");
					if (!fout)
					{
						printf("ERROR: Failed to open WEAP.ini file!\n");
						return 1;
					}
					fprintf(fout, ";-------------------------%03d\n", i);
					// SpriteType DWORD
					out = ReadInt(in);
					string spriteTypeText = GetSpriteTypeText(out);
					if (!spriteTypeText.empty()) {
						fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
					}
					else {
						fprintf(fout, "SpriteType=%i\n", out);
					}
					// Property DWORD
					out = ReadInt(in);
					string propertyText = GetNWeaponPropertyText(out);
					if (!propertyText.empty()) {
						fprintf(fout, "Property=%s\n", propertyText.c_str());
					}
					else {
						fprintf(fout, "Property=0x%X\n", out);
					}
					// Length Float
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Length=%s\n", obuffer);
					// Weight Float
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Weight=%s\n", obuffer);
					// Power Float
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Power=%s\n", obuffer);
					// DetectRange Float
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "DetectRange=%s\n", obuffer);
					// BattleRange Float
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "BattleRange=%s\n", obuffer);
					// WeaponAim Float
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "WeaponAim=%s\n", obuffer);
					// ReloadTime DWORD
					out = ReadInt(in);
					fprintf(fout, "ReloadTime=%i\n", out);
					// BuildTime DWORD
					out = ReadInt(in);
					fprintf(fout, "BuildTime=%i\n", out);
					// MaxAmmo DWORD
					out = ReadInt(in);
					fprintf(fout, "MaxAmmo=%i\n", out);
					// DefaultArmy DWORD
					out = ReadInt(in);
					fprintf(fout, "DefaultArmy=%i\n", out);
					// DefaultBehave DWORD
					out = ReadInt(in);
					string DefaultBehaveText = GetDefaultBehaveText(out);
					if (!DefaultBehaveText.empty()) {
						fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
					}
					else {
						fprintf(fout, "DefaultBehave=%i\n", out);
					}
					// Icon DWORD
					out = ReadInt(in);
					fprintf(fout, "Icon=%i\n", out);
					// EnemyRating DWORD
					out = ReadInt(in);
					fprintf(fout, "EnemyRating=%i\n", out);
					// DeadZone Float
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "DeadZone=%s\n", obuffer);
					// Period DWORD
					out = ReadInt(in);
					fprintf(fout, "Period=%i\n", out);
					// Time[8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Time=%s\n", obuffer);
					// GammaR [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "GammaR=%s\n", obuffer);
					// GammaG [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "GammaG=%s\n", obuffer);
					// GammaB [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "GammaB=%s\n", obuffer);
					// GammaA [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "GammaA=%s\n", obuffer);
					// ScaleX [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ScaleX=%s\n", obuffer);
					// ScaleY [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ScaleY=%s\n", obuffer);
					// ScaleZ [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ScaleZ=%s\n", obuffer);
					// ShiftX [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ShiftX=%s\n", obuffer);
					// ShiftY [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ShiftY=%s\n", obuffer);
					// ShiftZ [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ShiftZ=%s\n", obuffer);
					// DirectionX [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "DirectionX=%s\n", obuffer);
					// DirectionY [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "DirectionY=%s\n", obuffer);
					// DirectionZ [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "DirectionZ=%s\n", obuffer);
					// FrameSpeed [8] DWORD
					{
						for (int i = 0; i < 8; ++i)
						{
							arrayi[i] = ReadInt(in);
						}

						std::string formattedOutput = processIntValues(arrayi, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "FrameSpeed=%s\n", obuffer);
					// Speed [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Speed=%s\n", obuffer);
					// ZSpeed [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 8);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "ZSpeed=%s\n", obuffer);
					fprintf(fout, "\n");
					fclose(fout); // fout file close
				}

				// Read CNST section
				copyFileContent("data\\CNST\\gen1_CNST.ini", "unpacked_inis\\CNST.ini");
				// CNST Header
				out = ReadInt(in);
				printf("OK: CNST Header found\n", out);
				if (!out == 'CNST')
				{
					printf("ERROR: CNST header not found! \n");
					return 1;
				}
				out = ReadInt(in); // unk1
				out = ReadInt(in); // unk2
				out = ReadInt(in); // unk3
				out = ReadInt(in); // unk4
				out = ReadInt(in); // Section size
				{
					fout = fopen("unpacked_inis\\CNST.ini", "a+");
					if (!fout)
					{
						printf("ERROR: Failed to open CNST.ini file!\n");
						return 1;
					}
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Gravitation=%s\n", obuffer);
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "Gravitation2=%s\n", obuffer);
					//
					out = ReadInt(in);
					fprintf(fout, "RepairSpeed=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "AmmoReloadTime=%i\n", out);
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "PatrolRadius=%s\n", obuffer);
					//
					out = ReadInt(in);
					fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "DebugMode=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "MouseTipsTime=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "RepairSettingMineTime=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "SelectUnitGamma=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "AttackUnitGamma=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "LightedUnitGamma=%i\n", out);
					//
					out = ReadInt(in);
					sprintf(obuffer, "0x%X", out);
					fprintf(fout, "NukeForBirth=%s\n", obuffer);
					//
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}

					{
						std::string formattedOutput = processFloatValues(arrayf, 1);
						snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
					}
					fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
					//
					out = ReadInt(in);
					fprintf(fout, "MessageStartDelay=%i\n", out);
					//
					printf("OK: Reading CNST Section\n");
					fclose(fout); // Закрытие файла fout
				}

				// Read SFX Section
				copyFileContent("data\\SFX\\non_extSFX.ini", "unpacked_inis\\SFX.ini");
				out = ReadInt(in);
				printf("OK: SFX Header found\n", out);
				if (!out == 'SFX ')
				{
					printf("ERROR: SFX header not found! \n");
					return 1;
				}
				out = ReadInt(in); // Section size
				out = ReadInt(in); // unk1
				out = ReadInt(in); // unk2
				int amountOfWAVs = ReadInt(in); // amountOfWAVs
				printf("OK: Reading %d WAV`s\n", amountOfWAVs);
				for (int i = 0; i < amountOfWAVs; i++)
				{
					out = ReadInt(in); // Size
					fout = fopen("unpacked_inis\\SFX.ini", "a+");
					if (!fout)
					{
						printf("ERROR: Failed to open SFX.ini file!\n");
						return 1;
					}
					fprintf(fout, ";-------------------------%03d\n", i);
					out = ReadByte(in); // Priority
					fprintf(fout, "Priority=%i\n", out);
					// Wave
					std::string arraySFX[8]; // Массив для хранения путей до файлов

					// Считываем 8 строк для путей до файлов
					for (int i = 0; i < 8; ++i) {
						if (!feof(in)) {
							arraySFX[i] = ReadStringNoRTN(in);
						}
					}
					// Формируем строку с путями до файлов
					std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
						arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

					fprintf(fout, "Wave=%s\n", obuffer.c_str());
					fprintf(fout, "\n");
					fclose(fout); // Закрываем файл fout
				}
			}
		}

				// Theseus PC version
				else if (mode == "theseus_pc")
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\gen1_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClassText(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjectsPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// MoveMask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Reserved CHAR[16]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeaponPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "WeaponAim=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehaveText(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen1_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "PatrolRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\gen1.1_extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFXPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 1: World
				else if (mode == "as1world")
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\asworld_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClassText(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjectsPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Property2 DWORD
							out = ReadInt(in);
							string property2Text = GetWorldObjectsProperty2Text(out);
							if (!property2Text.empty()) {
								fprintf(fout, "Property2=%s\n", property2Text.c_str());
							}
							else {
								fprintf(fout, "Property2=0x%X\n", out);
							}
							// Property3 DWORD
							out = ReadInt(in);
							string property3Text = GetWorldObjectsProperty3Text(out);
							if (!property3Text.empty()) {
								fprintf(fout, "Property3=%s\n", property3Text.c_str());
							}
							else {
								fprintf(fout, "Property3=0x%X\n", out);
							}
							// Reserved CHAR[8]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}

							std::string formattedOutput = processIntValues(arrayi, 17);
							snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeaponPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehaveText(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFXPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Volume
							out = ReadInt(in);
							fprintf(fout, "Volume=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Zombie Shooter 1
				else if (mode == "zs1")				
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\gen1.1_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClassText(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjectsPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Reserved CHAR[16]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeaponPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehaveText(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFXPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Volume
							out = ReadInt(in);
							fprintf(fout, "Volume=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Zombie Shooter 1 Mobile
				else if (mode == "zs1_mobile")
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\zs1mobile_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClassText(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjectsPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Property2 DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property2=%s\n", obuffer);
							// Reserved CHAR[12]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteTypeText(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeaponPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehaveText(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFXPropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Volume
							out = ReadInt(in);
							fprintf(fout, "Volume=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 2 Gold / Vengeance
				else if (mode == "as2_original")				
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\gen2_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClass2Text(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjects2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							{
								for (int i = 0; i < 2; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Reserved CHAR[16]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeapon2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehave2Text(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\gen1.1_extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFX2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 2 Reloaded, Conscription, Zombie Shooter 2 Teaser, Objects Extended Project (Old versions before 1.1.0.6)
				else if (mode == "as2_addons")
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\gen2_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClass2Text(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjects2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							{
								for (int i = 0; i < 2; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Reserved CHAR[16]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeapon2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehave2Text(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFX2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Volume
							out = ReadInt(in);
							fprintf(fout, "Volume=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Zombie Shooter 2 / Alien Shooter: Revisited
				else if (mode == "zs2_engine")
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\zs2_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClass2Text(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjects2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							{
								for (int i = 0; i < 2; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Reserved CHAR[16]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[5]
							{
								for (int i = 0; i < 5; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 5);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeapon2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehave2Text(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFX2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Volume
							out = ReadInt(in);
							fprintf(fout, "Volume=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 2 Legend & TD (Steam and Mobile), Alien Shooter 2 New Era, Alien Shooter 2 Reloaded (Mobile)
				else if (mode == "as2legend_engine")
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\OBJ\\legend_OBJ.ini", "unpacked_inis\\OBJ.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DATA Header found\n", out);
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClass2Text(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjects2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							{
								for (int i = 0; i < 2; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Property2 DWORD
							out = ReadInt(in);
							string property2Text = GetLegendObjectsProperty2Text(out);
							if (!property2Text.empty()) {
								fprintf(fout, "Property2=%s\n", property2Text.c_str());
							}
							else {
								fprintf(fout, "Property2=0x%X\n", out);
							}
							// Reserved CHAR[12]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
						}
						// WEAP Header
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeapon2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehave2Text(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFX2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Volume
							out = ReadInt(in);
							fprintf(fout, "Volume=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Objects Extended Project - new structure
				else if (mode == "oe_engine")
				{
					validMode = true;
					CreateDirectoryA("unpacked_inis", NULL);
					copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
					{
						//header
						out = ReadInt(in);
						printf("OK: RES Header found\n", out);
						if (!out == 'RES ')
						{
							printf("ERROR: Could not find RES header! \n");
							fclose(in);
							return 1;
						}

						//size
						out = ReadInt(in);
						printf("OK: RES Size %d bytes\n", out);

						//data
						out = ReadInt(in);
						printf("OK: DB Header found\n", out);
						if (!out == 'DB  ')
						{
							printf("ERROR: Could not find DB header! \n");
							fclose(in);
							return 1;
						}

						// Read CNST section
						out = ReadInt(in);
						printf("OK: CNST Header found\n", out);
						if (!out == 'CNST')
						{
							printf("ERROR: CNST header not found! \n");
							return 1;
						}
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						out = ReadInt(in); // unk3
						out = ReadInt(in); // unk4
						out = ReadInt(in); // Section size
						{
							fout = fopen("unpacked_inis\\CNST.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open CNST.ini file!\n");
								return 1;
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Friction=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoMillisecondsInSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DebugMode=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoRepairTimeInSeconds=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MouseTipsTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DepoAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MasterAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "FortCannonsAutoAddHpPerSecond=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSettingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairDestroyingMineTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DirijbanAmmoReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "SelectUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AttackUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "LightedUnitGamma=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "NukeForBirth=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
						out = ReadInt(in);
						printf("OK: WEAP Header found\n", out);
						if (!out == 'WEAP')
						{
							printf("ERROR: WEAP header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
						printf("OK: Reading %d NWeapon`s\n", amountOfWEAPs);
						for (int i = 0; i < amountOfWEAPs; i++)
						{
							out = ReadInt(in); // NWeapon Size
							fout = fopen("unpacked_inis\\WEAP.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open WEAP.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							//
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							//
							out = ReadInt(in);
							string propertyText = GetNWeapon2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Length=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "AimRadius=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "FireInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "MaxAmmo=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "ReloadTimeInVolley=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "BuildTime=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "DefaultArmy=%i\n", out);
							//
							out = ReadInt(in);
							string DefaultBehaveText = GetDefaultBehave2Text(out);
							if (!DefaultBehaveText.empty()) {
								fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
							}
							else {
								fprintf(fout, "DefaultBehave=%i\n", out);
							}
							//
							out = ReadInt(in);
							fprintf(fout, "Icon=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							//
							out = ReadInt(in);
							fprintf(fout, "EnemyRating=%i\n", out);
							//
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Time=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							{
								for (int i = 0; i < 8; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 8);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						//obj
						copyFileContent("data\\OBJ\\gen2_OBJ.ini", "unpacked_inis\\OBJ.ini");
						out = ReadInt(in);
						printf("OK: OBJ Header found\n", out);
						if (!out == 'OBJ ')
						{
							printf("ERROR: Could not find OBJ header! \n");
							fclose(in);
							return 1;
						}

						out = ReadInt(in); // Section Size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
						printf("OK: Reading %d NVid`s\n", amountOfNVIDs);
						for (int _ = 0; _ < amountOfNVIDs; _++)
						{
							out = ReadInt(in); // NVid Size
							out = ReadInt(in); // NVid Number
							fout = fopen("unpacked_inis\\OBJ.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open OBJ.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------------------------------- \n");
							fprintf(fout, "NVid=%i\n", out);
							// Name STRING
							ReadString(in, fout, "Name");
							// SpriteType DWORD
							out = ReadInt(in);
							string spriteTypeText = GetSpriteType2Text(out);
							if (!spriteTypeText.empty()) {
								fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
							}
							else {
								fprintf(fout, "SpriteType=%i\n", out);
							}
							// SpriteClass DWORD
							out = ReadInt(in);
							string spriteClassText = GetSpriteClass2Text(out);
							if (!spriteClassText.empty()) {
								fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
							}
							else {
								fprintf(fout, "SpriteClass=%i\n", out);
							}
							// Property DWORD
							out = ReadInt(in);
							string propertyText = GetObjects2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							{
								for (int i = 0; i < 2; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 1);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 2);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
							// LifeTime DWORD
							out = ReadInt(in);
							fprintf(fout, "LifeTime=%i\n", out);
							// Reserved CHAR[16]
							arrayf[0] = ReadFloat(in);
							arrayf[1] = ReadFloat(in);
							arrayf[2] = ReadFloat(in);
							arrayf[3] = ReadFloat(in);
							fprintf(fout, "Reserved=\n");
							// NoDir DWORD
							out = ReadInt(in);
							fprintf(fout, "NoDir=%i\n", out);
							// NoFrame DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							{
								for (int i = 0; i < 17; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 17);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							{
								for (int i = 0; i < 4; ++i)
								{
									arrayi[i] = ReadInt(in);
								}

								std::string formattedOutput = processIntValues(arrayi, 4);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}

							{
								std::string formattedOutput = processFloatValues(arrayf, 3);
								snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
							}
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";stnd stp mov strt lrot rrot op hit fgt sal sto lnk clsh wnd birth death explode\n");
							fprintf(fout, "\n");
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
						//
						if (activateCharPadFlag)
						{
							char pad;
							fread(&pad, sizeof(char), 1, in);
						}
						// SFX Header
						out = ReadInt(in);
						printf("OK: SFX Header found\n", out);
						if (!out == 'SFX ')
						{
							printf("ERROR: SFX header not found! \n");
							return 1;
						}
						out = ReadInt(in); // Section size
						out = ReadInt(in); // unk1
						out = ReadInt(in); // unk2
						int amountOfWAVs = ReadInt(in); // amountOfWAVs
						printf("OK: Reading %d WAV`s\n", amountOfWAVs);
						for (int i = 0; i < amountOfWAVs; i++)
						{
							out = ReadInt(in); // Size
							fout = fopen("unpacked_inis\\SFX.ini", "a+");
							if (!fout)
							{
								printf("ERROR: Failed to open SFX.ini file!\n");
								return 1;
							}
							fprintf(fout, ";-------------------------%03d\n", i);
							// Property
							out = ReadInt(in);
							string propertyText = GetSFX2PropertyText(out);
							if (!propertyText.empty()) {
								fprintf(fout, "Property=%s\n", propertyText.c_str());
							}
							else {
								fprintf(fout, "Property=0x%X\n", out);
							}
							// Priority
							out = ReadByte(in);
							fprintf(fout, "Priority=%i\n", out);
							// Volume
							out = ReadInt(in);
							fprintf(fout, "Volume=%i\n", out);
							// Wave
							std::string arraySFX[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // Массив для хранения путей до файлов

							// Считываем 8 строк для путей до файлов
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// Формируем строку с путями до файлов
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							fprintf(fout, "\n");
							fclose(fout); // Закрываем файл fout
						}
					}
				}

		else
		{
			cout << "Invalid file mode: " << mode << endl;
			cout << endl;
			fclose(in);

			// Запрос повторного ввода режима
			cout << "Enter file mode: ";
			getline(cin, mode);
			cout << endl;

			in = fopen(filename.c_str(), "rb");
			if (!in)
			{
				cout << "Failed to open file: " << filename << endl;
				cout << "Press Enter to try again or enter 'q' to quit...";
				cout << endl;
				string userInput;
				getline(cin, userInput);
				if (userInput == "q" || userInput == "Q")
					return 1;
				continue;
			}
		}
	}
	cout << endl;
	cout << filename << " has been unpacked into the 'unpacked_inis' folder." << endl;
	cout << endl;
	cout << "Press Enter to exit..." << endl;
	getchar();

	return 0;
}