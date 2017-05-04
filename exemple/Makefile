.PHONY: all clean

SYSTEMC   ?= /usr/local/systemc-2.3.1
SYSTEMC   ?= /comelec/softs/opt/systemc/current
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

CC = g++

EXE = type_logique vecteurs entiers_taille_arbitraire fixed fix time

all: $(EXE)

clean:
	@rm -f $(EXE)
