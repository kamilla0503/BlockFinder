CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-g -std=c++11 
LDFLAGS=-g -std=c++11
LDLIBS=

SRCS=ncs.cpp blockfinder.cpp scheme.cpp blockfinder_main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test_ncs

ncs.o: ncs.cpp classes.cpp ncs.h

blockfinder.o: classes.cpp blockfinder_main.cpp blockfinder.cpp blockfinder.h ncs.h

scheme.o: scheme.cpp scheme.h

test_ncs: $(OBJS)
	$(CXX) $(LDFLAGS) -o test_ncs $(OBJS) $(LDLIBS)

test:
	./test_ncs

clean:
	$(RM) $(OBJS) test_ncs
