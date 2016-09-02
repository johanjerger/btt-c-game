SOURCE_FOLDER=src
BUILD_FOLDER=build
TEMPORAL_FOLDER=tmp
INSTALL_FOLDER=/usr/bin

CFLAG=-O3 -Wall -std=c11
DEBUG=-g


.PHONY: all clean folders install uninstall reinstall
all: folders main.o $(TEMPORAL_FOLDER) $(BUILD_FOLDER)
	    gcc $(TEMPORAL_FOLDER)/** -o $(BUILD_FOLDER)/btt $(CFLAG) $(DEBUG)

main.o: 
		gcc -c $(SOURCE_FOLDER)/btt.c -o $(TEMPORAL_FOLDER)/btt.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/function.c -o $(TEMPORAL_FOLDER)/function.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/verify.c -o $(TEMPORAL_FOLDER)/verify.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/moves.c -o $(TEMPORAL_FOLDER)/moves.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/cheats.c -o $(TEMPORAL_FOLDER)/cheats.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/generate.c -o $(TEMPORAL_FOLDER)/generate.o $(CFLAG) $(DEBUG)

clean: 
		rm -r $(TEMPORAL_FOLDER) $(BUILD_FOLDER)

folders:
		-mkdir $(TEMPORAL_FOLDER) $(BUILD_FOLDER)

install: $(BUILD_FOLDER)/btt
		cp -p $(BUILD_FOLDER)/btt $(INSTALL_FOLDER)

uninstall: $(INSTALL_FOLDER)/btt
		rm $(INSTALL_FOLDER)/btt

reinstall: uninstall install