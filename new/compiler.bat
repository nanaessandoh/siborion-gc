del build\*.obj
del build\*.hex
del build\*.cof
del build\*.lst


"C:\Program Files\HI-TECH Software\PICC\9.50\bin/picc.exe"  -16f690 -C -G -E -O"build/main.obj" -Zg  main.c
"C:\Program Files\HI-TECH Software\PICC\9.50\bin/picc.exe"  -16f690 -C -G -E -O"build/gsm.obj"  -Zg  gsm.c
"C:\Program Files\HI-TECH Software\PICC\9.50\bin/picc.exe"  -16f690 -C -G -E -O"build/init.obj" -Zg  init.c
"C:\Program Files\HI-TECH Software\PICC\9.50\bin/picc.exe"  -16f690 -C -G -E -O"build/int.obj" -Zg  int.c
"C:\Program Files\HI-TECH Software\PICC\9.50\bin/picc.exe" "build/main.obj" "build/gsm.obj" "build/init.obj" "build/int.obj" -M"build/main.map" -O"build/main.cof" -O"build/main.hex"  -16f690
