#ifndef __USBIO_H
#define __USBIO_H

/* alg */
#define SM4             0x1
#define AES             0x2

/* mode */
#define ECB             0x0
#define CBC             0x1
#define CFB             0x2
#define OFB             0x3
#define CTR             0x4
#define XTS             0x5

/* func */
#define ENC             0x0
#define DEC             0x1

/* endian */
#define LITTLE_ENDI     0x0
#define BIG_ENDI        0x1

/* keybits */
#define KEY_128_BITS    0x0
#define KEY_256_BITS    0x1



////////////////////////////////////////////////
#define FP_PACKET_HEADER		0x6c
#define FP_ADDR_MCU				0x63
#define FP_ADDR_MOD				0x62


#define FP_CMD_REQCAPTUREANDEXTRACT  		0x51  //抓取指纹图像并同时提取特征量 
#define FP_CMD_REQENROLL   					0x7F  //注册新指纹用户 
#define FP_CMD_REQMATCH1N   				0x71  //采集指纹进行 1：N 比对 
#define FP_CMD_REQERASEONE  				0x73  //删除指定 ID 用户 
#define FP_CMD_REQERASEALL  				0x54  //删除所有用户 
#define FP_CMD_REQGETUSERNUM  				0x55  //获取已经注册的用户数量 
#define FP_CMD_REQGETIDAVAILABILITY  		0x74  //获取可用的最小 ID 数值 
#define FP_CMD_REQCHANGEBAUDRATE  			0x7E  //修改指纹模块的波特率 
#define FP_CMD_REQCAPTURE  					0x10  //抓取指纹图像 
#define FP_CMD_REQEXTRACT  					0x11  //提取指纹图像的特征量 通常配合 10h 使用
#define FP_CMD_REQGETSECURITYLEVEL  		0x56  //获取指纹模块的安全等级 
#define FP_CMD_REQSETSECURITYLEVEL  		0x57  //设置指纹模块的安全等级 



#define FP_RET_ACKCAPTUREANDEXTRACT  		0x51  //返回抓取指纹图像并同时提取特征量的结果 
#define FP_RET_ACKENROLL   					0x7F  //返回注册新用户的结果 
#define FP_RET_ACKMATCH1N   				0x71  //返回采集指纹进行 1：N 比对的结果 
#define FP_RET_ACKERASEONE  				0x73  //返回删除指定 ID 用户的结果 
#define FP_RET_ACKERASEALL  				0x54  //返回删除所有用户的结果 
#define FP_RET_ACKGETUSERNUM  				0x55  //返回已经注册的用户数量 
#define FP_RET_ACKGETIDAVAILABILITY  		0x74  //返回可用的最小 ID 数值 
#define FP_RET_ACKCHANGEBAUDRATE  			0x7E  //返回修改波特率的结果 
#define FP_RET_ACKCAPTURE  					0x10  //返回抓取指纹图像的结果 
#define FP_RET_ACKEXTRACT  					0x11  //返回提取指纹图像特征量的结果 
#define FP_RET_ACKGETSECURITYLEVEL  		0x56  //返回指纹模块安全等级的结果 
#define FP_RET_ACKSETSECURITYLEVEL  		0x57  //返回指纹模块安全等级设置的结果


#define FP_ERROR_INVALID_CMD				0x80	//指纹模块接收到无效命令 
#define FP_ERROR_SUM						0x81	//指纹模块接收到错误校验和 
#define FP_ERROR_PARA						0x83	//指纹模块接收到无效参数 
#define FP_ERROR_RAM						0x84	//指纹模块遇到内存错误 
#define FP_ERROR_REGISTER					0x91	//注册失败(用户区域已满) 
#define FP_ERROR_ID							0x93	//已经注册的 ID  
////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

//设备信息结构体
typedef struct masKUDeviceInfo
{
	unsigned short VID;									//厂商编号
	unsigned short PID;									//产品编号
	unsigned char	SN[16];								//产品序列号
	unsigned int diskQuantity;							//usb设备各分区属性;D7~D0表示光盘iso区'T',D15~D8表示加密区'S',D23~D16表示隐藏区'H',D31~D24表示普通u盘区'U'
	unsigned int tDiskCapacity;							//光盘iso区大小，单位为MByte
	unsigned int sDiskCapacity;							//加密区大小，单位为MByte
	unsigned int hDiskCapacity;							//隐藏区大小，单位为MByte
	unsigned int uDiskCapacity;							//普通u盘区大小，单位为MByte
	unsigned int unit;									//usb传输的最小单位扇区的字节大小
	unsigned int usbVersion;							//usb设备固件版本号
	unsigned int AllDiskCapacity;						//usb设备的总容量，单位为MByte
	unsigned int TaxCapacity;							//税控盘大小，单位为MByte
	unsigned char	ManufacturerInfo[8];				//厂商信息,0x12命令内容
	unsigned char	ProductInfo[16];					//产品信息,0x12命令内容
	unsigned char	ManufacturerStr[8];					//厂商字符串
	unsigned char	ProductStr[16];						//产品字符串
} MASKU_INFO;

#define uint16          unsigned short
typedef struct {
	uint16	app_id;
	uint16	con_id;
	uint16	fk_id;
	uint16	rsv;
}PRV_STRUCT_T;
//时间信息结构体
typedef struct _masKU_Timer
{
	int seconds;			//秒数，范围0-59
	int minute;				//分数，范围0-59
	int hour;					//时数，从午夜算起，范围0-23
	int day;					//天数，范围01-31
	int weekday;			//星期数，范围为0-6,从星期天算起，依次对应星期天至星期6
	int month;				//月份，从一月算起，范围1-12
	int year;					//年数，范围2000-2099
} MASKU_TIMER;


unsigned char _stdcall masKU_Scan(unsigned char *usbDriver,unsigned short usbVID,unsigned short usbPID);

unsigned int _stdcall masKU_Scan_GUID(char **pszDevicePath,unsigned short usbVID,unsigned short usbPID,char *productIdentification);

HANDLE _stdcall masKU_Open(char cDrive);

HANDLE _stdcall masKU_Open_GUID(char* strDevicePath);

BOOL _stdcall masKU_Close(HANDLE devHandle);

BOOL _stdcall masKU_UpdateISO(HANDLE handle, const char *pcISOFilePath);

BOOL  _stdcall masKU_Password_Verify(HANDLE handle, const char *pcPassword,BYTE ucDiskIndex,BYTE ucReadORWriteType);

BOOL _stdcall masKU_Password_Change(HANDLE handle,const char *pcNewPassword,BYTE ucDiskIndex,BYTE ucReadORWriteType);

BOOL _stdcall masKU_Password_Err(HANDLE handle,unsigned char ucDiskIndex,unsigned char errFlg,unsigned char *errSet,unsigned char *errCur);

BOOL _stdcall masKU_WriteHideDisk(HANDLE handle, unsigned int dwSectorAddr, unsigned int dwSectorCount, BYTE *pBuf,unsigned char uIndex);

BOOL _stdcall masKU_ReadHideDisk(HANDLE handle, unsigned int dwSectorAddr, unsigned int dwSectorCount, BYTE *pBuf,unsigned char uIndex);

BOOL _stdcall masKU_LogoutSecurityDisk(HANDLE handle);

BOOL _stdcall masKU_GetDiskInfo(HANDLE handle,MASKU_INFO *zfUsb);

BOOL _stdcall masKU_SetDiskInfo(HANDLE handle,MASKU_INFO zfUsb);

BOOL _stdcall masKU_SoftRestart(HANDLE handle);

BOOL _stdcall masKU_Time(HANDLE handle, unsigned char TimeFlg, MASKU_TIMER *pTime);

BOOL _stdcall masKU_Destroy(HANDLE handle,BYTE ucDiskIndex,BYTE ucReadORWriteType);

int _stdcall masKU_APDU(HANDLE handle,unsigned char cmdType,unsigned char * pData,unsigned long pDataLen,unsigned char * resp,unsigned long * rLen);

int _stdcall masKU_streamED(HANDLE handle,unsigned char * pData,unsigned long pDataLen,unsigned char * resp,unsigned long * rLen,unsigned char sFlg);

BOOL _stdcall Index_Query(HANDLE handle,BYTE ucDiskIndex,unsigned int *SectorB,unsigned int *DiskCapacity);

int _stdcall masKU_EncDec(HANDLE handle, unsigned char alg, unsigned char func, unsigned char mode,
                            unsigned char *key, unsigned int keyNbytes, unsigned char *iv,
                            unsigned char * pData, unsigned long pDataLen,
                            unsigned char * resp, unsigned long * rLen);
BOOL _stdcall masKU_WriteAppNor(HANDLE handle, unsigned int dwAddr, unsigned int dwByteCount, BYTE *pBuf, unsigned char uIndex);

BOOL _stdcall masKU_ReadAppNor(HANDLE handle, unsigned int dwAddr, unsigned int dwByteCount, BYTE *pBuf, unsigned char uIndex);

int _stdcall masKU_w2g_Init(HANDLE handle, unsigned char operation);

int _stdcall masKU_w2g_GetID_MCU(HANDLE handle, unsigned char *id, unsigned int len);

int _stdcall masKU_w2g_GetID_Flash(HANDLE handle, unsigned char *id,unsigned int len);

int _stdcall masKU_w2g_Heartbeat(HANDLE handle, unsigned char *id, unsigned int len);

int _stdcall masKU_w2g_GetID_CheckRes(HANDLE handle, unsigned char res);

int _stdcall masKU_fp_cmd(HANDLE handle,unsigned char *fp_cmd,unsigned char *out);

// num : 第几次
//返回值 ：
int _stdcall masKU_fp_collection(HANDLE handle,unsigned char num);

int _stdcall masKU_fp_register(HANDLE handle, unsigned char id,unsigned char *md5);

int _stdcall masKU_fp_match1n(HANDLE handle, unsigned char *id,unsigned char *md5);

int _stdcall masKU_fp_fp_erase1(HANDLE handle, unsigned char id);

int _stdcall masKU_fp_fp_erase_all(HANDLE handle);

int _stdcall masKU_fp_get_usr_num(HANDLE handle,unsigned char *num);

int _stdcall masKU_fp_set_sec_level(HANDLE handle, unsigned char level);

int _stdcall masKU_fp_get_sec_level(HANDLE handle,unsigned char *level);

int _stdcall masKU_fp_get_finger_st(HANDLE handle);



int _stdcall prv_interface(HANDLE handle, PRV_STRUCT_T *p);
//usr: 1,给PC用，0，给设备用
int _stdcall masKU_fp_employ(HANDLE handle, unsigned char usr);
int _stdcall masKU_crytpo_config(HANDLE handle, unsigned char alg, unsigned char func, unsigned char mode, unsigned char *key, unsigned int keyNbytes, unsigned char *iv);
int _stdcall masKU_crypto_ed(HANDLE handle, unsigned char * pData, unsigned long pDataLen, unsigned char * resp, unsigned long *rLen);

//检测
int _stdcall masKU_get_usb_ver(HANDLE handle, unsigned char *version);

int _stdcall masKU_check_emmc(HANDLE handle, unsigned int *time, unsigned char *res);

#ifdef __cplusplus
}
#endif

#endif	//__USBIO_H

