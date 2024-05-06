CC ?= gcc
CFLAGS = -g -O0 -lm
CXX ?= g++
CXXFLAGS = -std=c++17

SRCS = $(wildcard *.c)
BINS = $(basename $(SRCS))
DATS = data.dat

.PHONY: all clean distclean

all: $(BINS)

avx2: CFLAGS += -mavx2

%: %.c | $(DATS)
	$(CC) $< -o $@ $(CFLAGS)

$(DATS): | gen
	./gen

gen: gen.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

clean:
	@-rm $(BINS)

distclean: clean
	@-rm *.dat gen