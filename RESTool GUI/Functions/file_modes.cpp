#include "file_modes.h"
#include "file_functions.h"
#include "parsers/DefaultBehaveParser.h"
#include "parsers/NWeaponPropertyParser.h"
#include "parsers/ObjectsPropertyParser.h"
#include "parsers/SFXPropertyParser.h"
#include "parsers/SpriteClassParser.h"
#include "parsers/SpriteTypeParser.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <QDir>

int out;							// Output value
int arrayi[17];						// Maximum number of Int values ​​per line
float arrayf[17];					// Maximum number of Float values ​​per line
char obuffer[65535];				// Maximum buffer for values
char header[5];						// File header length
FILE* in;							// Opening a file in read mode
FILE* fout;							// Opening a file in write mode				

void FileUnpacker::processFileUnpackMode(const QString& resFilename, const QString& mode, bool alternativeModeEnabled)
{
	// Предложение активировать режим альтернативной распаковки
	QMessageBox::StandardButton alternativeModeAnswer = QMessageBox::question(
		nullptr, // Замените this на nullptr или передайте указатель на соответствующий QWidget
		"Alternative Unpacking Mode",
		"Do you want to activate the alternative unpacking mode?",
		QMessageBox::Yes | QMessageBox::No
	);

	// Проверка ответа пользователя
	if (alternativeModeAnswer == QMessageBox::Yes)
	{
		alternativeModeEnabled = true;
	}
	else
	{
		alternativeModeEnabled = false;
	}

	// Alien Shooter 1 Engine
	if (mode == "as1_engine")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

			// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						copyFileContent("data\\OBJ\\gen1_OBJ.ini", "unpacked_inis\\OBJ.ini");
						qDebug() << "OK: OBJ Header found";
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}
			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				copyFileContent("data\\WEAP\\gen1_WEAP.ini", "unpacked_inis\\WEAP.ini");
				qDebug() << "OK: WEAP Header found";
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetNWeaponPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				// Weight Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				// Power Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Power=%s\n", obuffer);
				// DetectRange Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				// BattleRange Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				// WeaponAim Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehaveText(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // fout file close
			}
			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen1_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}
			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\non_extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				out = ReadByte(in); // Priority
				fprintf(fout, "Priority=%i\n", out);
				// Wave
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}

	// Theseus PC version
	else if (mode == "theseus_pc")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\gen1_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}
			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");

				fclose(fout); // Закрытие файла fout
			}
			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen1_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				//
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeaponPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Power=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehaveText(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen1_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				//
				fclose(fout); // Закрытие файла fout
			}
			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\gen1.1_extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFXPropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}
	
	// Alien Shooter 1: World
	else if (mode == "as1world")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

			// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
					qDebug() << "OK: OBJ Header found";
					copyFileContent("data/OBJ/asworld_OBJ.ini", "unpacked_inis/OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
				// LifeTime DWORD
				out = ReadInt(in);
				fprintf(fout, "LifeTime=%i\n", out);
				// ext1Property DWORD
				out = ReadInt(in);
				std::string ext1Property = GetExt1PropertyText(out);
				if (!ext1Property.empty()) {
					fprintf(fout, "ext1Property=%s\n", ext1Property.c_str());
				}
				else {
					fprintf(fout, "ext1Property=0x%X\n", out);
				}
				// ext2Property DWORD
				out = ReadInt(in);
				std::string ext2Property = GetExt2PropertyText(out);
				if (!ext2Property.empty()) {
					fprintf(fout, "ext2Property=%s\n", ext2Property.c_str());
				}
				else {
					fprintf(fout, "ext2Property=0x%X\n", out);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}

			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				//
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeaponPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehaveText(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}

			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\NewEngineAS1_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "CriticalHitMulti=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BrutalDeathHPMulti=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}
			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFXPropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}

	// Zombie Shooter 1
	else if (mode == "zs1")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\gen1.1_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}
			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeaponPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehaveText(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
				// Time[8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}
			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				//
				fclose(fout); // Закрытие файла fout
			}
			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFXPropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}
	
	// Zombie Shooter 1 Mobile
	else if (mode == "zs1_mobile")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\zs1mobile_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
				// LifeTime DWORD
				out = ReadInt(in);
				fprintf(fout, "LifeTime=%i\n", out);
				// ext1Property DWORD
				out = ReadInt(in);
				std::string ext1Property = GetExt1PropertyText(out);
				if (!ext1Property.empty()) {
					fprintf(fout, "ext1Property=%s\n", ext1Property.c_str());
				}
				else {
					fprintf(fout, "ext1Property=0x%X\n", out);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}

			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				//
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeaponPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehaveText(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}

			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\NewEngineAS1_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "CriticalHitMulti=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BrutalDeathHPMulti=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFXPropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}
	
	// Alien Shooter 2 Gold / Vengeance
	else if (mode == "as2_original")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\gen2_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClass2Text(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjects2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathRange=%s\n", obuffer);
				// DeathDamageMinMax DWORD[2]
				{
					for (int i = 0; i < 2; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
				// DeathPush FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathPush=%s\n", obuffer);
				// LinkCoor FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}
			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				//
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeapon2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehave2Text(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}

			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\gen1.1_extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFX2PropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}
	
	// Alien Shooter 2 Reloaded, Conscription, Zombie Shooter 2 Teaser
	else if (mode == "as2_addons")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\gen2_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClass2Text(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjects2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathRange=%s\n", obuffer);
				// DeathDamageMinMax DWORD[2]
				{
					for (int i = 0; i < 2; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
				// DeathPush FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathPush=%s\n", obuffer);
				// LinkCoor FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}
			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				//
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeapon2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehave2Text(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}
			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFX2PropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}

	// Zombie Shooter 2 / Alien Shooter: Revisited
	else if (mode == "zs2_engine")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\zs2_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClass2Text(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjects2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathRange=%s\n", obuffer);
				// DeathDamageMinMax DWORD[2]
				{
					for (int i = 0; i < 2; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
				// DeathPush FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathPush=%s\n", obuffer);
				// LinkCoor FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[5]
				{
					for (int i = 0; i < 5; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 5, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}

			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				//
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeapon2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehave2Text(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}

			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFX2PropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}

	// Alien Shooter 2 Legend & TD (Steam and Mobile), Alien Shooter 2 New Era, Alien Shooter 2 Reloaded (Mobile)
	else if (mode == "as2legend_engine")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\legend_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClass2Text(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjects2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathRange=%s\n", obuffer);
				// DeathDamageMinMax DWORD[2]
				{
					for (int i = 0; i < 2; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
				// DeathPush FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathPush=%s\n", obuffer);
				// LinkCoor FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ForMoveUpDownZ=%s\n", obuffer);
				// LifeTime DWORD
				out = ReadInt(in);
				fprintf(fout, "LifeTime=%i\n", out);
				// ext1Property DWORD
				out = ReadInt(in);
				std::string ext1Property = GetExt1PropertyText(out);
				if (!ext1Property.empty()) {
					fprintf(fout, "ext1Property=%s\n", ext1Property.c_str());
				}
				else {
					fprintf(fout, "ext1Property=0x%X\n", out);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");

				fclose(fout); // Закрытие файла fout
			}

			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeapon2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehave2Text(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}

			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\NewEngineAS2_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "CriticalHitMulti=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BrutalDeathHPMulti=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				//
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFX2PropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}
	
	// Objects Extended Project - new structure
	else if (mode == "oe_engine")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DB") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DB header!");
					qDebug() << "ERROR: Could not find DB header!";
					return;
				}
				else {
					qDebug() << "OK: DB Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "CNST") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
						qDebug() << "ERROR: Could not find CNST header!";
						return;
					}
					else {
						qDebug() << "OK: CNST Header found";
						qDebug() << "OK: Reading CNST Section";
						copyFileContent("data\\CNST\\gen2_CNST.ini", "unpacked_inis\\CNST.ini");
					}
				}
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}

			// Read Weapon section
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen2_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				if (!fout)
					//
					fprintf(fout, ";-------------------------%03d\n", i);
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeapon2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehave2Text(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}

			// OBJ Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "OBJ ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
				qDebug() << "ERROR: Could not find OBJ header!";
				return;
			}
			else {
				qDebug() << "OK: OBJ Header found";
				copyFileContent("data\\OBJ\\gen2_OBJ.ini", "unpacked_inis\\OBJ.ini");
			}
			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";-------------------------------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClass2Text(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjects2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathRange=%s\n", obuffer);
				// DeathDamageMinMax DWORD[2]
				{
					for (int i = 0; i < 2; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
				// DeathPush FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeathPush=%s\n", obuffer);
				// LinkCoor FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);
			}
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFX2PropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}
	
	// Crazy Lunch
	else if (mode == "crazylunch")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\gen1_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}

			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\CrazyLunch_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				//
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteType2Text(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				//
				out = ReadInt(in);
				std::string propertyText = GetNWeapon2PropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehave2Text(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
				}
				//
				out = ReadInt(in);
				fprintf(fout, "Icon=%i\n", out);
				// Reserved[8]
				arrayf[0] = ReadFloat(in);
				arrayf[1] = ReadFloat(in);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DeadZone=%s\n", obuffer);
				//
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // Закрытие файла fout
			}

			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen1_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				//
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\non_extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				out = ReadByte(in); // Priority
				fprintf(fout, "Priority=%i\n", out);
				// Wave
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}

	// Chacks Temple
	else if (mode == "chackstemple")
	{
		in = fopen(resFilename.toStdString().c_str(), "rb");
		if (in == nullptr)
		{
			QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
			qDebug() << "Failed to open the file!";
			return;
		}

		QString folderPath = QDir::currentPath() + "/unpacked_inis";
		QDir dir;
		if (!dir.exists(folderPath))
		{
			if (!dir.mkpath(folderPath))
			{
				QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
				qDebug() << "Failed to create folder 'unpacked_inis'";
				return;
			}
		}

		// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\gen1_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}

			// Read Weapon section
			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen1_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetNWeaponPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				// Weight Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				// Power Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Power=%s\n", obuffer);
				// DetectRange Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				// BattleRange Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				// WeaponAim Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				std::string DefaultBehaveText = GetDefaultBehaveText(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				fprintf(fout, "Time=\t\t%s\n", obuffer);
				// GammaR [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaR=\t\t%s\n", obuffer);
				// GammaG [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaG=\t\t%s\n", obuffer);
				// GammaB [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaB=\t\t%s\n", obuffer);
				// GammaA [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaA=\t\t%s\n", obuffer);
				// ScaleX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleX=\t\t%s\n", obuffer);
				// ScaleY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleY=\t\t%s\n", obuffer);
				// ScaleZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleZ=\t\t%s\n", obuffer);
				// ShiftX [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftX=\t\t%s\n", obuffer);
				// ShiftY [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftY=\t\t%s\n", obuffer);
				// ShiftZ [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ShiftZ=\t\t%s\n", obuffer);
				// DirectionX [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionX=\t%s\n", obuffer);
				// DirectionY [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionY=\t%s\n", obuffer);
				// DirectionZ [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DirectionZ=\t%s\n", obuffer);
				// FrameSpeed [8] DWORD
				{
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "FrameSpeed=\t%s\n", obuffer);
				// Speed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Speed=\t\t%s\n", obuffer);
				// ZSpeed [8] Float
				for (int i = 0; i < 8; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 8);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ZSpeed=\t\t%s\n", obuffer);
				fclose(fout); // fout file close
			}

			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen1_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Gravitation=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
				//
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout); // Закрытие файла fout
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// Property
				out = ReadInt(in);
				std::string propertyText = GetSFXPropertyText(out);
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
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				// ForceFeedBack
				const int forceFeedBackNumStrings = 8;
				std::string forceFeedBackBuffer = readPathsFromFile(in, forceFeedBackNumStrings);
				fprintf(fout, "ForceFeedBack=%s\n", forceFeedBackBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}

	// Locoland (SteamLand or Road to Khon-Ka-Du)
	else if (mode == "locoland") {
		{
			in = fopen(resFilename.toStdString().c_str(), "rb");
			if (in == nullptr)
			{
				QMessageBox::critical(nullptr, "Error", "Failed to open the file!");
				qDebug() << "Failed to open the file!";
				return;
			}

			QString folderPath = QDir::currentPath() + "/unpacked_inis";
			QDir dir;
			if (!dir.exists(folderPath))
			{
				if (!dir.mkpath(folderPath))
				{
					QMessageBox::critical(nullptr, "Error", "Failed to create folder 'unpacked_inis'");
					qDebug() << "Failed to create folder 'unpacked_inis'";
					return;
				}
			}

			// RES Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "RES ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find RES header!");
				qDebug() << "ERROR: Could not find RES header!";
				return;
			}
			else {
				qDebug() << "OK: RES Header found";

				// size
				out = ReadInt(in);
				qDebug() << "OK: RES Size" << out << "bytes";

				// DATA Header
				fread(header, sizeof(char), 4, in);
				header[4] = '\0';

				if (strcmp(header, "DATA") != 0) {
					QMessageBox::critical(nullptr, "Error", "Could not find DATA header!");
					qDebug() << "ERROR: Could not find DATA header!";
					return;
				}
				else {
					qDebug() << "OK: DATA Header found";

					// OBJ Header
					fread(header, sizeof(char), 4, in);
					header[4] = '\0';

					if (strcmp(header, "OBJ ") != 0) {
						QMessageBox::critical(nullptr, "Error", "Could not find OBJ header!");
						qDebug() << "ERROR: Could not find OBJ header!";
						return;
					}
					else {
						qDebug() << "OK: OBJ Header found";
						copyFileContent("data\\OBJ\\gen0_OBJ.ini", "unpacked_inis\\OBJ.ini");
					}
				}
			}

			out = ReadInt(in); // Section Size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfNVIDs = ReadInt(in); // NumbersOfNVids
			qDebug() << "OK: Reading" << amountOfNVIDs << "NVid`s";
			for (int _ = 0; _ < amountOfNVIDs; _++)
			{
				out = ReadInt(in); // NVid Size
				out = ReadInt(in); // NVid Number
				fout = fopen("unpacked_inis\\OBJ.ini", "a+");
				//
				fprintf(fout, ";------------------------- \n");
				fprintf(fout, "NVid=%i\n", out);
				// Name STRING
				ReadString(in, fout, "Name");
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// SpriteClass DWORD
				out = ReadInt(in);
				std::string spriteClassText = GetSpriteClassText(out);
				if (!spriteClassText.empty()) {
					fprintf(fout, "SpriteClass=%s\n", spriteClassText.c_str());
				}
				else {
					fprintf(fout, "SpriteClass=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetObjectsPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxSpeed=%s\n", obuffer);
				// MaxZSpeed FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "MaxZSpeed=%s\n", obuffer);
				// Acceleration FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Acceleration=%s\n", obuffer);
				// RotationPeridod FLOAT
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "TopZ=%s\n", obuffer);
				// ForMoveUpDownZ FLOAT[2]
				for (int i = 0; i < 2; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 2, false);
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
				fprintf(fout, "NoFrame=\t%s\n", obuffer);
				// SFX DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "SFX=\t\t%s\n", obuffer);
				// FrameSpeed DWORD[17]

				// ChildX FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildX=\t\t%s\n", obuffer);
				// ChildY FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildY=\t\t%s\n", obuffer);
				// ChildZ FLOAT[17]
				for (int i = 0; i < 17; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildZ=\t\t%s\n", obuffer);
				// ChildVid DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ChildVid=\t%s\n", obuffer);
				// NoChild DWORD[17]
				{
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 17);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "NoChild=\t%s\n", obuffer);
				// GammaRGBA DWORD[4]
				{
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}

					std::string formattedOutput = processIntValues(arrayi, 4, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "GammaRGBA=\t%s\n", obuffer);
				// ScaleXYZ FLOAT[3]
				for (int i = 0; i < 3; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 3, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "ScaleXYZ=\t%s\n", obuffer);
				// VidName STRING
				ReadString(in, fout, "VidName");
				fprintf(fout, ";       	stnd  	stp  	mov  	strt 	lrot 	rrot  	op   	hit 	fgt  	sal  	sto 	vClsh 	clsh 	wnd 	birth 	death 	explode\n");
				fclose(fout); // Закрытие файла fout
			}

			if (alternativeModeEnabled)
			{
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
			}
			// Read CNST section
			// CNST Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "CNST") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find CNST header!");
				qDebug() << "ERROR: Could not find CNST header!";
				return;
			}
			else {
				qDebug() << "OK: CNST Header found";
				qDebug() << "OK: Reading CNST Section";
				copyFileContent("data\\CNST\\gen0_CNST.ini", "unpacked_inis\\CNST.ini");
			}
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			out = ReadInt(in); // unk3
			out = ReadInt(in); // unk4
			out = ReadInt(in); // Section size
			{
				fout = fopen("unpacked_inis\\CNST.ini", "a+");
				//
				out = ReadInt(in);
				fprintf(fout, "MaxScrollSpeedX=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "MaxScrollSpeedY=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "Gravitation=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "Gravitation2=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "RepairSpeed=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "AmmoReloadTime=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "RailRepairSpeed=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "MasterRepairSpeed=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "PatrolRadius=%i\n", out);
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
				sprintf(obuffer, "0x%X", out);
				fprintf(fout, "SelectUnitGamma=%s\n", obuffer);
				//
				out = ReadInt(in);
				sprintf(obuffer, "0x%X", out);
				fprintf(fout, "AttackUnitGamma=%s\n", obuffer);
				//
				out = ReadInt(in);
				sprintf(obuffer, "0x%X", out);
				fprintf(fout, "LightedUnitGamma=%s\n", obuffer);
				//
				out = ReadInt(in);
				sprintf(obuffer, "0x%X", out);
				fprintf(fout, "NukeForBirth=%s\n", obuffer);
				//
				out = ReadInt(in);
				fprintf(fout, "SafeClashSpeed=%i\n", out);
				//
				out = ReadInt(in);
				fprintf(fout, "MessageStartDelay=%i\n", out);
				fclose(fout);
			}

			// Read Weapon section
			// WEAP Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "WEAP") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find WEAP header!");
				qDebug() << "ERROR: Could not find WEAP header!";
				return;
			}
			else {
				qDebug() << "OK: WEAP Header found";
				copyFileContent("data\\WEAP\\gen0_WEAP.ini", "unpacked_inis\\WEAP.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWEAPs = ReadInt(in); // amountOfWEAPs
			qDebug() << "OK: Reading" << amountOfWEAPs << "NWeapon`s";
			for (int i = 0; i < amountOfWEAPs; i++)
			{
				out = ReadInt(in); // NWeapon Size
				fout = fopen("unpacked_inis\\WEAP.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				// SpriteType DWORD
				out = ReadInt(in);
				std::string spriteTypeText = GetSpriteTypeText(out);
				if (!spriteTypeText.empty()) {
					fprintf(fout, "SpriteType=%s\n", spriteTypeText.c_str());
				}
				else {
					fprintf(fout, "SpriteType=%i\n", out);
				}
				// Property DWORD
				out = ReadInt(in);
				std::string propertyText = GetNWeaponPropertyText(out);
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
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Length=%s\n", obuffer);
				// Weight Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Weight=%s\n", obuffer);
				// Power Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "Power=%s\n", obuffer);
				// DetectRange Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "DetectRange=%s\n", obuffer);
				// BattleRange Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
					snprintf(obuffer, sizeof(obuffer), "%s", formattedOutput.c_str());
				}
				fprintf(fout, "BattleRange=%s\n", obuffer);
				// WeaponAim Float
				for (int i = 0; i < 1; ++i)
				{
					arrayf[i] = ReadFloat(in);
				}

				{
					std::string formattedOutput = processFloatValues(arrayf, 1, false);
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
				// Icon DWORD
				out = ReadInt(in);
				fprintf(fout, "Icon=%i\n", out);
				// DefaultArmy DWORD
				out = ReadInt(in);
				fprintf(fout, "DefaultArmy=%i\n", out);
				// DefaultBehave DWORD
				out = ReadInt(in);
				std::string DefaultBehaveText = GetDefaultBehaveText(out);
				if (!DefaultBehaveText.empty()) {
					fprintf(fout, "DefaultBehave=%s\n", DefaultBehaveText.c_str());
				}
				else {
					fprintf(fout, "DefaultBehave=0x%X\n", out);
				}
				// EnemyRating DWORD
				out = ReadInt(in);
				fprintf(fout, "EnemyRating=%i\n", out);
				// DeadZone
				out = ReadInt(in);
				fprintf(fout, "DeadZone=%i\n", out);
				// Period
				out = ReadInt(in);
				fprintf(fout, "Period=%i\n", out);
				fclose(fout); // fout file close
			}

			// Read SFX Section
			// SFX Header
			fread(header, sizeof(char), 4, in);
			header[4] = '\0';

			if (strcmp(header, "SFX ") != 0) {
				QMessageBox::critical(nullptr, "Error", "Could not find SFX header!");
				qDebug() << "ERROR: Could not find SFX header!";
				return;
			}
			else {
				qDebug() << "OK: SFX Header found";
				copyFileContent("data\\SFX\\non_extSFX.ini", "unpacked_inis\\SFX.ini");
			}
			out = ReadInt(in); // Section size
			out = ReadInt(in); // unk1
			out = ReadInt(in); // unk2
			int amountOfWAVs = ReadInt(in); // amountOfWAVs
			qDebug() << "OK: Reading" << amountOfWAVs << "WAV`s";
			for (int i = 0; i < amountOfWAVs; i++)
			{
				out = ReadInt(in); // Size
				fout = fopen("unpacked_inis\\SFX.ini", "a+");
				//
				fprintf(fout, ";-------------------------%03d\n", i);
				out = ReadByte(in); // Priority
				fprintf(fout, "Priority=%i\n", out);
				// Wave
				const int waveNumStrings = 8;
				std::string waveBuffer = readPathsFromFile(in, waveNumStrings);
				fprintf(fout, "Wave=%s\n", waveBuffer.c_str());
				fclose(fout); // Закрываем файл fout
			}
		}
	}
}