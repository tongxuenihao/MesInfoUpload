// log.h : log DLL ����ͷ�ļ�
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
	int		iType;							//������ͣ� ȡֵ��TEST_TYPE
	bool	bResult;						//�����Ƿ�ͨ�����
	double	dValue;							//���Խ��ֵ
	double	dLimit;							//���Ե�����
	double  dLimitUp;						//����ֵ����
	double  dLimitDown;						//����ֵ����
};

// ƵƫУ׼��������
struct sCalFreqDataStruct
{
	int			iDemode;					//���Ե�Э��
	double		dDataRate;					//�������� 
	int			iMcs;
	int			iChannel;					//����ͨ��
	double		dFreq;
	int			iFreqReg;					//���Ե�Ƶƫ�Ĵ���ֵ
	double		dFreqValue;					//���Ե�Ƶƫֵ
	double		dTargetFreqValue;			//Ŀ��Ƶƫֵ
	double		dErrRange;					//Ƶƫ����
	bool		bIsPass;					//�����Ƿ�ͨ��
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
// ����У׼��������
struct  sCalPowAndFreqErrDataStruct
{
	int			iDemode;					//���Ե�Э��
	int			iAnt;						//��������
	int			iMcs;
	int			iChannel;					//����ͨ��
	double		dDataRate;					//��������
	double		dFreq;

	vector <int>iPowReg;					//���ԵĹ��ʼĴ���ֵ
	double		dPowValue;					//���ԵĹ���ֵ
	double		dTargetPow;					//Ŀ�깦��ֵ
	double		dToleraneUp;				//����Ĺ������� dTargetPow + dToleraneUp
	double		dToleraneLow;				//����Ĺ�������	dTargetPow + dToleraneLow
		
	int			iFreqReg;					//���Ե�Ƶƫ�Ĵ���ֵ
	double		dTargetFreqValue;			//Ŀ��Ƶƫֵ
	double		dFreqValue;					//���Ե�Ƶƫֵ
	double		dFreqErrRange;				//Ƶƫ����

	bool		bIsPass;					//�����Ƿ�ͨ��
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

// ����У׼��������
struct  sCalPowDataStruct
{
	int			iDemode;					//���Ե�Э��
	int			iAnt;						//��������
	double		dDataRate;					//��������
	int			iMcs;
	int			iChannel;					//����ͨ��
	double		dFreq;
	vector <int>iPowReg;					//���ԵĹ��ʼĴ���ֵ
	double		dPowValue;					//���ԵĹ���ֵ
	double		dTargetPow;					//Ŀ�깦��ֵ
	double		dToleraneUp;				//����Ĺ������� dTargetPow + dToleraneUp
	double		dToleraneLow;				//����Ĺ�������	dTargetPow + dToleraneLow
	bool		bIsPass;					//�����Ƿ�ͨ��
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

// TX Verify��������
struct sTXVerifyDateStruct
{
	int			iDemode;					//���Ե�Э��
	int			iAnt;						//���Ե�����
	double		dDataRate;					//���Ե�����
	int			iMcs;
	int			iChannel;					//���Ե�ͨ��
	double		dFreq;
	vector<int>	iPowReg;					//���ԵĹ��ʼĴ���ֵ
	vector <sTestData>	sSeparateTestItem; 
	bool		bIsPass;					//�����Ƿ�ͨ��
	int			iPreamble;					//����ǰ��
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
		iPreamble = 1;						//Ĭ��Ϊ��ǰ��
		dTestTime = 0;
	}
};
// RX Verify��������
struct sRXVerifyDataStruct
{
	int			iDemode;					//���Ե�Э��
	int			iAnt;						//��������
	double		dDataRate;					//��������
	int			iMcs;
	int			iChannel;					//����ͨ��
	double		dFreq;
	int			iSendFrameCount;			//����֡������
	int			iReceiveFrameCount;			//����֡������
	double		dSendPow;					//�������书��
	sTestData	sSeparateTestItem;
	bool		bIsPass;					//�����Ƿ�ͨ��
	int			iPreamble;					//����ǰ��
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
		iPreamble = 1;						//Ĭ��Ϊ��ǰ��
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



