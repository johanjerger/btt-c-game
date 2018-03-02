SOURCE_FOLDER=src
BUILD_FOLDER=build
TEMPORAL_FOLDER=tmp
INSTALL_FOLDER=/usr/bin

CFLAG=-O3 -Wall -std=gnu11 -pedantic -Wextra -Wcast-qual -Wwrite-strings -Wshadow
# DEBUG=-g


.PHONY: all clean folders install uninstall reinstall
all: clean folders main.o $(TEMPORAL_FOLDER) $(BUILD_FOLDER)
	    gcc $(TEMPORAL_FOLDER)/** -o $(BUILD_FOLDER)/btt $(CFLAG) $(DEBUG)

main.o:
		gcc -c $(SOURCE_FOLDER)/main.c -o $(TEMPORAL_FOLDER)/main.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/btt.c -o $(TEMPORAL_FOLDER)/btt.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/function.c -o $(TEMPORAL_FOLDER)/function.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/verify.c -o $(TEMPORAL_FOLDER)/verify.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/moves.c -o $(TEMPORAL_FOLDER)/moves.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/cheats.c -o $(TEMPORAL_FOLDER)/cheats.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/generate.c -o $(TEMPORAL_FOLDER)/generate.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/menu.c -o $(TEMPORAL_FOLDER)/menu.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/score_table.c -o $(TEMPORAL_FOLDER)/score_table.o $(CFLAG) $(DEBUG)
		gcc -c $(SOURCE_FOLDER)/game_loop_function.c -o $(TEMPORAL_FOLDER)/game_loop_function.o $(CFLAG) $(DEBUG)

clean:
		rm -r $(TEMPORAL_FOLDER) $(BUILD_FOLDER)

folders:
		-mkdir $(TEMPORAL_FOLDER) $(BUILD_FOLDER)

install: $(BUILD_FOLDER)/btt
		cp -p $(BUILD_FOLDER)/btt $(INSTALL_FOLDER)

uninstall: $(INSTALL_FOLDER)/btt
		rm $(INSTALL_FOLDER)/btt

reinstall: uninstall install

lines:
		@ printf "	.c files               "
		@ wc -l $(SOURCE_FOLDER)/*.c | grep total
		@ printf "	.h files      		"
		@ wc -l $(SOURCE_FOLDER)/include/* | grep total

compile_install: all install
