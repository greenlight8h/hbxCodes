#ifndef _TRADE_LIB_H_
#define _TRADE_LIB_H_

#include <map>
#include <vector>
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "tdxfuncType.h"
#define RET_SUCCESS 0
#define RET_FAILED  0x8000
using namespace std;
//extern DataPaser tmpPaser;
//extern ShareQuotation quotation;

//检查handle不正确，返回
#define CHECK_HANDLE_RETURN(handle,info)			\
    do{											\
        if(handle == NULL) {							\
			p("%s ERROR!",info);		\
            return RET_FAILED;					\
        }										\
    }while(0)   
//检查ret不正确，返回
#define CHECK_BOOL_RETURN(ret,info)         \
    do{                             \
        if(!ret) {    \
            printf("%s ERROR",info);\
            return RET_FAILED;                 \
        }                           \
    }while(0)   
#if 0
//检查ret不正确，返回
#define CHECK_RET_RETURN(ret，info)         \
    do{                             \
        if(ret != RET_SUCCESS) {    \
			printf("%s ERROR:%x",info,ret);\
            return ret;                 \
        }                           \
    }while(0)   


//检查ret不正确，挂起
#define CHECK_RET_HALT(ret)         \
    do{                             \
        if(ret != RET_SUCCESS) {    \
            halt();                 \
        }                           \
    }while(0)   


//检查ret不正确，软复位
#define CHECK_RET_RESET(ret)        \
    do{                             \
        if(ret != RET_SUCCESS) {    \
            soft_reset();           \
        }                           \
    }while(0)          

//检查ret不正确，跳转到ERROR处
#define CHECK_RET_GOTO_ERROR(ret)   \
    do{                             \
        if(ret != RET_SUCCESS) {    \
            goto ERROR;             \
        }                           \
    }while(0)   
#endif


#define ORDER_BUY  0
#define ORDER_SELL 1
#define ORDER_MARGIN_BUY  2
#define ORDER_MARGIN_SELL 3

#define ORDER_LIMIT_PRICE  0

#define YHZQ_SH_PROFILE ""
#define YHZQ_SZ_PROFILE ""
#define YHZQ_ID 5

#define WHZQ_SH_PROFILE ""
#define WHZQ_SZ_PROFILE ""
#define WHZQ_ID 0
#define WHZQ_IP  "210.21.212.198"
#define WHZQ_PORT 7708

#define GJZQ_SH_PROFILE ""
#define GJZQ_SZ_PROFILE ""
#define GJZQ_ID 1

#define GJZQ_R_SH_PROFILE ""
#define GJZQ_R_SZ_PROFILE ""
#define GJZQ_R_ID 2
//#define GJZQ_R_IP  "222.73.69.88"
//#define GJZQ_R_PORT 443
#define GJZQ_R_IP  "221.236.15.16"
#define GJZQ_R_PORT 7708
class ShareInfo {
public:
	int id;
	char code[8];
	char name[12];
	char strTime[32];
	char strFreeNum[32];
	char strClose[32];
	int freeNum;
	float close_last;
	float open;
	float close;
	float high;
	float low;
	float high_limit;
	float low_limit;

};

class TradeLib
{
private:
	char result[1024*5];
	int freeMoney=0;
	//vector<ShareInfo*> freeShares;
	ShareInfo *pShareInfo;

	//char libname_[32];
	//char libname_[32];
	BOOL bInited_=FALSE;
	int clientID_;
	char ErrInfo_[256];
	short branchID_;
	char shID_[32];
	char szID_[32];
	char account_[32];
	char pass_[32];

	OpenTdxDelegate OpenTdx;
	CloseTdxDelegate CloseTdx;
	LogonDelegate Logon;
	LogoffDelegate Logoff;
	QueryDataDelegate QueryData;
	SendOrderDelegate SendOrder;
	CancelOrderDelegate CancelOrder;
	GetQuoteDelegate GetQuote;
	RepayDelegate Repay;
public:
	map<string, ShareInfo*> freeShares;
	map<string, ShareInfo*>::iterator it;

	TradeLib();
	TradeLib(short branchID, char* account, char *pass, char* shID, char* szID);
	~TradeLib() {}
	int init(TCHAR* libname);

	int login(char* ip, int port);
	int sendOrder(int orderType, int priceType, char* shareCode, float price, int quantity, char* Result);
	int cancelOrder(char* exchangeID, char* orderSn, char* Result);
	int sell(char* shareCode, float price, int quantity, int priceType = ORDER_LIMIT_PRICE);
	int buy(char* shareCode, float price, int quantity, int priceType = ORDER_LIMIT_PRICE);
	int fast_exchange(char* sellCode, char* buyCode, float buyPrice);

#define QUERY_MONEY			0	//资金
#define QUERY_SHARES		1	//股份
#define QUERY_ALL_ORDERS	2	//当日委托
#define QUERY_DONE_ORDERS	3	//已成交
#define QUERY_UNDONE_ORDERS	4	//可撤销
#define QUERY_HOLDER_ID		5	//股东代码
	int queryData(int queryType, char* Result);

	int updateMoney();
	int updateShares();
	int updateQuotation();
	int getMoney();
	int clearShare();
	int clearShare(vector<string>& exceptList);
	void selfTest();


};


extern TradeLib yhLib;
extern TradeLib gjLib;
extern TradeLib gjRLib;
extern TradeLib whLib;

#endif //_TRADE_LIB_H_
