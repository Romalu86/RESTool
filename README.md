# RESTool 1.7 by romalu86
**List of games with which the program works:**

**Games on the engine AS1\ZS1:**
- Alien Shooter (PC\Mobile),
- Alien Shooter - Last Hope (Steam\Mobile),
- Alien Shooter - Lost World (Theseus Mobile),
- Alien Shooter - World (Mobile),
- Theseus (PC),
- Zombie Shooter 1 (PC\Mobile),
- Crazy Lunch (PC\Mobile),
- Chacks Temple.

**Games on the engine AS2\ZS2:**
- Alien Shooter - Revisited,
- Alien Shooter 2 - Gold,
- Alien Shooter 2 - Vengeance,
- Alien Shooter 2 - Reloaded (PC\Mobile),
- Alien Shooter 2 - Conscription,
- Alien Shooter 2 - The Legend (Steam\Mobile),
- Alien Shooter 2 - Tower Defence (Steam\Mobile),
- Alien Shooter 2 - New Era,
- Zombie Shooter 2,
- Objects Extended Project (Old \ New versions),

**How to use?**

The program currently operates through the console. To unpack the file, you need to launch RESTool and follow the instructions on the screen.

After the decompilation process is completed, the "unpacked_inis" folder will appear with the files: OBJ.ini, WEAP.ini, CNST.ini and SFX.ini

The reverse compilation process is also possible. The folder with the program contains everything you need (the compiler and customized batch files !MakeRES !MakeDB_OE_old !MakeDB_OE_new).
When you run one of the available batch files, the program takes the files "OBJ.ini, WEAP.ini, CNST.ini, SFX.ini.", and performs a reverse compilation.
If the process was successful, the test.res or test.db file will appear in the root directory.

**Dictionary of variables:**

The program supports the ability to supplement the base of unknown variables that are unpacked in the INT format (numbers - 1, 2, 4, etc.) or hexadecimal number system (example 0x1000). All information is in the constants.ini file, new values are added by analogy with others.

**File modes list:**

- as1_engine - works with Alien Shooter 1, Alien Shooter 1 Last Hope, Alien Shooter - Lost World (Theseus Mobile) 

- theseus_pc - works with Theseus (PC Only)

- as1world - works with Alien Shooter 1 - World

- zs1 - works with Zombie Shooter 1

- zs1_mobile - works with Zombie Shooter 1 (Mobile)

- as2_original - works with Gold and Vengeance editions

- as2_addons - works with Reloaded, Conscription, Zombie Shooter 2 Teaser, Objects Extended Project (Old versions before 1.1.0.6)

- zs2_engine - works with Zombie Shooter 2 / Alien Shooter: Revisited

- as2legend_engine - works with Alien Shooter 2 Legend & TD (Steam and Mobile), Alien Shooter 2 New Era, Alien Shooter 2 Reloaded (Mobile)

- oe_engine - works with Objects Extended Project (version 1.1.0.6+)

- crazylunch - works with Crazy Lunch

- chackstemple - works with Chacks Temple
