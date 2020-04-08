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
#include <turbojpeg.h>
//#include "libyuv.h"

#define ALIGN(x,a)    (((x)+(a)-1)&~(a-1))


//using namespace libyuv;


typedef enum {
    IN_YUVNV12, //yuv
    IN_YUVNV21, //yvu
}inyuvfmt_t;

int compress(tjhandle hdl, int width, int height, char *y, char *u, char *v, char **jpeg_buf, unsigned long *jpeg_size)
{

    /*
     * DLLEXPORT int DLLCALL tjCompressFromYUVPlanes(tjhandle handle,
     *   const unsigned char **srcPlanes, int width, const int *strides, int height,
     *     int subsamp, unsigned char **jpegBuf, unsigned long *jpegSize, int jpegQual,
     *       int flags);
     *
     * */
    unsigned char *srcplanes[] = { (unsigned char *)y, (unsigned char *)u, (unsigned char *)v};
    int strides[3] = {0};
    strides[0] = 0;
    strides[1] = strides[2] = 1536;
    printf("width: %d, height: %d\n", width, height);

    tjCompressFromYUVPlanes(hdl, (const unsigned char **)srcplanes, width, strides, height,  TJSAMP_420, \
        (unsigned char **)jpeg_buf, (unsigned long *)jpeg_size, 100, 0);
    return 0;
}


int formatyuv(char *buf, char *y, char *u, char *v, inyuvfmt_t in_fmt, uint32_t in_width, uint32_t in_height, uint32_t in_stride, uint32_t in_scanline)
{

    char *y_plan = buf;
    uint32_t y_plan_size = ALIGN(in_stride * in_scanline, 4*1024);
    //uint32_t y_plan_size = in_stride * in_scanline;
    printf("y_plan_size: %u\n", y_plan_size);
   /* if (in_fmt == IN_YUVNV12) {
        SplitUVPlane((uint8 *)y_plan+y_plan_size, in_stride, (uint8 *)u, in_stride, (uint8 *)v, in_stride, in_width, in_height);
    } else if (in_fmt == IN_YUVNV21) {
        SplitUVPlane((uint8 *)y_plan+y_plan_size, in_stride, (uint8 *)v, in_stride, (uint8 *)u, in_stride, in_width, in_height);
    }*/
    for (int i = 0; i < (int)in_height; i++) {
        memcpy(y + (i * in_width), y_plan + (i * in_stride), in_width);
    }
    char *p = u,*q = v;
    for (int i = 0; i < (int)(in_height/2); i++) {
        for (int j = 0; j < (int)in_width; j++) {
            if (j%2 == 0){
                memcpy(p++, y_plan + ((in_height + i) * in_stride) + j,1);
            }else{
                memcpy(q++, y_plan + ((in_height + i) * in_stride) + j,1);
            }
        }
    }
    return 0;
}



void showhelp()
{
    printf("./yuv2jpeg --infile [infile] --inwidth [width] --inheight [height] --instride [stride] --inscanline [scanline] --infmt [fmt] --outfile [outfile]\n");
    printf("fmt: \n");
    printf("  0 --> NV12\n");
    printf("  1 --> NV21\n");
}


int main(int argc, char **argv)
{

    int option_index = 0;
    int opt_v;


    struct option long_options[] = {
        {"infile", required_argument, &opt_v, 1},
        {"inwidth", required_argument, &opt_v, 2},
        {"instride", required_argument, &opt_v, 3},
        {"inscanline", required_argument, &opt_v, 4},
        {"infmt", required_argument, &opt_v, 5},
        {"outfile", required_argument, &opt_v, 6},
        {"inheight", required_argument, &opt_v, 7},
        {0, 0, 0, 0},
    };

    if (argc != 15) {
        showhelp();
        return -1;
    }

    char *infile = NULL;
    uint32_t inwidth = 0;
    uint32_t instride = 0;
    uint32_t inscanline = 0;
    uint32_t infmt = 0;
    char *outfile = NULL;
    uint32_t inheight = 0;

    while (1) {
        int opt_index = 0;
        int ret = getopt_long(argc, argv, "", long_options, &opt_index);
        if (ret < 0) {
            break;
        }

        switch(opt_v) {
            case 0: {
                break;
            }
            case 1: {
                infile = optarg;
                break;
            }
            case 2: {
                inwidth = atoi(optarg);
                break;
            }
            case 3: {
                instride = atoi(optarg);
                break;
            }
            case 4: {
                inscanline = atoi(optarg);
                break;
            }
            case 5: {
                infmt = atoi(optarg);
                break;
            }
            case 6: {
                outfile = optarg;
                break;
            }
            case 7: {
                inheight = atoi(optarg);
                break;
            }
            default:{
                break;
            }
        };
    }

    printf("infile: %s, inwidth: %d, inheight: %d,  instride: %d, inscanline: %d, infmt: %d, outfile: %s\n", \
        infile, inwidth, inheight, instride, inscanline, infmt, outfile);

    int fd = open(infile, O_RDONLY);
    if (fd < 0) {
        printf("file: %s, fd: %d", infile, fd);
        showhelp();
        return -1;
    }


    int file_size = lseek(fd, 0, SEEK_END);

    lseek(fd, 0, SEEK_SET);

    char *yuv_buf = (char *)malloc(file_size);
    /*char *jpeg_buf = (char *)malloc(file_size);*/
    char *jpeg_buf = NULL;
    unsigned long jpeg_size;

    read(fd, yuv_buf, file_size);

    char *y = (char *)malloc(instride*inscanline);
    char *u = (char *)malloc(instride*inscanline);
    char *v = (char *)malloc(instride*inscanline);

    printf("y: %p, u: %p, v: %p\n", y, u, v);


    formatyuv(yuv_buf, y, u, v, (inyuvfmt_t)infmt, inwidth, inheight, instride, inscanline);

#define DEBUG 0
#if DEBUG
    {
        {
            int fd = open("./y.data", O_RDWR|O_CREAT, 0644);
            write(fd, y, instride*inscanline);
        }

        {
            int fd = open("./u.data", O_RDWR|O_CREAT, 0644);
            write(fd, u, instride*inscanline);
        }

        {
            int fd = open("./v.data", O_RDWR|O_CREAT, 0644);
            write(fd, v, instride*inscanline);
        }
    }
#endif

    tjhandle hdl = tjInitCompress();
    compress(hdl, inwidth, inheight, y, u, v, &jpeg_buf, &jpeg_size);
    tjDestroy(hdl);

    int out_fd = open(outfile, O_RDWR|O_CREAT, 0644);
    write(out_fd, jpeg_buf, jpeg_size);

    close(fd);
    close(out_fd);
    free(yuv_buf);
    free(y);
    free(u);
    free(v);


    printf("jpegbuf: %p, jpeg_size: %lu\n", jpeg_buf, jpeg_size);

}
