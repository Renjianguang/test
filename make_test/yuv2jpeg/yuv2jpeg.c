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

typedef unsigned char uint8;

typedef enum {
    IN_YUVNV12, //yuv
    IN_YUVNV21, //yvu
}inyuvfmt_t;

typedef struct{
    char* img_buf;
    int width;
    int height;
    int stride;
    int scanline;
    int format;
    int framenum;
    char* out_path;
}img_info;

tjhandle g_hdl = NULL;

void SplitUVRow(const uint8* src_uv,uint8* dst_u,uint8* dst_v,int width){
    for(int x = 0;x < width -1;x += 2){
        dst_u[x] = src_uv[0];
        dst_u[x+1] = src_uv[2];
        dst_v[x] = src_uv[1];
        dst_v[x+1] = src_uv[3];
        src_uv +=4;
    }
    if (width & 1){
        dst_u[width-1] = src_uv[0];
        dst_v[width-1] = src_uv[1];
    }
}

void SplitUVPlane(const uint8* src_uv,int src_stride_uv,uint8* dst_u,int dst_stride_u,uint8* dst_v,int dst_stride_v,int width,int height){
    for(int y = 0;y < height/2; ++y){
        SplitUVRow(src_uv,dst_u,dst_v,width);
        dst_u += dst_stride_u;
        dst_v += dst_stride_v;
        src_uv += src_stride_uv;
    }
}
void CopyandConvert(img_info* src,uint8* y,uint8* u,uint8* v){
    char* y_plan = src->img_buf;
    int stride = src->stride;
    int scanline = src->scanline;
    int width = src->width;
    int height = src->height;
    inyuvfmt_t in_fmt = src->format;
    unsigned int y_plan_size = src->stride*src->height;
    if(in_fmt == IN_YUVNV12){
        SplitUVPlane((uint8*)y_plan+y_plan_size,stride,u,stride,v,stride,width,height);
    }else if(in_fmt == IN_YUVNV21){
        SplitUVPlane((uint8*)y_plan+y_plan_size,stride,v,stride,u,stride,width,height);
    }
    for(int i = 0; i < height; i++){
    memcpy(y + (i*width),y_plan + (i*stride),width);
    }
}

int Init(){
    g_hdl = tjInitCompress();
    if(g_hdl == NULL){
        printf("tjInitCompress fail!");
    }
}

int DeInit(){
    tjDestroy(g_hdl);
    g_hdl = NULL;
}

int Process(img_info *src){
    int width = src->width;
    int height = src->height;
    int stride = src->stride;
    int scanline = src->scanline;
    char* out_path = src->out_path;
    unsigned long framenum = src->framenum;
    //分配 y,u,v分量内存，接受输入yuv图的数据
    uint8* y = (uint8*)malloc(width*height);
    uint8* u = (uint8*)malloc(width*height);
    uint8* v = (uint8*)malloc(width*height);
    //分割分量
    CopyandConvert(src,y,u,v);
    uint8* jpeg_buf = NULL;
    unsigned long  jpeg_size;
    uint8* srcplanes[] = {y,u,v};
    int strides[3] = {0};

    //!!此处有问题
    strides[0] = strides[1] = strides[2] = stride;
    //compress
    tjCompressFromYUVPlanes(g_hdl,(const uint8**)srcplanes,width,strides,height,TJSAMP_420,&jpeg_buf,&jpeg_size,100,0);
    free(y);
    free(u);
    free(v);
    //将压缩后的数据写入文件
    char outfile[256];
    snprintf(outfile,sizeof(outfile),"%s/%dx%d_%lu.jpg",out_path,width,height,framenum);
    int out_fd = open(outfile,O_RDWR|O_CREAT,0644);
    write(out_fd,jpeg_buf,jpeg_size);
    close(out_fd);
    free(jpeg_buf);
}

int main(int argc,char* argv[]){
    img_info src = {0};
    src.width = src.stride = atoi(argv[3]);
    src.height = src.scanline = atoi(argv[4]);
    src.out_path = argv[2];
    src.format = 0;
    int in_fd = open(argv[1],O_RDONLY);
    int file_size = lseek(in_fd,0,SEEK_END);
    lseek(in_fd,0,SEEK_SET);
    src.img_buf = (char*)malloc(file_size);
    int rd_size = read(in_fd,src.img_buf,file_size);
    close(in_fd);
    Init();
    Process(&src);
    DeInit();
    return 0;
}


























