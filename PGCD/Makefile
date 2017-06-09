.PHONY: all clean

SYSTEMC   ?= /usr/local
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS  ?=  -L$(SYSTEMC)/lib
LDLIBS    =  -lsystemc -std=c++11

CC = g++

EXE = PGCD_algo PGCD_cthread PGCD_method

all: $(EXE)

clean:
	@rm -f $(EXE) $(EXE).vcd
