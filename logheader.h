// log.h : log DLL 的主头文件
//
#ifndef  __LOG_HEADER_H__
#define __LOG_HEADER_H__

#ifdef LOG_EXPORTS
#define  LOG_API __declspec(dllexport)
#else
#define LOG_API __declspec(dllimport)
#endif // COMMON_EXPORTS

#include <string>
#include <vector>
#include <Windows.h>  
#include <deque>
//#include "commonlib.h"

using namespace std;

enum TESTRE_TYPE{
	eum_Unknow,
	eum_WT160,
	eum_WT200,
	eum_WT208,
};
enum TEST_TYPE {
	TEST_POWER,
	TEST_PEAK_POWER,
	TEST_EVM,
	TEST_EVM_PEAK,
	TEST_MASK,
	TEST_MASK_LOWER1,
	TEST_MASK_LOWER2,
	TEST_MASK_UPPER1,
	TEST_MASK_UPPER2,
	TEST_PHASE,
	TEST_SYMOL_CLK,
	TEST_FREQERR,
	TEST_FREQERR_LOWER1,
	TEST_FREQERR_LOWER2,
	TEST_FREQERR_UPPER1,
	TEST_FREQERR_UPPER2,
	TEST_LO_LEAKAGE,
	TEST_OBW,
	TEST_AMP_ERR,
	TEST_PHASE_NOISE_RMS_ALL,
	TEST_PER,
	TEST_TSSI,
	TEST_DATA_RATE,
	TEST_MASK_FLATNESS,
	TEST_BT_FREQ_DRIFT,
	TEST_BT_POWER_DIFF,
	TEST_BT_DEVM,
	TEST_BT_DEVM_PEAK,
	TEST_BT_DEVM_PCT,
	TEST_BT_OMEGAI,
	TEST_BT_OMEGAO,
	TEST_BT_OMEGAIO,
	TEST_BT_ICFT,
	TEST_DELTA_F1_AVG,
	TEST_DELTA_F2_AVG,
	TEST_DELTA_F2_F1_RATIO,
	TEST_DELTA_F2_MAX,
	TEST_BT_BER,
	TEST_ZIGBEE_EVM,
	TEST_ZIGBEE_POWER,
	TEST_BLE_Fn_MAX,
	TEST_BLE_F0Fn_MAX,
	TEST_BLE_F0F1_DELTA,
	TEST_BLE_FnFn5_MAX,
	TEST_BR_FREQ_DRIFT_RATE,
};

struct sTestData 
{
	int		iType;							//结果类型， 取值见TEST_TYPE
	bool	bResult;						//测试是否通过结果
	double	dValue;							//测试结果值
	double	dLimit;							//测试的门限
	double  dLimitUp;						//测试值上限
	double  dLimitDown;						//测试值下限
};

// 频偏校准测试数据
struct sCalFreqDataStruct
{
	int			iDemode;					//测试的协议
	double		dDataRate;					//测试速率 
	int			iMcs;
	int			iChannel;					//测试通道
	double		dFreq;
	int			iFreqReg;					//测试的频偏寄存器值
	double		dFreqValue;					//测试的频偏值
	double		dTargetFreqValue;			//目标频偏值
	double		dErrRange;					//频偏门限
	bool		bIsPass;					//测试是否通过
	double		dTestTime;

	sCalFreqDataStruct()
	{
		iDemode = 0;
		dDataRate = 0;
		iMcs = 0;
		iChannel = 0;
		dFreq = 0;
		iFreqReg = 0;
		dFreqValue = 0;
		dTargetFreqValue = 0;
		dErrRange = 0;
		bIsPass = false;
		dTestTime = 0;
	}
};
// 功率校准测试数据
struct  sCalPowAndFreqErrDataStruct
{
	int			iDemode;					//测试的协议
	int			iAnt;						//测试天线
	int			iMcs;
	int			iChannel;					//测试通道
	double		dDataRate;					//测试速率
	double		dFreq;

	vector <int>iPowReg;					//测试的功率寄存器值
	double		dPowValue;					//测试的功率值
	double		dTargetPow;					//目标功率值
	double		dToleraneUp;				//允许的功率上限 dTargetPow + dToleraneUp
	double		dToleraneLow;				//允许的功率下限	dTargetPow + dToleraneLow
		
	int			iFreqReg;					//测试的频偏寄存器值
	double		dTargetFreqValue;			//目标频偏值
	double		dFreqValue;					//测试的频偏值
	double		dFreqErrRange;				//频偏门限

	bool		bIsPass;					//测试是否通过
	double		dTestTime;

	sCalPowAndFreqErrDataStruct()
	{
		iDemode = 0;
		iAnt =	0;
		dDataRate = 0;
		iMcs = 0;
		iChannel = 0;
		dFreq = 0;
		iPowReg.clear();
		dPowValue = 0;
		dTargetPow = 0;
		dToleraneLow = 0;
		dToleraneUp = 0;
		iFreqReg = 0;
		dTargetFreqValue = 0;
		dFreqValue = 0;
		dFreqErrRange = 0;
		bIsPass = false;
		dTestTime = 0;
	}
};

// 功率校准测试数据
struct  sCalPowDataStruct
{
	int			iDemode;					//测试的协议
	int			iAnt;						//测试天线
	double		dDataRate;					//测试速率
	int			iMcs;
	int			iChannel;					//测试通道
	double		dFreq;
	vector <int>iPowReg;					//测试的功率寄存器值
	double		dPowValue;					//测试的功率值
	double		dTargetPow;					//目标功率值
	double		dToleraneUp;				//允许的功率上限 dTargetPow + dToleraneUp
	double		dToleraneLow;				//允许的功率下限	dTargetPow + dToleraneLow
	bool		bIsPass;					//测试是否通过
	double		dTestTime;

	sCalPowDataStruct()
	{
		iDemode = 0;
		iAnt =	0;
		dDataRate = 0;
		iMcs = 0;
		iChannel = 0;
		dFreq = 0;
		iPowReg.clear();
		dPowValue = 0;
		dTargetPow = 0;
		dToleraneLow = 0;
		dToleraneUp = 0;
		bIsPass = false;
		dTestTime = 0;
	}
};

// TX Verify测试数据
struct sTXVerifyDateStruct
{
	int			iDemode;					//测试的协议
	int			iAnt;						//测试的天线
	double		dDataRate;					//测试的速率
	int			iMcs;
	int			iChannel;					//测试的通道
	double		dFreq;
	vector<int>	iPowReg;					//测试的功率寄存器值
	vector <sTestData>	sSeparateTestItem; 
	bool		bIsPass;					//测试是否通过
	int			iPreamble;					//长短前导
	double		dTestTime;

	sTXVerifyDateStruct()
	{
		iDemode = 0;
		iAnt = 0;
		dDataRate = 0;
		iMcs = 0;
		iChannel = 0;
		dFreq = 0;
		iPowReg.clear();
		sSeparateTestItem.clear();
		bIsPass = false;
		iPreamble = 1;						//默认为长前导
		dTestTime = 0;
	}
};
// RX Verify测试数据
struct sRXVerifyDataStruct
{
	int			iDemode;					//测试的协议
	int			iAnt;						//测试天线
	double		dDataRate;					//测试速率
	int			iMcs;
	int			iChannel;					//测试通道
	double		dFreq;
	int			iSendFrameCount;			//发送帧的总数
	int			iReceiveFrameCount;			//接受帧的总数
	double		dSendPow;					//仪器发射功率
	sTestData	sSeparateTestItem;
	bool		bIsPass;					//测试是否通过
	int			iPreamble;					//长短前导
	double		dTestTime;

	sRXVerifyDataStruct()
	{
		iDemode = 0;
		iAnt = 0;
		dDataRate = 0;
		iMcs = 0;
		iChannel = 0;
		dFreq = 0;
		iSendFrameCount = 0;
		iReceiveFrameCount = 0;
		dSendPow = 0;
		memset(&sSeparateTestItem, 0, sizeof(sTestData));
		bIsPass = false;
		iPreamble = 1;						//默认为长前导
		dTestTime = 0;
	}
};

struct sCsvLogParam
{
	int  iId;
	char cSn[256];
	char cMac[256];
	char cTesterSN[256];
	bool bTestResult;
	struct tm startTm;
	struct tm endTm;
	char cReserve[256];
	sCsvLogParam()
	{
		iId = 0;
		bTestResult = false;
		for (int i=0; i<256; i++)
		{
			cSn[i] = '\0';
			cMac[i] = '\0';
			cReserve[i] = '\0';
			cTesterSN[i] = '\0';
		}
	}
};

#endif // __LOG_H__



