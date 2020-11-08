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


#define FP_CMD_REQCAPTUREANDEXTRACT  		0x51  //ץȡָ��ͼ��ͬʱ��ȡ������ 
#define FP_CMD_REQENROLL   					0x7F  //ע����ָ���û� 
#define FP_CMD_REQMATCH1N   				0x71  //�ɼ�ָ�ƽ��� 1��N �ȶ� 
#define FP_CMD_REQERASEONE  				0x73  //ɾ��ָ�� ID �û� 
#define FP_CMD_REQERASEALL  				0x54  //ɾ�������û� 
#define FP_CMD_REQGETUSERNUM  				0x55  //��ȡ�Ѿ�ע����û����� 
#define FP_CMD_REQGETIDAVAILABILITY  		0x74  //��ȡ���õ���С ID ��ֵ 
#define FP_CMD_REQCHANGEBAUDRATE  			0x7E  //�޸�ָ��ģ��Ĳ����� 
#define FP_CMD_REQCAPTURE  					0x10  //ץȡָ��ͼ�� 
#define FP_CMD_REQEXTRACT  					0x11  //��ȡָ��ͼ��������� ͨ����� 10h ʹ��
#define FP_CMD_REQGETSECURITYLEVEL  		0x56  //��ȡָ��ģ��İ�ȫ�ȼ� 
#define FP_CMD_REQSETSECURITYLEVEL  		0x57  //����ָ��ģ��İ�ȫ�ȼ� 



#define FP_RET_ACKCAPTUREANDEXTRACT  		0x51  //����ץȡָ��ͼ��ͬʱ��ȡ�������Ľ�� 
#define FP_RET_ACKENROLL   					0x7F  //����ע�����û��Ľ�� 
#define FP_RET_ACKMATCH1N   				0x71  //���زɼ�ָ�ƽ��� 1��N �ȶԵĽ�� 
#define FP_RET_ACKERASEONE  				0x73  //����ɾ��ָ�� ID �û��Ľ�� 
#define FP_RET_ACKERASEALL  				0x54  //����ɾ�������û��Ľ�� 
#define FP_RET_ACKGETUSERNUM  				0x55  //�����Ѿ�ע����û����� 
#define FP_RET_ACKGETIDAVAILABILITY  		0x74  //���ؿ��õ���С ID ��ֵ 
#define FP_RET_ACKCHANGEBAUDRATE  			0x7E  //�����޸Ĳ����ʵĽ�� 
#define FP_RET_ACKCAPTURE  					0x10  //����ץȡָ��ͼ��Ľ�� 
#define FP_RET_ACKEXTRACT  					0x11  //������ȡָ��ͼ���������Ľ�� 
#define FP_RET_ACKGETSECURITYLEVEL  		0x56  //����ָ��ģ�鰲ȫ�ȼ��Ľ�� 
#define FP_RET_ACKSETSECURITYLEVEL  		0x57  //����ָ��ģ�鰲ȫ�ȼ����õĽ��


#define FP_ERROR_INVALID_CMD				0x80	//ָ��ģ����յ���Ч���� 
#define FP_ERROR_SUM						0x81	//ָ��ģ����յ�����У��� 
#define FP_ERROR_PARA						0x83	//ָ��ģ����յ���Ч���� 
#define FP_ERROR_RAM						0x84	//ָ��ģ�������ڴ���� 
#define FP_ERROR_REGISTER					0x91	//ע��ʧ��(�û���������) 
#define FP_ERROR_ID							0x93	//�Ѿ�ע��� ID  
////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

//�豸��Ϣ�ṹ��
typedef struct masKUDeviceInfo
{
	unsigned short VID;									//���̱��
	unsigned short PID;									//��Ʒ���
	unsigned char	SN[16];								//��Ʒ���к�
	unsigned int diskQuantity;							//usb�豸����������;D7~D0��ʾ����iso��'T',D15~D8��ʾ������'S',D23~D16��ʾ������'H',D31~D24��ʾ��ͨu����'U'
	unsigned int tDiskCapacity;							//����iso����С����λΪMByte
	unsigned int sDiskCapacity;							//��������С����λΪMByte
	unsigned int hDiskCapacity;							//��������С����λΪMByte
	unsigned int uDiskCapacity;							//��ͨu������С����λΪMByte
	unsigned int unit;									//usb�������С��λ�������ֽڴ�С
	unsigned int usbVersion;							//usb�豸�̼��汾��
	unsigned int AllDiskCapacity;						//usb�豸������������λΪMByte
	unsigned int TaxCapacity;							//˰���̴�С����λΪMByte
	unsigned char	ManufacturerInfo[8];				//������Ϣ,0x12��������
	unsigned char	ProductInfo[16];					//��Ʒ��Ϣ,0x12��������
	unsigned char	ManufacturerStr[8];					//�����ַ���
	unsigned char	ProductStr[16];						//��Ʒ�ַ���
} MASKU_INFO;

#define uint16          unsigned short
typedef struct {
	uint16	app_id;
	uint16	con_id;
	uint16	fk_id;
	uint16	rsv;
}PRV_STRUCT_T;
//ʱ����Ϣ�ṹ��
typedef struct _masKU_Timer
{
	int seconds;			//��������Χ0-59
	int minute;				//��������Χ0-59
	int hour;					//ʱ��������ҹ���𣬷�Χ0-23
	int day;					//��������Χ01-31
	int weekday;			//����������ΧΪ0-6,���������������ζ�Ӧ������������6
	int month;				//�·ݣ���һ�����𣬷�Χ1-12
	int year;					//��������Χ2000-2099
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

// num : �ڼ���
//����ֵ ��
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
//usr: 1,��PC�ã�0�����豸��
int _stdcall masKU_fp_employ(HANDLE handle, unsigned char usr);
int _stdcall masKU_crytpo_config(HANDLE handle, unsigned char alg, unsigned char func, unsigned char mode, unsigned char *key, unsigned int keyNbytes, unsigned char *iv);
int _stdcall masKU_crypto_ed(HANDLE handle, unsigned char * pData, unsigned long pDataLen, unsigned char * resp, unsigned long *rLen);

//���
int _stdcall masKU_get_usb_ver(HANDLE handle, unsigned char *version);

int _stdcall masKU_check_emmc(HANDLE handle, unsigned int *time, unsigned char *res);

#ifdef __cplusplus
}
#endif

#endif	//__USBIO_H

