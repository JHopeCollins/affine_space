
#-------------------------------------

# directories
INCLDEDIR = inc/#	      header .h files
SOURCEDIR = src/#			class / function .cpp source files
SCRIPTDIR = script/#		main() function .cpp source files
PROGRMDIR = progrm/#		executables

# Class / function definition source files
CSOURCE = scalar.cpp \
			 vector.cpp

# main() function files
CSCRIPT = tests.cpp

# optimised (opt) or debug (dbg) mode?
#MODE = opt
MODE = dbg

# compiler
#CCMP = g++-11
CCMP = clang++-10

#-------------------------------------

ifeq ($(MODE),dbg) # debug flags
COPT = -ggdb3 -fsanitize=address,undefined -fno-omit-frame-pointer# -D_GLIBCXX_DEBUG
else ifeq ($(MODE),opt) # optimisation flags
COPT = -O3# -DNDEBUG
else
$(error specify MODE as dbg or opt)
endif

# warnings
CWARN = -Wall -Wextra -Wpedantic -Wshadow -Wconversion# -fconcepts-diagnostics-depth=2

# language specs
CSTD = -std=c++20

# external libraries, eg lapack, blas
LIBS =

#-------------------------------------
#  variable definitions

DIRS = $(INCLDEDIR) $(SOURCEDIR) $(SCRIPTDIR) $(PROGRMDIR)

INCLDE = $(addprefix -I,$(INCLDEDIR)) -I../affine_space/

# full paths for source, script and executable files
SOURCE = $(addprefix $(SOURCEDIR),$(CSOURCE))
SCRIPT = $(addprefix $(SCRIPTDIR),$(CSCRIPT))
PROGRM = $(addprefix $(PROGRMDIR),$(CSCRIPT:.cpp=.out))

# names of scripts (no suffix)
PNAMES = $(CSCRIPT:.cpp=)

# object files
SOURCEOBJ = $(SOURCE:.cpp=.o)
SCRIPTOBJ = $(SCRIPT:.cpp=.o)

OBJS = $(SOURCEOBJ) $(SCRIPTOBJ)

#-------------------------------------
# compilation recipes

# default
%.o : %.cpp
	$(CCMP) $(COPT) $(CSTD) $(CWARN) $(INCLDE) -o $@ -c $<

# each executable depends on its own object file, and all source objects

$(PROGRM) : $(PROGRMDIR)%.out : $(SCRIPTDIR)%.o $(SOURCEOBJ)
	$(CCMP) $(COPT) $(CSTD) $(CWARN) $(INCLDE) -o $@ $^ $(LIBS)


#-------------------------------------
# misc recipes

.PHONY : $(PNAMES) all names clean flags mkdir

# make <pname> will compile only the executable 'pname.out'
$(PNAMES) : % : $(PROGRMDIR)%.out

# make all executables
all: $(PROGRM)

# print names of all executables to standard output
names:
	@for name in $(PNAMES); do echo $$name; done

# delete all non-source files
clean:
	rm -f $(OBJS) $(PROGRM)

# print compilation flags
flags:
	@echo $(COPT) $(CSTD) $(CWARN) $(INCLDE)

# create required directories
mkdir:
	mkdir $(DIRS)

