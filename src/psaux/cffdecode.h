/****************************************************************************
 *
 * cffdecode.h
 *
 *   PostScript CFF (Type 2) decoding routines (specification).
 *
 * Copyright (C) 2017-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef CFFDECODE_H_
#define CFFDECODE_H_


#include <freetype/internal/psaux.h>


FT_BEGIN_HEADER

  fn void /* internal */
  cff_decoder_init( CFF_Decoder*                     decoder,
                    TT_Face                          face,
                    CFF_Size                         size,
                    CFF_GlyphSlot                    slot,
                    FT_Bool                          hinting,
                    FT_Render_Mode                   hint_mode,
                    CFF_Decoder_Get_Glyph_Callback   get_callback,
                    CFF_Decoder_Free_Glyph_Callback  free_callback );

  fn FT_Error /* internal */
  cff_decoder_prepare( CFF_Decoder*  decoder,
                       CFF_Size      size,
                       uint       glyph_index );


  fn int /* internal */
  cff_lookup_glyph_by_stdcharcode( CFF_Font  cff,
                                   int    charcode );


#ifdef CFF_CONFIG_OPTION_OLD_ENGINE
  fn FT_Error /* internal */
  cff_decoder_parse_charstrings( CFF_Decoder*  decoder,
                                 FT_Byte*      charstring_base,
                                 FT_ULong      charstring_len,
                                 FT_Bool       in_dict );
#endif


FT_END_HEADER

#endif


/* END */
