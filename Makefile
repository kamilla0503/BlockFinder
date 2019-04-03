CC=gcc
CXX=g++
RM=rm -f


CPPFLAGS=-O3 -g -std=c++11 -I.
LDFLAGS=-O3 -g -std=c++11 -pthread
LDLIBS=

PROGNAME= blockfinder_parallel_ctpl

SRCS=ncs.cpp \
     classes.cpp \
     blockfinder.cpp \
     scheme.cpp \
     blockfinder_main.cpp \
     PatternCodes.cpp \
     tasks.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: $(PROGNAME)

ncs.o: ncs.cpp ncs.h

classes.o: classes.cpp ncs.h

blockfinder.o: blockfinder.cpp blockfinder.h ncs.h

blockfinder_main.o: blockfinder_main.cpp blockfinder.h ncs.h

scheme.o: scheme.cpp scheme.h

PatternCodes.o: PatternCodes.cpp PatternCodes.h

tasks.o: tasks.cpp tasks.h

$(PROGNAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PROGNAME) $(OBJS) $(LDLIBS)

clean:
	rm -rf $(OBJS) $(PROGNAME) 
