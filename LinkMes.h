#ifndef __WT_LINK_MES_H__
#define __WT_LINK_MES_H__

#include <string>
#include "logheader.h"
using namespace std;

#ifdef WTLINKMES_EXPORTS
#define MES_Decl __declspec(dllexport)
#else
#define MES_Decl __declspec(dllimport)
#endif

enum{
	eumMacType_Wifi=0,
	eumMacType_Lan=1,
	eumMacType_Wan=2,
	eumMacType_Wifi_5G=3,	//������ӵ�Mac��ַ
	eumMacType_Bt=4,
	eumMacType_Wan0_1=5,
	eumMacType_Wan0_2=6,
	eumMacType_Wan0_3=7,
	eumMacType_Wan0_4=8,
	eumMacType_Wan1_1=9,
	eumMacType_Wan1_2=10,
	eumMacType_Wan1_3=11,
	eumMacType_Wan1_4=12,
	eumMacType_Ex0=13,
	eumMacType_Ex1=14,
	eumMacType_MaxCount,
};

enum{
	eumRet_True = 0,
	eumRet_False ,
	eumRet_Error
};

struct sMacStuct
{
	char cMacContainer[eumMacType_MaxCount][13];
};

struct MESDutTestInfo
{
	bool testResult;
	struct tm startTm;
	struct tm endTm;
	string dutSN;
	int errorCode;
	string errorString;
};

class MES_Decl cMesOperateBase
{
public:
	//���õ�ǰID
	virtual int setId(int id) = 0;
	//����MES 
	//ÿһ�β����̶߳������ӣ�����һ���ľͻ�����4��
	virtual int connectMes(char *errMsg, int errBuffSize) = 0;
	//�Ͽ�MES
	virtual int disconnectMes(char *errMsg,int errBuffSize) = 0;
	//��MES��ȡMAC
	virtual int getMacFromMes(sMacStuct &sMac, char *errMsg,int errBuffSize) = 0;
	//����MACд������MES
	virtual int replyWriteMacRet(sMacStuct sMac, bool ret, char *errMsg,int errBuffSize) = 0;
	//��鵱ǰ��DUT barCode�Ƿ�Ϸ�
	//barCode ����Դ���������MES��MAC�����Ǽ��MAC
	//����ɨ��ǹ����ͣ�����������Ϣ
	virtual int checkDutBarCode(const char *barCode, char *errMsg,int errBuffSize) = 0;
	//��������Ϣ�ϴ���MES
	virtual int uploadTestInfoToMesServer(const MESDutTestInfo &testInfo,
									  const vector <sCalFreqDataStruct > &CalFreqDataStruct,
									  const vector <sCalPowDataStruct > &CalPowDataStruct,
									  const vector <sTXVerifyDateStruct> &TXVerifyDateStruct,
									  const vector <sRXVerifyDataStruct> &RXVerifyDataStruct,
									  char *errMsg,int errBuffSize) = 0;
	//������LOG�ϴ���MES
	virtual int uploadLogToMesServer(const char *log,char *errMsg,int errBuffSize) = 0;
};

#endif


