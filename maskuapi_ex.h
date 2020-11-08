#ifndef MASKUAPI_EX_H_
#define MASKUAPI_EX_H_
#include < windows.h>
#ifdef __cplusplus
extern "C" {
#endif



#ifndef uint64
#define uint64          unsigned long long
#endif

#ifndef uint32
#define uint32          unsigned int
#endif

#ifndef int32
#define int32           int
#endif

#ifndef uint16
#define uint16          unsigned short
#endif

#ifndef int16
#define int16           short
#endif

#ifndef uint8
#define uint8           unsigned char
#endif

#ifndef int8
#define int8            char
#endif


/* alg */
#define SM4                     0x1 
#define AES                     0x2 

/* mode */
#define ECB                     0x0 
#define CBC                     0x1 

/* func */
#define ENC                     0x0
#define DEC                     0x1

/* key type */
#define INTERNEL_KEY            0x0  
#define EXTERNEL_KEY            0x1  
typedef struct {
	uint32 op;
	uint32 alg;
	uint32 func;
	uint32 mode;
	uint32 key_type;
	uint32 key_index;
	uint32 key_nbytes;
	uint8  key[32];
	uint8  iv[16];
	uint32 nbytes;
}tih_symm_param_t;


int secu_crypto_cfg(HANDLE dev,\
                    uint8 alg, \
                    uint8 *key, \
                    uint32 keyNbytes);

int secu_crypto_enc(HANDLE dev);
int secu_crypto_dec(HANDLE dev);   


#define FP_TOY_MAX_USER	16

typedef struct fingerPrinter
{
	uint32 ID;
	uint8  usrName[16];
}_FP;

typedef struct {
	uint32 usr_num;
	_FP fp[FP_TOY_MAX_USER];
}_FP_ALL;



//==================================================================
//功能：    配置流加解密密钥，并设置为加密状态。
//输入参数：dev			设备句柄
//          alg			算法标识，SM4/AES
//          key			密钥指针
//			keyNbytes	密钥长度，SM4只支持16字节，AES可支持16和32字节。
//返回值：  返回0表示成功，其它值为错误。
//==================================================================

int32 secu_crypto_cfg(HANDLE dev, \
	uint8 alg, \
	uint8 *key, \
	uint32 keyNbytes);

//==================================================================
//功能：    配置流加解密状态为加密。
//输入参数：dev			设备句柄
//返回值：  返回0表示成功，其它值为错误。
//==================================================================
int32 secu_crypto_enc(HANDLE dev);


//==================================================================
//功能：    配置流加解密状态为解密。
//输入参数：dev			设备句柄
//返回值：  返回0表示成功，其它值为错误。
//==================================================================
int32 secu_crypto_dec(HANDLE dev);

//==================================================================
//功能：    获取芯片ID
//输入参数：dev			设备句柄
//			buf			主机缓冲区，至少12个字节的空间。
//返回值：  返回大于0表示chipid长度，其它值为错误。
//==================================================================
int32 secu_get_chipid(HANDLE dev, uint8 *buf);
//==================================================================
//功能：    采集指纹
//输入参数：dev			设备句柄
//返回值：  返回0表示成功，其它值为失败。
//==================================================================
int32 fp_toy_get_img(HANDLE dev);

//==================================================================
//功能：    上传刚刚采集到的指纹数据。
//输入参数：dev			设备句柄
//			img			指纹数据缓冲区指针（指纹数据会有超过10K，缓冲区不可过小）
//返回值：  返回0表示成功，其它值为失败。
//==================================================================
int32 fp_up_img(HANDLE dev, uint8 *img);


//==================================================================
//功能：    计算刚采集的指纹数据特征值并存入内部指定buffer
//输入参数：dev			设备句柄
//			buf_id		特征值将存入的buffer 号，取值1-5
//返回值：  返回0表示成功，其它值为失败。
//==================================================================
int32 fp_toy_get_abs(HANDLE dev, uint8 buf_id);

//==================================================================
//功能：    合并buffer 1-5的特征值并存入buffer1中。
//输入参数：dev			设备句柄
//返回值：  返回0表示成功，其它值为失败。
//==================================================================
int32 fp_toy_reg(HANDLE dev);

//==================================================================
//功能：    禁止/允许设备操作指纹模块，上位机进行指纹操作流程时应先禁止设备操作指纹模块，当上位机结束流程时再允许设备操作指纹。
//输入参数：dev			设备句柄
//			st			1：禁止设备操作指纹模块；0：允许设备操作指纹模块。
//返回值：  返回0表示成功，其它值为失败。
//==================================================================
int32 fp_toy_occ(HANDLE dev, uint8 st);

//==================================================================
//功能：    存储指纹特征值到指定id号。
//输入参数：dev			设备句柄
//			fp_id		要存储的指纹id号。
//			name		用户名，最长不可超过15个字符。
//返回值：  返回0表示成功，其它值为失败。
//==================================================================
int32 fp_toy_save(HANDLE dev, uint16 fp_id, char *name);

//==================================================================
//功能：    获取所有指纹用户信息
//输入参数：dev			设备句柄
//			usr_info	用户信息缓冲区指针
//返回值：  返回0表示成功，其它值为失败。
//==================================================================
int32 fp_toy_usr_info(HANDLE dev, _FP_ALL *usr_info);


void masku_ex_test(void);


#ifdef __cplusplus
}  /* end of the 'extern "C"' block */
#endif

#endif