CC = gcc
INCCLUDE = ./include/
LIBPATH = ./lib/
LIBS = turbojpeg
CFLAGE = -I $(INCCLUDE) -L $(LIBPATH) -l $(LIBS)
yuv2jpeg:yuv2jpeg.c
	$(CC) $< -o $@ $(CFLAGE)
clean:
	rm yuv2jpeg
