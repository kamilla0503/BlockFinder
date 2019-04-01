CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-O3
LDFLAGS=-O3
LDLIBS=

SRCS=blockfinder.cpp blockfinder_main.cpp classes.cpp ncs.cpp scheme.cpp task.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: blockfinder

blockfinder.o: blockfinder.cpp blockfinder.h scheme.h task.h

ncs.o: ncs.cpp ncs.h

classes.o: classes.cpp ncs.h 

scheme.o: scheme.cpp ncs.h scheme.h

task.o: task.cpp task.h

blockfinder_main.o: blockfinder_main.cpp blockfinder.h

blockfinder: $(OBJS)
	$(CXX) $(LDFLAGS) -o blockfinder $(OBJS) $(LDLIBS)

#test:
#	./test_ncs

clean:
	$(RM) $(OBJS) blockfinder
