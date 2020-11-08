/**
*@autho stardust
*@time 2013-10-10
*@param ʵ��AES���ּ���ģʽ�Ĳ���
*/
#include <iostream>
using namespace std;

//���ܱ�����̺���,16λ1��0
int dataLen = 16;   //��Ҫ�������ݵĳ���
int encLen = 4;     //���ֶܷεĳ���
int encTable[4] = {1,0,1,0};  //�û���
int data[16] = {1,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0}; //����
int ciphertext[16]; //����

//��Ƭ���ܺ���
void encode(int arr[])
{
    for(int i=0;i<encLen;i++)
    {
        arr[i] = arr[i] ^ encTable[i];
    }
}

//���뱾ģʽ���ܣ�4λ�ֶ�
void ECB(int arr[])
{
    //����������Ƭ
    int a[4][4];
    int dataCount = 0;  //λ�ñ���
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;//����λ�ñ���
    for(int i=0;i<dataLen;i=i+encLen)
    {
        int r = i/encLen;//��
        int l = 0;//��
        int encQue[4]; //����Ƭ��
        for(int j=0;j<encLen;j++)
        {
            encQue[j] = a[r][l];
            l++;
        }
        encode(encQue); //��Ƭ����
        //��ӵ����ı���
        for(int p=0;p<encLen;p++)
        {
            ciphertext[dataCount] = encQue[p];
            dataCount++;
        }
    }
    cout<<"ECB���ܵ�����Ϊ��"<<endl;
    for(int t1=0;t1<dataLen;t1++) //�������
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//CBC
//�����������ģʽ��4λ�ֶ�
void CCB(int arr[])
{
    //����������Ƭ
    int a[4][4];
    int dataCount = 0;  //λ�ñ���
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;//����λ�ñ���

    int init[4] = {1,1,0,0};  //��ʼ�����������
    //��ʼ�������
    for(int i=0;i<dataLen;i=i+encLen)
    {
        int r = i/encLen;//��
        int l = 0;//��
        int encQue[4]; //����Ƭ��
        //��ʼ���������
        for(int k=0;k<encLen;k++)
        {
            a[r][k] = a[r][k] ^ init[k];
        }
         //��Key���ܵĵ���Ƭ
        for(int j=0;j<encLen;j++)
        {
            encQue[j] = a[r][j];
        }
        encode(encQue); //��Ƭ����
        //��ӵ����ı���
        for(int p=0;p<encLen;p++)
        {
            ciphertext[dataCount] = encQue[p];
            dataCount++;
        }
        //�任��ʼ����
        for(int t=0;t<encLen;t++)
        {
            init[t] = encQue[t];
        }
    }


    cout<<"CCB���ܵ�����Ϊ��"<<endl;
    for(int t1=0;t1<dataLen;t1++) //�������
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//CTR
//������ģʽ��4λ�ֶ�
void CTR(int arr[])
{
    //����������Ƭ
    int a[4][4];
    int dataCount = 0;  //λ�ñ���
    for(int k=0;k<4;k++)
    {
        for(int t=0;t<4;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;//����λ�ñ���

    int init[4][4] = {{1,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0}};  //���ӱ�
    int l = 0; //������Ƭ����
    //��ʼ�������
    for(int i=0;i<dataLen;i=i+encLen)
    {
        int r = i/encLen;//��
        int encQue[4]; //����Ƭ��
        //��������Ƭ
        for(int t=0;t<encLen;t++)
        {
            encQue[t] = init[r][t];
        }
        encode(encQue); //������key����
        //�����������
        for(int k=0;k<encLen;k++)
        {
            encQue[k] = encQue[k] ^ a[l][k];
        }
        l++;

        //��ӵ����ı���
        for(int p=0;p<encLen;p++)
        {
            ciphertext[dataCount] = encQue[p];
            dataCount++;
        }
    }


    cout<<"CTR���ܵ�����Ϊ��"<<endl;
    for(int t1=0;t1<dataLen;t1++) //�������
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//CFB
//���뷴��ģʽ��4λ�ֶ�
void CFB(int arr[])
{
    //����������Ƭ,�г�2 * 8 Ƭ
    int a[8][2];
    int dataCount = 0;  //λ�ñ���
    for(int k=0;k<8;k++)
    {
        for(int t=0;t<2;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;  //�ָ���ʼ������
    int lv[4] = {1,0,1,1};  //��ʼ���õ�λ�Ʊ���
    int encQue[2]; //K�ĸ���λ
    int k[4]; //K

    for(int i=0;i<2 * encLen;i++) //������ѭ��
    {
        //����K
        for(int vk=0;vk<encLen;vk++)
        {
            k[vk] = lv[vk];
        }
        encode(k);
        for(int k2=0;k2<2;k2++)
        {
            encQue[k2] = k[k2];
        }
        //K��������������������
        for(int j=0;j<2;j++)
        {
            ciphertext[dataCount] = a[dataCount/2][j] ^ encQue[j];
            dataCount++;
        }
        //lv���Ʊ任
        lv[0] = lv[2];
        lv[1] = lv[3];
        lv[2] = ciphertext[dataCount-2];
        lv[3] = ciphertext[dataCount-1];
    }

    cout<<"CFB���ܵ�����Ϊ��"<<endl;
    for(int t1=0;t1<dataLen;t1++) //�������
    {
        if(t1!=0 && t1%4==0)
            cout<<endl;
        cout<<ciphertext[t1]<<" ";
    }
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;
}

//OFB
//�������ģʽ��4λ�ֶ�
void OFB(int arr[])
{
    //����������Ƭ,�г�2 * 8 Ƭ
    int a[8][2];
    int dataCount = 0;  //λ�ñ���
    for(int k=0;k<8;k++)
    {
        for(int t=0;t<2;t++)
        {
            a[k][t] = data[dataCount];
            dataCount++;
        }
    }
    dataCount = 0;  //�ָ���ʼ������
    int lv[4] = {1,0,1,1};  //��ʼ���õ�λ�Ʊ���
    int encQue[2]; //K�ĸ���λ
    int k[4]; //K

    for(int i=0;i<2 * encLen;i++) //������ѭ��
    {
        //����K
        for(int vk=0;vk<encLen;vk++)
        {
            k[vk] = lv[vk];
        }
        encode(k);
        for(int k2=0;k2<2;k2++)
        {
            encQue[k2] = k[k2];
        }
        //K��������������������
        for(int j=0;j<2;j++)
        {
            ciphertext[dataCount] = a[dataCount/2][j] ^ encQue[j];
            dataCount++;
        }
        //lv���Ʊ任
        lv[0] = lv[2];
        lv[1] = lv[3];
        lv[2] = encQue[0];
        lv[3] = encQue[1];
    }

    cout<<"CFB���ܵ�����Ϊ��"<<endl;
    for(int t1=0;t1<dataLen;t1++) //�������
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
    cout<<"����ʾ��AES���ּ���ģʽ�Ĳ��Խ����"<<endl;
    cout<<"---------------------------------------------"<<endl;
    cout<<"����Ϊ��"<<endl;
    for(int t1=0;t1<dataLen;t1++) //�������
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
������£�CBCδȥ��Padding����
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


