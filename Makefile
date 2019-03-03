CC=gcc-8

SRCDIR=src
OBJDIR=build

_INCDIRS=include
INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=lib
LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=m
LIBS=$(addprefix -l,$(_LIBS))

CFLAGS=-O3 -fopenmp -Wall $(INCDIRS)
LDFLAGS=-O3 -fopenmp $(INCDIRS) $(LIBDIRS) $(LIBS)

_SRCFILES=body.c gravity.c sim.c
SRCS=$(addprefix $(SRCDIR)/,$(_SRCFILES))

_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(addprefix $(OBJDIR)/,$(_OBJFILES))

EXES=sim.exe

all: $(EXES)

%.exe : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $< -c -o $@ $(CFLAGS)

.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm $(OBJDIR)/*.o
	rm *.exe
