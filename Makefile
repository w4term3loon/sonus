CC = gcc
WFLAGS = -Wno-deprecated-declarations
WFLAGS += -Wall

demo: SoundDevice.c SoundDevice.h demo.c
	$(CC) $(WFLAGS) demo.c -I/usr/local/include SoundDevice.c -o demo -lopenal -lm

sample: sample.c
	$(CC) $(WFLAGS) -o sample sample.c -lopenal -lm
