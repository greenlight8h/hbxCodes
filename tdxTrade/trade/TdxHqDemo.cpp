// TdxHqDemoCpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winbase.h>
#include <iostream>

using namespace std;


//开发文档
//

//1.行情API均是TdxHqApi.dll文件的导出函数，包括以下函数：
//bool  TdxHq_Connect(char* IP, int Port, char* Result, char* ErrInfo);
//void  TdxHq_Disconnect();
//bool  TdxHq_GetSecurityBars(byte Category, byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);
//bool  TdxHq_GetIndexBars(byte Category, byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);
//bool  TdxHq_GetMinuteTimeData(byte Market, char* Zqdm, char* Result, char* ErrInfo);
//bool  TdxHq_GetHistoryMinuteTimeData(byte Market, char* Zqdm, int date, char* Result, char* ErrInfo);
//bool  TdxHq_GetTransactionData(byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);
//bool  TdxHq_GetHistoryTransactionData(byte Market, char* Zqdm, short Start, short& Count, int date, char* Result, char* ErrInfo);
//bool  TdxHq_GetSecurityQuotes(byte Market[], char* Zqdm[], short& Count, char* Result, char* ErrInfo);
//bool  TdxHq_GetCompanyInfoCategory(byte Market, char* Zqdm, char* Result, char* ErrInfo);
//bool  TdxHq_GetCompanyInfoContent(byte Market, char* Zqdm, char* FileName, int Start, int Length, char* Result, char* ErrInfo);
//bool  TdxHq_GetXDXRInfo(byte Market, char* Zqdm, char* Result, char* ErrInfo);
//bool  TdxHq_GetFinanceInfo(byte Market, char* Zqdm, char* Result, char* ErrInfo);

//2.API使用流程为: 应用程序先调用TdxHq_Connect连接通达信行情服务器,然后才可以调用其他接口获取行情数据,应用程序应自行处理网络断线问题, 接口是线程安全的

//3.各个函数功能说明
/// <summary>
///  连接通达信行情服务器,服务器地址可在券商软件登录界面中的通讯设置中查得
/// </summary>
/// <param name="IP">服务器IP</param>
/// <param name="Port">服务器端口</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall*  TdxHq_ConnectDelegate)(char* IP, int Port, char* Result, char* ErrInfo);


/// <summary>
/// 断开同服务器的连接
/// </summary>
typedef void(__stdcall* TdxHq_DisconnectDelegate)();



/// <summary>
/// 获取证券的K线数据
/// </summary>
/// <param name="Category">K线种类, 0->5分钟K线    1->15分钟K线    2->30分钟K线  3->1小时K线    4->日K线  5->周K线  6->月K线  7->1分钟  8->1分钟K线  9->日K线  10->季K线  11->年K线< / param>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Start">K线开始位置,最后一条K线位置是0, 前一条是1, 依此类推</param>
/// <param name="Count">API执行前,表示用户要请求的K线数目, API执行后,保存了实际返回的K线数目, 最大值800</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetSecurityBarsDelegate)(byte Category, byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);


/// <summary>
/// 获取指数的K线数据
/// </summary>
/// <param name="Category">K线种类, 0->5分钟K线    1->15分钟K线    2->30分钟K线  3->1小时K线    4->日K线  5->周K线  6->月K线  7->1分钟  8->1分钟K线  9->日K线  10->季K线  11->年K线< / param>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Start">K线开始位置,最后一条K线位置是0, 前一条是1, 依此类推</param>
/// <param name="Count">API执行前,表示用户要请求的K线数目, API执行后,保存了实际返回的K线数目,最大值800</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetIndexBarsDelegate)(byte Category, byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);



/// <summary>
/// 获取分时数据
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetMinuteTimeDataDelegate)(byte Market, char* Zqdm, char* Result, char* ErrInfo);


/// <summary>
/// 获取历史分时数据
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Date">日期, 比如2014年1月1日为整数20140101</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetHistoryMinuteTimeDataDelegate)(byte Market, char* Zqdm, int Date, char* Result, char* ErrInfo);


/// <summary>
/// 获取分时成交数据
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Start">K线开始位置,最后一条K线位置是0, 前一条是1, 依此类推</param>
/// <param name="Count">API执行前,表示用户要请求的K线数目, API执行后,保存了实际返回的K线数目</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetTransactionDataDelegate) (byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);


/// <summary>
/// 获取历史分时成交数据
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Start">K线开始位置,最后一条K线位置是0, 前一条是1, 依此类推</param>
/// <param name="Count">API执行前,表示用户要请求的K线数目, API执行后,保存了实际返回的K线数目</param>
/// <param name="Date">日期, 比如2014年1月1日为整数20140101</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetHistoryTransactionDataDelegate) (byte Market, char* Zqdm, short Start, short& Count, int Date, char* Result, char* ErrInfo);

/// <summary>
/// 批量获取多个证券的五档报价数据
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海, 第i个元素表示第i个证券的市场代码</param>
/// <param name="Zqdm">证券代码, Count个证券代码组成的数组</param>
/// <param name="Count">API执行前,表示用户要请求的证券数目,最大290, API执行后,保存了实际返回的数目</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetSecurityQuotesDelegate) (byte Market[], char* Zqdm[], short& Count, char* Result, char* ErrInfo);


/// <summary>
/// 获取F10资料的分类
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据, 形式为表格数据，行数据之间通过\n字符分割，列数据之间通过\t分隔。一般要分配1024*1024字节的空间。出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetCompanyInfoCategoryDelegate) (byte Market, char* Zqdm, char* Result, char* ErrInfo);




/// <summary>
/// 获取F10资料的某一分类的内容
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="FileName">类目的文件名, 由TdxHq_GetCompanyInfoCategory返回信息中获取</param>
/// <param name="Start">类目的开始位置, 由TdxHq_GetCompanyInfoCategory返回信息中获取</param>
/// <param name="Length">类目的长度, 由TdxHq_GetCompanyInfoCategory返回信息中获取</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据,出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetCompanyInfoContentDelegate) (byte Market, char* Zqdm, char* FileName, int Start, int Length, char* Result, char* ErrInfo);




/// <summary>
/// 获取除权除息信息
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据,出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetXDXRInfoDelegate) (byte Market, char* Zqdm, char* Result, char* ErrInfo);



/// <summary>
/// 获取财务信息
/// </summary>
/// <param name="Market">市场代码,   0->深圳     1->上海</param>
/// <param name="Zqdm">证券代码</param>
/// <param name="Result">此API执行返回后，Result内保存了返回的查询数据,出错时为空字符串。</param>
/// <param name="ErrInfo">此API执行返回后，如果出错，保存了错误信息说明。一般要分配256字节的空间。没出错时为空字符串。</param>
/// <returns>成功返货true, 失败返回false</returns>
typedef bool(__stdcall* TdxHq_GetFinanceInfoDelegate) (byte Market, char* Zqdm, char* Result, char* ErrInfo);




int _tmain(int argc, _TCHAR* argv[])
{
	//载入dll, dll要复制到debug目录下,或者release目录下,采用多字节字符集编程设置
	HMODULE TdxApiHMODULE = LoadLibrary(L"TdxHqApi.dll");

	//获取api函数
	TdxHq_ConnectDelegate TdxHq_Connect = (TdxHq_ConnectDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_Connect");
	TdxHq_DisconnectDelegate TdxHq_Disconnect = (TdxHq_DisconnectDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_Disconnect");
	TdxHq_GetSecurityBarsDelegate TdxHq_GetSecurityBars = (TdxHq_GetSecurityBarsDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetSecurityBars");
	TdxHq_GetIndexBarsDelegate TdxHq_GetIndexBars = (TdxHq_GetIndexBarsDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetIndexBars");
	TdxHq_GetMinuteTimeDataDelegate TdxHq_GetMinuteTimeData = (TdxHq_GetMinuteTimeDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetMinuteTimeData");
	TdxHq_GetHistoryMinuteTimeDataDelegate TdxHq_GetHistoryMinuteTimeData = (TdxHq_GetHistoryMinuteTimeDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetHistoryMinuteTimeData");
	TdxHq_GetTransactionDataDelegate TdxHq_GetTransactionData = (TdxHq_GetTransactionDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetTransactionData");
	TdxHq_GetHistoryTransactionDataDelegate TdxHq_GetHistoryTransactionData = (TdxHq_GetHistoryTransactionDataDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetHistoryTransactionData");
	TdxHq_GetSecurityQuotesDelegate TdxHq_GetSecurityQuotes = (TdxHq_GetSecurityQuotesDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetSecurityQuotes");
	TdxHq_GetCompanyInfoCategoryDelegate TdxHq_GetCompanyInfoCategory = (TdxHq_GetCompanyInfoCategoryDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetCompanyInfoCategory");
	TdxHq_GetCompanyInfoContentDelegate TdxHq_GetCompanyInfoContent = (TdxHq_GetCompanyInfoContentDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetCompanyInfoContent");
	TdxHq_GetXDXRInfoDelegate TdxHq_GetXDXRInfo = (TdxHq_GetXDXRInfoDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetXDXRInfo");
	TdxHq_GetFinanceInfoDelegate TdxHq_GetFinanceInfo = (TdxHq_GetFinanceInfoDelegate)GetProcAddress(TdxApiHMODULE, "TdxHq_GetFinanceInfo");



	//开始获取行情数据
	char* Result = new char[1024 * 1024];
	char* ErrInfo = new char[256];
	short Count = 10;

	//连接服务器
	bool bool1 = TdxHq_Connect("218.18.103.38", 7709, Result, ErrInfo);
	if (!bool1)
	{
		cout << ErrInfo << endl;//连接失败
		return 0;
	}
	cout << Result << endl;



	//获取股票K线数据
	bool1 = TdxHq_GetSecurityBars(0, 0, "000001", 0, Count, Result, ErrInfo);//数据种类, 0->5分钟K线    1->15分钟K线    2->30分钟K线  3->1小时K线    4->日K线  5->周K线  6->月K线  7->1分钟K线  8->1分钟K线  9->日K线  10->季K线  11->年K线
	if (!bool1)
	{
		cout << ErrInfo << endl;
		return 0;
	}
	cout << Result << endl;



	//获取指数K线数据
	bool1 = TdxHq_GetIndexBars(4, 1, "000001", 0, Count, Result, ErrInfo);//数据种类, 0->5分钟K线    1->15分钟K线    2->30分钟K线  3->1小时K线    4->日K线  5->周K线  6->月K线  7->1分钟K线     8->1分钟K线    9->日K线  10->季K线  11->年K线
	if (!bool1)
	{
		cout << ErrInfo << endl;
		return 0;
	}
	cout << Result << endl;





	//获取分时图数据
	bool1 = TdxHq_GetMinuteTimeData(0, "000001",  Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;


	//获取历史分时图数据
	bool1 = TdxHq_GetHistoryMinuteTimeData(0, "000001", 20140904, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;


	//获取分笔图数据
	bool1 = TdxHq_GetTransactionData(0, "000001", 0, Count, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;



	//获取历史分笔图数据
	bool1 = TdxHq_GetHistoryTransactionData(0, "000001", 0, Count, 20140904,  Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;




	//获取五档报价数据
	byte Market[] = {0,1};
	char* Zqdm[] = {"000001","600030"};
	short ZqdmCount = 2;
	bool1 = TdxHq_GetSecurityQuotes(Market, Zqdm, ZqdmCount, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl; 



	//获取F10数据的类别
	bool1 = TdxHq_GetCompanyInfoCategory(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;



	//获取F10数据的某类别的内容
	bool1 = TdxHq_GetCompanyInfoContent(1, "600030", "600030.txt", 0, 16824, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;


	//获取除权除息信息
	bool1 = TdxHq_GetXDXRInfo(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;





	//获取财务信息
	bool1 = TdxHq_GetFinanceInfo(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;






	TdxHq_Disconnect();	

	cout << "已经断开服务器" << endl;


	FreeLibrary(TdxApiHMODULE);

	int a;
	cin >> a;

	return 0;
}
