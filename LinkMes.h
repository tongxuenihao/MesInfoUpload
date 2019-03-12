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
	eumMacType_Wifi_5G=3,	//额外添加的Mac地址
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
	//设置当前ID
	virtual int setId(int id) = 0;
	//连接MES 
	//每一次测试线程都会连接，例如一拖四就会连接4次
	virtual int connectMes(char *errMsg, int errBuffSize) = 0;
	//断开MES
	virtual int disconnectMes(char *errMsg,int errBuffSize) = 0;
	//从MES获取MAC
	virtual int getMacFromMes(sMacStuct &sMac, char *errMsg,int errBuffSize) = 0;
	//反馈MAC写入结果给MES
	virtual int replyWriteMacRet(sMacStuct sMac, bool ret, char *errMsg,int errBuffSize) = 0;
	//检查当前的DUT barCode是否合法
	//barCode 的来源如果是来自MES的MAC，就是检查MAC
	//来自扫面枪输入就，检查输入的信息
	virtual int checkDutBarCode(const char *barCode, char *errMsg,int errBuffSize) = 0;
	//将测试信息上传给MES
	virtual int uploadTestInfoToMesServer(const MESDutTestInfo &testInfo,
									  const vector <sCalFreqDataStruct > &CalFreqDataStruct,
									  const vector <sCalPowDataStruct > &CalPowDataStruct,
									  const vector <sTXVerifyDateStruct> &TXVerifyDateStruct,
									  const vector <sRXVerifyDataStruct> &RXVerifyDataStruct,
									  char *errMsg,int errBuffSize) = 0;
	//将本地LOG上传给MES
	virtual int uploadLogToMesServer(const char *log,char *errMsg,int errBuffSize) = 0;
};

#endif


