
#include "hbx_helper.h"

#include "TradeLib.h"
#include "tdxfuncType.h"

#pragma once
const int QUOTE_HEADER_SIZE = 256;
const int QUOTE_LINE_MAX_SIZE = 320;
class ShareQuotation
{
    private:
		static BOOL bInit;
        //��ȡapi����
        TdxHq_ConnectDelegate TdxHq_Connect;
        TdxHq_DisconnectDelegate TdxHq_Disconnect;
        TdxHq_GetSecurityBarsDelegate TdxHq_GetSecurityBars;
        TdxHq_GetIndexBarsDelegate TdxHq_GetIndexBars;
        TdxHq_GetMinuteTimeDataDelegate TdxHq_GetMinuteTimeData;
        TdxHq_GetHistoryMinuteTimeDataDelegate TdxHq_GetHistoryMinuteTimeData;
        TdxHq_GetTransactionDataDelegate TdxHq_GetTransactionData;
        TdxHq_GetHistoryTransactionDataDelegate TdxHq_GetHistoryTransactionData;
        TdxHq_GetSecurityQuotesDelegate TdxHq_GetSecurityQuotes;
        TdxHq_GetCompanyInfoCategoryDelegate TdxHq_GetCompanyInfoCategory;
        TdxHq_GetCompanyInfoContentDelegate TdxHq_GetCompanyInfoContent;
        TdxHq_GetXDXRInfoDelegate TdxHq_GetXDXRInfo;
        TdxHq_GetFinanceInfoDelegate TdxHq_GetFinanceInfo;



        //��ʼ��ȡ��������
        char Result[1024*2];
        char ErrInfo_[1024];
        bool bRet;
        short Count;
		char server_[32];
		short port_;


    public:


        ShareQuotation();
        ~ShareQuotation();
        int init(TCHAR* libname){
			if (bInit) return RET_SUCCESS;

            HMODULE hModule = LoadLibrary(libname);
            CHECK_HANDLE_RETURN(hModule, "LoadLibrary failed");

            //��ȡapi����
            TdxHq_Connect = (TdxHq_ConnectDelegate)GetProcAddress(hModule, "TdxHq_Connect");
            CHECK_HANDLE_RETURN(TdxHq_Connect, "GetProcAddress:TdxHq_Connect");
            TdxHq_Disconnect = (TdxHq_DisconnectDelegate)GetProcAddress(hModule, "TdxHq_Disconnect");
            TdxHq_GetSecurityBars = (TdxHq_GetSecurityBarsDelegate)GetProcAddress(hModule, "TdxHq_GetSecurityBars");
            TdxHq_GetIndexBars = (TdxHq_GetIndexBarsDelegate)GetProcAddress(hModule, "TdxHq_GetIndexBars");
            TdxHq_GetMinuteTimeData = (TdxHq_GetMinuteTimeDataDelegate)GetProcAddress(hModule, "TdxHq_GetMinuteTimeData");
            TdxHq_GetHistoryMinuteTimeData = (TdxHq_GetHistoryMinuteTimeDataDelegate)GetProcAddress(hModule, "TdxHq_GetHistoryMinuteTimeData");
            TdxHq_GetTransactionData = (TdxHq_GetTransactionDataDelegate)GetProcAddress(hModule, "TdxHq_GetTransactionData");
            TdxHq_GetHistoryTransactionData = (TdxHq_GetHistoryTransactionDataDelegate)GetProcAddress(hModule, "TdxHq_GetHistoryTransactionData");
            TdxHq_GetSecurityQuotes = (TdxHq_GetSecurityQuotesDelegate)GetProcAddress(hModule, "TdxHq_GetSecurityQuotes");
            TdxHq_GetCompanyInfoCategory = (TdxHq_GetCompanyInfoCategoryDelegate)GetProcAddress(hModule, "TdxHq_GetCompanyInfoCategory");
            TdxHq_GetCompanyInfoContent = (TdxHq_GetCompanyInfoContentDelegate)GetProcAddress(hModule, "TdxHq_GetCompanyInfoContent");
            TdxHq_GetXDXRInfo = (TdxHq_GetXDXRInfoDelegate)GetProcAddress(hModule, "TdxHq_GetXDXRInfo");
            TdxHq_GetFinanceInfo = (TdxHq_GetFinanceInfoDelegate)GetProcAddress(hModule, "TdxHq_GetFinanceInfo");

			bInit = TRUE;
            return RET_SUCCESS;
        }

        int connect(char* ip, int port) { 
			
			strncpy(server_, ip, sizeof(server_));
			port_ = port;

			return 	reconnect(20);
           
        }

		int reconnect(int maxretry) {
			while (maxretry-- > 0) {
				bRet = TdxHq_Connect(server_, port_, Result, ErrInfo_);
				if (bRet) {
					p("Result:%s\n", Result);
					return RET_SUCCESS;
				}
				Sleep(1000);
			
			}

			return RET_FAILED;


		}

        //��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��  8->1����K��  9->��K��  10->��K��  11->��K��
        int get_k_datas(byte Category, char* Zqdm, short Start, short& Count, char* Result){
            byte market=0;
            if(*Zqdm=='6') market=1; 
            bRet=TdxHq_GetSecurityBars(Category,market,Zqdm,Start,Count,Result,ErrInfo_);
            CHECK_BOOL_RETURN(bRet, ErrInfo_);
            p("%s\n",Result);

            return RET_SUCCESS;
        }
/// <summary>
/// ������ȡ���֤ȯ���嵵��������
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�, ��i��Ԫ�ر�ʾ��i��֤ȯ���г�����</param>
/// <param name="Zqdm">֤ȯ����, Count��֤ȯ������ɵ�����</param>
/// <param name="Count">APIִ��ǰ,��ʾ�û�Ҫ�����֤ȯ��Ŀ,���290, APIִ�к�,������ʵ�ʷ��ص���Ŀ</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
#define MAX_SHARE_COUNT_ONCE 81
        int get_quotes(byte marketList[],char* Zqdm[], short& Count, char* Result){
			int realcount=0;
			char* tmpResult = Result;
			short once_count;

			do {
				if ((Count - realcount) < MAX_SHARE_COUNT_ONCE) {
					once_count = Count - realcount;
				}
				else {
					once_count = MAX_SHARE_COUNT_ONCE;
				}

 				bRet = TdxHq_GetSecurityQuotes(marketList, Zqdm, once_count, tmpResult, ErrInfo_);
				if (!bRet) {
					p("reconect \n");
					reconnect(100);
					bRet = TdxHq_GetSecurityQuotes(marketList, Zqdm, once_count, tmpResult, ErrInfo_);

					//getchar();

				}
				CHECK_BOOL_RETURN(bRet, ErrInfo_);
				int len = strlen(tmpResult);
				//p(tmpResult);
				tmpResult += len;
				marketList += once_count;
				Zqdm += once_count;
				realcount += once_count;
			} while (realcount < Count);
			//int len = strlen(Result);
            //p("%s\n", Result);
			Count = realcount;
            return RET_SUCCESS;
        }
		
		//ʱ��	�۸� 	���� 	����('B'/'S'/' ') 	����
		//09:30	2.590000	14923	 	0
		//09:32	2.620000	1980	B	0
		//09:32	2.620000	23	S	0
		int get_hist_tick_data(char* Zqdm, short Start, short& Count, int Date, char* Result) {
			byte market = 0;
			if (*Zqdm == '6') market = 1;
			bRet = TdxHq_GetHistoryTransactionData(market, Zqdm, Start, Count, Date, Result, ErrInfo_);
			CHECK_BOOL_RETURN(bRet, ErrInfo_);
			p("%s\n", Result);

			return RET_SUCCESS;
		}

		int get_tick_data(char* Zqdm, short Start, short& Count, char* Result) {
			byte market = 0;
			if (*Zqdm == '6') market = 1;
			bRet = TdxHq_GetTransactionData(market, Zqdm, Start, Count, Result, ErrInfo_);
			CHECK_BOOL_RETURN(bRet, ErrInfo_);
			p("%s\n", Result);

			return RET_SUCCESS;
		}






};

