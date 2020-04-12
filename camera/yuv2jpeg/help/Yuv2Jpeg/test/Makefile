.PHONY: clean
NDKROOT=/opt/android_ndk/android-ndk-r21
PLATFORM=$(NDKROOT)/platforms/android-29/arch-arm64
CROSS_COMPILE=$(NDKROOT)/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-
CC=$(NDKROOT)/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android29-clang
AR=$(CROSS_COMPILE)ar
LD=$(CROSS_COMPILE)ld
CFLAGS = -I$(PWD) -I$(PLATFORM)/usr/include -Wall -O2 -fPIC -DANDROID -DHAVE_PTHREAD -mfpu=neon -mfloat-abi=softfp
LDFLAGS =
TARGET =renjg.a
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(AR) -rc $(TARGET) $(OBJS)
clean:
	rm -f *.o *.a *.so
