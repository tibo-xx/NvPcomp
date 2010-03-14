/**********************************************************************/
//! NvPcomp Logging.
/*!
 *
 * Description: Based on the article:
 * 				"Logging In C++
 * 				A typesafe, threadsafe, portable logging mechanism"
 * 				by Petru Marginean, Dr. Dobb's Sept. 5, 2007.
 *
 * 				This code is somewhat confusing.  Everything is included
 * 				here to ensure performance.  This is why the code is
 * 				template and macro based.  Additionally all of the 
 * 				variables are static and access to them is not through 
 * 				more traditional get/set methods.  The main logging 
 * 				class, NvPcomp_logger is actually a template that
 * 				requires a class to handle the File IO.  This is done 
 * 				here with the INFOLog_2File Macro.  Since all of the
 * 				methods and variables of this class are static each
 * 				file requires a separate definition of the INFOLog_2File
 * 				class.  All of this creates very fast code but does 
 * 				increase the size of the binary.  To add a new output
 * 				destination use this macro (here we're going to call the
 * 				new class New_Output_2File):
 * 
 * 					LOG2FILE(New_Output_2File);
 * 
 * 				Then create a new class that derives from the 
 * 				NvPcomp_logger class:
 * 
 * 					class New_Output : public NvPcomp_logger<New_Output_2File>
 * 
 * 				Please pay attention to the naming conventions used 
 * 				here.  This is extremely important to the subsequent 
 * 				Macros that use these classes.  The Log2File 
 * 				implementation must have the name of the NvPcomp_logger
 * 				class we're creating follow by a "_2File"  If you decide
 * 				to change this convention make sure you change the LOG
 * 				Macro below.  This brings us to using the newly created 
 * 				loggers.  In your code simplly call the macro LOG, with 
 * 				the name of the NvPcomp_logger class and the desired
 * 				level of output and treat that as a std::ostringstream.
 * 
 * 					LOG(New_Output, LEVEL1) << "Some logging message."
 * 
 * 				Since this is a ostringstream you can also pass it the
 * 				same object types you would pipe to cout.
 * 
 * \author CMT & DRJ
 *
 */
/**********************************************************************/
#ifndef __NVPCOMP_LOGGER_H__
#define __NVPCOMP_LOGGER_H__
/**********************************************************************
 * Includes
 **********************************************************************/
#include <sstream>
#include <string>
#include <stdio.h>
/**********************************************************************
 * Macros
 **********************************************************************/
//! This is the Macro call that will output information if needed.
#define LOG(log_name, level) \
	if (level > FILELOG_MAX_LEVEL) ;\
    else if (level > log_name::ReportingLevel() || !log_name##_2File::Stream()) ; \
    else log_name().Get(level)

#define SET_OUTPUT(log_name, out) \
	log_name##_2File::Stream() = out;

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logLEVEL8
#endif
/**********************************************************************
 * Enumerations
 **********************************************************************/
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

/**********************************************************************/
//! Templatized Logging Class
/*!
 * \class NvPcomp_logger
 * 
 * \author CMT & DRJ
 *
 */
/**********************************************************************/
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

/**********************************************************************
 * Logging Class Implementation
 **********************************************************************/
// Public Constructor.
template <typename T>
NvPcomp_logger<T>::NvPcomp_logger(){}

// Get Function
template <typename T>
std::ostringstream& NvPcomp_logger<T>::Get(LogLevel level)
{
    //os << " " << ToString(level) << ": ";
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

/**********************************************************************
 * Macro definition of the file logging class.
 **********************************************************************/

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
		static void Output(const std::string& msg);				\
	};															\
	inline FILE*& className::Stream() 							\
	{															\
		static FILE* pStream; 									\
		return pStream; 										\
	}															\
	inline void className::Output(const std::string& msg)		\
	{   														\
		FILE* pStream = Stream(); 								\
		if (!pStream) 											\
			return; 											\
		fprintf(pStream, "%s", msg.c_str()); 					\
		fflush(pStream); 										\
	}
/**********************************************************************/

/**********************************************************************/
// This is defining all of the different Log2File converters
// it is done this way for efficiency, as well as to confuse anyone
// who considers looking at it.
LOG2FILE(INFOLog_2File);
LOG2FILE(DEBUGLog_2File);

// Definition of the seperate log classes.
class DEBUGLog : public NvPcomp_logger<DEBUGLog_2File> {};
class INFOLog : public NvPcomp_logger<INFOLog_2File> {};
/**********************************************************************/

#endif // __NVPCOMP_LOGGER_H__
