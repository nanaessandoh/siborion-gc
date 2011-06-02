rm build/*.obj
rm build/*.hex
rm build/*.cof
rm build/*.lst

rm *.obj
rm *.hex
rm *.cof
rm *.lst
rm *.rlf
rm *.cce
rm *.sdb

wine cmd.exe /C "C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  main.c --outdir=build
wine cmd.exe /C "C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  gsm.c  --outdir=build
wine cmd.exe /C "C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  init.c --outdir=build
wine cmd.exe /C "C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  int.c  --outdir=build
wine cmd.exe /C "C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 build/main.obj build/gsm.obj build/init.obj build/int.obj -Mout.map -Oout.cof -Oout.hex
