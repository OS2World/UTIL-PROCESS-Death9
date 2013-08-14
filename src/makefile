CC=wcc386 $[. -w4 -zq -otexan -of+ -4s -bd -bt=os2 -mf

.c.obj:
 $(CC)

death.lib: deathapi.obj
 wlib -b -c -n -q -p=512 death.lib +deathapi.obj

all: death.dll

death.dll: death.obj death.lib 
 wlink @death.lnk