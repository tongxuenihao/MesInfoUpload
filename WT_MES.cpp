// WT_MES.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "WT_MES.h"

#include <stdlib.h>
#include <stdio.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "WTLinkMes.lib")
#pragma comment(lib, "json_vc71_libmt.lib")

cWT_Mes::cWT_Mes(){};

cWT_Mes::~cWT_Mes(){};

int cWT_Mes::setId(int id)
{
	m_Id = id;
	return 0;
}

int cWT_Mes::connectMes(char *errMsg, int errBuffSize)
{
	return 0;
}

int cWT_Mes::disconnectMes(char *errMsg, int errBuffSize)
{
	return 0;
}

int cWT_Mes::getMacFromMes(sMacStuct &sMac, char *errMsg,int errBuffSize)
{
	for (int i=0; i<12; i++)
	{
		sMac.cMacContainer[0][i] = '2';
	}
	sMac.cMacContainer[0][12] = '\0';
	return 0;
}

int cWT_Mes::replyWriteMacRet(sMacStuct sMac, bool ret, char *errMsg,int errBuffSize)
{
	char tempMac[13] = { 0 };
	memcpy_s(errMsg, errBuffSize, "replyWriteMacRet(ADD BY XUETONG)", 33);
	for (int i = 0; i < 13; i++)
	{
		tempMac[i] = sMac.cMacContainer[0][i];
	}
	string macStr = tempMac;
	for (int i = 0; i < 5; i++)
	{
		macStr.insert(2 + 3 * i, ":");
	}
	macCodeSet();
	//memcpy_s(errMsg, errBuffSize, macStr.data(), 12);
	return 0;
}


int cWT_Mes::checkDutBarCode(const char *barCode, char *errMsg,int errBuffSize)
{
	return 0;
}


int cWT_Mes:: uploadTestInfoToMesServer(const MESDutTestInfo &testInfo,
										const vector <sCalFreqDataStruct > &CalFreqDataStruct,
										const vector <sCalPowDataStruct > &CalPowDataStruct,
										const vector <sTXVerifyDateStruct> &TXVerifyDateStruct,
										const vector <sRXVerifyDataStruct> &RXVerifyDataStruct,
										char *errMsg,int errBuffSize)
{
	int a = CalFreqDataStruct.size();
	int b = CalPowDataStruct.size();
	int c = TXVerifyDateStruct.size();
	int d = RXVerifyDataStruct.size();

	int i;
	double m_EVM_dB;
	double m_Pow_dBm;
	double m_FreqErr_ppm;
	double m_Mask_percent;
	
	char *p = "*********************ADD BY XUETONG ********************************";
	memcpy_s(errMsg, errBuffSize, p, 69);
	for (i = 0; i < c; i++)
	{
		if (TXVerifyDateStruct[i].iChannel == 7)
		{
			for (int j = 0; j < TXVerifyDateStruct[i].sSeparateTestItem.size(); j++)
			{
				if (TXVerifyDateStruct[i].sSeparateTestItem[j].iType == TEST_FREQERR)
				{
					m_FreqErr_ppm = TXVerifyDateStruct[i].sSeparateTestItem[j].dValue;
					freqErrCodeSet(m_FreqErr_ppm);
				}
			}
		}
	}
	struct tm st = testInfo.startTm;	

	/*******************************循环接口调用************************/
	timeCodeSet(st);
	socketFd = tcpSocketCreate();
	httpHardwarePostPacketBuild();
	tcpSocketRecv(NULL);
	macCodeSet();
	return 0;
}     

/************************************自定义接口**************************/
void cWT_Mes::itemCodeSet(int channel)

{
	mChannel = channel;
}

int cWT_Mes::itemCodeGet()
{
	return mChannel;
}

void cWT_Mes::macCodeSet()
{
	unsigned char lastMacFormBuff[6];
	long val = strtol((char *)macPresentStr.c_str(), NULL, 16);
	printf("val: %06X\n", val);
	val += 1;
	sprintf((char *)lastMacFormBuff, "%06X", val);
	string Str = (char *)lastMacFormBuff;
	std::cout << "Str:" << Str << std::endl;
	modifyLineData("macConfig.txt", 4, "WT_MAC_CURRENT=" + Str);
}

string cWT_Mes::macCodeGet()
{
	getMacStrFromConfig();
	mMac = macHeadStr + macPresentStr;
	for (int i = 0; i < 5; i++)
	{
		mMac.insert(2 + 3 * i, ":");
	}
	return mMac;
}

void cWT_Mes::timeCodeSet(struct tm st)
{
	//mTime = time;
	char timeBuff[512] = { 0 };
	sprintf_s(timeBuff, "%d-%d-%d %02d:%d:%d", st.tm_year + 1900, st.tm_mon, st.tm_mday, st.tm_hour, st.tm_min = 10, st.tm_sec = 10);
	mTime = timeBuff;
}

string cWT_Mes::timeCodeGet()
{
	return mTime;
}


void cWT_Mes::freqErrCodeSet(int freqErr)
{
	mFreqErr = freqErr;
}

int cWT_Mes::freqErrCodeGet()
{
	return mFreqErr;
}

int cWT_Mes::uploadLogToMesServer(const char *log,char *errMsg,int errBuffSize)
{
	string a = log;
	return 0;
}

int cWT_Mes::tcpSocketCreate()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("初始化Winsock失败");
		return 0;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6690);
	inet_pton(AF_INET, "192.168.0.2", &addrSrv.sin_addr);

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockClient)
	{
		printf("Socket() error:%d", WSAGetLastError());
		return 0;
	}
	if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
	{
		printf("连接失败:%d", WSAGetLastError());
		return 0;
	}
	printf("连接成功\n");
	return sockClient;
}

int cWT_Mes::tcpSocketSend(SOCKET socketFd, char *buff, int len)
{
	return send(socketFd, buff, len, 0);
}

DWORD WINAPI cWT_Mes::tcpSocketRecv(LPVOID lpParamter)
{
	int ret;
	int recvCount;
	fd_set fd;
	struct timeval tm;
	char rxBuff[1024];
	while (1)
	{
		tm.tv_sec = 10;
		tm.tv_usec = 0;
		memset(rxBuff, 0, 1024);
		FD_ZERO(&fd);
		FD_SET(socketFd, &fd);
		ret = select(socketFd + 1, &fd, NULL, NULL, &tm);
		if (ret <= 0)
		{
			continue;
		}
		else
		{
			recvCount = recv(socketFd, rxBuff, 1024, 0);
			std::cout << "recv :" << rxBuff << std::endl;
			ret = msgHandle(rxBuff);
			if (ret == 1 || ret == -1)
			{                          
				closesocket(socketFd);
				socketFd = -1;
				return 0;
			}
		}
		Sleep(2000);
	}
}

std::string cWT_Mes::jsonHardwarePacketCreate()
{
	Json::Value arrayObj, arrayObjExt;
	Json::Value jsonData;
	Json::Value testValueExt;
	jsonData["ITEM_CODE"] = "WIFI_TX_CH7_11M";
	jsonData["MAC_ADDRESS"] = macCodeGet();//"84:7C:9B:00:03:40";
	jsonData["PROCESS_STATUS"] = "Pending";
	jsonData["TEST_DATETIME"] = timeCodeGet();//"2018-12-19 15:20:35";
	jsonData["TEST_RESULT"] = 1;

	testValueExt["ITEM_CODE_SUFFIX"] = "FreqErr";
	testValueExt["TEST_VALUE"] = freqErrCodeGet();
	arrayObjExt.append(testValueExt);
	jsonData["TEST_VALUE_EXT"] = arrayObjExt;

	arrayObj.append(jsonData);
	arrayObj.toStyledString();
	std::string out = arrayObj.toStyledString();
	return out;
}

std::string cWT_Mes::jsonMacPacketCreate()
{
	Json::Value arrayObj, arrayObjExt;
	Json::Value jsonData;

	jsonData["MAC_ADDRESS"] = macCodeGet();//"84:7C:9B:00:03:40";
	jsonData["PROCESS_STATUS"] = "Pending";
	jsonData["TEST_DATETIME"] = timeCodeGet();//"2018-12-19 15:20:35";
	jsonData["TEST_RESULT"] = 1;
	arrayObj.append(jsonData);
	arrayObj.toStyledString();
	std::string out = arrayObj.toStyledString();
	return out;
}

void cWT_Mes::httpHardwarePostPacketBuild()
{
	char *url = "/api/iot/testing/hardware/stduri/bulkadd";
	const char *payLoad;
	char txBuff[1024] = { 0 };
	std::string jsonStr = jsonHardwarePacketCreate();
	payLoad = jsonStr.data();
	int payLoadLenth = strlen(payLoad);
	snprintf((char *)txBuff, 1024, "%s %s %s%s%s %s%s%s %d%s%s%s%s%s",
		"POST", url, "HTTP/1.1", kCRLFNewLine,
		"Host:", "192.168.0.2", kCRLFNewLine,
		"Content-Length:", payLoadLenth, kCRLFNewLine,
		"Content-Type: application/json", kCRLFNewLine,
		kCRLFNewLine,
		payLoad
	);
	std::cout << "send :" << txBuff << std::endl;
	tcpSocketSend(socketFd, txBuff, strlen(txBuff));
}

void cWT_Mes::httpMacPostPacketBuild()
{
	char *url = "/api/iot/testing/burning/stduri/bulkadd";
	const char *payLoad;
	char txBuff[1024] = { 0 };
	std::string jsonStr = jsonMacPacketCreate();
	payLoad = jsonStr.data();
	int payLoadLenth = strlen(payLoad);
	snprintf((char *)txBuff, 1024, "%s %s %s%s%s %s%s%s %d%s%s%s%s%s",
		"POST", url, "HTTP/1.1", kCRLFNewLine,
		"Host:", "192.168.0.2", kCRLFNewLine,
		"Content-Length:", payLoadLenth, kCRLFNewLine,
		"Content-Type: application/json", kCRLFNewLine,
		kCRLFNewLine,
		payLoad
	);
	std::cout << "send :" << txBuff << std::endl;
	tcpSocketSend(socketFd, txBuff, strlen(txBuff));
}

int cWT_Mes::msgHandle(char *data)
{
	Json::Reader Reader;
	Json::Value jsonData;
	Json::Value jsonDataElement;
	Json::Value jsonDataElementObj;
	int returnval;
	char *header = NULL;
	char *body = NULL;
	header = strstr(data, kCRLFLineEnding);
	if (header)
	{
		body = header + strlen("\r\n\r\n");
	}
	else
	{
		return -1;
	}


	Reader.parse(body, jsonData);
	bool out = jsonData["success"].asBool();
	if (out == true)
	{
		jsonDataElement = jsonData["data"];
		if (jsonDataElement.isArray())
		{
			jsonDataElementObj = jsonDataElement[(unsigned int)0];
			if (jsonDataElementObj["ITEM_CODE"].isString())
			{
				goto HARDWARE;

			}
			else
			{
				goto MAC;
			}
		}
	}

HARDWARE:
	returnval = jsonDataElementObj["ReturnVal"].asInt();
	std::cout << "returnval:" << returnval << std::endl;
	if (returnval == 1)
	{
		httpMacPostPacketBuild();
	}
	else
	{
		return -1;
	}
	return 0;

MAC:
	returnval = jsonDataElementObj["ReturnVal"].asInt();
	std::cout << "returnval:" << returnval << std::endl;
	if (returnval == 1)
	{
		std::cout << "success" << std::endl;
	}
	else
	{
		return -1;
	}
	return 1;
}

void cWT_Mes::macStrHandle()
{
	string macStr;
	for (int i = 0; i < 5; i++)
	{
		macStr.insert(2 + 3 * i, ":");
	}
}

string cWT_Mes::getStr(string str)
{
	char *tempStr = (char *)str.c_str();
	char *pos = strchr(tempStr, '=');
	string macStr = pos + 1;
	return macStr;
}

string cWT_Mes::charToStr(char * contentChar)
{
	string tempStr;
	for (int i = 0; contentChar[i] != '\0'; i++)
	{
		tempStr += contentChar[i];
	}
	return tempStr;
}


void cWT_Mes::modifyLineData(char* fileName, int lineNum, string lineData)
{
	ifstream in;
	in.open(fileName);

	string strFileData = "";
	int line = 1;
	char tmpLineData[1024] = { 0 };
	while (in.getline(tmpLineData, sizeof(tmpLineData)))
	{
		if (line == lineNum)
		{
			strFileData += lineData;// charToStr(lineData);
			strFileData += "\n";
		}
		else
		{
			strFileData += charToStr(tmpLineData);
			strFileData += "\n";
		}
		line++;
	}
	in.close();

	ofstream out;
	out.open(fileName);
	out.flush();
	out << strFileData;
	out.close();
}



void cWT_Mes::getMacStrFromConfig()
{
	string::size_type idx;
	string s;
	ifstream inf;
	inf.open("macConfig.txt");
	while (getline(inf, s))
	{
		idx = s.find("WT_MAC_VENDOR_ID=");
		if (idx != string::npos)
		{
			macHeadStr = getStr(s);
		}
		idx = s.find("WT_MAC_RANGE_BEGIN=");
		if (idx != string::npos)
		{
			macStartStr = getStr(s);
		}
		idx = s.find("WT_MAC_RANGE_END=");
		if (idx != string::npos)
		{
			macEndStr = getStr(s);
		}
		idx = s.find("WT_MAC_CURRENT=");
		if (idx != string::npos)
		{
			macPresentStr = getStr(s);

		}
	}
	inf.close();
}

int cWT_Mes::strToHex(char *string, unsigned char *cbuf, int len)
{
	BYTE high, low;
	int idx, ii = 0;
	for (idx = 0; idx<len; idx += 2)
	{
		high = string[idx];
		low = string[idx + 1];

		if (high >= '0' && high <= '9')
			high = high - '0';
		else if (high >= 'A' && high <= 'F')
			high = high - 'A' + 10;
		else if (high >= 'a' && high <= 'f')
			high = high - 'a' + 10;
		else
			return -1;

		if (low >= '0' && low <= '9')
			low = low - '0';
		else if (low >= 'A' && low <= 'F')
			low = low - 'A' + 10;
		else if (low >= 'a' && low <= 'f')
			low = low - 'a' + 10;
		else
			return -1;

		cbuf[ii++] = high << 4 | low;
	}
	return 0;
}


extern "C" __declspec(dllexport) cMesOperateBase *createMes()
{
	return new cWT_Mes;
}

extern "C" __declspec(dllexport) void deleteMes(cMesOperateBase *pMes)
{
	delete pMes;
}


