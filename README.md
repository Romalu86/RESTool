# RESTool
RESTool v1.4 by romalu86

List of games with which the program works at the moment:

- Games on the engine AS1\ZS1:
Alien Shooter (PC NonSteam);
Alien Shooter (Steam);
Alien Shooter - Last Hope (Steam\Mobile);
Alien Shooter - Lost World (Theseus Mobile);
Alien Shooter - World (Mobile);
Alien Shooter - Revisited;
Theseus (PC);
Zombie Shooter 1 (PC Steam & NonSteam);
Zombie Shooter 1 (Mobile);

- Games on the engine AS2\ZS2:
Alien Shooter - Revisited;
Alien Shooter 2 - Gold;
Alien Shooter 2 - Vengeance;
Alien Shooter 2 - Reloaded;
Alien Shooter 2 - Conscription;
Alien Shooter 2 - The Legend (Steam\Mobile);
Alien Shooter 2 - Tower Defence (Steam\Mobile);
Alien Shooter 2 - Reloaded (Mobile);
Alien Shooter 2 - New Era (Steam);
Zombie Shooter 2 (Steam\NonSteam);
Objects Extended Project.

How to use?

The program currently works through the console. For unpacking, you need to create a bat file. Its structure consists of three variables.

example: RESTool objects.res as1pad

Also, unpacking through Unpack.bat has been added. You need to specify the path to the file or just its name if it is located in the same folder, and then choose the operating mode.

After Bat File completes the work, 4 files will appear in the folder: OBJ.ini, WEAP.ini, CNST.ini and SFX.ini

Dictionary of variables:

The program supports the ability to supplement the base of unknown variables that are unpacked in the INT format (numbers - 1, 2, 4, etc.) or hexadecimal number system (example 0x1000). All information is in the constants.ini file, new values ​​are added by analogy with others.

File modes list:
"as1pad" - works with Alien Shooter 1 Steam, Alien Shooter 1 Last Hope (Steam & Mobile), Alien Shooter - Lost World (Theseus Mobile)

"as1nopad" - works with Alien Shooter 1 - Old (NonSteam)

"theseus" - works with Theseus

"as1pad" - works with Alien Shooter 1 - World (Mobile)

"as1nopad" - works with Alien Shooter 1 - World (Mobile)

"zs1" - works with Zombie Shooter 1

"zs1mobile" - works with Zombie Shooter 1

"as2original" - works with Gold and Vengeance editions

"as2addons" - works with Reloaded, Conscription

"zs2nonpad" - works with Zombie Shooter 2 (Steam)

"zs2pad" - works with Zombie Shooter 2 (NonSteam)

"asr" - works with Alien Shooter Revisited

"as2legend" - works with Alien Shooter 2 Legend & TD (Steam\Mobile)

"as2legendpad" - works with Alien Shooter 2 New Era (Steam) & Alien Shooter 2 Reloaded (Mobile)

"oe" - works with Objects Extended Project

"oe1105" - works with Objects Extended Project (Old Versions)


thx ermaccer for original c++ project. Many things helped to release this program much faster.
