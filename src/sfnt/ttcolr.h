/****************************************************************************
 *
 * ttcolr.h
 *
 *   TrueType and OpenType colored glyph layer support (specification).
 *
 * Copyright (C) 2018-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * Originally written by Shao Yu Zhang <shaozhang@fb.com>.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef __TTCOLR_H__
#define __TTCOLR_H__


#include "ttload.h"


FT_BEGIN_HEADER


  fn FT_Error /* internal */
  tt_face_load_colr( TT_Face    face,
                     FT_Stream  stream );

  fn void /* internal */
  tt_face_free_colr( TT_Face  face );

  fn FT_Bool /* internal */
  tt_face_get_colr_layer( TT_Face            face,
                          uint            base_glyph,
                          uint           *aglyph_index,
                          uint           *acolor_index,
                          FT_LayerIterator*  iterator );

  fn FT_Bool /* internal */
  tt_face_get_colr_glyph_paint( TT_Face                  face,
                                uint                  base_glyph,
                                FT_Color_Root_Transform  root_transform,
                                FT_OpaquePaint*          paint );

  fn FT_Bool /* internal */
  tt_face_get_color_glyph_clipbox( TT_Face      face,
                                   uint      base_glyph,
                                   FT_ClipBox*  clip_box );

  fn FT_Bool /* internal */
  tt_face_get_paint_layers( TT_Face            face,
                            FT_LayerIterator*  iterator,
                            FT_OpaquePaint*    paint );

  fn FT_Bool /* internal */
  tt_face_get_colorline_stops( TT_Face                face,
                               FT_ColorStop*          color_stop,
                               FT_ColorStopIterator*  iterator );

  fn FT_Bool /* internal */
  tt_face_get_paint( TT_Face         face,
                     FT_OpaquePaint  opaque_paint,
                     FT_COLR_Paint*  paint );

  fn FT_Error /* internal */
  tt_face_colr_blend_layer( TT_Face       face,
                            uint       color_index,
                            FT_GlyphSlot  dstSlot,
                            FT_GlyphSlot  srcSlot );


FT_END_HEADER


#endif /* __TTCOLR_H__ */

/* END */
