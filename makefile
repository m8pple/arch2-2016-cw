# Your login. For example, mine is dt10. Yours
# won't be eie2ugs...
LOGIN ?= eie2ugs

# Turn on all warnings
CPPFLAGS += -W -Wall

# Add debug information
CPPFLAGS += -g

# Pick up any headers in the ./include directories
CPPFLAGS += -I include

# C++11 by default
CXXFLAGS += -std=c++11

DEFAULT_OBJECTS = \
	src/shared/mips_test_framework.o \
	src/shared/mips_mem_ram.o 

USER_CPU_SRCS = \
	$(wildcard src/$(LOGIN)/mips_cpu.cpp) \
	$(wildcard src/$(LOGIN)/mips_cpu_*.cpp) \
	$(wildcard src/$(LOGIN)/mips_cpu/*.cpp) \
	$(wildcard src/$(LOGIN)/mips_cpu_*/*.cpp)

	
USER_TEST_SRCS = \
	$(wildcard src/$(LOGIN)/test_mips.cpp) \
	$(wildcard src/$(LOGIN)/test_mips_*.cpp) \
	$(wildcard src/$(LOGIN)/test_mips/*.cpp) \
	$(wildcard src/$(LOGIN)/test_mips_*/*.cpp)

	
USER_CPU_OBJECTS = $(patsubst %.cpp,%.o,$(USER_CPU_SRCS))
USER_TEST_OBJECTS = $(patsubst %.cpp,%.o,$(USER_TEST_SRCS))

src/$(LOGIN)/test_mips : $(DEFAULT_OBJECTS) $(USER_CPU_OBJECTS) $(USER_TEST_OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LFLAGS) $(LDLIBS)
	

fragments/run_fibonacci : $(DEFAULT_OBJECTS) $(USER_CPU_OBJECTS)
	
fragments/run_addu : $(DEFAULT_OBJECTS) $(USER_CPU_OBJECTS)

clean : 
	-rm src/$(LOGIN)/test_mips
	-rm $(DEFAULT_OBJECTS) $(USER_CPU_OBJECTS) $(USER_TEST_OBJECTS)

all : src/$(LOGIN)/test_mips
