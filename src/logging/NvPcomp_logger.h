/**********************************************************************/
//! NvPcomp Logging.
/*!
 * \class NvPcomp_logger
 *
 * Description: Based on the article:
 * 				"Logging In C++
 * 				A typesafe, threadsafe, portable logging mechanism"
 * 				by Petru Marginean, Dr. Dobb's Sept. 5, 2007.
 *
 * \author CMT & DRJ
 *
 */
/**********************************************************************/
#ifndef __NVPCOMP_LOGGER_H__
#define __NVPCOMP_LOGGER_H__

#include <sstream>
#include <string>
#include <stdio.h>

//! This is the Macro call that will output information if needed.
#define LOG(log_name, level) \
	if (level > FILELOG_MAX_LEVEL) ;\
    else if (level > log_name::ReportingLevel() || !log_name##_2File::Stream()) ; \
    else log_name().Get(level)

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logLEVEL8
#endif

//! enum of Log Level
/*! This holds information about the possible enum levels.*/
enum LogLevel {
	logLEVEL1,
	logLEVEL2,
	logLEVEL3,
	logLEVEL4,
	logLEVEL5,
	logLEVEL6,
	logLEVEL7,
	logLEVEL8
};

//! enum of Log Level
/*! This holds information about the different streams.*/
enum LogDestination {
	destERROR,
	destWARNING,
	destINFO,
	destDEBUG, 
	destPARSER 
};

template <typename T>
class NvPcomp_logger {
public:
	//! Constructor
    NvPcomp_logger();
	//! Virtual Desctructor
    virtual ~NvPcomp_logger();
	//! Get function to return the processing stream
	/*!
	 * \param level The log level of this statement
	 */ 
    std::ostringstream& Get(LogLevel level = logLEVEL3);
public:
    static LogLevel& ReportingLevel();
    static std::string ToString(LogLevel level);
    static LogLevel FromString(const std::string& level);
protected:
	//! The output string stream
    std::ostringstream os;
private:
    NvPcomp_logger(const NvPcomp_logger&);
    NvPcomp_logger& operator =(const NvPcomp_logger&);
};

// Public Constructor.
template <typename T>
NvPcomp_logger<T>::NvPcomp_logger()
{
}

// Get Function
template <typename T>
std::ostringstream& NvPcomp_logger<T>::Get(LogLevel level)
{
    os << " " << ToString(level) << ": ";
    os << std::string(level > logLEVEL1 ? level - logLEVEL1 : 0, '\t');
    return os;
}

// Destructor
template <typename T>
NvPcomp_logger<T>::~NvPcomp_logger()
{
    os << std::endl;
    T::Output(os.str());
}

// Reorting Level
template <typename T>
LogLevel& NvPcomp_logger<T>::ReportingLevel()
{
    static LogLevel reportingLevel = logLEVEL3;
    return reportingLevel;
}


template <typename T>
std::string NvPcomp_logger<T>::ToString(LogLevel level)
{
	static const char* const buffer[] = {"LEVEL1", "LEVEL2", "LEVEL3", "LEVEL4", "LEVEL5", "LEVEL6", "LEVEL7", "LEVEL8"};
    return buffer[level];
}


template <typename T>
LogLevel NvPcomp_logger<T>::FromString(const std::string& level)
{
    if (level == "LEVEL1")
        return logLEVEL1;
	if (level == "LEVEL2")
        return logLEVEL2;
	if (level == "LEVEL3")
        return logLEVEL3;		
	if (level == "LEVEL4")
        return logLEVEL4;
	if (level == "LEVEL5")
        return logLEVEL5;
	if (level == "LEVEL6")
        return logLEVEL6;
	if (level == "LEVEL7")
        return logLEVEL7;
	if (level == "LEVEL8")
        return logLEVEL8;
    NvPcomp_logger<T>().Get(logLEVEL3) << "Unknown logging level '" << level << "'. Using LEVEL4 as default.";
    return logLEVEL4;
}

/**********************************************************************/
//! Write log to Information File.
/*!
 * \class INFOLog_2File
 *
 * Description:
 *
 * \author CMT & DRJ
 *
 */
/**********************************************************************/
#define LOG2FILE(className) 									\
	class className 											\
	{ 															\
	public: 													\
		static FILE*& Stream(); 								\
		static void Output(const std::string& msg); 			\
	}; 															\
	inline FILE*& className::Stream() 							\
	{ 															\
		static FILE* pStream; 									\
		return pStream; 										\
	} 															\
	inline void className::Output(const std::string& msg) 	\
	{   														\
		FILE* pStream = Stream(); 								\
		if (!pStream) 											\
			return; 											\
		fprintf(pStream, "%s", msg.c_str()); 					\
		fflush(pStream); 										\
	}

// This is defining all of the different Log2File converters
// it is done this way for efficiency, as well as to confuse anyone
// who considers looking at it.
LOG2FILE(INFOLog_2File);
LOG2FILE(DEBUGLog_2File);

// Definition of the seperate log classes.
class DEBUGLog : public NvPcomp_logger<DEBUGLog_2File> {};
//class DEBUGLog : public NvPcomp_logger<Log2File> {};
class INFOLog : public NvPcomp_logger<INFOLog_2File> {};

#endif // __NVPCOMP_LOGGER_H__
