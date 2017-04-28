.PHONY: all clean

SYSTEMC   ?= /comelec/softs/opt/systemc/current
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

CC = g++

EXE = type_logique vecteurs

all: $(EXE)

clean:
	@rm -f $(EXE)
