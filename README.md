# RESTool
RESTool v1.6 by romalu86



--- List of games with which the program works:

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

--- How to use?

The program currently works through the console. For unpacking, you need to create a bat file. Its structure consists of three variables.

example: RESTool objects.res as1pad

or run the !Unpack_RES.bat file and follow the instructions on the screen.

After the decompilation process is completed, the "unpacked_inis" folder will appear with the files: OBJ.ini, WEAP.ini, CNST.ini and SFX.ini

The reverse compilation process is also possible. The folder with the program contains everything you need (the compiler and customized batch files !MakeRES !MakeDB_OE_old !MakeDB_OE_new).
When you run one of the available batch files, the program takes the files "OBJ.ini, WEAP.ini, CNST.ini, SFX.ini.", and performs a reverse compilation.
If the process was successful, the test.res or test.db file will appear in the root directory.

--- Dictionary of variables:

The program supports the ability to supplement the base of unknown variables that are unpacked in the INT format (numbers - 1, 2, 4, etc.) or hexadecimal number system (example 0x1000). All information is in the constants.ini file, new values ​​are added by analogy with others.

--- File modes list:
"as1_pad" - works with Alien Shooter 1 Steam, Alien Shooter 1 Last Hope (Steam & Mobile), Alien Shooter - Lost World (Theseus Mobile)

"as1_nonpad" - works with Alien Shooter 1 - Old (NonSteam)

"theseus_pc" - works with Theseus

"as1world_pad" - works with Alien Shooter 1 - World (Mobile)

"as1world_nonpad" - works with Alien Shooter 1 - World (Mobile)

"zs1" - works with Zombie Shooter 1

"zs1_mobile" - works with Zombie Shooter 1

"as2_original" - works with Gold and Vengeance editions

"as2_addons" - works with Reloaded, Conscription

"zs2_nonpad" - works with Zombie Shooter 2 (Steam)

"zs2_pad" - works with Zombie Shooter 2 (NonSteam)

"asr" - works with Alien Shooter Revisited

"as2legend_pad" - works with Alien Shooter 2 Legend & TD (Steam\Mobile)

"as2legend_nonpad" - works with Alien Shooter 2 New Era (Steam) & Alien Shooter 2 Reloaded (Mobile)

"oe_pad" - works with Objects Extended Project

"oe_nonpad" - works with Objects Extended Project

"oe1105" - works with Objects Extended Project (Old Versions)


thx ermaccer for original c++ project. Many things helped to release this program much faster.
