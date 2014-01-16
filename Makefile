# Builds the packet dumpers

CC=gcc
CFLAGS=-O2 -Wall -Werror

TARGETS = af_packet_dump inet_raw_dump

all: $(TARGETS) af_packet_dump inet_raw_dump

af_packet_dump: af_packet_dump.o hexdump.o
inet_raw_dump: inet_raw_dump.o hexdump.o

af_packet_dump..o: af_packet_dump.c
inet_raw_dump.o: inet_raw_dump.c
hexdump.o: hexdump.c

clean:
	rm -f *.o $(TARGETS)
