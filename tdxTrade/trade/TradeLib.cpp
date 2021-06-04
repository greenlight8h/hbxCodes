#include "stdafx.h"
#include "hbx_helper.h"
#include "TradeLib.h"
#include "tdxfuncType.h"
#include "ShareData.h"
#include "DataPaser.h"


DataPaser tmpPaser;

//TradeLib yhLib = TradeLib(YHZQ_ID, YHZQ_ACCOUNT_ID, DEFAULT_PASS, YHZQ_SH_PROFILE, YHZQ_SZ_PROFILE,"2.20");
TradeLib gjLib = TradeLib(GJZQ_ID, GJZQ_ACCOUNT_ID, DEFAULT_PASS, GJZQ_SH_PROFILE, GJZQ_SZ_PROFILE, "2.21");
//TradeLib gjRLib = TradeLib(GJZQ_R_ID, GJZQ_ACCOUNT_ID, DEFAULT_PASS, GJZQ_R_SH_PROFILE, GJZQ_R_SZ_PROFILE,"2.20");
//TradeLib whLib = TradeLib(WHZQ_ID, "2200001507", DEFAULT_PASS, WHZQ_SH_PROFILE, WHZQ_SZ_PROFILE,"2.20");

TradeLib::TradeLib() {
	branchID_ = -1;
	strcpy_s(account_, "");
	strcpy_s(pass_, "");
	strcpy_s(shID_, "");
	strcpy_s(szID_, "");
}
TradeLib::TradeLib(short branchID, char* account, char *pass, char* shID, char* szID,char* clientVersion) {
	branchID_ = branchID;
	strcpy_s(account_, account);
	strcpy_s(pass_, pass);
	strcpy_s(shID_, shID);
	strcpy_s(szID_, szID);
	strcpy_s(clientVersion_, clientVersion);

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
	CHECK_HANDLE_RETURN(Logoff, "GetProcAddress:Logoff");

	QueryData = (QueryDataDelegate)GetProcAddress(hModule, "QueryData");
	CHECK_HANDLE_RETURN(QueryData, "GetProcAddress:QueryData");

	SendOrder = (SendOrderDelegate)GetProcAddress(hModule, "SendOrder");
	CHECK_HANDLE_RETURN(SendOrder, "GetProcAddress:SendOrder");

	CancelOrder = (CancelOrderDelegate)GetProcAddress(hModule, "CancelOrder");
	CHECK_HANDLE_RETURN(CancelOrder, "GetProcAddress:CancelOrder");

	GetQuote = (GetQuoteDelegate)GetProcAddress(hModule, "GetQuote");
	CHECK_HANDLE_RETURN(GetQuote, "GetProcAddress:GetQuote");

	Repay = (RepayDelegate)GetProcAddress(hModule, "Repay");
	CHECK_HANDLE_RETURN(Repay, "GetProcAddress:Repay");
	
	OpenTdx();

	bInited_ = TRUE;
	return RET_SUCCESS;

}

void TradeLib::add_server(char* ip, short port) {
	server_info* pServerInfo = new server_info;
	pServerInfo->ip = ip;
	pServerInfo->port = port;
	serverVec.push_back(pServerInfo);
}



int TradeLib::login() {
	char *ip = (char*)serverVec[0]->ip.c_str();
	short port = serverVec[0]->port;
	char strversion[8]="900.1";
	int version = 221;

RETRY:
#if 0
	itoa(version, strversion, 10);
	strversion[4] = '\0';
	strversion[3] = strversion[2];
	strversion[2] = strversion[1];
	strversion[1] = '.';
#endif

	//gj 2.20 ->9.99 failed
	clientID_ = Logon(ip, port, strversion, branchID_, account_, account_, pass_, "", ErrInfo_);
	if (clientID_ < 0) {
		p("trade login failed %s \n", ErrInfo_);
		Sleep(1000);
		version++;
		goto RETRY;
		return RET_FAILED;
	}
	
	return RET_SUCCESS;
}

int TradeLib::queryData(int queryType, char* Result) {
	if (clientID_ <0) {
		p("trade didn't login\n");
		return RET_FAILED;
	}

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
		strcpy(Result, ErrInfo_);
		p("ErrInfo_:%s\n", ErrInfo_);
		return RET_FAILED;
	}
	p("orderType %d,shareCode %s, price %f, quantity%d\n", orderType, shareCode, price, quantity);

	return RET_SUCCESS;
}
int TradeLib::sell( char* shareCode, float price, int quantity, int priceType) {
	int ret;
	ret = sendOrder(ORDER_SELL, priceType, (char*)shareCode, price, quantity, result);
	if (ret != RET_SUCCESS) {
		strcpy(result, ErrInfo_);
		p("TradeLib::sell failed\n");
	}
	return RET_SUCCESS;
}

int TradeLib::buy(char* shareCode, float price, int quantity, int priceType) {
	int ret;
	ret = sendOrder(ORDER_BUY, priceType, (char*)shareCode, price, quantity, result);
	if (ret != RET_SUCCESS) {
		strcpy(result, ErrInfo_);
		p("TradeLib::sell failed\n");
	}
	return RET_SUCCESS;
}

int TradeLib::fast_exchange(char* sellCode, char* buyCode, float buyPrice) {
	int ret1=RET_FAILED;
	int ret2 = RET_FAILED;
	int quantity;
#if 0
	pShareInfo = freeShares[sellCode];
	if (pShareInfo != NULL && pShareInfo->freeNum>0) {
		ret1 = sell(sellCode, pShareInfo->low_limit, pShareInfo->freeNum);
		updateMoney();
	}
	quantity = (freeMoney / (int)(buyPrice * 100)) / 100;
	ret2=buy(buyCode, buyPrice, quantity);
#endif
	return ret2;

}


int TradeLib::cancelOrder(char* exchangeID, char* orderSn, char* Result) {
	CancelOrder(clientID_, exchangeID, orderSn, Result, ErrInfo_);
	p("Result:%s\n", Result);
	//Result:句柄     保留信息
	//18DF0E98        撤单申报成功
	p("==================================\n");
	if (strcmp(ErrInfo_, "") != 0) {
		strcpy(Result, ErrInfo_);
		p("cancelOrder failed==================\n");
		p("ErrInfo_:%s\n", ErrInfo_);
		return RET_FAILED;
	}
	if (strstr(Result, "撤单申报成功") == NULL) {
		p("cancelOrder failed==================%s\n ",Result);
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
int TradeLib::getFreeMoney() {

	return freeMoney;

}

int TradeLib::getFreePosition(int code)
{
	for each (auto pInfo in positionVec)
	{
		if (pInfo->code == code) {
			return pInfo->freeNum;
		}
	}
	return 0;
}

int TradeLib::updatePositions() {
	int ret = RET_SUCCESS;

	ret = queryData(QUERY_SHARES, result);
	int oldNum = positionVec.size();
	if (ret == RET_SUCCESS) {
		tmpPaser.paserData(result);
		PositionInfo *pPositionInfo;
		int j=0;
		for (int i = 1,j=0; i < tmpPaser.getRowNum(); i++) {
			if (j<oldNum) {
				pPositionInfo = positionVec[j];
				j++;
			}
			else {
				pPositionInfo = new PositionInfo;
				positionVec.push_back(pPositionInfo);
			}
			pPositionInfo->code = atoi(tmpPaser.getItem("证券代码", i));
			pPositionInfo->freeNum= atoi(tmpPaser.getItem("可卖数量", i));
			pPositionInfo->firstCost = atof(tmpPaser.getItem("参考成本价", i)) * 100;
		}
		if (oldNum > tmpPaser.getRowNum() - 1) {
			//delete not exagsi
			for (int i = j; i < oldNum; i++) {
				delete(positionVec[i]);
			}
			positionVec.resize(j);
		}

	}
	else {
		p("updateMoney failed\n");
	}

	return ret;
}


#define PER_QUOTA_NUM 290
int TradeLib::updateQuotation() {
	int ret = RET_FAILED;




	return ret;
}
int TradeLib::clearShare() {
	int ret = RET_FAILED;
#if 0
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
#endif
	return ret;

}
int TradeLib::clearShare(vector<string>& exceptList) {
	int ret = RET_FAILED;
#if 0

	for (it = freeShares.begin(); it != freeShares.end(); it++)
	{
		//p("%s %d\n", it->first.c_str(), it->second);
		//ret=sendOrder(ORDER_SELL, ORDER_LIMIT_PRICE, (char*)it->first.c_str(), 999.81f, it->second, result);

	}
#endif
	return ret;

}

void TradeLib::selfTest() {
#if 0
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
#endif


}



