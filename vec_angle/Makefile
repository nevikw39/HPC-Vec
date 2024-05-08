CC ?= gcc
CFLAGS = -g -O0 -lm
CXX ?= g++
CXXFLAGS = -std=c++17

SRCS = $(wildcard *.c)
BINS = $(basename $(SRCS))
DATS = data.dat

.PHONY: all clean distclean

all: $(BINS)

avx: CFLAGS += -mavx
avx512: CFLAGS += -mavx512f
avx512_fma: CFLAGS += -mavx512f

sse_fma: CFLAGS += -mfma
avx_fma: CFLAGS += -mfma
avx512_fma: CFLAGS += -mfma

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