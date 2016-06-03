/******************************************************************
@file name:   types.h

@brief:
     this file has include definition of data type, this is special
     useful if transplant system

@note

@author 

@version/date 

******************************************************************/

#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef __BOOL
typedef int                 BOOL;
#define __BOOL
#endif


#ifndef __INT32
typedef signed int        INT32;
#define __INT32
#endif

#ifndef __UINT32
typedef unsigned int      UINT32;
#define __UINT32
#endif

#ifndef __INT16
typedef signed short      INT16;
#define __INT16
#endif

#ifndef __UINT16
typedef unsigned short    UINT16;
#define __UINT16
#endif

#ifndef __INT8
typedef signed char       INT8;
#define __INT8
#endif

#ifndef __UINT8
typedef unsigned char     UINT8;
#define __UINT8
#endif


#ifndef __INT8S
typedef    signed   char  INT8S;    
#define __INT8S
#endif

#ifndef __INT16U
typedef    unsigned short INT16U;   
#define __INT16U
#endif

#ifndef __INT16S
typedef    signed   short INT16S;
#define __INT16S
#endif

#ifndef __INT32S
typedef    signed   long  INT32S; 
#define __INT32S
#endif



#ifndef TRUE
#define TRUE 	1
#endif

#ifndef FALSE
#define FALSE	0
#endif


//---------- flow direction for parameters
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IN_OUT
#define IN_OUT
#endif

#define FLOAT_IS_ZERO(x)  ((x) < 0.00001 && (x) > -0.00001)

#ifdef __cplusplus
}
#endif

#endif // TYPES_H

