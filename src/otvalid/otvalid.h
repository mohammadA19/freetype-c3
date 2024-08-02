/****************************************************************************
 *
 * otvalid.h
 *
 *   OpenType table validation (specification only).
 *
 * Copyright (C) 2004-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef OTVALID_H_
#define OTVALID_H_


#include <freetype/freetype.h>

#include "otverror.h"                      /* must come before `ftvalid.h' */

#include <freetype/internal/ftvalid.h>
#include <freetype/internal/ftstream.h>


FT_BEGIN_HEADER


  fn void /* internal */
  otv_BASE_validate( FT_Bytes      table,
                     FT_Validator  valid );

  /* GSUB and GPOS tables should already be validated; */
  /* if missing, set corresponding argument to 0       */
  fn void /* internal */
  otv_GDEF_validate( FT_Bytes      table,
                     FT_Bytes      gsub,
                     FT_Bytes      gpos,
                     uint       glyph_count,
                     FT_Validator  valid );

  fn void /* internal */
  otv_GPOS_validate( FT_Bytes      table,
                     uint       glyph_count,
                     FT_Validator  valid );

  fn void /* internal */
  otv_GSUB_validate( FT_Bytes      table,
                     uint       glyph_count,
                     FT_Validator  valid );

  /* GSUB and GPOS tables should already be validated; */
  /* if missing, set corresponding argument to 0       */
  fn void /* internal */
  otv_JSTF_validate( FT_Bytes      table,
                     FT_Bytes      gsub,
                     FT_Bytes      gpos,
                     uint       glyph_count,
                     FT_Validator  valid );

  fn void /* internal */
  otv_MATH_validate( FT_Bytes      table,
                     uint       glyph_count,
                     FT_Validator  ftvalid );


FT_END_HEADER

#endif /* OTVALID_H_ */


/* END */
