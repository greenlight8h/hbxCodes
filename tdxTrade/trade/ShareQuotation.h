
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
        //获取api函数
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



        //开始获取行情数据
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

            //获取api函数
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

        //数据种类, 0->5分钟K线    1->15分钟K线    2->30分钟K线  3->1小时K线    4->日K线  5->周K线  6->月K线  7->1分钟K线  8->1分钟K线  9->日K线  10->季K线  11->年K线
        int get_k_datas(byte Category, char* Zqdm, short Start, short& Count, char* Result){
            byte market=0;
            if(*Zqdm=='6') market=1; 
            bRet=TdxHq_GetSecurityBars(Category,market,Zqdm,Start,Count,Result,ErrInfo_);
            CHECK_BOOL_RETURN(bRet, ErrInfo_);
            p("%s\n",Result);

            return RET_SUCCESS;
        }
/// <summary>
/// 批量获取多个证券的五档报价数据
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海, 第i个元素表示第i个证券的市场代码</param>
/// <param name="Zqdm">证券代码, Count个证券代码组成的数组</param>
/// <param name="Count">API执行前,表示用户要请求的证券数目,最大290, API执行后,保存了实际返回的数目</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
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
		
		//时间	价格 	现量 	买卖('B'/'S'/' ') 	保留
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

