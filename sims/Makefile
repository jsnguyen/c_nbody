CC=gcc-8

_INCDIRS=/Users/jsnguyen/repos/cnbody/include
INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=/Users/jsnguyen/repos/cnbody/lib
LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=m nb
LIBS=$(addprefix -l,$(_LIBS))

CFLAGS=-O3 -fopenmp -Wall $(INCDIRS)
LDFLAGS=-O3 -fopenmp $(INCDIRS) $(LIBDIRS) $(LIBS)

_SRCFILES=sim.c
SRCS=$(_SRCFILES)

_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(_OBJFILES)

EXES=sim.exe

LIBNAME=libnb.so

all: $(EXES)

%.exe: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) $< -c -o $@ $(CFLAGS)


.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm *.o
	rm *.exe
