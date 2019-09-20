CC=gcc
CXX=g++
RM=rm -f


CPPFLAGS=-std=c++17 -O3 -I. -march=native -fopenmp
LDFLAGS=-std=c++17 -O3 -march=native -fopenmp
LDLIBS= 

PROGRAM=nolde_vec

SRCS=test1.cpp \
     mydata.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: $(PROGRAM)

mydata.o: mydata.cpp mydata.h

test1.o: test1.cpp mydata.h

$(PROGRAM): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)

clean:
	rm -rf $(OBJS) $(PROGRAM)
