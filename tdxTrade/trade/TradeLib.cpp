#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "tchar.h"
#include "TradeLib.h"
#include "tdxfuncType.h"
#include "DataPaser.h"
#include "ShareQuotation.h"

DataPaser tmpPaser;
ShareQuotation quotation;
TradeLib yhLib = TradeLib(5, "11100028250", "Wx801123", YHZQ_SH_PROFILE, YHZQ_SZ_PROFILE);
TradeLib gjLib = TradeLib(GJZQ_ID, "39958469", "880418", GJZQ_SH_PROFILE, GJZQ_SZ_PROFILE);
TradeLib gjRLib = TradeLib(GJZQ_R_ID, "139958469", "041888", GJZQ_R_SH_PROFILE, GJZQ_R_SZ_PROFILE);
TradeLib whLib = TradeLib(WHZQ_ID, "2200001507", "618518", WHZQ_SH_PROFILE, WHZQ_SZ_PROFILE);

TradeLib::TradeLib() {
	branchID_ = -1;
	strcpy_s(account_, "");
	strcpy_s(pass_, "");
	strcpy_s(shID_, "");
	strcpy_s(szID_, "");
}
TradeLib::TradeLib(short branchID, char* account, char *pass, char* shID, char* szID) {
	branchID_ = branchID;
	strcpy_s(account_, account);
	strcpy_s(pass_, pass);
	strcpy_s(shID_, shID);
	strcpy_s(szID_, szID);

}

int TradeLib::init(TCHAR* libname) {
	//载入dll, 所有4个dll都要复制到debug和release目录下,必须采用多字节字符集编程设置
	if (bInited_) {
		p("%ls reinited\n", libname);
		return RET_SUCCESS;
	}
	HMODULE hModule = LoadLibrary(libname);
	CHECK_HANDLE_RETURN(hModule, "GetProcAddress:CloseTdx");

	//获取api函数
	OpenTdx = (OpenTdxDelegate)GetProcAddress(hModule, "OpenTdx");
	CHECK_HANDLE_RETURN(OpenTdx, "GetProcAddress:OpenTdx");

	CloseTdx = (CloseTdxDelegate)GetProcAddress(hModule, "CloseTdx");
	CHECK_HANDLE_RETURN(CloseTdx, "GetProcAddress:CloseTdx");

	Logon = (LogonDelegate)GetProcAddress(hModule, "Logon");
	CHECK_HANDLE_RETURN(Logon, "GetProcAddress:Logon");

	Logoff = (LogoffDelegate)GetProcAddress(hModule, "Logoff");
	QueryData = (QueryDataDelegate)GetProcAddress(hModule, "QueryData");
	SendOrder = (SendOrderDelegate)GetProcAddress(hModule, "SendOrder");
	CancelOrder = (CancelOrderDelegate)GetProcAddress(hModule, "CancelOrder");
	GetQuote = (GetQuoteDelegate)GetProcAddress(hModule, "GetQuote");
	Repay = (RepayDelegate)GetProcAddress(hModule, "Repay");


	OpenTdx();

	bInited_ = TRUE;
	return RET_SUCCESS;

}

int TradeLib::login(char* ip, int port) {
	clientID_ = Logon(ip, port, "2.20", branchID_, account_, account_, pass_, "", ErrInfo_);
	CHECK_HANDLE_RETURN(clientID_, ErrInfo_);
	return RET_SUCCESS;
}

int TradeLib::queryData(int queryType, char* Result) {
	QueryData(clientID_, queryType, Result, ErrInfo_);
	if (strcmp(ErrInfo_, "") != 0) {
		p("==================================\n");
		p("queryData %d failed\n", queryType);
		p("==================================\n");
		p("%s\n", ErrInfo_);
		p("==================================\n");
		return RET_FAILED;
	}
	p("==================================\n");
	p("queryData %d\n", queryType);
	p("==================================\n");
	p("%s\n", Result);
	p("==================================\n\n");


	return RET_SUCCESS;

}
int TradeLib::sendOrder(int orderType, int priceType, char* shareCode, float price, int quantity, char* Result) {
	char* marketID;
	if (shareCode[0] == '6') {
		marketID = shID_;

	}
	else {
		marketID = szID_;
	}
	SendOrder(clientID_, orderType, priceType, marketID, shareCode, price, quantity, Result, ErrInfo_);
	p("Result:%s\n", Result);
	p("==================================\n");
	if (strcmp(ErrInfo_, "") != 0) {
		p("ErrInfo_:%s\n", ErrInfo_);
	}

	return RET_SUCCESS;
}
int TradeLib::sell( char* shareCode, float price, int quantity, int priceType) {
	int ret;
	ret = sendOrder(ORDER_SELL, priceType, (char*)shareCode, price, quantity, result);
	if (ret != RET_SUCCESS) {
		p("TradeLib::sell failed\n");
	}
	return RET_SUCCESS;
}

int TradeLib::buy(char* shareCode, float price, int quantity, int priceType) {
	int ret;
	ret = sendOrder(ORDER_BUY, priceType, (char*)shareCode, price, quantity, result);
	if (ret != RET_SUCCESS) {
		p("TradeLib::sell failed\n");
	}
	return RET_SUCCESS;
}

int TradeLib::fast_exchange(char* sellCode, char* buyCode, float buyPrice) {
	int ret1=RET_FAILED;
	int ret2 = RET_FAILED;
	int quantity;
	pShareInfo = freeShares[sellCode];
	if (pShareInfo != NULL && pShareInfo->freeNum>0) {
		ret1 = sell(sellCode, pShareInfo->low_limit, pShareInfo->freeNum);
		updateMoney();
	}
	quantity = (freeMoney / (int)(buyPrice * 100)) / 100;
	ret2=buy(buyCode, buyPrice, quantity);
	return ret2;

}


int TradeLib::cancelOrder(char* exchangeID, char* orderSn, char* Result) {
	CancelOrder(clientID_, exchangeID, orderSn, Result, ErrInfo_);
	p("Result:%s\n", Result);
	//Result:句柄     保留信息
	//18DF0E98        撤单申报成功
	p("==================================\n");
	if (strcmp(ErrInfo_, "") != 0) {
		p("cancelOrder failed==================\n");
		p("ErrInfo_:%s\n", ErrInfo_);
		return RET_FAILED;
	}
	if (strstr(Result, "撤单申报成功") == NULL) {
		p("cancelOrder failed==================\n ");
		return RET_FAILED;

	}

	return RET_SUCCESS;
}


int TradeLib::updateMoney() {
	//char result[512];
	int ret = queryData(QUERY_MONEY, result);
	if (ret == RET_SUCCESS) {
		tmpPaser.paserData(result);
		freeMoney = (int)atof(tmpPaser.getItem("可用资金", 1));
		if (freeMoney > 200) {
			freeMoney -= 200;
		}
	}
	else {
		p("updateMoney failed\n");
	}


	return ret;

}
int TradeLib::getMoney() {

	return freeMoney;

}

int TradeLib::updateShares() {
	for (it = freeShares.begin(); it != freeShares.end(); it++)
	{
		free(it->second);
	}
	freeShares.clear();

	int ret = queryData(QUERY_SHARES, result);
	if (ret == RET_SUCCESS) {
		tmpPaser.paserData(result);
		for (int i = 1; i < tmpPaser.getRowNum(); i++) {
			ShareInfo *pShareInfo = new ShareInfo;
			strncpy_s(pShareInfo->code, tmpPaser.getItem("证券代码", i), 6);
			strncpy_s(pShareInfo->name, tmpPaser.getItem("证券名称", i), 10);
			strncpy_s(pShareInfo->strFreeNum, tmpPaser.getItem("可用余额", i), sizeof(ShareInfo::strFreeNum)-1);

			pShareInfo->freeNum = atoi(pShareInfo->strFreeNum);
			freeShares.insert(map<string, ShareInfo*> ::value_type(pShareInfo->code, pShareInfo));
		}

	}
	else {
		p("updateMoney failed\n");
	}


	return ret;
}
#define PER_QUOTA_NUM 290
int TradeLib::updateQuotation() {

	short count = 0;
	byte market[PER_QUOTA_NUM];
	const char *code[PER_QUOTA_NUM];
	for (it = freeShares.begin(); it != freeShares.end(); it++, count++)
	{
		code[count] = it->first.c_str();
		if (code[count][0] == '6') {
			market[count] = 1;
		}
		else {
			market[count] = 0;
		}
	}
	int ret = quotation.get_quotes(market, (char**)code, count, result);
	if (ret == RET_SUCCESS) {
		tmpPaser.paserData(result);
		for (int i = 1; i < tmpPaser.getRowNum(); i++) {


			pShareInfo = freeShares[tmpPaser.getItem("代码", i)];
			strncpy_s(pShareInfo->strTime, tmpPaser.getItem("时间", i), 31);
			strncpy_s(pShareInfo->strClose, tmpPaser.getItem("现价", i), sizeof(ShareInfo::strClose) - 1);
			pShareInfo->close_last =(float)(atof(tmpPaser.getItem("昨收", i)) );
			pShareInfo->close = (float)(atof(pShareInfo->strClose) );
			pShareInfo->open = (float)(atof(tmpPaser.getItem("开盘", i)) );
			pShareInfo->high = (float)(atof(tmpPaser.getItem("最高", i)) );
			pShareInfo->low = (float)(atof(tmpPaser.getItem("最低", i)) );
			//14:59:69



			//time_t rawtime1;
			//time(&rawtime1);
			//timeinfo = localtime(&rawtime1);
			//printf("The current date/time is: %s", asctime(timeinfo));
			pShareInfo->high_limit = (pShareInfo->close_last*(float)1.1);
			pShareInfo->low_limit =  (pShareInfo->close_last*(float)0.9);

		}

	}
	else {
		p("TradeLib::updateQuotation() failed\n");
	}



	return ret;
}
int TradeLib::clearShare() {
	int ret = RET_FAILED;
	updateQuotation();
	for (it = freeShares.begin(); it != freeShares.end(); it++)
	{
		//p("%s %d\n", it->first.c_str(), it->second);
		pShareInfo = it->second;
		ret = sendOrder(ORDER_SELL, ORDER_LIMIT_PRICE, (char*)pShareInfo->code, \
			(float)pShareInfo->high_limit / 100, pShareInfo->freeNum, result);
		if (ret != RET_SUCCESS) {
			p("TradeLib::clearShare() failed\n");
			break;
		}


	}
	return ret;

}
int TradeLib::clearShare(vector<string>& exceptList) {
	int ret = RET_FAILED;


	for (it = freeShares.begin(); it != freeShares.end(); it++)
	{
		//p("%s %d\n", it->first.c_str(), it->second);
		//ret=sendOrder(ORDER_SELL, ORDER_LIMIT_PRICE, (char*)it->first.c_str(), 999.81f, it->second, result);

	}
	return ret;

}

void TradeLib::selfTest() {
	p("1.1\n");
	updateMoney();
	p("2\n");
	updateShares();
	p("free money:%d\n", getMoney());
	clearShare();
	for (it = freeShares.begin(); it != freeShares.end(); it++)
	{
		pShareInfo = it->second;
		p("time:%s  %s %s 股:%d 昨:%.2f 现:%.2f 开:%.2f 高:%.2f 低:%.2f 涨停:%.3f 跌停:%.3f\n", pShareInfo->strTime, pShareInfo->code, pShareInfo->name, pShareInfo->freeNum,
			pShareInfo->close_last, pShareInfo->close, pShareInfo->open,
			pShareInfo->high, pShareInfo->low, pShareInfo->high_limit,
			pShareInfo->low_limit);

		//cout << it->first << ":" << it->second << endl;
	}



}



