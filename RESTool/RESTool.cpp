// RESTool.cpp : Defines the entry point for the console application.
// original idea by ermaccer. Complete code fix by romalu86

#include "stdafx.h"
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
	if (argc != 3)
	{
		printf("RESTool ver.1.5 by romalu86\n");
		printf("\n");
		printf("How to work:\n");
		printf("example: RESTool objects.res as1pad\n");
		printf("\n");
		printf("File modes:\n");
		printf("as1_pad - works with Alien Shooter 1 Steam, Alien Shooter 1 Last Hope Steam, Theseus Mobile\n");
		printf("as1_nonpad - works with Alien Shooter 1 - Old (No steam version)\n");
		printf("theseus_pc - works with Theseus PC\n");
		printf("as1world_pad - works with Alien Shooter 1 - World (mobile)\n");
		printf("as1world_nonpad - works with Alien Shooter 1 - World (mobile)\n");
		printf("zs1 - works with Zombie Shooter 1\n");
		printf("zs1_mobile - works with Zombie Shooter 1\n");
		printf("as2_original - works with Gold and Vengeance editions\n");
		printf("as2_addons - works with Reloaded, Conscription\n");
		printf("zs2_nonpad - works with Zombie Shooter 2 (Steam)\n");
		printf("zs2_pad - works with Zombie Shooter 2 (NonSteam)\n");
		printf("asr - works with Alien Shooter Revisited\n");
		printf("as2legend_pad - works with Alien Shooter 2 Legend & TD (Steam and Mobile)\n");
		printf("as2legend_nonpad - works with Alien Shooter 2 New Era (Steam) & Alien Shooter 2 Reloaded (Mobile)\n");
		printf("oe - works with Objects Extended Project\n");
		printf("oe1105 - works with Objects Extended Project (Old versions)\n");
		return 1;
	}

	int out;
	float arrayf[17];
	int arrayi[17];
	char obuffer[65535];
	FILE* in;
	FILE* fout;

	in = fopen(argv[1], "rb");
	if (in)
	{
				// Alien Shooter 1 Engine - with char pad in WEAP section
				if (strcmp("as1_pad", argv[2]) == 0)
		{
				copyFileContent("data\\OBJ\\gen1_OBJ.ini", "OBJ.ini");
			{
				// RES Header
				out = ReadInt(in);
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
				if (!out == 'DATA')
				{
					printf("ERROR: Could not find DATA header! \n");
					fclose(in);
					return 1;
				}

				// OBJ Header
				out = ReadInt(in);
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
					sprintf(obuffer, "%s", "OBJ.ini");
					fout = fopen(obuffer, "a+");
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
					sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
					fprintf(fout, "SizeXYZ=%s\n", obuffer);
					// MaxHP DWORD
					out = ReadInt(in);
					fprintf(fout, "MaxHP=%i\n", out);
					// MaxSpeed FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "MaxSpeed=%s\n", obuffer);
					// MaxZSpeed FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "MaxZSpeed=%s\n", obuffer);
					// Acceleration FLOAT[2]
					for (int i = 0; i < 2; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
					fprintf(fout, "Acceleration=%s\n", obuffer);
					// RotationPeridod FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "RotationPeriod=%s\n", obuffer);
					// NWeapon DWORD
					out = ReadInt(in);
					fprintf(fout, "NWeapon=%i\n", out);
					// DeathRange FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.0f", arrayf[0]);
					fprintf(fout, "DeathRange=%s\n", obuffer);
					// DeathDamage DWORD
					out = ReadInt(in);
					fprintf(fout, "DeathDamage=%i\n", out);
					// LinkCoor FLOAT[3]
					for (int i = 0; i < 3; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
					fprintf(fout, "LinkCoor=%s\n", obuffer);
					// LinkVid DWORD
					out = ReadInt(in);
					fprintf(fout, "LinkVid=%i\n", out);
					// TopZ FLOAT
					for (int i = 0; i < 1; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.0f", arrayf[0]);
					fprintf(fout, "TopZ=%s\n", obuffer);
					// ForMoveUpDownZ FLOAT[2]
					for (int i = 0; i < 2; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
						, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
					fprintf(fout, "NoFrame=%s\n", obuffer);
					// SFX DWORD[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
						, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
					fprintf(fout, "SFX=%s\n", obuffer);
					// FrameSpeed DWORD[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
						, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
					fprintf(fout, "FrameSpeed=%s\n", obuffer);
					// ChildX FLOAT[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
						, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
					fprintf(fout, "ChildX=%s\n", obuffer);
					// ChildY FLOAT[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
						, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
					fprintf(fout, "ChildY=%s\n", obuffer);
					// ChildZ FLOAT[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
						, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
					fprintf(fout, "ChildZ=%s\n", obuffer);
					// ChildVid DWORD[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
						, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
					fprintf(fout, "ChildVid=%s\n", obuffer);
					// NoChild DWORD[17]
					for (int i = 0; i < 17; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
						, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
					fprintf(fout, "NoChild=%s\n", obuffer);
					// GammaRGBA DWORD[4]
					for (int i = 0; i < 4; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
					fprintf(fout, "GammaRGBA=%s\n", obuffer);
					// ScaleXYZ FLOAT[3]
					for (int i = 0; i < 3; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
					fprintf(fout, "ScaleXYZ=%s\n", obuffer);
					// VidName STRING
					ReadString(in, fout, "VidName");
					fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
					fclose(fout); // �������� ����� fout
				}

				// Read Weapon section
				copyFileContent("data\\WEAP\\gen1_WEAP.ini", "WEAP.ini");
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Char PAD for WEAP Section
				// WEAP Header
				out = ReadInt(in);
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
					sprintf(obuffer, "%s", "WEAP.ini");
					fout = fopen(obuffer, "a+");
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
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "Length=%s\n", obuffer);
					// Weight Float
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "Weight=%s\n", obuffer);
					// Power Float
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "Power=%s\n", obuffer);
					// DetectRange Float
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "DetectRange=%s\n", obuffer);
					// BattleRange Float
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "BattleRange=%s\n", obuffer);
					// WeaponAim Float
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.1f", arrayf[0]);
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
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.1f", arrayf[0]);
					fprintf(fout, "DeadZone=%s\n", obuffer);
					// Period DWORD
					out = ReadInt(in);
					fprintf(fout, "Period=%i\n", out);
					// Time[8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "Time=%s\n", obuffer);
					// GammaR [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "GammaR=%s\n", obuffer);
					// GammaG [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "GammaG=%s\n", obuffer);
					// GammaB [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "GammaB=%s\n", obuffer);
					// GammaA [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "GammaA=%s\n", obuffer);
					// ScaleX [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "ScaleX=%s\n", obuffer);
					// ScaleY [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "ScaleY=%s\n", obuffer);
					// ScaleZ [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "ScaleZ=%s\n", obuffer);
					// ShiftX [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "ShiftX=%s\n", obuffer);
					// ShiftY [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "ShiftY=%s\n", obuffer);
					// ShiftZ [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "ShiftZ=%s\n", obuffer);
					// DirectionX [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "DirectionX=%s\n", obuffer);
					// DirectionY [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "DirectionY=%s\n", obuffer);
					// DirectionZ [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "DirectionZ=%s\n", obuffer);
					// FrameSpeed [8] DWORD
					for (int i = 0; i < 8; ++i)
					{
						arrayi[i] = ReadInt(in);
					}
					sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
					fprintf(fout, "FrameSpeed=%s\n", obuffer);
					// Speed [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "Speed=%s\n", obuffer);
					// ZSpeed [8] Float
					for (int i = 0; i < 8; ++i)
					{
						arrayf[i] = ReadFloat(in);
					}
					sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
					fprintf(fout, "ZSpeed=%s\n", obuffer);
					fclose(fout); // fout file close
				}

				// Read CNST section
				copyFileContent("data\\CNST\\gen1_CNST.ini", "CNST.ini");
				// CNST Header
				out = ReadInt(in);
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
					sprintf(obuffer, "%s", "CNST.ini");
					fout = fopen(obuffer, "a+");
					//
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
					fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
					//
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
					fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
					//
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
					fprintf(fout, "Gravitation=%s\n", obuffer);
					//
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
					fprintf(fout, "Gravitation2=%s\n", obuffer);
					//
					out = ReadInt(in);
					fprintf(fout, "RepairSpeed=%i\n", out);
					//
					out = ReadInt(in);
					fprintf(fout, "AmmoReloadTime=%i\n", out);
					//
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
					fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
					//
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
					fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
					//
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
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
					arrayf[0] = ReadFloat(in);
					sprintf(obuffer, "%.f", arrayf[0]);
					fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
					//
					out = ReadInt(in);
					fprintf(fout, "MessageStartDelay=%i\n", out);
					//
					printf("OK: Reading CNST Section\n");
					fclose(fout); // �������� ����� fout
				}

				// Read SFX Section
				copyFileContent("data\\SFX\\non_extSFX.ini", "SFX.ini");
				out = ReadInt(in);
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
					sprintf(obuffer, "%s", "SFX.ini");
					fout = fopen(obuffer, "a+");
					fprintf(fout, ";-------------------------%03d\n", i);
					out = ReadByte(in); // Priority
					fprintf(fout, "Priority=%i\n", out);
					// Wave
					std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

					// ��������� 8 ����� ��� ����� �� ������
					for (int i = 0; i < 8; ++i) {
						if (!feof(in)) {
							arraySFX[i] = ReadStringNoRTN(in);
						}
					}
					// ��������� ������ � ������ �� ������
					std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
						arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

					fprintf(fout, "Wave=%s\n", obuffer.c_str());

					fclose(fout); // ��������� ���� fout
				}
			}
		}

				// Alien Shooter 1 Engine - without char pad in WEAP section
				if (strcmp("as1_nonpad", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\gen1_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							// Movemask DWORD
							out = ReadInt(in);
							fprintf(fout, "MoveMask=%i\n", out);
							// SizeXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen1_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\non_extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
							fprintf(fout, ";-------------------------%03d\n", i);
							out = ReadByte(in); // Priority
							fprintf(fout, "Priority=%i\n", out);
							// Wave
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());

							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Theseus PC version
				if (strcmp("theseus_pc", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\gen1_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "BattleRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen1_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\gen1.1_extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Alien Shooter 1: World (Mobile\PC) - with char pad in WEAP section
				if (strcmp("as1world_pad", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\asworld_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "WEAP.ini");
						char pad;
						fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Alien Shooter 1: World (Mobile\PC) - without char pad in WEAP section
				if (strcmp("as1world_nonpad", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\asworld_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Zombie Shooter 1
				if (strcmp("zs1", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\gen1.1_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "WEAP.ini");
						char pad;
						fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Zombie Shooter 1 Mobile
				if (strcmp("zs1_mobile", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\zs1mobile_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamage DWORD
							out = ReadInt(in);
							fprintf(fout, "DeathDamage=%i\n", out);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen1.1_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Alien Shooter 2 Gold / Vengeance
				if (strcmp("as2_original", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\gen2_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\gen1.1_extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Alien Shooter 2 Reloaded / Conscription
				if (strcmp("as2_addons", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\gen2_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						char pad;
						fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Zombie Shooter 2 - Steam
				if (strcmp("zs2_nonpad", argv[2]) == 0)		
				{
					copyFileContent("data\\OBJ\\zs2_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[5]
							for (int i = 0; i < 5; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Zombie Shooter 2 - NonSteam
				if (strcmp("zs2_pad", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\zs2_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[5]
							for (int i = 0; i < 5; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						char pad;
						fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Alien Shooter: Revisited
				if (strcmp("asr", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\zs2_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[5]
							for (int i = 0; i < 5; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						char pad;
						fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Alien Shooter 2 Legend & TD (Steam\Mobile)
				if (strcmp("as2legend_pad", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\legend_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						char pad;
						fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Alien Shooter 2 New Era & Reloaded (Steam\Mobile)
				if (strcmp("as2legend_nonpad", argv[2]) == 0)				
				{
					copyFileContent("data\\OBJ\\legend_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DATA')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Objects Extended Project
				if (strcmp("oe", argv[2]) == 0)
				{
					copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DB  ')
						{
							printf("ERROR: Could not find DB header! \n");
							fclose(in);
							return 1;
						}

						// Read CNST section
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						//obj
						copyFileContent("data\\OBJ\\gen2_OBJ.ini", "OBJ.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						char pad;
						fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				// Objects Extended Project Old versions
				if (strcmp("oe1105", argv[2]) == 0)
				{
					copyFileContent("data\\OBJ\\gen2_OBJ.ini", "OBJ.ini");
					{
						//header
						out = ReadInt(in);
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
						if (!out == 'DB  ')
						{
							printf("ERROR: Could not find DATA header! \n");
							fclose(in);
							return 1;
						}

						//obj
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "OBJ.ini");
							fout = fopen(obuffer, "a+");
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
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "SizeXYZ=%s\n", obuffer);
							// MaxHP DWORD
							out = ReadInt(in);
							fprintf(fout, "MaxHP=%i\n", out);
							// MaxSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxSpeed=%s\n", obuffer);
							// MaxZSpeed FLOAT
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "MaxZSpeed=%s\n", obuffer);
							// Acceleration FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
							fprintf(fout, "Acceleration=%s\n", obuffer);
							// RotationPeridod FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "RotationPeriod=%s\n", obuffer);
							// NWeapon DWORD
							out = ReadInt(in);
							fprintf(fout, "NWeapon=%i\n", out);
							// DeathRange FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "DeathRange=%s\n", obuffer);
							// DeathDamageMinMax DWORD[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i", arrayi[0], arrayi[1]);
							fprintf(fout, "DeathDamageMinMax=%s\n", obuffer);
							// DeathPush FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeathPush=%s\n", obuffer);
							// LinkCoor FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f %.1f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "LinkCoor=%s\n", obuffer);
							// LinkVid DWORD
							out = ReadInt(in);
							fprintf(fout, "LinkVid=%i\n", out);
							// TopZ FLOAT
							for (int i = 0; i < 1; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.0f", arrayf[0]);
							fprintf(fout, "TopZ=%s\n", obuffer);
							// ForMoveUpDownZ FLOAT[2]
							for (int i = 0; i < 2; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.1f %.1f", arrayf[0], arrayf[1]);
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
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoFrame=%s\n", obuffer);
							// SFX DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "SFX=%s\n", obuffer);
							// FrameSpeed DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							// ChildX FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildX=%s\n", obuffer);
							// ChildY FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildY=%s\n", obuffer);
							// ChildZ FLOAT[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "\t\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f\t %.0f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7], arrayf[8], arrayf[9], arrayf[10]
								, arrayf[11], arrayf[12], arrayf[13], arrayf[14], arrayf[15], arrayf[16]);
							fprintf(fout, "ChildZ=%s\n", obuffer);
							// ChildVid DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "ChildVid=%s\n", obuffer);
							// NoChild DWORD[17]
							for (int i = 0; i < 17; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "\t\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i\t %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7], arrayi[8], arrayi[9], arrayi[10]
								, arrayi[11], arrayi[12], arrayi[13], arrayi[14], arrayi[15], arrayi[16]);
							fprintf(fout, "NoChild=%s\n", obuffer);
							// GammaRGBA DWORD[4]
							for (int i = 0; i < 4; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3]);
							fprintf(fout, "GammaRGBA=%s\n", obuffer);
							// ScaleXYZ FLOAT[3]
							for (int i = 0; i < 3; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.6f %.6f %.6f", arrayf[0], arrayf[1], arrayf[2]);
							fprintf(fout, "ScaleXYZ=%s\n", obuffer);
							// VidName STRING
							ReadString(in, fout, "VidName");
							fprintf(fout, ";\t\t\tstnd\t stp\t mov\t strt\t lrot\t rrot\t op\t hit\t fgt\t sal\t sto\t lnk\t clsh\t wnd\t birth death explode\n");
							fclose(fout); // �������� ����� fout
						}

						// Read Weapon section
						copyFileContent("data\\WEAP\\gen2_WEAP.ini", "WEAP.ini");
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // ��������� ������ ����. ����� ��� ����������� ������ ��������� ��� ��������� ������.

						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "WEAP.ini");
							fout = fopen(obuffer, "a+");
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Length=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Weight=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "Power=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "DetectPeriod=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DetectRange=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.1f", arrayf[0]);
							fprintf(fout, "DeadZone=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "Period=%i\n", out);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Time=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaR=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaG=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaB=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "GammaA=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ScaleZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ShiftZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionX=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionY=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "DirectionZ=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayi[i] = ReadInt(in);
							}
							sprintf(obuffer, "%i %i %i %i %i %i %i %i", arrayi[0], arrayi[1], arrayi[2], arrayi[3], arrayi[4], arrayi[5], arrayi[6], arrayi[7]);
							fprintf(fout, "FrameSpeed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "Speed=%s\n", obuffer);
							//
							for (int i = 0; i < 8; ++i)
							{
								arrayf[i] = ReadFloat(in);
							}
							sprintf(obuffer, "%1f %1f %1f %1f %1f %1f %1f %1f", arrayf[0], arrayf[1], arrayf[2], arrayf[3], arrayf[4], arrayf[5], arrayf[6], arrayf[7]);
							fprintf(fout, "ZSpeed=%s\n", obuffer);
							fclose(fout); // �������� ����� fout
						}

						// Read CNST section
						copyFileContent("data\\CNST\\gen2_CNST.ini", "CNST.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "CNST.ini");
							fout = fopen(obuffer, "a+");
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedX=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MaxScrollSpeedY=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "Gravitation2=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "RepairSpeed=%i\n", out);
							//
							out = ReadInt(in);
							fprintf(fout, "AmmoReloadTime=%i\n", out);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "RailRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "MasterRepairSpeed=%s\n", obuffer);
							//
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
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
							arrayf[0] = ReadFloat(in);
							sprintf(obuffer, "%.f", arrayf[0]);
							fprintf(fout, "SafeClashSpeed=%s\n", obuffer);
							//
							out = ReadInt(in);
							fprintf(fout, "MessageStartDelay=%i\n", out);
							//
							printf("OK: Reading CNST Section\n");
							fclose(fout); // �������� ����� fout
						}

						// Read SFX Section
						copyFileContent("data\\SFX\\extSFX.ini", "SFX.ini");
						out = ReadInt(in);
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
							sprintf(obuffer, "%s", "SFX.ini");
							fout = fopen(obuffer, "a+");
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
							std::string arraySFX[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arraySFX[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer = arraySFX[0] + " " + arraySFX[1] + " " + arraySFX[2] + " " + arraySFX[3] + " " +
								arraySFX[4] + " " + arraySFX[5] + " " + arraySFX[6] + " " + arraySFX[7];

							fprintf(fout, "Wave=%s\n", obuffer.c_str());
							// ForceFeedBack
							std::string arrayForceFeedBack[8]; // ������ ��� �������� ����� �� ������

							// ��������� 8 ����� ��� ����� �� ������
							for (int i = 0; i < 8; ++i) {
								if (!feof(in)) {
									arrayForceFeedBack[i] = ReadStringNoRTN(in);
								}
							}
							// ��������� ������ � ������ �� ������
							std::string obuffer2 = arrayForceFeedBack[0] + " " + arrayForceFeedBack[1] + " " + arrayForceFeedBack[2] + " " + arrayForceFeedBack[3] + " " +
								arrayForceFeedBack[4] + " " + arrayForceFeedBack[5] + " " + arrayForceFeedBack[6] + " " + arrayForceFeedBack[7];
							fprintf(fout, "ForceFeedBack=%s\n", obuffer2.c_str());
							//
							fclose(fout); // ��������� ���� fout
						}
					}
				}

				fclose(in); // �������� ����� in
	}
	return 0;
}