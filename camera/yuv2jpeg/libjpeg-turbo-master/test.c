#include <turbojpeg.h>
#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>
#include <custom_define.h>
int yuv420sp_to_jpg(char *filename, int width, int height, unsigned char *pYUVBuffer)
{
    FILE *fJpg;
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    int row_stride;
    int i = 0, j = 0;
    unsigned char yuvbuf[width * 3];
    unsigned char *pY, *pU, *pV;
    int ulen;

    ulen = width * height / 4;

    if(pYUVBuffer == NULL){
        printf("pBGRBuffer is NULL!\n");
        return -1;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    fJpg = fopen(filename, "wb");
    if(fJpg == NULL){
        printf("Cannot open file %s, %s\n", filename, strerror(errno));
        jpeg_destroy_compress(&cinfo);
        return -1;
    }

    jpeg_stdio_dest(&cinfo, fJpg);
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_YCbCr;
    cinfo.dct_method = JDCT_ISLOW;
    jpeg_set_defaults(&cinfo);


    jpeg_set_quality(&cinfo, 99, TRUE);

    jpeg_start_compress(&cinfo, TRUE);
    row_stride = cinfo.image_width * 3; /* JSAMPLEs per row in image_buffer */
    
    pY = pYUVBuffer;
    pU = pYUVBuffer + width*height;
    pV = pYUVBuffer + width*height + ulen;
    j = 1;
    while (cinfo.next_scanline < cinfo.image_height) {
        /* jpeg_write_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could pass
         * more than one scanline at a time if that's more convenient.
         */

        /*Test yuv buffer serial is : yyyy...uu..vv*/
        if(j % 2 == 1 && j > 1){
            pU = pYUVBuffer + width*height + width / 2 * (j / 2);
            pV = pYUVBuffer + width*height * 5 / 4 + width / 2 *(j / 2);
        }
        for(i = 0; i < width; i += 2){
            yuvbuf[i*3] = *pY++;
            yuvbuf[i*3 + 1] = *pU;
            yuvbuf[i*3 + 2] = *pV;

            yuvbuf[i*3 + 3] = *pY++;
            yuvbuf[i*3 + 4] = *pU++;
            yuvbuf[i*3 + 5] = *pV++;
        }

        row_pointer[0] = yuvbuf;
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
        j++;
    }

    jpeg_finish_compress(&cinfo);

    jpeg_destroy_compress(&cinfo);
    fclose(fJpg);

    return 0;
}

int main(int argc,char* argv[]){
	unsigned char* pyuv = (char*)malloc(4*388800);
	int fd =open(argv[1],O_RDONLY | O_CREAT,S_IRUSR | S_IWUSR);
	if (!fd) {
		printf("open src file error!");
		return 1;
	}
	int size = read(fd,pyuv,4*388800);
	if (size == -1) {
		printf("read frome src file error!");
		return 2;
	}
	int ret = yuv420sp_to_jpg(argv[2],960,540,pyuv);
	if (ret == -1) {
		printf("yuv420sp_to_jpg error!");
		return 3;
	}
	return 0;
}
