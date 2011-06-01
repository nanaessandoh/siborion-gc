del build\*.obj
del build\*.hex
del build\*.cof
del build\*.lst

del *.obj
del *.hex
del *.cof
del *.lst
del *.rlf
del *.cce
del *.sdb

"C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  main.c --outdir=build
"C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  gsm.c  --outdir=build
"C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  init.c --outdir=build
"C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 -C -G  -Zg  int.c  --outdir=build
"C:\Program Files\HI-TECH Software\PICC\std\9.60\bin/picc.exe" -16f690 build/main.obj build/gsm.obj build/init.obj build/int.obj -Mout.map -Oout.cof -Oout.hex 
