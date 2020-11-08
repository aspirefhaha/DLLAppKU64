/**
*@autho stardust
*@time 2013-10-10
*@param 实现AES五种加密模式的测试
*/
#include <iostream>
using namespace std;

//加密编码过程函数,16位1和0
int dataLen = 16;   //需要加密数据的长度
int encLen = 4;     //加密分段的长度
int encTable[4] = {1,0,1,0};  //置换表
int data[16] = {1,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0}; //明文
int ciphertext[16]; //密文

//切片加密函数
void encode(int arr[])
{
    for(int i=0;i<encLen;i++)
    {
        arr[i] = arr[i] ^ encTable[i];
    }
}

//电码本模式加密，4位分段
void ECB(int arr[])
{
    //数据明文切片
    int a[4][4];
    int dataCount = 0;  //位置变量
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;//重置位置变量
    for(int i=0;i<dataLen;i=i+encLen)
    {
        int r = i/encLen;//行
        int l = 0;//列
        int encQue[4]; //编码片段
        for(int j=0;j<encLen;j++)
        {
            encQue[j] = a[r][l];
            l++;
        }
        encode(encQue); //切片加密
        //添加到密文表中
        for(int p=0;p<encLen;p++)
        {
            ciphertext[dataCount] = encQue[p];
            dataCount++;
        }
    }
    cout<<"ECB加密的密文为："<<endl;
    for(int t1=0;t1<dataLen;t1++) //输出密文
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//CBC
//密码分组链接模式，4位分段
void CCB(int arr[])
{
    //数据明文切片
    int a[4][4];
    int dataCount = 0;  //位置变量
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;//重置位置变量

    int init[4] = {1,1,0,0};  //初始异或运算输入
    //初始异或运算
    for(int i=0;i<dataLen;i=i+encLen)
    {
        int r = i/encLen;//行
        int l = 0;//列
        int encQue[4]; //编码片段
        //初始化异或运算
        for(int k=0;k<encLen;k++)
        {
            a[r][k] = a[r][k] ^ init[k];
        }
         //与Key加密的单切片
        for(int j=0;j<encLen;j++)
        {
            encQue[j] = a[r][j];
        }
        encode(encQue); //切片加密
        //添加到密文表中
        for(int p=0;p<encLen;p++)
        {
            ciphertext[dataCount] = encQue[p];
            dataCount++;
        }
        //变换初始输入
        for(int t=0;t<encLen;t++)
        {
            init[t] = encQue[t];
        }
    }


    cout<<"CCB加密的密文为："<<endl;
    for(int t1=0;t1<dataLen;t1++) //输出密文
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//CTR
//计算器模式，4位分段
void CTR(int arr[])
{
    //数据明文切片
    int a[4][4];
    int dataCount = 0;  //位置变量
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;//重置位置变量

    int init[4][4] = {{1,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0}};  //算子表
    int l = 0; //明文切片表列
    //初始异或运算
    for(int i=0;i<dataLen;i=i+encLen)
    {
        int r = i/encLen;//行
        int encQue[4]; //编码片段
        //将算子切片
        for(int t=0;t<encLen;t++)
        {
            encQue[t] = init[r][t];
        }
        encode(encQue); //算子与key加密
        //最后的异或运算
        for(int k=0;k<encLen;k++)
        {
            encQue[k] = encQue[k] ^ a[l][k];
        }
        l++;

        //添加到密文表中
        for(int p=0;p<encLen;p++)
        {
            ciphertext[dataCount] = encQue[p];
            dataCount++;
        }
    }


    cout<<"CTR加密的密文为："<<endl;
    for(int t1=0;t1<dataLen;t1++) //输出密文
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//CFB
//密码反馈模式，4位分段
void CFB(int arr[])
{
    //数据明文切片,切成2 * 8 片
    int a[8][2];
    int dataCount = 0;  //位置变量
    for(int k=0;k<8;k++)
    {
        for(int t=0;t<2;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;  //恢复初始化设置
    int lv[4] = {1,0,1,1};  //初始设置的位移变量
    int encQue[2]; //K的高两位
    int k[4]; //K

    for(int i=0;i<2 * encLen;i++) //外层加密循环
    {
        //产生K
        for(int vk=0;vk<encLen;vk++)
        {
            k[vk] = lv[vk];
        }
        encode(k);
        for(int k2=0;k2<2;k2++)
        {
            encQue[k2] = k[k2];
        }
        //K与数据明文异或产生密文
        for(int j=0;j<2;j++)
        {
            ciphertext[dataCount] = a[dataCount/2][j] ^ encQue[j];
            dataCount++;
        }
        //lv左移变换
        lv[0] = lv[2];
        lv[1] = lv[3];
        lv[2] = ciphertext[dataCount-2];
        lv[3] = ciphertext[dataCount-1];
    }

    cout<<"CFB加密的密文为："<<endl;
    for(int t1=0;t1<dataLen;t1++) //输出密文
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//OFB
//输出反馈模式，4位分段
void OFB(int arr[])
{
    //数据明文切片,切成2 * 8 片
    int a[8][2];
    int dataCount = 0;  //位置变量
    for(int k=0;k<8;k++)
    {
        for(int t=0;t<2;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;  //恢复初始化设置
    int lv[4] = {1,0,1,1};  //初始设置的位移变量
    int encQue[2]; //K的高两位
    int k[4]; //K

    for(int i=0;i<2 * encLen;i++) //外层加密循环
    {
        //产生K
        for(int vk=0;vk<encLen;vk++)
        {
            k[vk] = lv[vk];
        }
        encode(k);
        for(int k2=0;k2<2;k2++)
        {
            encQue[k2] = k[k2];
        }
        //K与数据明文异或产生密文
        for(int j=0;j<2;j++)
        {
            ciphertext[dataCount] = a[dataCount/2][j] ^ encQue[j];
            dataCount++;
        }
        //lv左移变换
        lv[0] = lv[2];
        lv[1] = lv[3];
        lv[2] = encQue[0];
        lv[3] = encQue[1];
    }

    cout<<"CFB加密的密文为："<<endl;
    for(int t1=0;t1<dataLen;t1++) //输出密文
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}


void printData()
{
    cout<<"以下示范AES五种加密模式的测试结果："<<endl;
    cout<<"---------------------------------------------"<<endl;
    cout<<"明文为："<<endl;
    for(int t1=0;t1<dataLen;t1++) //输出密文
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<data[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}
int main_test()
{
    printData();
    ECB(data);
    CCB(data);
    CTR(data);
    CFB(data);
    OFB(data);
    return 0;
}



//**********************************************************************************************//
#include <iostream>
#include <string>
#include <time.h>

#include "aes/aes.h"

typedef unsigned char  uint8;
typedef char           int8;
typedef unsigned short uint16;
typedef short          int16;
typedef unsigned int   uint32;
typedef int            int32;

typedef unsigned __int64 uint64;
typedef __int64          int64;
/******************************
For _LINUX
typedef long   long    int64;
typedef unsigned long  long  uint64;
******************************/

using namespace std;

//same as function rfc3686_inc
void ctr_inc(unsigned char ctr_buf[16])
{
    if(!(++(ctr_buf[15])))
        if(!(++(ctr_buf[14])))
            if(!(++(ctr_buf[13])))
                ++(ctr_buf[12]);
}

//same as function rfc3686_init
//4Bytes nounce+8Bytes iv+4Bytes counter
void ctr_init( unsigned char nonce[4], unsigned char iv[8], unsigned char ctr_buf[16])
{
    memcpy(ctr_buf, nonce, 4);
    memcpy(ctr_buf +  4, iv, 8);
    memset(ctr_buf + 12, 0, 4); 
    ctr_inc(ctr_buf);
}

void print_hex(uint8* buf, uint64 len)
{
	//Print results:
	for(int i=0;i<len;i++) {
		printf("%02X",buf[i]);
		if(15 == i%16)
			printf("\n");
	}
	printf("\n");
}

void main()
{
	uint8	key[]	= {0x10,0xa5,0x88,0x69,0xd7,0x4b,0xe5,0xa3,0x74,0xcf,	0x86,0x7c,0xfb,0x47,0x38,0x59};//AES::DEFAULT_KEYLENGTH
	uint8	buf[16];//tmp buffer

	uint8	msg[]	= "HelloWorld!23456";
	uint64	fsize=strlen((char*)msg);//message size
	uint8*	DataBuf=new uint8[1024];//Data Buffer

	//AES with CBC
	printf("AES with CBC\n");			
	
	//Copy data
	memset(DataBuf,0,1024);
	strcpy((char*)DataBuf,(char*)msg);
	uint8* pDataBuf = DataBuf;//tmp pointer
	uint8	iv1[]	= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00};

	uint64	iEncryptTimes = fsize/16+1;
	uint8	iPaddings	  = 16-fsize%16;//Padding size
	uint64	newlen = fsize+iPaddings;//New length
	
	//memcpy(DataBuf,iv,16);//Save iv
	memset(pDataBuf+fsize, iPaddings,iPaddings);//Padding
	printf("input	=\n");
	print_hex(DataBuf,newlen);
	aes_encrypt_ctx en_ctx[1];//Init encrypt
	
	//Encrypt
	for(uint64 i=0;i<iEncryptTimes;i++) {
		aes_encrypt_key128(key,en_ctx);
		aes_cbc_encrypt(pDataBuf,buf,16,iv1,en_ctx);//iv has been changed, ctx has been changed!!!
		memcpy(pDataBuf,buf,16);
		pDataBuf += 16;
	}
	
	printf("encrypt	=\n");
	print_hex(DataBuf,newlen);
	
	//Decrypt
	pDataBuf = DataBuf;
	uint8	iv2[]		= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00};
	uint8	buf3[256]={'\0'};
	aes_decrypt_ctx de_ctx[1];
	aes_decrypt_key128(key,de_ctx);
	aes_cbc_decrypt(pDataBuf,buf3,newlen,iv2,de_ctx);
	
	printf("decrypt	=\n");
	print_hex(buf3,newlen);
	
	//================================

	printf("AES with CTR\n");			
	//Copy data
	memset(DataBuf,0,1024);
	strcpy((char*)DataBuf,(char*)msg);
	pDataBuf = DataBuf;//tmp pointer
	uint8	iv3[]	= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00};

	iEncryptTimes = fsize/16;
	uint8	iRemain		  = fsize%16;
	uint8	ctr_buf[AES_BLOCK_SIZE];
	
	//Save iv(as ctrl buffer)
	//memcpy(DataBuf,iv,16);
	printf("input	=\n");
	print_hex(DataBuf,fsize);
	
	//Init encrypt
	//aes_encrypt_ctx en_ctx[1];
	
	//Encrypt
	for(i=0;i<iEncryptTimes;i++) {
		aes_encrypt_key128(key,en_ctx);
		ctr_init(iv3,iv3+4,ctr_buf);//we set iv as the nouce
		aes_ctr_encrypt(pDataBuf,buf,16,ctr_buf,ctr_inc,en_ctx);//iv has been changed, ctx has been changed!!!
		memcpy(pDataBuf,buf,16);
		pDataBuf += 16;
	}
	
	if(iRemain!=0) {//last times
		pDataBuf += i*16;
		aes_encrypt_key128(key,en_ctx);
		ctr_init(iv3,iv3+4,ctr_buf);//we set iv as the nouce
		aes_ctr_encrypt(pDataBuf,buf,iRemain,ctr_buf,ctr_inc,en_ctx);//iv has been changed, ctx has been changed!!!
		memcpy(pDataBuf,buf,iRemain);
	}
	
	printf("encrypt	=\n");
	print_hex(DataBuf,fsize);
	
	//Decrypt
	pDataBuf = DataBuf;
	uint8	iv4[]		= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00};
	//uint8	buf3[256]={'\0'};
	//aes_decrypt_ctx de_ctx[1];
	//aes_decrypt_key128(key,de_ctx);
	aes_encrypt_key128(key,en_ctx);
	ctr_init(iv4,iv4+4,ctr_buf);//we set iv as the nouce
	aes_ctr_decrypt(pDataBuf,buf3,16,ctr_buf,ctr_inc,en_ctx);
	printf("decrypt	=\n");
	print_hex(buf3,fsize);
	
	printf("\n");
}

/*
输出如下（CBC未去掉Padding）：
AES with CBC
input   =
48656C6C6F576F726C64213233343536
10101010101010101010101010101010
encrypt =
F928E09884AA2BA8CC4B73C09304250C
C9A0EEFF2295B5D83BEA0410001BD7C6
decrypt =
48656C6C6F576F726C64213233343536
10101010101010101010101010101010
 
AES with CTR
input   =
48656C6C6F576F726C64213233343536
encrypt =
1CA0978FE499969C769B6346D46B66F9
decrypt =
48656C6C6F576F726C64213233343536
*/


