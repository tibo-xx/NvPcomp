/**********************************************************************/
//! NvPcomp Log Test.
/*!
 *
 * Description:
 *
 * \author CMT & DRJ
 *
 */
/**********************************************************************/

#include <NvPcomp_logger.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "\nLog Test...\n";
    try
    {
        DEBUGLog::ReportingLevel() = DEBUGLog::FromString(argv[1] ? argv[1] : "LEVEL5");
		
		DEBUGLog_2File::Stream() = stderr;
		//INFOLog_2File::Stream() = stdout;
		
	    const int count = 3;
		LOG(DEBUGLog, logLEVEL5) << "A loop with " << count << " iterations";
        for (int i = 0; i != count; ++i)
        {
			LOG(DEBUGLog, logLEVEL4)  << "DEBUG: the counter i = " << i;
			LOG(INFOLog, logLEVEL3) <<  "INFO: the counter i = " << i;
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        LOG(DEBUGLog, logLEVEL3) << e.what();
    }
    return -1;
}
