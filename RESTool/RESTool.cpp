// RESTool.cpp : Defines the entry point for the console application.
// original idea by ermaccer. Complete code fix by romalu86

#include "stdafx.h"
#include "filefuncs.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("RESTool ver.1.3 by romalu86\n");
		printf("\n");
		printf("How to work:\n");
		printf("example: RESTool objects.res as1pad\n");
		printf("\n");
		printf("File modes:\n");
		printf("as1pad - works with Alien Shooter 1 Steam, Alien Shooter 1 Last Hope Steam, Theseus Mobile\n");
		printf("as1nopad - works with Alien Shooter 1 - Old (No steam version)\n");
		printf("theseus - works with Theseus\n");
		printf("as1mobile - works with Alien Shooter 1 - World (mobile)\n");
		printf("zs1 - works with Zombie Shooter 1\n");
		printf("zs1mobile - works with Zombie Shooter 1\n");
		printf("as2original - works with Gold and Vengeance editions\n");
		printf("as2addons - works with Reloaded, Conscription\n");
		printf("zs2nonpad - works with Zombie Shooter 2 (Steam)\n");
		printf("zs2pad - works with Zombie Shooter 2 (NonSteam)\n");
		printf("asr - works with Alien Shooter Revisited\n");
		printf("as2legend - works with Alien Shooter 2 Legend & TD (Steam and Mobile)\n");
		printf("as2legendpad - works with Alien Shooter 2 New Era (Steam) & Alien Shooter 2 Reloaded (Mobile)\n");
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
				if (strcmp("as1pad", argv[2]) == 0)
		{
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
					fprintf(fout, "SpriteType=%i\n", out);
					// SpriteClass DWORD
					out = ReadInt(in);
					fprintf(fout, "SpriteClass=%i\n", out);
					// Property DWORD
					out = ReadInt(in);
					sprintf(obuffer, "0x%X", out);
					fprintf(fout, "Property=%s\n", obuffer);
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
					fclose(fout); // Закрытие файла fout
				}

				// Read Weapon section
				char pad;
				fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка.

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
					fprintf(fout, "SpriteType=%i\n", out);
					//
					out = ReadInt(in);
					sprintf(obuffer, "0x%X", out);
					fprintf(fout, "Property=%s\n", obuffer);
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
					fprintf(fout, "DefaultBehave=%i\n", out);
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
					fclose(fout); // Закрытие файла fout
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
					fclose(fout); // Закрытие файла fout
				}

				// Read SFX Section
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

					fclose(fout); // Закрываем файл fout
				}
			}
		}

				// Alien Shooter 1 Engine - without char pad in WEAP section
				if (strcmp("as1nopad", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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

							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Theseus
				if (strcmp("theseus", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 1: World (Mobile\PC)
				if (strcmp("as1mobile", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							// Property3 DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property3=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						char pad;
						fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Zombie Shooter 1
				if (strcmp("zs1", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						char pad;
						fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Zombie Shooter 1 Mobile
				if (strcmp("zs1mobile", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 2 Gold / Vengeance
				if (strcmp("alienshooter2original", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 2 Reloaded / Conscription
				if (strcmp("as2addons", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						char pad;
						fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Zombie Shooter 2 - Steam
				if (strcmp("zs2nonpad", argv[2]) == 0)				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Zombie Shooter 2 - NonSteam
				if (strcmp("zs2pad", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						char pad;
						fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter: Revisited
				if (strcmp("asr", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						char pad;
						fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 2 Legend & TD (Steam\Mobile)
				if (strcmp("as2legend", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						char pad;
						fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Alien Shooter 2 New Era & Reloaded (Steam\Mobile)
				if (strcmp("as2legendpad", argv[2]) == 0)				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Objects Extended Project
				if (strcmp("oe", argv[2]) == 0)
				{
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
						char pad;
						fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				// Objects Extended Project Old versions
				if (strcmp("oe1105", argv[2]) == 0)
				{
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
							fprintf(fout, "SpriteType=%i\n", out);
							// SpriteClass DWORD
							out = ReadInt(in);
							fprintf(fout, "SpriteClass=%i\n", out);
							// Property DWORD
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fclose(fout); // Закрытие файла fout
						}

						// Read Weapon section
						//char pad;
						//fread(&pad, sizeof(char), 1, in);  // Считываем пустой байт. Нужен для корректного чтения заголовка для некоторых версий.

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
							fprintf(fout, "SpriteType=%i\n", out);
							//
							out = ReadInt(in);
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							fprintf(fout, "DefaultBehave=%i\n", out);
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
							fclose(fout); // Закрытие файла fout
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
							fclose(fout); // Закрытие файла fout
						}

						// Read SFX Section
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
							sprintf(obuffer, "0x%X", out);
							fprintf(fout, "Property=%s\n", obuffer);
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
							//
							fclose(fout); // Закрываем файл fout
						}
					}
				}

				fclose(in); // Закрытие файла in
	}
	return 0;
}