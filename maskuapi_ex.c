
//#include "stdafx.h"

#include "maskuapi_ex.h"
#include "masKUApi.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

int32 secu_crypto_cfg(HANDLE dev, \
	uint8 alg, \
	uint8 *key, \
	uint32 keyNbytes)
{
	uint8 resp[512];
	unsigned long rLen = sizeof(resp);
	tih_symm_param_t symm_t;
	uint8 cmd[512];
	uint16 cmd_len;
	cmd_len = sizeof(tih_symm_param_t);
	memcpy(cmd, "\x80\xff\x00\x00", 4);
	cmd[4] = cmd_len & 0xff;
	cmd[5] = (cmd_len >> 8) & 0xff;

	symm_t.op = 5;
	symm_t.alg = alg;
	symm_t.func = ENC;
	symm_t.mode = ECB;
	memcpy(symm_t.key, key, keyNbytes);
	symm_t.key_nbytes = keyNbytes;
	symm_t.key_type = EXTERNEL_KEY;
	memcpy(cmd + 6, (uint8 *)&symm_t, sizeof(tih_symm_param_t));
	return masKU_APDU(dev, 0, cmd, cmd_len + 6, resp, &rLen);
}

int32 secu_crypto_enc(HANDLE dev)
{
	uint8 resp[512];
	unsigned long rLen = sizeof(resp);
	uint8 cmd[256];
	memcpy(cmd, "\x80\xFF\x00\x00\x02\x00\x08\x00", 8);
	return masKU_APDU(dev, 0, cmd, 8, resp, &rLen);
}

int32 secu_crypto_dec(HANDLE dev)
{
	uint8 resp[512];
	unsigned long rLen = sizeof(resp);
	uint8 cmd[256];
	memcpy(cmd, "\x80\xFF\x00\x00\x02\x00\x08\x01", 8);
	return masKU_APDU(dev, 0, cmd, 8, resp, &rLen);
}

int32 secu_get_chipid(HANDLE dev, uint8 *buf)
{
	uint8 resp[512];
	unsigned long rLen = sizeof(resp);
	uint8 cmd[256];
	memcpy(cmd, "\x80\xFF\x00\x00\x01\x00\x13", 7);
	if (masKU_APDU(dev, 0, cmd, 7, resp, &rLen))
	{
		return -1;
	}
	rLen -= 2;
	memcpy(buf, resp, rLen);
	return rLen;
}
int32 fp_toy_get_img(HANDLE dev)
{
	uint8 cmd[128];
	uint8 resp[128];
	ULONG rLen = sizeof(resp);
	uint32 ret;
	cmd[0] = 0x80;
	cmd[1] = 0xff;
	cmd[2] = 0x00;
	cmd[3] = 0x03;
	cmd[4] = 0x01;
	cmd[5] = 0x00;
	cmd[6] = 1;
	ret = masKU_APDU(dev, 0, cmd, 7, resp, &rLen);
	if (ret)
	{
		return -1;
	}
	ret = (resp[3] << 24) | (resp[2] << 16) | (resp[1] << 8) | resp[0];
	if (ret) {
		return 0;
	}
	return 1;
}

int32 fp_up_img(HANDLE dev,uint8 *img)
{
	uint8 cmd[128];
	uint8 resp[40960];
	ULONG rLen = sizeof(resp);
	int32 ret;

	cmd[0] = 0x80;
	cmd[1] = 0xff;
	cmd[2] = 0x00;
	cmd[3] = 0x03;
	cmd[4] = 0x01;
	cmd[5] = 0x00;
	cmd[6] = 0x11;
	masKU_APDU(dev, 0, cmd, 10, resp, &rLen);
	if (rLen <10) {
		return -1;
	}
	memcpy(img, resp, rLen);
	return rLen;
}
int32 fp_toy_get_abs(HANDLE dev, uint8 buf_id)
{
	uint8 cmd[128];
	uint8 resp[128];
	ULONG rLen = sizeof(resp);
	uint32 ret;
	cmd[0] = 0x80;
	cmd[1] = 0xff;
	cmd[2] = 0x00;
	cmd[3] = 0x03;
	cmd[4] = 0x01;
	cmd[5] = 0x00;
	cmd[6] = 9;
	cmd[7] = buf_id;
	ret = masKU_APDU(dev, 0, cmd, 8, resp, &rLen);
	if (ret)
	{
		return ret;
	}
	ret = (resp[3] << 24) | (resp[2] << 16) | (resp[1] << 8) | resp[0];
	return ret;
}

int32 fp_toy_reg(HANDLE dev)
{
	uint8 cmd[128];
	uint8 resp[128];
	ULONG rLen = sizeof(resp);
	uint32 ret;

	cmd[0] = 0x80;
	cmd[1] = 0xff;
	cmd[2] = 0x00;
	cmd[3] = 0x03;
	cmd[4] = 0x01;
	cmd[5] = 0x00;
	cmd[6] = 0x0a;
	ret = masKU_APDU(dev, 0, cmd, 7, resp, &rLen);
	if (ret)
	{
		return ret;
	}
	ret = (resp[3] << 24) | (resp[2] << 16) | (resp[1] << 8) | resp[0];
	return ret;
}

int32 fp_toy_occ(HANDLE dev, uint8 st)
{
	uint8 cmd[128];
	uint8 resp[128];
	ULONG rLen = sizeof(resp);
	uint32 ret;

	cmd[0] = 0x80;
	cmd[1] = 0xff;
	cmd[2] = 0x00;
	cmd[3] = 0x03;
	cmd[4] = 0x01;
	cmd[5] = 0x00;
	cmd[6] = 0x08;
	cmd[7] = st;
	ret = masKU_APDU(dev, 0, cmd, 8, resp, &rLen);
	if (ret)
	{
		return ret;
	}
	ret = (resp[3] << 24) | (resp[2] << 16) | (resp[1] << 8) | resp[0];
	return ret;
}

int32 fp_toy_save(HANDLE dev,uint16 fp_id,char *name)
{
	uint8 cmd[128];
	uint8 resp[128];
	ULONG rLen = sizeof(resp);
	uint32 ret;

	cmd[0] = 0x80;
	cmd[1] = 0xff;
	cmd[2] = 0x00;
	cmd[3] = 0x03;
	cmd[4] = 0x06;
	cmd[5] = 0x00;
	cmd[6] = 4;
	cmd[7] = 0;
	cmd[8] = fp_id & 0xff;
	cmd[9] = (fp_id >> 8) & 0xff;
	strcpy(cmd + 10, name);

	ret = masKU_APDU(dev, 0, cmd, 12, resp, &rLen);
	if (ret)
	{
		return ret;
	}
	ret = resp[0] | (resp[1] << 8) | (resp[2] << 16) | (resp[3] << 24);
	return ret;
}




int32 fp_toy_usr_info(HANDLE dev, _FP_ALL *usr_info)
{
	uint8 cmd[512];
	uint8 resp[512];
	ULONG rLen = sizeof(resp);
	uint32 ret;

	cmd[0] = 0x80;
	cmd[1] = 0xff;
	cmd[2] = 0x00;
	cmd[3] = 0x03;
	cmd[4] = 0x01;
	cmd[5] = 0x00;
	cmd[6] = 0x0c;
	ret = masKU_APDU(dev, 0, cmd, 7, resp, &rLen);
	if (ret){
		return -1;
	}
	if (rLen != (sizeof(_FP_ALL) + 2)){
		return -2;
	}
	memcpy(usr_info, resp, (rLen - 2));
	return 0;
}


void masku_ex_test(void)
{
	HANDLE dev = NULL;
	char* path[16] = { '\0' };
	uint8 dev_num;
	uint32 i;
	int32 ret;
	uint8 buf[4096];

	for (i = 0; i < 16; i++)
	{
		path[i] = (char*)malloc(512);
	}

	dev_num = masKU_Scan_GUID(path, 0x465a, 0x2480, (LPSTR)"udisk_keyu");
	for (i = 0; i < dev_num; i++) {
		dev = masKU_Open_GUID(path[0]);
		if (dev != INVALID_HANDLE_VALUE) {
			break;
		}
	}
	if (i == dev_num) {
		return;
	}
	fp_toy_occ(dev,1);
	while (1) {
		if (fp_toy_get_img(dev)) {
			break;
		}
	}

	fp_up_img(dev, buf);
	fp_toy_occ(dev, 0);
	masKU_Close(dev);


	return;
}


#ifdef __cplusplus
}  /* end of the 'extern "C"' block */
#endif