@echo off
echo Enter file name... Example: objects.res or game.res
Set /p varFile=
echo Enter file mode... Example: as1pad (check readme for more modes).
Set /p varMode=
start "" "RESTool.exe" %varFile% %varMode%