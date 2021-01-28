SRC_PACKAGES = BOOST
BOOST_ROOT = /usr/local/include/boost_1_75_0

EXTRA_INCLUDE_DIR = $(foreach loop, $(SRC_PACKAGES), -I$($(loop)_ROOT))

# compiler
CXX = g++
CPPFLAGS = -g -Wall $(EXTRA_INCLUDE_DIR)

SRC_DIR = src

EXEC = solver
SOURCES = $(wildcard $(foreach loop, $(SRC_DIR), $(loop)/*.cc))
OBJECTS = $(patsubst %.cc, %.o, $(SOURCES))

$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $^

.PHONEY: clean
clean:
	rm $(SRC_DIR)/*.o
