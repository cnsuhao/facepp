/******************************************************************
@file name:   debug.h

@brief:
     this file has include definition of debug function or macro,

@note

@author 

@version/date

******************************************************************/
#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif


#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include "types.h"


#define DEBUG_SWITCH 1


// ===== name of file for save print log
#define DEF_LOGINFO_PATH  			"/tmp/logInfo.txt"
#define DEF_VITAL_LOGINFO_PATH  	"/tmp/vitalLogInfo.txt"
#define DEF_LOGINFO_ONLY_NAME  		"logInfo"
#define DEF_LOGINFO_ONLY_NAME_EXT  	"txt"


//========  select data carrier for debugging message
#define DEBUG_DATA_CARRIER_NOANY 	0x00
#define DEBUG_DATA_CARRIER_UART  	0x01
#define DEBUG_DATA_CARRIER_FILE  	0x02
#define DEBUG_DATA_CARRIER_NETWORK  0x04
#define DEBUG_DATA_CARRIER_ALL 		0xff


//========  select print module for debugging message
#define DEBUG_OUTPUT_MDL_UPPRO 		0x01 	// up protocol module
#define DEBUG_OUTPUT_MDL_DOWNPRO 	0x02 	// down protocol module
#define DEBUG_OUTPUT_MDL_DB 		0x04 	// Database acess
#define DEBUG_OUTPUT_MDL_OTHER 		0x08 	// other module
#define DEBUG_OUTPUT_MDL_PROTOCOL   0x10 	// local web accesss
#define DEBUG_OUTPUT_MDL_ALL 		0xff 	// all of module

//========  select level of 
#define DBG_LVL_RESERVE  	0x0
#define DBG_LVL_ALLINFO_0  	0x1 	// all of infor 0
#define DBG_LVL_ALLINFO_1  	0x2 	// all of infor 1
#define DBG_LVL_DBG         0x3 	// debug
#define DBG_LVL_VITAL  		0x4		// important
#define DBG_LVL_WARN  		0x5 	// warning
#define DBG_LVL_ERR  		0x6 	// error

#define LOG_CLEAR_CYCLE		60


typedef  struct DbgInfoParam_t
{  
	UINT32 carrierMask; 	// Which Channel need to print
	UINT32 mdlMask; 		// Which modules need to print
	UINT32 level;			// Print level 
} DbgInfoParam;
extern DbgInfoParam gDbgInfoParam;


#define DBG_GET_MDLMSK  (gDbgInfoParam.mdlMask) 
#define DBG_GET_LEVEL 	(gDbgInfoParam.level)

int logtofile(UINT32 mdlMask, UINT32 level, char *logfilename_prefix, char *function, int line, const char *fmt, ...);
int printlog(UINT32 mdlMask, UINT32 level, char* logfilename_prefix, char* file, char* function, int line, const char *fmt, ...);

#if 1
#define DBG_LOGTOFILE(level,filePrefix,argvar...)   \
		logtofile(DEBUG_OUTPUT_MDL_ALL, level, filePrefix, (char*)__func__, __LINE__, ##argvar);

#define DBG_LOG(mdlMask,level, args ...)	\
		printlog(mdlMask, level, "/tmp/log", __FILE__, (char*)__func__, __LINE__, ##args )
#endif


//========================================================
#if 1
#define LOGD(...)	 DBG_LOGTOFILE(DBG_LVL_DBG,LOG_TAG, __VA_ARGS__)
#define LOGI(...)	 DBG_LOGTOFILE(DBG_LVL_VITAL,LOG_TAG, __VA_ARGS__)
#define LOGW(...)	 DBG_LOGTOFILE(DBG_LVL_WARN,LOG_TAG, __VA_ARGS__)
#define LOGE(...)	 DBG_LOGTOFILE(DBG_LVL_ERR,LOG_TAG, __VA_ARGS__)
#define LOGF(...)	 DBG_LOGTOFILE(DBG_LVL_ALLINFO_1,LOG_TAG, __VA_ARGS__)
#else
#define LOGI(...)	 printf(__VA_ARGS__)
#define LOGW(...)	 printf(__VA_ARGS__)
#define LOGE(...)	 printf(__VA_ARGS__)
#define LOGF(...)	 printf(__VA_ARGS__)
#define LOGD(...)	 printf(__VA_ARGS__)
#endif




//=====================================================C++
#if DEBUG_SWITCH
#define ENTER_FILE_FUNC__() msg_print("\n\n### ---***--- ENTER file %s, %s() in the LINE: %d\n\n", \
							__FILE__, __FUNCTION__, __LINE__)

#define LEAVE_FILE_FUNC__() msg_print("\n\n### ---***--- LEAVE file %s, %s() in the LINE: %d\n\n", \
							__FILE__, __FUNCTION__, __LINE__)

#define ENTER_FUNC__() 	msg_print("\n### ---***--- ENTER %s() in the LINE: %d\n", __FUNCTION__, __LINE__)
#define LEAVE_FUNC__() 	msg_print("\n### ---***--- LEAVE %s() in the LINE: %d\n", __FUNCTION__, __LINE__)
#define TRACE_OUT 		msg_print

#define TRACE_OUT_MASS_DATA    msg_print_mass_data

#else
#define ENTER_FILE_FUNC__(...)
#define LEAVE_FILE_FUNC__(...)
#define ENTER_FUNC__(...)
#define LEAVE_FUNC__(...)
#define TRACE_OUT(...)
#define TRACE_OUT_MASS_DATA(...)
#endif

#define TRACE_VITAL_INFO  msg_print


void debug_mdl_init(void);
void debug_mdl_deinit(void);
void debug_mdl_set_carrier_mask(UINT32 carrierMask);

DbgInfoParam* debug_mdl_get_param(void);
void debug_mdl_set_carrier_data(IN char* infoPtr, BOOL isAddNewLine, BOOL isAddTmTag);
void debug_mdl_set_param(IN DbgInfoParam *pParam);
void msg_print(const char* fmt, ...);
void msg_print_mass_data(const char* fmt, ...);
void debug_print(UINT32 mdlMask, char * fmt,...);

//========auto add time tag before printing debug infor.
void debug_print_info(UINT32 mdlMask, BOOL isAddTmTag, char * fmt,...);
void debug_print_detail_info(UINT32 mdlMask, UINT32 level, BOOL isAddTmTag, char * fmt,...);

//---- force write debug infor. to log file
void debug_force_sav_vital_log_info(BOOL isAddTmTag, char * fmt,...);


#ifdef __cplusplus
}
#endif

#endif // DEBUG_H

