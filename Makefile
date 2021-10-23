CC=gcc
CFLAGS=-O2

DEPS = pgm.h effects.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: pgm_efekt pgm_median

pgm_efekt: pgm.o effects.o effects_main.o
	$(CC) $(CFLAGS) -o $@ $^
	
pgm_median: pgm.o median_main.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o pgm_efekt pgm_median binarize_* noise_* invert_* smooth_* sharpen_* brightness_*