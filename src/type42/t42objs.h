/****************************************************************************
 *
 * t42objs.h
 *
 *   Type 42 objects manager (specification).
 *
 * Copyright (C) 2002-2024 by
 * Roberto Alameda.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef T42OBJS_H_
#define T42OBJS_H_

#include <freetype/freetype.h>
#include <freetype/t1tables.h>
#include <freetype/internal/t1types.h>
#include "t42types.h"
#include <freetype/internal/ftobjs.h>
#include <freetype/internal/ftdrv.h>
#include <freetype/internal/services/svpscmap.h>
#include <freetype/internal/pshints.h>


FT_BEGIN_HEADER


  /* Type42 size */
  typedef struct  T42_SizeRec_
  {
    FT_SizeRec  root;
    FT_Size     ttsize;

  } T42_SizeRec, *T42_Size;


  /* Type42 slot */
  typedef struct  T42_GlyphSlotRec_
  {
    FT_GlyphSlotRec  root;
    FT_GlyphSlot     ttslot;

  } T42_GlyphSlotRec, *T42_GlyphSlot;


  /* Type 42 driver */
  typedef struct  T42_DriverRec_
  {
    FT_DriverRec     root;
    FT_Driver_Class  ttclazz;

  } T42_DriverRec, *T42_Driver;


  /* */


  fn FT_Error /* internal */
  T42_Face_Init( FT_Stream      stream,
                 FT_Face        face,
                 int         face_index,
                 int         num_params,
                 FT_Parameter*  params );


  fn void /* internal */
  T42_Face_Done( FT_Face  face );


  fn FT_Error /* internal */
  T42_Size_Init( FT_Size  size );


  fn FT_Error /* internal */
  T42_Size_Request( FT_Size          size,
                    FT_Size_Request  req );


  fn FT_Error /* internal */
  T42_Size_Select( FT_Size   size,
                   FT_ULong  strike_index );


  fn void /* internal */
  T42_Size_Done( FT_Size  size );


  fn FT_Error /* internal */
  T42_GlyphSlot_Init( FT_GlyphSlot  slot );


  fn FT_Error /* internal */
  T42_GlyphSlot_Load( FT_GlyphSlot  glyph,
                      FT_Size       size,
                      uint       glyph_index,
                      int      load_flags );

  fn void /* internal */
  T42_GlyphSlot_Done( FT_GlyphSlot  slot );


  fn FT_Error /* internal */
  T42_Driver_Init( FT_Module  module );

  fn void /* internal */
  T42_Driver_Done( FT_Module  module );

 /* */

FT_END_HEADER


#endif /* T42OBJS_H_ */


/* END */
