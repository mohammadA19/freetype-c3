/****************************************************************************
 *
 * internal/compiler-macros.h
 *
 *   Compiler-specific macro definitions used internally by FreeType.
 *
 * Copyright (C) 2020-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */

#ifndef INTERNAL_COMPILER_MACROS_H_
#define INTERNAL_COMPILER_MACROS_H_

#include <freetype/config/public-macros.h>

FT_BEGIN_HEADER


#ifdef __UINTPTR_TYPE__
  /*
   * GCC and Clang both provide a `__UINTPTR_TYPE__` that can be used to
   * avoid a dependency on `stdint.h`.
   */
#  define FT_UINT_TO_POINTER( x )  (void *)(__UINTPTR_TYPE__)(x)
#elif defined( _WIN64 )
  /* only 64bit Windows uses the LLP64 data model, i.e., */
  /* 32-bit integers, 64-bit pointers.                   */
#  define FT_UINT_TO_POINTER( x )  (void *)(unsigned __int64)(x)
#else
#  define FT_UINT_TO_POINTER( x )  (void *)(unsigned long)(x)
#endif

  /*
   * Use `FT_TYPEOF( type )` to cast a value to `type`.  This is useful to
   * suppress signedness compilation warnings in macros.
   *
   * Example:
   *
   *   #define PAD_( x, n )  ( (x) & ~FT_TYPEOF( x )( (n) - 1 ) )
   *
   * (The `typeof` condition is taken from gnulib's `intprops.h` header
   * file.)
   */
#if ( ( defined( __GNUC__ ) && __GNUC__ >= 2 )                       || \
      ( defined( __IBMC__ ) && __IBMC__ >= 1210 &&                      \
        defined( __IBM__TYPEOF__ ) )                                 || \
      ( defined( __SUNPRO_C ) && __SUNPRO_C >= 0x5110 && !__STDC__ ) )
#define FT_TYPEOF( type )  ( __typeof__ ( type ) )
#else
#define FT_TYPEOF( type )  /* empty */
#endif


  /*
   * FreeType supports compilation of its C sources with a C++ compiler (in
   * C++ mode); this introduces a number of subtle issues.
   *
   * The main one is that a C++ function declaration and its definition must
   * have the same 'linkage'.  Because all FreeType headers declare their
   * functions with C linkage (i.e., within an `extern "C" { ... }` block
   * due to the magic of FT_BEGIN_HEADER and FT_END_HEADER), their
   * definition in FreeType sources should also be prefixed with `extern
   * "C"` when compiled in C++ mode.
   *
   * The `FT_FUNCTION_DECLARATION` and `FT_FUNCTION_DEFINITION` macros are
   * provided to deal with this case, as well as `FT_CALLBACK_DEF` and its
   * siblings below.
   */

  /*
   * Use `FT_LOCAL` and `FT_LOCAL_DEF` to declare and define, respectively,
   * an internal FreeType function that is only used by the sources of a
   * single `src/module/` directory.  This ensures that the functions are
   * turned into static ones at build time, resulting in smaller and faster
   * code.
   */
#ifdef FT_MAKE_OPTION_SINGLE_OBJECT

#endif  /* FT_MAKE_OPTION_SINGLE_OBJECT */



  /*
   * The following macros are needed to compile the library with a
   * C++ compiler and with 16bit compilers.
   */


#if defined( __GNUC__ ) && defined( __i386__ )
#define FT_COMPARE_DEF( x )  FT_CALLBACK_DEF( x ) __attribute__(( cdecl ))
#elif defined( _MSC_VER ) && defined( _M_IX86 )
#define FT_COMPARE_DEF( x )  FT_CALLBACK_DEF( x ) __cdecl
#elif defined( __WATCOMC__ ) && __WATCOMC__ >= 1240
#define FT_COMPARE_DEF( x )  FT_CALLBACK_DEF( x ) __watcall
#else
#define FT_COMPARE_DEF( x )  FT_CALLBACK_DEF( x )
#endif

FT_END_HEADER

#endif  /* INTERNAL_COMPILER_MACROS_H_ */
