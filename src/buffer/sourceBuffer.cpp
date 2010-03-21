/***********************************************************************
 *   symNode - Symbol Table Node.
 *   Copyright (C) 2010  CMT & DRJ
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 **********************************************************************/
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
	
	char *str[256];
	string strTemp;
	int i;
	
	// Clear the string
	_curLineBuffer.clear();
	
	// Check if the input stream is good.
	if(in.good()) {
				
		// Are we currently past the requested line?	
		if(lineNumStart < _curLine) {
			resetBuffer();
		}
		
		// Loop through the file discarding unwanted lines.
		if(_curLine < lineNumStart - 1) {
			cout << "curLine: "<< _curLine << " lineNumStart: " << lineNumStart << endl;
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

bool sourceBuffer::skipLine(long numLines) {
	bool retVal = true;
	int i;
	LOG(DEBUGLog, logLEVEL4) << BUFFERLOG_START << "skipping " << numLines << " lines";
	for(i = 0;i < numLines;i++) {
		while(in.get() != '\n') {}
		cout << "i: " << i << endl;
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





