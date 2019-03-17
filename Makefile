CC=gcc-8

CFLAGS=-O3 -fopenmp -Wall $(INCDIRS)
LDFLAGS=-O3 -shared -fopenmp $(INCDIRS) $(LIBDIRS) $(LIBS)

_INCDIRS=/Users/jsnguyen/repos/cnbody/include
INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=/Users/jsnguyen/repos/cnbody/lib
LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=m
LIBS=$(addprefix -l,$(_LIBS))

SRCDIR=src
_SRCFILES=body.c gravity.c config.c
SRCS=$(addprefix $(SRCDIR)/,$(_SRCFILES))

OBJDIR=build
_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(addprefix $(OBJDIR)/,$(_OBJFILES))

LIBDIR=lib
LIBNAME=libnb.so

all: $(LIBDIR)/$(LIBNAME)

$(LIBDIR)/$(LIBNAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $< -c -o $@ $(CFLAGS)


.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm $(OBJDIR)/*.o
	rm $(LIBDIR)/*.so
