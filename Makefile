
#-------------------------------------------------------------------------------
# project settings
#-------------------------------------------------------------------------------

TARGET_NAMES = rpg/main

# .o / .cpp / .h / .d directories
# -------------------------------
# location of output executables
BINDIR := bin
# location of .o files
OBJDIR := obj
# location of .cpp files
SRCDIR := src
# location of .h files
INCDIR := include
# location of .d files
DEPDIR := .deps

#-------------------------------------------------------------------------------
# dependency settings
#-------------------------------------------------------------------------------

ifeq ($(OS), Windows_NT) # Windows dependencies

LIBDIRS += \
D:/libs/sfml_2.5.1 \
# D:/SFML-2.5.1

LIBNAMES += \
sfml-graphics-s \
sfml-window-s \
sfml-system-s \
opengl32 \
winmm \
gdi32 \
freetype \

else # Unix dependencies

LIBNAMES += \
sfml-graphics \
sfml-window \
sfml-system \

endif

#-------------------------------------------------------------------------------
# compiler settings
#-------------------------------------------------------------------------------

# the c++ compiler to use
CC = g++

# compiler flags
CFLAGS += -U__STRICT_ANSI__ -Wall -std=c++1z -DDEBUG

ifeq ($(OS), Windows_NT) # Windows ----------

	CFLAGS += -static -static-libgcc -static-libstdc++
	CFLAGS += -DSFML_STATIC

else # Unix ---------------------------------

endif

#-------------------------------------------------------------------------------
# !! automatic below !!
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# compiler flags variables
#-------------------------------------------------------------------------------

TARGETS += $(TARGET_NAMES:%=$(SRCDIR)/%.cpp)
$(info TARGETS = $(TARGETS))

EXES += $(TARGET_NAMES:%=$(BINDIR)/%)

INCFLAGS += \
	$(INCDIR:%=-I'%') \
	$(LIBDIRS:%=-isystem'%/include') \

LIBFLAGS += \
	$(addprefix -l, \
	$(LIBNAMES))

LIBDIRFLAGS += $(LIBDIRS:%=-L'%/lib')

# -MT: sets the name of the target generated
# -MMD: ignores system headers when generating dependancies
# -MP: generates phony targets for each dependency
# -MF: sets the name of the .d file generated

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

#-------------------------------------------------------------------------------
# find source files
#-------------------------------------------------------------------------------

$(info collecting source/header files...)

# automatically find all source files in this project and store it in $(SRCS)
# (first wildcard gets root-level .cpp's, second gets nested .cpp's)

ifeq ($(OS), Windows_NT)

    ALL_SRCS := $(shell dir /s/b *.cpp)
    ALL_SRCS := $(ALL_SRCS:$(shell cd)\\%=%)
    ALL_SRCS := $(subst \,/,$(ALL_SRCS))

else

    ALL_SRCS := $(shell find src/ -type f -name "*.cpp")

endif

SRCS := $(filter-out $(TARGETS),$(ALL_SRCS))

OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

DEPS := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)

EXES := $(addprefix $(BINDIR)/, $(TARGET_NAMES))

# Windows vars
# ------------

ifeq ($(OS), Windows_NT)

EXES := $(EXES:=.exe)

endif

#-------------------------------------------------------------------------------
# command variables
#-------------------------------------------------------------------------------

# compile/link commands

COMPILE.c =\
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $(INCFLAGS) $(FLAGS) $< -o $@

LINK.c	  =\
	$(CC) $^ $(CFLAGS) $(LIBDIRFLAGS) $(LIBFLAGS) $(FLAGS) -o $@

ifeq ($(OS), Windows_NT)

	# execute
	RUN.c = \
		$(eval POST ?= $(firstword $(TARGETS))) \
		$(POST)


	# execute & debug
	DEBUG.c = gdb -ex='set confirm on' -ex=run -ex=quit --args $(BINDIR)\$(PROJECT_NAME)
	#$(OUTFILE)

	# commands to silently make missing folders

	MKDIR_OBJS.c = \
		$(eval OBJDIR_WIN = $(subst /,\,$(@D))) \
		@if not exist "$(OBJDIR_WIN)" mkdir $(OBJDIR_WIN)
	MKDIR_DEPS.c = \
		$(eval DEPDIR_WIN = $(subst /,\,$(subst $(OBJDIR),$(DEPDIR),$(@D)))) \
		@if not exist "$(DEPDIR_WIN)" mkdir $(DEPDIR_WIN)
	MKDIR_BINS.c = \
		$(eval BINDIR_WIN = $(subst /,\,$(subst $(OBJDIR),$(BINDIR),$(@D)))) \
		@if not exist "$(BINDIR_WIN)" mkdir $(BINDIR_WIN)

	# clean command
	CLEAN.c = del /Q /S *.exe *.o *.d

# Unix vars
# ---------

else

	# execute
	RUN.c = \
		$(eval POST ?= $(firstword $(TARGETS))) \
		$(POST)

	# execute & debug
	DEBUG.c = gdb -ex run $(BINDIR)/$(PROJECT_NAME)

	# create missing folders
	MKDIR.c      = @mkdir -p $(@D)
	MKDIR_OBJS.c = @mkdir -p $(OBJDIR)
	MKDIR_DEPS.c = @mkdir -p $(DEPDIR)
	MKDIR_BINS.c = @mkdir -p $(BINDIR)

	# clean
	CLEAN.c = rm -rf $(OBJDIR)/*; rm -rf $(BINDIR)/*; rm -f $(OUTFILE); rm -rf $(DEPDIR)/*

endif

#==============================================================================
# targets
#==============================================================================

%.o : %.cpp # remove default target

# compile
# -------

$(DEPDIR)/%.d : $(OBJDIR)/%.o

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(MKDIR_OBJS.c)
	$(MKDIR_DEPS.c)
	$(MKDIR_BINS.c)
	$(MKDIR.c)
	$(COMPILE.c)

# link
# ----

$(BINDIR)/% $(BINDIR)/%.exe : $(OBJDIR)/%.o $(OBJS)
	@echo [INFO] creating exec $@
	$(MKDIR_BINS.c)
	$(LINK.c)

include $(wildcard $(DEPS))

#==============================================================================
# utility rules
#==============================================================================

.PHONY: info all run run-debug run-test clean set-debug

# prevents make from deleting .o files on success
.SECONDARY: $(OBJS)

info :
	@echo =====================================================================
	@echo COMPILING INFO:
	@echo =====================================================================
	@echo additional flags: $(FLAGS)
	@echo working dir: $(CD)
	@echo src dir: $(SRCDIR)/
	@echo inc dir: $(INCDIR)/
	@echo dep dir: $(DEPDIR)/
	@echo bin dir: $(BINDIR)/
	@echo exes: $(EXES)
	@echo objs: $(OBJS)
	@echo srcs: $(ALL_SRCS)
	@echo =====================================================================

# sets flags to compile the program for use in GDB
set-debug:
	$(eval FLAGS=-g -DDEBUG)

all : info $(EXES)

run: all
	$(RUN.c)

run-debug: set-debug all
	$(DEBUG.c)

clean:
	$(CLEAN.c)


