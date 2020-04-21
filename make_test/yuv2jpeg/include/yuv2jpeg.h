
#ifndef __YUV2JPEG_H__
#define __YUV2JPEG_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "turbojpeg.h"

tjhandle g_hdl = NULL;

typedef unsigned char uint8;

typedef enum {
    IN_YUVNV12, //yuv
    IN_YUVNV21, //yvu
}inyuvfmt_t;

typedef struct{
    char* src_img;
    int width;
    int height;
    int instride;
    int inscanline;
    int format;
    int framenum;
    char* out_path;
}img_info;

int Init();

int Process(img_info* src_yuv);

int Deinit();
#endif
