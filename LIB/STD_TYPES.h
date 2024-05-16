#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Unsigned Data Types */
typedef unsigned char      u8 ;  //1  Bytes  
typedef unsigned short int u16;  //2 Bytes 
typedef unsigned int       u32;  //4 Bytes
typedef unsigned long int  u64;  //8 Bytes
/* Signed Data Types */
typedef signed char        s8 ;  //1 Bytes 
typedef signed short int   s16;  //2 Bytes
typedef signed int         s32;  //4 Bytes
typedef signed long int    s64;  //8 Bytes
/* Floating Data Types */
typedef float              f32 ; //4 Bytes
typedef double             f64 ; //8 Bytes
typedef long double        f128; //16 Bytes

/* check Error Status Macro */
#define  STD_TYPES_OK             1
#define  STD_TYPES_NOK            0

/* NULL Macro */
#define  NULL      ((void*)0)




#endif