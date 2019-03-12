#ifndef __WT_MES_H__
#define __WT_MES_H__
#include "LinkMes.h"
#include <winsock2.h>
#include <WS2tcpip.h>
#include "json.h"
#include <fstream>
#include <cassert>

class cWT_Mes : public cMesOperateBase{
public:
	cWT_Mes();
	~cWT_Mes();
	virtual int setId(int id);

	virtual int connectMes(char *errMsg, int errBuffSize);

	virtual int disconnectMes(char *errMsg, int errBuffSize);

	virtual int getMacFromMes(sMacStuct &sMac, char *errMsg,int errBuffSize);

	virtual int replyWriteMacRet(sMacStuct sMac, bool ret, char *errMsg,int errBuffSize);

	virtual int checkDutBarCode(const char *barCode, char *errMsg,int errBuffSize);

	virtual int uploadTestInfoToMesServer(const MESDutTestInfo &testInfo,
											const vector <sCalFreqDataStruct > &CalFreqDataStruct,
											const vector <sCalPowDataStruct > &CalPowDataStruct,
											const vector <sTXVerifyDateStruct> &TXVerifyDateStruct,
											const vector <sRXVerifyDataStruct> &RXVerifyDataStruct,
											char *errMsg,int errBuffSize);

	virtual int uploadLogToMesServer(const char *log,char *errMsg,int errBuffSize);
	virtual int tcpSocketSend(SOCKET socketFd, char *buff, int len);
	virtual int tcpSocketCreate();
	DWORD WINAPI tcpSocketRecv(LPVOID lpParamter);
	//DWORD WINAPI cWT_Mes::tcpSocketRecv(LPVOID lpParamter);
	std::string jsonHardwarePacketCreate();
	std::string jsonMacPacketCreate();
	void httpHardwarePostPacketBuild();
	void httpMacPostPacketBuild();
	int msgHandle(char *data);
	void itemCodeSet(int channel);
	int itemCodeGet();
	void macCodeSet();
	string macCodeGet();
	void timeCodeSet(struct tm st);
	string timeCodeGet();
	void freqErrCodeSet(int freqErr);
	int freqErrCodeGet();
	string getStr(string str);
	string charToStr(char * contentChar);
	void modifyLineData(char* fileName, int lineNum, string lineData);
	void getMacStrFromConfig();
	int strToHex(char *string, unsigned char *cbuf, int len);
	void macStrHandle();

private:
	#define kCRLFNewLine "\r\n" 
	#define kCRLFLineEnding "\r\n\r\n"
	int m_Id;
	SOCKET socketFd;
	int mChannel;
	int mFreqErr;
	string mMac;
	string mTime;

	string macHeadStr;
	string macStartStr;
	string macEndStr;
	string macPresentStr;

};

#endif
