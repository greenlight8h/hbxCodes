#ifndef _TDX_FUNCTYPE_
#define _TDX_FUNCTYPE_
//3. ������������˵��
#if 1
/// <summary>
/// ��ͨ����ʵ��
/// </summary>
///void   OpenTdx();
typedef void(__stdcall* OpenTdxDelegate)();


/// <summary>
/// �ر�ͨ����ʵ��
/// </summary>
///void   CloseTdx();
typedef void(__stdcall* CloseTdxDelegate)();


/// <summary>
/// �����˻���¼
/// </summary>
/// <param name="IP">ȯ�̽��׷�����IP</param>
/// <param name="Port">ȯ�̽��׷������˿�</param>
/// <param name="Version">����ͨ���ſͻ��˵İ汾��</param>
/// <param name="YybID">Ӫҵ�����룬�뵽��ַ http://www.chaoguwaigua.com/downloads/qszl.htm ��ѯ</param>
/// <param name="AccountNo">�����ĵ�¼�˺ţ�ȯ��һ��ʹ���ʽ��ʻ���ͻ���</param>
/// <param name="TradeAccount">�����˺ţ�һ�����¼�ʺ���ͬ. ���¼ȯ��ͨ�����������ѯ�ɶ��б��ɶ��б��ڵ��ʽ��ʺž��ǽ����ʺ�, �����ѯ���������վ���ȵ��ʴ���Ŀ</param>
/// <param name="JyPassword">��������</param>
/// <param name="TxPassword">ͨѶ����</param>
/// <param name="ErrInfo">��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����</param>
/// <returns>�ͻ���ID��ʧ��ʱ����-1</returns>
///  int  Logon(char* IP, short Port, char* Version,short YybID,  char* AccountNo,char* TradeAccount, char* JyPassword,   char* TxPassword, char* ErrInfo);
typedef int(__stdcall* LogonDelegate)(char* IP, short Port, char* Version, short YybID, char* AccountNo, char* TradeAccount, char* JyPassword, char* TxPassword, char* ErrInfo);

/// <summary>
/// �����˻�ע��
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// void  Logoff(int ClientID);
typedef void(__stdcall* LogoffDelegate)(int ClientID);

/// <summary>
/// ��ѯ���ֽ�������
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Category">��ʾ��ѯ��Ϣ�����࣬0�ʽ�  1�ɷ�   2����ί��  3���ճɽ�     4�ɳ���   5�ɶ�����  6�������   7��ȯ���  8����֤ȯ</param>
/// <param name="Result">��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����</param>
/// <param name="ErrInfo">ͬLogon������ErrInfo˵��</param>
/// void  QueryData(int ClientID, int Category, char* Result, char* ErrInfo);
typedef void(__stdcall* QueryDataDelegate)(int ClientID, int Category, char* Result, char* ErrInfo);




/// <summary>
/// ������ͨ�����湦��,��ѯ������ʷ����
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Category">��ʾ��ѯ��Ϣ�����࣬0��ʷί��  1��ʷ�ɽ�   2���</param>
/// <param name="StartDate">��ʾ��ʼ���ڣ���ʽΪyyyyMMdd,����2014��3��1��Ϊ  20140301
/// <param name="EndDate">��ʾ�������ڣ���ʽΪyyyyMMdd,����2014��3��1��Ϊ  20140301
/// <param name="Result">ͬ��</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  QueryHistoryData(int ClientID, int Category, char* StartDate, char* EndDate, char* Result, char* ErrInfo);
typedef void(__stdcall* QueryHistoryDataDelegate)(int ClientID, int Category, char* StartDate, char* EndDate, char* Result, char* ErrInfo);

/// <summary>
/// ������ͨ�����湦��,������ѯ���ֽ�������,�����鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i����ѯ����Ӧ����
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Category">��Ϣ�����������, ��i��Ԫ�ر�ʾ��i����ѯ����Ϣ���࣬0�ʽ�  1�ɷ�   2����ί��  3���ճɽ�     4�ɳ���   5�ɶ�����  6�������   7��ȯ���  8����֤ȯ</param>
/// <param name="Count">��ѯ�ĸ�����������ĳ���</param>
/// <param name="Result">�������ݵ�����, ��i��Ԫ�ر�ʾ��i��ί�еķ�����Ϣ. ��APIִ�з��غ�Result[i]����ͬ�ϡ�</param>
/// <param name="ErrInfo">������Ϣ�����飬��i��Ԫ�ر�ʾ��i��ί�еĴ�����Ϣ. ��APIִ�з��غ�ErrInfo[i]����ͬ�ϡ�</param>
/// void  QueryDatas(int ClientID, int Category[], int Count, char* Result[], char* ErrInfo[]);
typedef void(__stdcall* QueryDatasDelegate)(int ClientID, int Category[], int Count, char* Result[], char* ErrInfo[]);



/// <summary>
/// ��ί�н���֤ȯ
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Category">��ʾί�е����࣬0���� 1����  2��������  3��ȯ����   4��ȯ��ȯ   5��ȯ����  6��ȯ��ȯ</param>
/// <param name="PriceType">��ʾ���۷�ʽ 0�Ϻ��޼�ί�� �����޼�ί�� 1(�м�ί��)���ڶԷ����ż۸�  2(�м�ί��)���ڱ������ż۸�  3(�м�ί��)���ڼ�ʱ�ɽ�ʣ�೷��  4(�м�ί��)�Ϻ��嵵����ʣ�� �����嵵����ʣ�� 5(�м�ί��)����ȫ��ɽ����� 6(�м�ί��)�Ϻ��嵵����ת�޼�
/// <param name="Gddm">�ɶ�����, �����Ϻ���Ʊ���Ϻ��Ĺɶ����룻�������ڵĹ�Ʊ�������ڵĹɶ�����</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Price">ί�м۸�</param>
/// <param name="Quantity">ί������</param>
/// <param name="Result">ͬ��,���к���ί�б������</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  SendOrder(int ClientID, int Category ,int PriceType,  char* Gddm,  char* Zqdm , float Price, int Quantity,  char* Result, char* ErrInfo);
typedef void(__stdcall* SendOrderDelegate)(int ClientID, int Category, int PriceType, char* Gddm, char* Zqdm, float Price, int Quantity, char* Result, char* ErrInfo);



/// <summary>
/// ������ͨ�����湦��,������ί�н���֤ȯ�������鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i��ί�е���Ӧ����
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Category">ί����������飬��i��Ԫ�ر�ʾ��i��ί�е����࣬0���� 1����  2��������  3��ȯ����   4��ȯ��ȯ   5��ȯ����  6��ȯ��ȯ</param>
/// <param name="PriceType">��ʾ���۷�ʽ������,  ��i��Ԫ�ر�ʾ��i��ί�еı��۷�ʽ, 0�Ϻ��޼�ί�� �����޼�ί�� 1(�м�ί��)���ڶԷ����ż۸�  2(�м�ί��)���ڱ������ż۸�  3(�м�ί��)���ڼ�ʱ�ɽ�ʣ�೷��  4(�м�ί��)�Ϻ��嵵����ʣ�� �����嵵����ʣ�� 5(�м�ί��)����ȫ��ɽ����� 6(�м�ί��)�Ϻ��嵵����ת�޼�
/// <param name="Gddm">�ɶ��������飬��i��Ԫ�ر�ʾ��i��ί�еĹɶ����룬�����Ϻ���Ʊ���Ϻ��Ĺɶ����룻�������ڵĹ�Ʊ�������ڵĹɶ�����</param>
/// <param name="Zqdm">֤ȯ�������飬��i��Ԫ�ر�ʾ��i��ί�е�֤ȯ����</param>
/// <param name="Price">ί�м۸����飬��i��Ԫ�ر�ʾ��i��ί�е�ί�м۸�</param>
/// <param name="Quantity">ί���������飬��i��Ԫ�ر�ʾ��i��ί�е�ί������</param>
/// <param name="Count">ί�еĸ�����������ĳ���</param>
/// <param name="Result">ͬ��</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  SendOrders(int ClientID, int Category[] , int PriceType[], char* Gddm[],  char* Zqdm[] , float Price[], int Quantity[],  int Count, char* Result[], char* ErrInfo[]);
typedef void(__stdcall* SendOrdersDelegate)(int ClientID, int Category[], int PriceType[], char* Gddm[], char* Zqdm[], float Price[], int Quantity[], int Count, char* Result[], char* ErrInfo[]);



/// <summary>
/// ��ί��
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="ExchangeID">������ID�� �Ϻ�1������0(����֤ȯ��ͨ�˻�������2)</param>
/// <param name="hth">��ʾҪ����Ŀ��ί�еı��</param>
/// <param name="Result">ͬ��</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  CancelOrder(int ClientID, char* ExchangeID, char* hth, char* Result, char* ErrInfo);
typedef void(__stdcall* CancelOrderDelegate)(int ClientID, char* ExchangeID, char* hth, char* Result, char* ErrInfo);




/// <summary>
/// ������ͨ�����湦��,������ί��, �����鴫��ÿ��ί�еĲ����������i��Ԫ�ر�ʾ��i����ί�е���Ӧ����
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
// <param name="ExchangeID">������ID�� �Ϻ�1������0(����֤ȯ��ͨ�˻�������2)</param>
/// <param name="hth">��ʾҪ����Ŀ��ί�еı��</param>
/// <param name="Count">��ί�еĸ�����������ĳ���</param>
/// <param name="Result">ͬ��</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  CancelOrders(int ClientID, char* ExchangeID[], char* hth[], int Count, char* Result[], char* ErrInfo[]);
typedef void(__stdcall* CancelOrdersDelegate)(int ClientID, char* ExchangeID[], char* hth[], int Count, char* Result[], char* ErrInfo[]);




/// <summary>
/// ��ȡ֤ȯ��ʵʱ�嵵����
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Result">ͬ��</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  GetQuote(int ClientID, char* Zqdm, char* Result, char* ErrInfo);
typedef void(__stdcall* GetQuoteDelegate)(int ClientID, char* Zqdm, char* Result, char* ErrInfo);


/// <summary>
/// ������ͨ�����湦��,������ȡ֤ȯ��ʵʱ�嵵����
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Zqdm">֤ȯ����</param>
/// <param name="Result">ͬ��</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  GetQuotes(int ClientID, char* Zqdm[], int Count, char* Result[], char* ErrInfo[]);
typedef void(__stdcall* GetQuotesDelegate)(int ClientID, char* Zqdm[], int Count, char* Result[], char* ErrInfo[]);



/// <summary>
/// ������ȯֱ�ӻ���
/// </summary>
/// <param name="ClientID">�ͻ���ID</param>
/// <param name="Amount">������</param>
/// <param name="Result">ͬ��</param>
/// <param name="ErrInfo">ͬ��</param>
/// void  Repay(int ClientID, char* Amount, char* Result, char* ErrInfo);
typedef void(__stdcall* RepayDelegate)(int ClientID, char* Amount, char* Result, char* ErrInfo);
#endif

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
#endif
