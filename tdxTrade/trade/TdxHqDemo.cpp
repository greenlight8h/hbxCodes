// TdxHqDemoCpp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <winbase.h>
#include <iostream>

using namespace std;


//�����ĵ�
//

//1.����API����TdxHqApi.dll�ļ��ĵ����������������º�����
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

//2.APIʹ������Ϊ: Ӧ�ó����ȵ���TdxHq_Connect����ͨ�������������,Ȼ��ſ��Ե��������ӿڻ�ȡ��������,Ӧ�ó���Ӧ���д��������������, �ӿ����̰߳�ȫ��

//3.������������˵��
/// <summary>
///  ����ͨ�������������,��������ַ����ȯ�������¼�����е�ͨѶ�����в��
/// </summary>
/// <param name="IP">������IP</param>
/// <param name="Port">�������˿�</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall*  TdxHq_ConnectDelegate)(char* IP, int Port, char* Result, char* ErrInfo);


/// <summary>
/// �Ͽ�ͬ������������
/// </summary>
typedef void(__stdcall* TdxHq_DisconnectDelegate)();



/// <summary>
/// ��ȡ֤ȯ��K������
/// </summary>
/// <param name="Category">K������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����  8->1����K��  9->��K��  10->��K��  11->��K��< / param>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Start">K�߿�ʼλ��,���һ��K��λ����0, ǰһ����1, ��������</param>
/// <param name="Count">APIִ��ǰ,��ʾ�û�Ҫ�����K����Ŀ, APIִ�к�,������ʵ�ʷ��ص�K����Ŀ, ���ֵ800</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetSecurityBarsDelegate)(byte Category, byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);


/// <summary>
/// ��ȡָ����K������
/// </summary>
/// <param name="Category">K������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����  8->1����K��  9->��K��  10->��K��  11->��K��< / param>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Start">K�߿�ʼλ��,���һ��K��λ����0, ǰһ����1, ��������</param>
/// <param name="Count">APIִ��ǰ,��ʾ�û�Ҫ�����K����Ŀ, APIִ�к�,������ʵ�ʷ��ص�K����Ŀ,���ֵ800</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetIndexBarsDelegate)(byte Category, byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);



/// <summary>
/// ��ȡ��ʱ����
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetMinuteTimeDataDelegate)(byte Market, char* Zqdm, char* Result, char* ErrInfo);


/// <summary>
/// ��ȡ��ʷ��ʱ����
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Date">����, ����2014��1��1��Ϊ����20140101</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetHistoryMinuteTimeDataDelegate)(byte Market, char* Zqdm, int Date, char* Result, char* ErrInfo);


/// <summary>
/// ��ȡ��ʱ�ɽ�����
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Start">K�߿�ʼλ��,���һ��K��λ����0, ǰһ����1, ��������</param>
/// <param name="Count">APIִ��ǰ,��ʾ�û�Ҫ�����K����Ŀ, APIִ�к�,������ʵ�ʷ��ص�K����Ŀ</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetTransactionDataDelegate) (byte Market, char* Zqdm, short Start, short& Count, char* Result, char* ErrInfo);


/// <summary>
/// ��ȡ��ʷ��ʱ�ɽ�����
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Start">K�߿�ʼλ��,���һ��K��λ����0, ǰһ����1, ��������</param>
/// <param name="Count">APIִ��ǰ,��ʾ�û�Ҫ�����K����Ŀ, APIִ�к�,������ʵ�ʷ��ص�K����Ŀ</param>
/// <param name="Date">����, ����2014��1��1��Ϊ����20140101</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetHistoryTransactionDataDelegate) (byte Market, char* Zqdm, short Start, short& Count, int Date, char* Result, char* ErrInfo);

/// <summary>
/// ������ȡ���֤ȯ���嵵��������
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�, ��i��Ԫ�ر�ʾ��i��֤ȯ���г�����</param>
/// <param name="Zqdm">֤ȯ����, Count��֤ȯ������ɵ�����</param>
/// <param name="Count">APIִ��ǰ,��ʾ�û�Ҫ�����֤ȯ��Ŀ,���290, APIִ�к�,������ʵ�ʷ��ص���Ŀ</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetSecurityQuotesDelegate) (byte Market[], char* Zqdm[], short& Count, char* Result, char* ErrInfo);


/// <summary>
/// ��ȡF10���ϵķ���
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetCompanyInfoCategoryDelegate) (byte Market, char* Zqdm, char* Result, char* ErrInfo);




/// <summary>
/// ��ȡF10���ϵ�ĳһ���������
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="FileName">��Ŀ���ļ���, ��TdxHq_GetCompanyInfoCategory������Ϣ�л�ȡ</param>
/// <param name="Start">��Ŀ�Ŀ�ʼλ��, ��TdxHq_GetCompanyInfoCategory������Ϣ�л�ȡ</param>
/// <param name="Length">��Ŀ�ĳ���, ��TdxHq_GetCompanyInfoCategory������Ϣ�л�ȡ</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����,����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetCompanyInfoContentDelegate) (byte Market, char* Zqdm, char* FileName, int Start, int Length, char* Result, char* ErrInfo);




/// <summary>
/// ��ȡ��Ȩ��Ϣ��Ϣ
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����,����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetXDXRInfoDelegate) (byte Market, char* Zqdm, char* Result, char* ErrInfo);



/// <summary>
/// ��ȡ������Ϣ
/// </summary>
/// <param name="Market">�г�����,   0->����     1->�Ϻ�</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����,����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ɹ�����true, ʧ�ܷ���false</returns>
typedef bool(__stdcall* TdxHq_GetFinanceInfoDelegate) (byte Market, char* Zqdm, char* Result, char* ErrInfo);




int _tmain(int argc, _TCHAR* argv[])
{
	//����dll, dllҪ���Ƶ�debugĿ¼��,����releaseĿ¼��,���ö��ֽ��ַ����������
	HMODULE TdxApiHMODULE = LoadLibrary(L"TdxHqApi.dll");

	//��ȡapi����
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



	//��ʼ��ȡ��������
	char* Result = new char[1024 * 1024];
	char* ErrInfo = new char[256];
	short Count = 10;

	//���ӷ�����
	bool bool1 = TdxHq_Connect("218.18.103.38", 7709, Result, ErrInfo);
	if (!bool1)
	{
		cout << ErrInfo << endl;//����ʧ��
		return 0;
	}
	cout << Result << endl;



	//��ȡ��ƱK������
	bool1 = TdxHq_GetSecurityBars(0, 0, "000001", 0, Count, Result, ErrInfo);//��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��  8->1����K��  9->��K��  10->��K��  11->��K��
	if (!bool1)
	{
		cout << ErrInfo << endl;
		return 0;
	}
	cout << Result << endl;



	//��ȡָ��K������
	bool1 = TdxHq_GetIndexBars(4, 1, "000001", 0, Count, Result, ErrInfo);//��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��     8->1����K��    9->��K��  10->��K��  11->��K��
	if (!bool1)
	{
		cout << ErrInfo << endl;
		return 0;
	}
	cout << Result << endl;





	//��ȡ��ʱͼ����
	bool1 = TdxHq_GetMinuteTimeData(0, "000001",  Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;


	//��ȡ��ʷ��ʱͼ����
	bool1 = TdxHq_GetHistoryMinuteTimeData(0, "000001", 20140904, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;


	//��ȡ�ֱ�ͼ����
	bool1 = TdxHq_GetTransactionData(0, "000001", 0, Count, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;



	//��ȡ��ʷ�ֱ�ͼ����
	bool1 = TdxHq_GetHistoryTransactionData(0, "000001", 0, Count, 20140904,  Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;




	//��ȡ�嵵��������
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



	//��ȡF10���ݵ����
	bool1 = TdxHq_GetCompanyInfoCategory(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;



	//��ȡF10���ݵ�ĳ��������
	bool1 = TdxHq_GetCompanyInfoContent(1, "600030", "600030.txt", 0, 16824, Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;


	//��ȡ��Ȩ��Ϣ��Ϣ
	bool1 = TdxHq_GetXDXRInfo(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;





	//��ȡ������Ϣ
	bool1 = TdxHq_GetFinanceInfo(0, "000001", Result, ErrInfo);
	if (!bool1)
	{
	cout << ErrInfo << endl;
	return 0;
	}
	cout << Result << endl;






	TdxHq_Disconnect();	

	cout << "�Ѿ��Ͽ�������" << endl;


	FreeLibrary(TdxApiHMODULE);

	int a;
	cin >> a;

	return 0;
}
