#ifndef _TRADE_LIB_H_
#define _TRADE_LIB_H_

#ifdef TDX_TRADE_DLL
#include "hbx_helper.h"
#include "tdxfuncType.h"
#include "accountInfo.h"

struct server_info {
	string ip;
	short port;
};

#define ORDER_BUY  0
#define ORDER_SELL 1
#define ORDER_MARGIN_BUY  2
#define ORDER_MARGIN_SELL 3

#define ORDER_LIMIT_PRICE  0

#define WHZQ_IP  "210.21.212.198"
#define WHZQ_PORT 7708
//#define GJZQ_R_IP  "222.73.69.88"
//#define GJZQ_R_PORT 443
#define GJZQ_R_IP  "221.236.15.16"
#define GJZQ_R_PORT 7708
struct PositionInfo {
	int code;
	int freeNum;
	int firstCost;
};

struct OrderInfo {
	int code;
	int num;
	int price;
	int action; //buy or sell
	int bDone;
};


struct DealInfo {
	string time;
	string code;
	string name;
	string op;
	string price;
	string vol;
	string amount;
	string okNum;
	string onwayNum;
};


class TradeLib
{
public:
	vector<PositionInfo*> positionVec;
	vector<OrderInfo*> orderVec;
	vector<server_info*> serverVec; //fastest in first 
private:
	char result[1024*5];
	int freeMoney=0;


	BOOL bInited_=FALSE;
	int clientID_;
	char ErrInfo_[256];
	short branchID_;
	char shID_[32];
	char szID_[32];
	char account_[32];
	char pass_[32];
	char clientVersion_[8];

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

	TradeLib();
	TradeLib(short branchID, char* account, char *pass, char* shID, char* szID, char* clientVersion);
	~TradeLib() {}
	int init(TCHAR* libname);
	void add_server(char* ip, short port);
	server_info& getFastServer();

	int login();
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
	int updatePositions();
	int updateQuotation();
	int getFreeMoney();
	int getFreePosition(int code);
	int clearShare();
	int clearShare(vector<string>& exceptList);
	void selfTest();
};


extern TradeLib yhLib;
extern TradeLib gjLib;
extern TradeLib gjRLib;
extern TradeLib whLib;
#endif
#endif //_TRADE_LIB_H_
