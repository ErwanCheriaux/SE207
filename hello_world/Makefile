.PHONY: all clean

SYSTEMC   ?= /usr/local
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS  ?=  -L$(SYSTEMC)/lib
LDLIBS    =  -lsystemc

CC = g++

EXE = hello_world

all: $(EXE)

clean:
	@rm -f $(EXE)
