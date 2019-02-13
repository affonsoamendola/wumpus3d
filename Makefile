#	Copyright Affonso Amendola 2019					#
#													#
#	Fofonso's 3D fuckery							#
#---------------------------------------------------#

GAMENAME = 3d
CC = tcc
RM = rm -f

INCLUDE = include;D:\tc\include;.
LIB = D:\tc\lib;lib
CCFLAGS = 

all: vga

vga:
	$(CC) "-I$(INCLUDE) -L$(LIB) -DVGA -e$(GAMENAME) -l $(CCFLAGS)"  *.c fflibvga.lib
	
run:
	dosbox -conf ~/.dosbox/tcc.conf -c "$(GAMENAME)"

clean:
	$(RM) *.OBJ *.EXE *.LOG *.BAT *.MAP
