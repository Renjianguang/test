#!/bin/bash

in_dir=$1
out_dir=$2
in_width=$3
in_height=$4
in_stride=$5
in_scanline=$6
fmt=$7

echo "$#"

if [ "$#" != "7" ];then
    echo "Usage:"
    echo "  ./yuv2jpegDir [indir] [out_dir] [in_width] [in_height] [in_stride] [in_scanline] [fmt]"
    echo "FMT:"
    echo "   0 -->  NV12"
    echo "   1 -->  NV21"
    exit -1
fi

files=(`ls $in_dir`)
#echo "files: ${files[*]}"

for i in ${files[*]}
do
    echo $i
done

mkdir -p ${out_dir}

#./yuv2jpeg --infile [infile] --inwidth [width] --inheight [height] --instride [stride] --inscanline [scanline] --infmt [fmt] --outfile [outfile]
for i in ${files[*]}
do
    echo " ================================================================\n"
    echo "./binary/64/yuv2jpeg --infile ${in_dir}/$i --inwidth ${in_width} --inheight ${in_height} --instride ${in_stride} --inscanline ${in_scanline} --infmt ${fmt} --outfile $out_dir/$i.jpeg"
    ./binary/64/yuv2jpeg --infile ${in_dir}/$i --inwidth ${in_width} --inheight ${in_height} --instride ${in_stride} --inscanline ${in_scanline} --infmt ${fmt} --outfile $out_dir/$i.jpeg
    echo "\n ================================================================ \n\n"
done
