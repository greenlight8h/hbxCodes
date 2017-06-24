#pragma once
#include <vector>
#include <string>
using namespace std;


class TradeLogger
{	 
private:
	string logStr;
public:
	TradeLogger();
	~TradeLogger();
	void add(const char* str) {
		logStr += str;
		//string *pStr = new string(str);
		//logVec.push_back(pStr);
	}
	void addFmt(const char *fmt, ...) {
		char printf_buf[1024];
		va_list args;
		int printed;

		va_start(args, fmt);
		printed = vsprintf_s(printf_buf, fmt, args);
		va_end(args);

		//puts(printf_buf);

		logStr += printf_buf;

	}
	void print() {
		//vector<int>::iterator it;
		//for (it = v.begin(); it != v.end(); it++) {
		//	cout << *it << "\t";
		//}
		printf("%s", logStr.c_str());
	}

};

extern FILE *hFile;
extern TradeLogger logger;
extern FILE *hFile;
#define p printf
//#define p(...) printf(__VA_ARGS__);//fprintf(hFile, __VA_ARGS__);
//#define p(...) logger.addFmt(__VA_ARGS__);