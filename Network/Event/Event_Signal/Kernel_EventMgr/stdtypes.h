#ifndef STD_TYPES
#define STD_TYPES

/**
 * \defgroup BasicTypes Basic Types
 *
 * All components - shall use basic types
 * to maintain compatibility of code with all systems.
 * \n File stdtypes.h will adapt the types to the native compiler.
 */
/*@{*/

/**
 * \enum Bool - Boolean Type
 */
typedef enum
{
    False = 0,
    True = 1
} Bool;

typedef int             Int;    /**< Signed base integer quanity */
typedef unsigned int    Uint;   /**< Unsigned base integer quantity */
typedef unsigned long   Ulong;  /**< Unsigned base long quantity */
typedef char            Char;   /**< Character quantity */
typedef char*           String; /**< Character pointer quantity */
typedef void*           Ptr;    /**< Arbitrary (void) pointer (works for pointing to any datum) */

/* Signed integer definitions (64bit, 32bit, 16bit, 8bit) follow... */
typedef long long       Int64;
typedef int             Int32;
typedef short           Int16;
typedef signed char     Int8;

/* Unsigned integer definitions (64bit, 32bit, 16bit, 8bit) follow... */
typedef unsigned long long  Uint64;
typedef unsigned int        Uint32;
typedef unsigned short      Uint16;
typedef unsigned char       Uint8;

/*@}*/
#endif /* STD_TYPES */

