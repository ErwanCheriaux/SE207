.PHONY: all clean

SYSTEMC   ?= /usr/local
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS  ?=  -L$(SYSTEMC)/lib
LDLIBS    =  -lsystemc

CC = g++

EXE = type_logique vecteurs entiers_taille_arbitraire fixed fix time

all: $(EXE)

clean:
	@rm -f $(EXE)
