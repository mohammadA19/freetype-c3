/****************************************************************************
 *
 * psconv.h
 *
 *   Some convenience conversions (specification).
 *
 * Copyright (C) 2006-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef PSCONV_H_
#define PSCONV_H_


#include <freetype/internal/psaux.h>

FT_BEGIN_HEADER


  fn FT_Long /* internal */
  PS_Conv_Strtol( FT_Byte**  cursor,
                  FT_Byte*   limit,
                  FT_Long    base );


  fn FT_Long /* internal */
  PS_Conv_ToInt( FT_Byte**  cursor,
                 FT_Byte*   limit );

  fn FT_Fixed /* internal */
  PS_Conv_ToFixed( FT_Byte**  cursor,
                   FT_Byte*   limit,
                   FT_Long    power_ten );

#if 0
  fn FT_UInt /* internal */
  PS_Conv_StringDecode( FT_Byte**  cursor,
                        FT_Byte*   limit,
                        FT_Byte*   buffer,
                        FT_Offset  n );
#endif

  fn FT_UInt /* internal */
  PS_Conv_ASCIIHexDecode( FT_Byte**  cursor,
                          FT_Byte*   limit,
                          FT_Byte*   buffer,
                          FT_Offset  n );

  fn FT_UInt /* internal */
  PS_Conv_EexecDecode( FT_Byte**   cursor,
                       FT_Byte*    limit,
                       FT_Byte*    buffer,
                       FT_Offset   n,
                       FT_UShort*  seed );


FT_END_HEADER

#endif /* PSCONV_H_ */


/* END */
