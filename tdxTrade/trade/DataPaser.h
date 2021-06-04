#include "hbx_helper.h"
#include "TradeLib.h"

#include "ShareQuotation.h"
#include "ShareData.h"
//#include <queue>
#pragma once




struct QuoteThreadPara {
	int count;
	HANDLE hParaEvent;
	char **codeList;
	byte *marketList;
	//ShareQuoteInfo *quoteNow;
	//queue<ShareQuoteInfo> *quoteQueue;
};




class ShareList
{
    private:
        //const static int MAX_SHARE_COUNT=3300;
        FILE *hFile;
		char codeListBuf[MAX_SHARE_COUNT][7];

		//ShareQuotation *pShareQuotation;
	public:

		char *codeList[MAX_SHARE_COUNT];
		byte marketList[MAX_SHARE_COUNT];
		//ShareQuoteInfo quoteNow[MAX_SHARE_COUNT];//最新行情
		//queue<ShareQuoteInfo> quoteQueue[MAX_SHARE_COUNT];//旧行情队列，用于计算涨速
		int count;


    public:
		ShareList() {
			count = 0;
			hFile = NULL;


		}
        ShareList(ShareQuotation *pShareQuotation){
            count=0;
            hFile = NULL;


        }
        ~ShareList(){}
        int initFromFile(char* filename){
            char tmpbuf[128];
            count=0;
            errno_t aaa=fopen_s(&hFile,filename, "r");
            if (hFile == NULL) {
                p("open file failed\n");
                return -1;

            }
            while(fgets(tmpbuf,sizeof(tmpbuf),hFile)!=NULL){
                //p("%s=======\n",tmpbuf);
				int tmplen = strlen(tmpbuf);
                if (tmplen != 8 && tmplen != 7) { //last line may be 7
                    continue;

                }
				marketList[count] = tmpbuf[0];
                strncpy_s(codeListBuf[count],tmpbuf+1,6);
				codeList[count] = codeListBuf[count];
                //p("%s#############\n", codeListBuf[count]);
                count++;
            }
			return RET_SUCCESS;
        }
		byte* getMarketList() {
			return marketList;	
		}
		char** getCodeList() {
			return (char**)codeList;
		}
		int getShareCount() {
			return count;
		}

		//para: countPerThread 每个进程负责获取多少只share quote
		int updateQuote(int countPerThread) {
		
		}


};


class QuoteThreadPool {
private:
	const static int MAX_THREAD_NUM = 20;
	HANDLE hThread[MAX_THREAD_NUM];
	HANDLE hEvent[MAX_THREAD_NUM];
	QuoteThreadPara threadPara[MAX_THREAD_NUM];
	int threadNum_;
public:
	QuoteThreadPool(ShareList &shareList, int threadNum) {
		threadNum_ = threadNum;
		int count = shareList.getShareCount();
		int perThreadCount = count / threadNum;
		int lastThreadCound = count - perThreadCount*(threadNum - 1);
		for (int i = 0; i < threadNum; i++) {
			threadPara[i].count = perThreadCount;
			threadPara[i].marketList = shareList.marketList;
			threadPara[i].codeList = shareList.codeList + i*perThreadCount;
			//threadPara[i].quoteNow = shareList.quoteNow;
			//threadPara[i].quoteQueue = shareList.quoteQueue;
			hEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
			hThread[i] = CreateThread(NULL, 0, QuoteThreadPool::ThreadFun, &threadPara[i], 0, NULL);
			//ThreadFun(&threadPara[i]);
		}
	}
	void waitEventAll() {
		DWORD dwRet;
		dwRet =WaitForMultipleObjects(threadNum_, hEvent, TRUE, INFINITE);

	}

	void SetEventAll() {
		for (int i = 0; i < threadNum_; i++) {
			SetEvent(hEvent[i]);
		}
	}
	static DWORD WINAPI ThreadFun(LPVOID pPara)
	{
		int ret;
		DataPaser quotesData;


		DWORD threadID = GetCurrentThreadId();
		QuoteThreadPara *threadPara = (QuoteThreadPara *)pPara;
		HANDLE hParaEvent = threadPara->hParaEvent;
		printf("子线程的线程ID号为：%d", threadID);
		ShareQuotation *quotation = new ShareQuotation;
		(*quotation).init(_T("TdxHqApi.dll"));
		//(*quotation).connect("218.75.75.20", 443);//银河证券杭州电信通用
		//(*quotation).connect("61.135.173.136", 443); //银河证券北京联通通用
		(*quotation).connect("203.212.5.66", 7709); //平安证券北京行情

		short count = threadPara->count;
		char lastResult[QUOTE_LINE_MAX_SIZE];
		char* result = new char[QUOTE_LINE_MAX_SIZE * threadPara->count+ QUOTE_HEADER_SIZE];
		vector<QuotoData*> *pQuoteVec;
		DWORD dwRet = WaitForSingleObject(hParaEvent, INFINITE);
		for (int j = 0; j < 100; ) {
			ret = (*quotation).get_quotes(threadPara->marketList, threadPara->codeList, count, result);
			
			if (j != 0) {
				if (strncmp(lastResult, &result[QUOTE_HEADER_SIZE], QUOTE_LINE_MAX_SIZE) == 0) {
					Sleep(100);
					//j--;
					continue;
				}
			}
			j++;
			strncpy(lastResult, &result[QUOTE_HEADER_SIZE], QUOTE_LINE_MAX_SIZE);
			if (count != threadPara->count) {
				printf("count != threadPara->count");
			}

			quotesData.paserData(result);
			//quotesData.print();

			for (int i = 1; i < count + 1; ++i)
			{
				//p("haha:%s\n", quotesData.getItem("代码", i));
				//p("haha:%s\n", quotesData.getItem("现价", i));
				//p("haha:%s\n", quotesData.getItem("时间", i));

				int code = atoi(quotesData.getItem("代码", i));
				int id = g_shareIdMap[code];
				u32 time= (u32)(atoi(quotesData.getItem("时间", i)));
				pQuoteVec = &g_shareDataAll[id].quotoDayVec[0]->quotoVec;
				if (pQuoteVec->size()>1 && time == pQuoteVec->back()->time) {
					break;
				}
				QuotoData *pQuotoInfo = new QuotoData;
				pQuotoInfo->set_data(&quotesData, i);

				g_shareDataAll[id].addQuotoData(pQuotoInfo);
			}
			Sleep(3000);
		}
		printf("over----------------------------\n");
		SetEvent(hParaEvent);
		delete[]result;
		return 0;
	}


};