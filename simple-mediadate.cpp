//
// Created by st199 on 2021/11/29.
//

#include "simple-mediadate.h"
// simplest_h264_parser.cpp: 定义控制台应用程序的入口点。
//严重性	代码	说明	项目	文件	行	禁止显示状态
//错误	C4996	'fopen': This function or variable may be unsafe.Consider using fopen_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.simplest_h264_parser	c : \users\administrator\source\repos\simplest_h264_parser\simplest_h264_parser\simplest_h264_parser.cpp	198


//#include "stdafx.h"
/**
* 最简单的视音频数据处理示例
* Simplest MediaData Test
*
* 雷霄骅 Lei Xiaohua
* leixiaohua1020@126.com
* 中国传媒大学/数字电视技术
* Communication University of China / Digital TV Technology
* http://blog.csdn.net/leixiaohua1020
*
* 本项目包含如下几种视音频测试示例：
*  (1)像素数据处理程序。包含RGB和YUV像素格式处理的函数。
*  (2)音频采样数据处理程序。包含PCM音频采样格式处理的函数。
*  (3)H.264码流分析程序。可以分离并解析NALU。
*  (4)AAC码流分析程序。可以分离并解析ADTS帧。
*  (5)FLV封装格式分析程序。可以将FLV中的MP3音频码流分离出来。
*  (6)UDP-RTP协议分析程序。可以将分析UDP/RTP/MPEG-TS数据包。
*
* This project contains following samples to handling multimedia data:
*  (1) Video pixel data handling program. It contains several examples to handle RGB and YUV data.
*  (2) Audio sample data handling program. It contains several examples to handle PCM data.
*  (3) H.264 stream analysis program. It can parse H.264 bitstream and analysis NALU of stream.
*  (4) AAC stream analysis program. It can parse AAC bitstream and analysis ADTS frame of stream.
*  (5) FLV format analysis program. It can analysis FLV file and extract MP3 audio stream.
*  (6) UDP-RTP protocol analysis program. It can analysis UDP/RTP/MPEG-TS Packet.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//- Network Abstraction Layer Units（NALU）
/*
H264编码数据存储或传输的基本单元，一般H264码流最开始的两个NALU是SPS和PPS，第三个NALU是IDR。SPS、PPS、SEI这三种NALU不属于帧的范畴。
*/
typedef enum {
    NALU_TYPE_SLICE = 1,
    NALU_TYPE_DPA = 2,
    NALU_TYPE_DPB = 3,
    NALU_TYPE_DPC = 4,
    NALU_TYPE_IDR = 5,	//-IDR(Instantaneous Decoding Refresh)：即时解码刷新。
    NALU_TYPE_SEI = 6,	//-SEI(Supplemental enhancement information)：附加增强信息，包含了视频画面定时等信息，一般放在主编码图像数据之前，在某些应用中，它可以被省略掉。
    NALU_TYPE_SPS = 7,	//-SPS(Sequence Parameter Sets)：序列参数集，作用于一系列连续的编码图像。
    NALU_TYPE_PPS = 8,	//-PPS(Picture Parameter Set)：图像参数集，作用于编码视频序列中一个或多个独立的图像。
    NALU_TYPE_AUD = 9,
    NALU_TYPE_EOSEQ = 10,
    NALU_TYPE_EOSTREAM = 11,
    NALU_TYPE_FILL = 12,
} NaluType;//-NALU类型

typedef enum {
    NALU_PRIORITY_DISPOSABLE = 0,
    NALU_PRIORITY_LOW = 1,
    NALU_PRIORITY_HIGH = 2,
    NALU_PRIORITY_HIGHEST = 3
} NaluPriority;//-NALU优先级

/*
NAL Header由三部分组成：
forbidden_bit(1bit)
nal_reference_bit(2bits)（优先级）
nal_unit_type(5bits)（类型）
*/
typedef struct
{
    int startcodeprefix_len;      //! 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
    unsigned len;                 //! Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
    unsigned max_size;            //! Nal Unit Buffer size
    //-下面三个变量是NAL Header
    int forbidden_bit;            //! should be always FALSE
    int nal_reference_idc;        //! NALU_PRIORITY_xxxx
    int nal_unit_type;            //! NALU_TYPE_xxxx

    char *buf;                    //! contains the first byte followed by the EBSP
} NALU_t;//-h.264的单元

FILE *h264bitstream = NULL;                //!< the bit stream file

int info2 = 0, info3 = 0;

static int FindStartCode2(unsigned char *Buf) {
    if (Buf[0] != 0 || Buf[1] != 0 || Buf[2] != 1) return 0; //0x000001?
    else return 1;
}

static int FindStartCode3(unsigned char *Buf) {
    if (Buf[0] != 0 || Buf[1] != 0 || Buf[2] != 0 || Buf[3] != 1) return 0;//0x00000001?
    else return 1;
}


/*
*/
//- Annex(附加)
//-	得到NALU_t
int GetAnnexbNALU(NALU_t *nalu) {
    int pos = 0;
    int StartCodeFound, rewind;
    unsigned char *Buf;

    //- 给Buf分配nalu->max_size的空间
    if ((Buf = (unsigned char*)calloc(nalu->max_size, sizeof(char))) == NULL)
        printf("GetAnnexbNALU: Could not allocate Buf memory\n");

    nalu->startcodeprefix_len = 3;

    //- 若输入的h.264流文件没有3bits返回
    if (3 != fread(Buf, 1, 3, h264bitstream)) {
        free(Buf);
        return 0;
    }
    info2 = FindStartCode2(Buf);
    if (info2 != 1) {
        if (1 != fread(Buf + 3, 1, 1, h264bitstream)) {
            free(Buf);
            return 0;
        }
        info3 = FindStartCode3(Buf);
        if (info3 != 1) {
            free(Buf);
            return -1;
        }
        else {
            pos = 4;
            nalu->startcodeprefix_len = 4;
        }
    }
    else {
        nalu->startcodeprefix_len = 3;
        pos = 3;
    }
    StartCodeFound = 0;
    info2 = 0;
    info3 = 0;

    while (!StartCodeFound) {
        if (feof(h264bitstream)) {
            nalu->len = (pos - 1) - nalu->startcodeprefix_len;
            memcpy(nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);
            nalu->forbidden_bit = nalu->buf[0] & 0x80;		//- 10000000   //1 bit
            nalu->nal_reference_idc = nalu->buf[0] & 0x60;	//- 01100000   // 2 bit
            nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;	//- 00011111   // 5 bit
            free(Buf);
            return pos - 1;
        }
        Buf[pos++] = fgetc(h264bitstream);
        info3 = FindStartCode3(&Buf[pos - 4]);
        if (info3 != 1)
            info2 = FindStartCode2(&Buf[pos - 3]);
        StartCodeFound = (info2 == 1 || info3 == 1);
    }

    // Here, we have found another start code (and read length of startcode bytes more than we should
    // have.  Hence, go back in the file
    rewind = (info3 == 1) ? -4 : -3;

    if (0 != fseek(h264bitstream, rewind, SEEK_CUR)) {
        free(Buf);
        printf("GetAnnexbNALU: Cannot fseek in the bit stream file");
    }

    // Here the Start code, the complete NALU, and the next start code is in the Buf.
    // The size of Buf is pos, pos+rewind are the number of bytes excluding the next
    // start code, and (pos+rewind)-startcodeprefix_len is the size of the NALU excluding the start code
    /*
    */
    nalu->len = (pos + rewind) - nalu->startcodeprefix_len;
    memcpy(nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);//
    //-得到NAL Header的信息
    nalu->forbidden_bit = nalu->buf[0] & 0x80;		//- 10000000   //1 bit
    nalu->nal_reference_idc = nalu->buf[0] & 0x60;	//- 01100000   // 2 bit
    nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;	//- 00011111   // 5 bit
    free(Buf);

    return (pos + rewind);
}


//-解析H.264的函数
/**
* Analysis H.264 Bitstream
* @param url    Location of input H.264 bitstream file.
*/
int simplest_h264_parser(const char *url) {

    NALU_t *n;
    int buffersize = 100000;

    FILE *myout=fopen("output_log.txt","wb+");
    //FILE *myout = stdout;

    h264bitstream = fopen(url, "rb+");
    if (h264bitstream == NULL) {
        printf("Open file error\n");
        return 0;
    }

    n = (NALU_t*)calloc(1, sizeof(NALU_t));
    if (n == NULL) {
        printf("Alloc NALU Error\n");
        return 0;
    }

    n->max_size = buffersize;
    n->buf = (char*)calloc(buffersize, sizeof(char));
    if (n->buf == NULL) {
        free(n);
        printf("AllocNALU: n->buf");
        return 0;
    }

    int data_offset = 0;
    int nal_num = 0;
    printf("-----+-------- NALU Table ------+---------+\n");
    printf(" NUM |    POS  |    IDC |  TYPE |   LEN   |\n");
    printf("-----+---------+--------+-------+---------+\n");

    while (!feof(h264bitstream))
    {
        int data_length;
        data_length = GetAnnexbNALU(n);

        char type_str[20] = { 0 };
        switch (n->nal_unit_type) {
            case NALU_TYPE_SLICE:sprintf(type_str, "SLICE"); break;
            case NALU_TYPE_DPA:sprintf(type_str, "DPA"); break;
            case NALU_TYPE_DPB:sprintf(type_str, "DPB"); break;
            case NALU_TYPE_DPC:sprintf(type_str, "DPC"); break;
            case NALU_TYPE_IDR:sprintf(type_str, "IDR"); break;
            case NALU_TYPE_SEI:sprintf(type_str, "SEI"); break;
            case NALU_TYPE_SPS:sprintf(type_str, "SPS"); break;
            case NALU_TYPE_PPS:sprintf(type_str, "PPS"); break;
            case NALU_TYPE_AUD:sprintf(type_str, "AUD"); break;
            case NALU_TYPE_EOSEQ:sprintf(type_str, "EOSEQ"); break;
            case NALU_TYPE_EOSTREAM:sprintf(type_str, "EOSTREAM"); break;
            case NALU_TYPE_FILL:sprintf(type_str, "FILL"); break;
        }
        char idc_str[20] = { 0 };
        switch (n->nal_reference_idc >> 5) {
            case NALU_PRIORITY_DISPOSABLE:sprintf(idc_str, "DISPOS"); break;
            case NALU_PRIORITY_LOW:sprintf(idc_str, "LOW"); break;
            case NALU_PRIORITY_HIGH:sprintf(idc_str, "HIGH"); break;
            case NALU_PRIORITY_HIGHEST:sprintf(idc_str, "HIGHEST"); break;
        }

        fprintf(myout, "%5d| %8d| %7s| %6s| %8d|\n", nal_num, data_offset, idc_str, type_str, n->len);

        data_offset = data_offset + data_length;

        nal_num++;
    }

    //Free
    if (n) {
        if (n->buf) {
            free(n->buf);
            n->buf = NULL;
        }
        free(n);
    }
    return 0;
}