#include "TradeLib.h"
#include "TradeLogger.h"
#include "ShareQuotation.h"
#include <queue>
#pragma once
#define MAX_ROW_NUM 100
#define MAX_COL_NUM 50
#define MAX_DATA_SIZE 1024*100
struct ShareQuoteInfo {
	int curPrice;
	int high;
	int low;
	int yesterdayPrice;
};

struct QuoteThreadPara {
	int count;
	HANDLE hParaEvent;
	char **codeList;
	byte *marketList;
	ShareQuoteInfo *quoteNow;
	queue<ShareQuoteInfo> *quoteQueue;
};




class ShareList
{
    private:
        const static int max_count=3300;
        FILE *hFile;
		char codeListBuf[max_count][7];

		ShareQuotation *pShareQuotation;
	public:

		char *codeList[max_count];
		byte marketList[max_count];
		ShareQuoteInfo quoteNow[max_count];//最新行情
		queue<ShareQuoteInfo> quoteQueue[max_count];//旧行情队列，用于计算涨速
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

class DataPaser
{
    private:
        int colNum;
        int rowNum;
        char dataBuf[MAX_DATA_SIZE];
        char* rows[MAX_ROW_NUM][MAX_COL_NUM];
        

    public:
		DataPaser() { };
		~DataPaser() {};

		DataPaser(char* queryData) {
			paserData(queryData);
		} 
		
		int paserData(char* queryData) {
            char *pData = queryData;
            char *head = dataBuf;
            int i = 0;
            int colIndex = 0;
            int rowIndex = 0;
            colNum = 0;
            rowNum = 0;
            ASSERT(queryData);
            while (pData[i] != '\0') {
                if (pData[i] == '\t') {
                    //rowNum++;//最后一行无'\n'
                    rows[rowIndex][colIndex++] = head;
                    head = dataBuf + i + 1;

                    dataBuf[i] = '\0';
                }
                else if (pData[i] == '\n') {
                    rowNum++;
                    rows[rowIndex++][colIndex++] = head;
                    if (colNum == 0) {
                        colNum = colIndex;
                    }
                    else if (colNum != colIndex) {
                        p("wrong data\n");
                        return RET_FAILED;
                    }
                    colIndex = 0;
                    head = dataBuf + i + 1;
                    dataBuf[i] = '\0';
                }
                else {
                    dataBuf[i] = queryData[i];


                }
                i++;
                if (i >= MAX_DATA_SIZE) {
                    p("buff overflow\n");
					return RET_FAILED;

                }
            }
            dataBuf[i] = '\0';
            if (rowNum > 0) {//最后一行无'\n'
                rows[rowIndex][colIndex] = head;
                rowNum++;
            }
			return RET_SUCCESS;
        }

        void print() {
            p("======================================\n");
            int i = 0, j = 0;
            for (i = 0; i < rowNum; i++)
            {
                for (j = 0; j < colNum; j++)
                {
                    if (rows[i][j][0] == '\0') {
                        p("N/A\t");
                    }
                    else {
                        p("%s\t", rows[i][j]);
                    }


                }
                p("\n");

            }
            p("======================================\n");

        }
        char *getItem(char* title, int rowIndex) {
            //first ROW is titles;
            int i;
            if (rowIndex > rowNum - 1 || rowIndex < 1) return NULL;
            for (i = 0; i < colNum; i++)
            {

                if (strcmp(rows[0][i], title) == 0) {
                    return rows[rowIndex][i];

                }

            }
            return NULL;
        }
		int getRowNum() {
			return rowNum;
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
			threadPara[i].quoteNow = shareList.quoteNow;
			threadPara[i].quoteQueue = shareList.quoteQueue;
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
		char* result = new char[300 * threadPara->count];//one share need 300 for quotation
		DWORD dwRet = WaitForSingleObject(hParaEvent, INFINITE);
		ret = (*quotation).get_quotes(threadPara->marketList, threadPara->codeList, count, result);
		if (ret == RET_FAILED) {
			p("reconect \n");
			(*quotation).connect("218.75.75.20", 443);
			ret = (*quotation).get_quotes(threadPara->marketList, threadPara->codeList, count, result);

			//getchar();

		}
		if (count != threadPara->count) {
			printf("count != threadPara->count");
		}
		ShareQuoteInfo *quoteNow = threadPara->quoteNow;
		quotesData.paserData(result);
		//quotesData.print();
		//p("haha:%s\n", quotesData.getItem("买一价",1));
		for (int i = 1; i < count + 1; ++i)
		{
			//p("haha:%s\n", quotesData.getItem("卖一量", i));
			//p("haha:%s\n", quotesData.getItem("买一量", i));
			//p("haha:%s\n", quotesData.getItem("买一价", i));
			quoteNow[i - 1].curPrice = (int)(atof(quotesData.getItem("买一价", i)) * 100);
			//sellVol1 = atoi(quotesData.getItem("卖一量", i));
			//buyVol1 = atoi(quotesData.getItem("买一量", i));
			//buyPrice1 = (int)(atof(quotesData.getItem("买一价", i)) * 100);
			//buyAmount1 = (int64_t)buyPrice1 *buyVol1;
			//p("卖一量:%d   买一量：%d price:%d buyAmount1:%lldw\n", sellVol1, buyVol1, buyPrice1, buyAmount1/10000);


		}
		SetEvent(hParaEvent);
		delete[]result;
		return 0;
	}


};