program_NAME := text_based_engine

program_C_SRCS := sqlite3/sqlite3.c
program_CXX_SRCS := $(wildcard *.cpp \
	dependencies/dep/*.cpp \
	sql_helpers/*.cpp \
	sql_helpers/*/*.cpp)

program_C_OBJS := ${program_C_SRCS:.c=.o}
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)
program_INCLUDE_DIRS := dependencies sqlite3
program_LIBRARY_DIRS := ../../_libs/_master/lib
program_LIBRARIES := pthread dl

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
CXXFLAGS += -std=c++11 -g -O0
LIB_DIR += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

# Prevents filename issues.
.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(info $(CXX))
	$(CXX) $(LIB_DIR) $(CXXFLAGS) -o $(program_NAME) $(program_OBJS) $(LDFLAGS)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean