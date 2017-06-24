// trade.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TradeLib.h"
#include "trade.h"
#include "DataPaser.h"
#include "ShareQuotation.h"
#include "TradeLogger.h"
#include "TdxL2HqApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
//#define p printf
#define MAX_SHARE_NUM 3300 
char result[300* MAX_SHARE_NUM];//one share need 300 for quotation
extern ShareQuotation quotation;
DataPaser quotesData;



FILE *hFile;
ShareList sharelist;
#define ONE_KW		(10000000LL)	//1ǧ��
#define FIVE_KW		(50000000LL)	//5ǧ��
#define ONE_YI		(100000000LL)	//һ��

#define RETURN_CODE_WHEN_OPEN	0
#define PAUSE_WHEN_OPEN			
char* wait_open(ShareList* pShareList, int64_t warnningAmount, int flag);
int wait_open_exchange() {
	sharelist.initFromFile("XA1.blk");
	char* pcode = wait_open(&sharelist, ONE_YI, RETURN_CODE_WHEN_OPEN);
	//gjRLib.exchange("603969", pcode);
	return 0;
}

char* wait_open(ShareList* pShareList, int64_t warnningAmount ,int flag) {
	int i, ret;
	int buyPrice1;
	int sellVol1 = 0;
	int buyVol1 = 0;
	char *pcode;
	int64_t buyAmount1;
	short count = pShareList->getShareCount();
	while (TRUE) {
		ret = quotation.get_quotes(pShareList->getMarketList(), pShareList->getCodeList(), count, result);
		if (ret == RET_FAILED) {
			p("reconect \n");
			quotation.connect("218.75.75.20", 443);
			ret = quotation.get_quotes(pShareList->getMarketList(), pShareList->getCodeList(), count, result);

			//getchar();

		}
		quotesData.paserData(result);
		//quotesData.print();
		//p("haha:%s\n", quotesData.getItem("��һ��",1));
		for (i = 1; i < count + 1; ++i)
		{
			//p("haha:%s\n", quotesData.getItem("��һ��", i));
			//p("haha:%s\n", quotesData.getItem("��һ��", i));
			//p("haha:%s\n", quotesData.getItem("��һ��", i));
			sellVol1 = atoi(quotesData.getItem("��һ��", i));
			buyVol1 = atoi(quotesData.getItem("��һ��", i));
			buyPrice1 = (int)(atof(quotesData.getItem("��һ��", i)) * 100);
			buyAmount1 = (int64_t)buyPrice1 *buyVol1;
			//p("��һ��:%d   ��һ����%d price:%d buyAmount1:%lldw\n", sellVol1, buyVol1, buyPrice1, buyAmount1/10000);
			pcode = quotesData.getItem("����", i);

			if (sellVol1 == 0) {

				if (buyAmount1 < warnningAmount) {
					p("=============================\n");
					p("��%s�� will open\n", pcode);
					p("��һ��:%d   ��һ����%d price:%d buyAmount1:%lldw\n", sellVol1, buyVol1, buyPrice1, buyAmount1 / 10000);
					if (flag == RETURN_CODE_WHEN_OPEN) {
						return pcode;

					}
					else {
						p("Press ENTER continue\n");
						getchar();
					}

				}
				else {
					//p("%s will not open at once\n", pcode);

				}
			}
			else {
				p("=============================\n");
				p("��%s�� have openen\n", pcode);
				p("��һ��:%d   ��һ����%d price:%d buyAmount1:%lldw\n", sellVol1, buyVol1, buyPrice1, buyAmount1 / 10000);
				if (flag == RETURN_CODE_WHEN_OPEN) {
					return pcode;
				}
				else {
					p("Press ENTER continue\n");
					getchar();
				}
			}
			//getchar();
		}
	}
	//

}

int wait_open1(ShareList* pShareList) {
	int i, ret;
	int buyPrice1;
	int sellVol1 = 0;
	int buyVol1 = 0;
	int64_t buyAmount1;
	short count = pShareList->getShareCount();
	while (TRUE) {
		ret = quotation.get_quotes(pShareList->getMarketList(), pShareList->getCodeList(), count, result);
		if (ret == RET_FAILED) {
			p("reconect \n");
			quotation.connect("218.75.75.20", 443);
			ret = quotation.get_quotes(pShareList->getMarketList(), pShareList->getCodeList(), count, result);

			getchar();

		}
		quotesData.paserData(result);
		//quotesData.print();
		//p("haha:%s\n", quotesData.getItem("��һ��",1));
		for (i = 1; i < count + 1; ++i)
		{
			//p("haha:%s\n", quotesData.getItem("��һ��", i));
			//p("haha:%s\n", quotesData.getItem("��һ��", i));
			//p("haha:%s\n", quotesData.getItem("��һ��", i));
			sellVol1 = atoi(quotesData.getItem("��һ��", i));
			buyVol1 = atoi(quotesData.getItem("��һ��", i));
			buyPrice1 = (int)(atof(quotesData.getItem("��һ��", i)) * 100);
			buyAmount1 = (int64_t)buyPrice1 *buyVol1;
			//p("��һ��:%d   ��һ����%d price:%d buyAmount1:%lldw\n", sellVol1, buyVol1, buyPrice1, buyAmount1/10000);

			if (sellVol1 == 0) {

				if (buyAmount1 < 10000LL * 10000LL) {
					p("=============================\n");
					p("��%s�� will open\n", quotesData.getItem("����", i));
					p("��һ��:%d   ��һ����%d price:%d buyAmount1:%lldw\n", sellVol1, buyVol1, buyPrice1, buyAmount1 / 10000);
					p("Press ENTER continue\n");
					getchar();

				}
				else {
					//p("%s will not open at once\n", quotesData.getItem("����", i));

				}
			}
			else {
				p("=============================\n");
				p("��%s�� have openen\n", quotesData.getItem("����", i));
				p("��һ��:%d   ��һ����%d price:%d buyAmount1:%lldw\n", sellVol1, buyVol1, buyPrice1, buyAmount1 / 10000);
				p("Press ENTER continue\n");
				getchar();
			}
			//getchar();
		}
	}
	//

}
int TdxL2Test()
{
	//����dll, dllҪ���Ƶ�debug��releaseĿ¼��,������ö��ֽ��ַ����������,�û����ʱ���Լ����Ƹ�������ʾ��С��λ���뾫��
	HMODULE TdxApiHMODULE = LoadLibrary(_T("TdxL2HqApi.dll"));

	//��ȡapi����
	TdxL2Hq_GetDetailTransactionDataDelegate TdxL2Hq_GetDetailTransactionData = (TdxL2Hq_GetDetailTransactionDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetDetailTransactionData");
	TdxL2Hq_GetDetailOrderDataDelegate TdxL2Hq_GetDetailOrderData = (TdxL2Hq_GetDetailOrderDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetDetailOrderData");
	TdxL2Hq_GetSecurityQuotes10Delegate TdxL2Hq_GetSecurityQuotes10 = (TdxL2Hq_GetSecurityQuotes10Delegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetSecurityQuotes10");
	TdxL2Hq_GetBuySellQueueDelegate TdxL2Hq_GetBuySellQueue = (TdxL2Hq_GetBuySellQueueDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetBuySellQueue");


	TdxL2Hq_ConnectDelegate TdxL2Hq_Connect = (TdxL2Hq_ConnectDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_Connect");
	TdxL2Hq_DisconnectDelegate TdxL2Hq_Disconnect = (TdxL2Hq_DisconnectDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_Disconnect");
	TdxL2Hq_GetSecurityBarsDelegate TdxL2Hq_GetSecurityBars = (TdxL2Hq_GetSecurityBarsDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetSecurityBars");
	TdxL2Hq_GetIndexBarsDelegate TdxL2Hq_GetIndexBars = (TdxL2Hq_GetIndexBarsDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetIndexBars");
	TdxL2Hq_GetMinuteTimeDataDelegate TdxL2Hq_GetMinuteTimeData = (TdxL2Hq_GetMinuteTimeDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetMinuteTimeData");
	TdxL2Hq_GetHistoryMinuteTimeDataDelegate TdxL2Hq_GetHistoryMinuteTimeData = (TdxL2Hq_GetHistoryMinuteTimeDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetHistoryMinuteTimeData");
	TdxL2Hq_GetTransactionDataDelegate TdxL2Hq_GetTransactionData = (TdxL2Hq_GetTransactionDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetTransactionData");
	TdxL2Hq_GetHistoryTransactionDataDelegate TdxL2Hq_GetHistoryTransactionData = (TdxL2Hq_GetHistoryTransactionDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetHistoryTransactionData");
	TdxL2Hq_GetSecurityQuotesDelegate TdxL2Hq_GetSecurityQuotes = (TdxL2Hq_GetSecurityQuotesDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetSecurityQuotes");
	TdxL2Hq_GetCompanyInfoCategoryDelegate TdxL2Hq_GetCompanyInfoCategory = (TdxL2Hq_GetCompanyInfoCategoryDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetCompanyInfoCategory");
	TdxL2Hq_GetCompanyInfoContentDelegate TdxL2Hq_GetCompanyInfoContent = (TdxL2Hq_GetCompanyInfoContentDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetCompanyInfoContent");
	TdxL2Hq_GetXDXRInfoDelegate TdxL2Hq_GetXDXRInfo = (TdxL2Hq_GetXDXRInfoDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetXDXRInfo");
	TdxL2Hq_GetFinanceInfoDelegate TdxL2Hq_GetFinanceInfo = (TdxL2Hq_GetFinanceInfoDelegate)GetProcAddress(TdxApiHMODULE, "TdxL2Hq_GetFinanceInfo");



	//��ʼ��ȡ��������
	char* Result = new char[1024 * 1024];
	char* ErrInfo = new char[256];
	short Count = 10;

	///����ȯ��L2��������һ����Ϊ���µ�ַ:
	///�߼�����_�Ϻ�����1:61.152.107.173:7707
	///�߼�����_�Ϻ�����2:61.152.168.232:7715
	///�߼�����_�Ϻ�����3:61.152.168.227:7709
	///�߼�����_�Ϻ�����4:61.152.107.170:7707
	///�߼�����_���ڵ���1:119.147.86.172:443
	///�߼�����_���ڵ���2:113.105.73.81:7721
	///�߼�����_��ݸ����1:113.105.142.138:7709
	///�߼�����_��ݸ����2:113.105.142.139:7709
	///�߼�����_�人����1:59.175.238.41:443
	///�߼�����_�人����2:119.97.185.4:7709
	///�߼�����_�人����3:59.175.238.38:7707
	///�߼�����_������ͨ:123.129.245.202:80
	///�߼�����_������ͨ:61.135.142.90:443
	///�߼�����_�Ϻ���ͨ:210.51.55.212:80
	///�߼�����_��ݸ��ͨ1:58.253.96.198:7709
	///�߼�����_��ݸ��ͨ2:58.253.96.200:7709

	bool bool1 = TdxL2Hq_Connect("61.135.142.90", 443, Result, ErrInfo);
	if (!bool1)
	{
		cout << ErrInfo << endl;//��¼ʧ��
		return 0;
	}

	cout << Result << endl;//��¼�ɹ�


	bool1 = TdxL2Hq_GetBuySellQueue(1, "600030", Result, ErrInfo); cout << Result << endl;


	byte Market[] = { 0,1 };
	char* Zqdm[] = { "000001","600030" };
	short ZqdmCount = 2;
	bool1 = TdxL2Hq_GetSecurityQuotes10(Market, Zqdm, ZqdmCount, Result, ErrInfo); cout << Result << endl;


	bool1 = TdxL2Hq_GetDetailTransactionData(0, "000001", 0, Count, Result, ErrInfo); cout << Result << endl;

	bool1 = TdxL2Hq_GetDetailOrderData(0, "000001", 0, Count, Result, ErrInfo); cout << Result << endl;



	//��ȡ��ƱK������
	//bool1 = TdxL2Hq_GetSecurityBars(0, 0, "000001", 0, Count, Result, ErrInfo);//��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��  8->1����K��  9->��K��  10->��K��  11->��K��
	//if (!bool1)
	//{
	//	cout << ErrInfo << endl;
	//	return 0;
	//}
	//cout << Result << endl;



	//��ȡָ��K������
	bool1 = TdxL2Hq_GetIndexBars(4, 1, "000001", 0, Count, Result, ErrInfo);//��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��     8->1����K��    9->��K��  10->��K��  11->��K��
	if (!bool1)
	{
		cout << ErrInfo << endl;
		return 0;
	}
	cout << Result << endl;





	//��ȡ��ʱͼ����
	/*bool1 = TdxL2Hq_GetMinuteTimeData(0, "000001",  Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/


	//��ȡ��ʷ��ʱͼ����
	/*bool1 = TdxL2Hq_GetHistoryMinuteTimeData(0, "000001", 20140904, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/


	//��ȡ�ֱ�ͼ����
	/*bool1 = TdxL2Hq_GetTransactionData(0, "000001", 0, Count, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/



	//��ȡ��ʷ�ֱ�ͼ����
	/*bool1 = TdxL2Hq_GetHistoryTransactionData(0, "000001", 0, Count, 20140904,  Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/




	//��ȡ�嵵��������
	/*byte Market[] = {0,1};
	char* Zqdm[] = {"000001","600030"};
	short ZqdmCount = 2;
	bool1 = TdxL2Hq_GetSecurityQuotes(Market, Zqdm, ZqdmCount, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl; */



	//��ȡF10���ݵ����
	/*bool1 = TdxL2Hq_GetCompanyInfoCategory(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/



	//��ȡF10���ݵ�ĳ��������
	/*bool1 = TdxL2Hq_GetCompanyInfoContent(1, "600030", "600030.txt", 0, 16824, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/


	//��ȡ��Ȩ��Ϣ��Ϣ
	/*bool1 = TdxL2Hq_GetXDXRInfo(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/





	//��ȡ������Ϣ
	/*bool1 = TdxL2Hq_GetFinanceInfo(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;*/






	TdxL2Hq_Disconnect();

	cout << "�Ѿ��Ͽ�������" << endl;


	FreeLibrary(TdxApiHMODULE);

	int a;
	cin >> a;

	return 0;
}


int main()
{
    char* zqdm[]={"600778","300010"};
    int nRetCode = 0;
    short count;
	//TdxL2Test();
	//logger.add("123\n");
	logger.addFmt("%s--%d--%f\n", zqdm[0], 1999, 1.456);
	logger.print();
	sharelist.initFromFile("HALL.blk");
	quotation.init(_T("TdxHqApi.dll"));
	quotation.connect("218.75.75.20", 443);

	//goto TRADE_TEST;

	wait_open1(&sharelist);

	getchar();

        count=5;
        //quotation.get_cur_datas("600010",count,result);
        count=2;
       // quotation.get_quotes(zqdm,count,result);
        return 0;

//	DataPaser aadata("�ɶ�����	�ɶ�����	�ʺ����	��Ʒ�˺�	������ȯ��ʶ	���	������Ϣ\n\
//0113203051	������	0		0	24F47FE0	���ɶ�\n\
//A564433480	������	1		0	24F47FE0	���ɶ�");
//	aadata.print();
//	p("%s\n",aadata.getItem("�ɶ�����",1));
//	//p("\n");
//	p("%s\n", aadata.getItem("�ɶ�����", 2));
	errno_t aaa=fopen_s(&hFile,"log.txt", "w+");
	if (hFile == NULL) {
		p("open file failed\n");
		return -1;
	}
	fprintf(hFile, "asdfasdfasdf:%d", 123123);
	//fclose(hFile);
TRADE_TEST:
	yhLib.init(_T("trade_yhzq.dll"));
	yhLib.login("219.143.214.206", 443);
	p("1\n");
	yhLib.selfTest();
	logger.print();
	getchar();
	//yhLib.queryData(QUERY_SHARES, result);


	gjRLib.init(_T("trade_gjR.dll"));
	gjRLib.login(GJZQ_R_IP, GJZQ_R_PORT);
	gjRLib.queryData(QUERY_SHARES, result);

	gjLib.init(_T("trade_gj.dll"));
	gjLib.login(GJZQ_R_IP, GJZQ_R_PORT);
	gjLib.queryData(QUERY_SHARES, result);

	whLib.init(_T("trade_wh1.dll"));
	whLib.login(WHZQ_IP, WHZQ_PORT);
	whLib.queryData(QUERY_SHARES, result);

	//yingHeLib.sendOrder(ORDER_BUY, ORDER_LIMIT_PRICE, "601991", 3.91f,100, result);
	//yingHeLib.sendOrder(ORDER_BUY, ORDER_LIMIT_PRICE, "300185", 2.81f, 100, result);
	//yingHeLib.cancelOrder("1", "1011929", result);
	//yingHeLib.cancelOrder("0", "1011931", result);
	//yhLib.queryData(QUERY_MONEY, result);
	//yhLib.queryData(QUERY_SHARES, result);
	//yhLib.queryData(QUERY_ALL_ORDERS, result);
	//yhLib.queryData(QUERY_DONE_ORDERS, result);
	//yhLib.queryData(QUERY_UNDONE_ORDERS, result);
	//yhLib.queryData(QUERY_HOLDER_ID, result);


	fclose(hFile);
	getchar();

    return nRetCode;
}
