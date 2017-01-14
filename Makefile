# file locations:
MAIN = src/main.cpp
LIB = src/lib
MOD = $(LIB)/modules
GEN = $(MOD)/generator/generator.cpp
ROLL = $(MOD)/roll/roll.cpp
UTIL = $(LIB)/utils.cpp

# compiler settings to use:
CC = g++
CFLAGS = -Wall -I$(LIB) -I$(MOD)/generator -I$(MOD)/roll -std=c++11 -o 

# build:
what:
		@echo "Options are:\nopenrpg - The whole package\ngenerator - The name generator\nroll - The dice roll simulator\nclean - Removes all compiled files"
openrpg: $(MAIN)
		@$(CC) $(CFLAGS) openrpg $(MAIN) $(UTIL) $(GEN) $(ROLL)
		
generator: $(MOD)/generator/main.cpp
		@$(CC) $(CFLAGS) generator $(MOD)/generator/main.cpp $(GEN) $(UTIL) $(ROLL)
		
roll: $(MOD)/generator/main.cpp
		@$(CC) $(CFLAGS) roll $(MOD)/roll/main.cpp $(GEN) $(UTIL) $(ROLL)
		
clean:
		@rm -f openrpg roll generator