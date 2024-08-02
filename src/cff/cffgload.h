/****************************************************************************
 *
 * cffgload.h
 *
 *   OpenType Glyph Loader (specification).
 *
 * Copyright (C) 1996-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef CFFGLOAD_H_
#define CFFGLOAD_H_


#include <freetype/freetype.h>
#include <freetype/internal/cffotypes.h>


FT_BEGIN_HEADER

  fn FT_Error /* internal */
  cff_get_glyph_data( TT_Face    face,
                      uint    glyph_index,
                      FT_Byte**  pointer,
                      FT_ULong*  length );
  fn void /* internal */
  cff_free_glyph_data( TT_Face    face,
                       FT_Byte**  pointer,
                       FT_ULong   length );


#if 0  /* unused until we support pure CFF fonts */

  /* Compute the maximum advance width of a font through quick parsing */
  fn FT_Error /* internal */
  cff_compute_max_advance( TT_Face  face,
                           int*  max_advance );

#endif /* 0 */


  fn FT_Error /* internal */
  cff_slot_load( CFF_GlyphSlot  glyph,
                 CFF_Size       size,
                 uint        glyph_index,
                 int       load_flags );


FT_END_HEADER

#endif /* CFFGLOAD_H_ */


/* END */
