/**********************************************************************/
//! SourceBuffer
/*!
 * \class sourceBuffer
 *
 * Description: 
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef SOURCEBUFFER_H_
#define SOURCEBUFFER_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

#define BUFFERLOG_START	"sourceBuffer: "

class sourceBuffer {
public:
	sourceBuffer();
	~sourceBuffer();
	bool openFile(const char *fileName);
	bool closeFile();
	bool good();
	std::string bufferGetLine(long lineNumStart, long lineNumFinish);
	std::string bufferGetLineNoCR(long lineNumStart, long lineNumFinish);
private:
	bool skipLine(long numLines);
	bool resetBuffer();
private:	
	long _curLine;
	std::string _curLineBuffer;
	std::string _fileName;
	std::ifstream in;	

};

#endif /* SOURCEBUFFER_H_ */
