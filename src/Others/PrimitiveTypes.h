#ifndef BASETYPES_H
#define BASETYPES_H

#include <stdint.h>

namespace flame_ide
{namespace types
{namespace primitive
{

#if defined __x86_64__ && !defined __ILP32__

typedef uint8_t uchar_t;
typedef  int8_t  char_t;

typedef uint16_t ushort_t;
typedef  int16_t  short_t;

typedef uint32_t uint_t;
typedef  int32_t  int_t;

#if __WORDSIZE == 64
typedef uint64_t ulong_t;
typedef  int64_t  long_t;

typedef uint64_t ullong_t;
typedef  int64_t  llong_t;

typedef uint64_t ptr_t;

typedef uint64_t size_t;
#else
typedef std::uint32_t size_t;
#endif

#elif defined __x86__ && defined __ILP32__

typedef std::uint8_t uchar_t;
typedef  std::int8_t  char_t;

typedef std::uint16_t ushort_t;
typedef  std::int16_t  short_t;

typedef std::uint32_t uint_t;
typedef  std::int32_t  int_t;

typedef std::uint32_t ulong_t;
typedef  std::int32_t  long_t;

#if __WORDSIZE == 64
typedef std::uint64_t ullong_t;
typedef  std::int64_t  llong_t;

typedef std::uint64_t size_t;
#else
typedef std::uint32_t size_t;
#endif

typdef uint32_t ptr_t;

#endif

typedef float float_t;
typedef double lfloat_t;


}}}

#endif // BASETYPES_H
