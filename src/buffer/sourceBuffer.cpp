/*!  Source Buffer 
 *  \file sourceBuffer.cpp
 *  \class sourceBuffer
 *  \brief Class for the sourceBuffer
 *  \author CMT, DRJ & BFB
 */
#include <sourceBuffer.h>
#include <NvPcomp_logger.h>

using namespace std;

sourceBuffer::sourceBuffer() {
	_curLine = 0;
	_curLineBuffer = " ";	
	_fileName.clear();
}

sourceBuffer::~sourceBuffer() {}

bool sourceBuffer::good() {
	return in.good();
}

bool sourceBuffer::openFile(const char *fileName) {
	
	if(in.is_open()) {
		LOG(DEBUGLog, logLEVEL4) << BUFFERLOG_START << "File is already open, closing file";
		in.close();
	}
	
	_fileName = fileName;
	LOG(DEBUGLog, logLEVEL4) << BUFFERLOG_START << "Opening file: " << fileName;
	in.open(_fileName.c_str(), ifstream::in);
	
	return in.good();
}

bool sourceBuffer::closeFile() {
	LOG(DEBUGLog, logLEVEL4) << BUFFERLOG_START << "Closing file: " << _fileName;
	in.close();
}

string sourceBuffer::bufferGetLine(long lineNumStart, long lineNumFinish) {
	
	string strTemp;
	int i;
	
	// Clear the string
	_curLineBuffer.clear();
	
	// Check if the input stream is good.
	if(in.good()) {
				
		// Are we currently past the requested line?	
		if(lineNumStart <= _curLine) {
			resetBuffer();
		}
		
		// Loop through the file discarding unwanted lines.
		if(_curLine < lineNumStart - 1) {
			skipLine(lineNumStart - 1 - _curLine);
		}
		
		for(i = 0; i <= (lineNumFinish - lineNumStart); i++) {
			getline(in, strTemp);
			LOG(DEBUGLog, logLEVEL5) << BUFFERLOG_START << "getLine: " << strTemp;
			_curLineBuffer += strTemp + '\n';
			_curLine++;
		}
	}
		
	return _curLineBuffer;
	
}

// For working with NvPcomp_logger Cleanly.
string sourceBuffer::bufferGetLineNoCR(long lineNumStart, long lineNumFinish) {
	
	string strTemp;
	int i;
	
	// Clear the string
	_curLineBuffer.clear();
	
	// Check if the input stream is good.
	if(in.good()) {
				
		// Are we currently past the requested line?	
		if(lineNumStart <= _curLine) {
			resetBuffer();
		}
		
		// Loop through the file discarding unwanted lines.
		if(_curLine < lineNumStart - 1) {
			skipLine(lineNumStart - 1 - _curLine);
		}
		
		for(i = 0; i <= (lineNumFinish - lineNumStart); i++) {
			getline(in, strTemp);
			LOG(DEBUGLog, logLEVEL5) << BUFFERLOG_START << "getLine: " << strTemp;
			if(i != (lineNumFinish - lineNumStart)) {
				_curLineBuffer += strTemp + '\n';
			} else {
				_curLineBuffer += strTemp;
			}
			_curLine++;
		}
	}
		
	return _curLineBuffer;
	
}

string sourceBuffer::bufferGetLineCommented(long lineNumStart, long lineNumFinish, string commentChar) {
	
	string strTemp;
	int i;
	
	// Clear the string
	_curLineBuffer.clear();
	
	// Check if the input stream is good.
	if(in.good()) {
				
		// Are we currently past the requested line?	
		if(lineNumStart <= _curLine) {
			resetBuffer();
		}
		
		// Loop through the file discarding unwanted lines.
		if(_curLine < lineNumStart - 1) {
			skipLine(lineNumStart - 1 - _curLine);
		}
		
		for(i = 0; i <= (lineNumFinish - lineNumStart); i++) {
			getline(in, strTemp);
			LOG(DEBUGLog, logLEVEL5) << BUFFERLOG_START << "getLine: " << strTemp;
			_curLineBuffer += commentChar + strTemp + '\n';
			_curLine++;
		}
	}
		
	return _curLineBuffer;
	
}

bool sourceBuffer::skipLine(long numLines) {
	bool retVal = true;
	int i;
	LOG(DEBUGLog, logLEVEL4) << BUFFERLOG_START << "skipping " << numLines << " lines";
	for(i = 0;i < numLines;i++) {
		while(in.get() != '\n') {}
	}
	_curLine += numLines;	
	return retVal;
}

bool sourceBuffer::resetBuffer() {
	bool retVal = true;
	
	if(in.good()) {
		in.close();
	}
	
	in.open(_fileName.c_str(), ifstream::in);
	
	if(!in.good()) {
		retVal = false;
	} else {
		_curLine = 0;
		_curLineBuffer = " ";
	}	
}





