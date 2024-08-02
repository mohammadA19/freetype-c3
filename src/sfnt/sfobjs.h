/****************************************************************************
 *
 * sfobjs.h
 *
 *   SFNT object management (specification).
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


#ifndef SFOBJS_H_
#define SFOBJS_H_


#include <freetype/internal/sfnt.h>
#include <freetype/internal/ftobjs.h>


FT_BEGIN_HEADER


  fn FT_Error /* internal */
  sfnt_init_face( FT_Stream      stream,
                  TT_Face        face,
                  int         face_instance_index,
                  int         num_params,
                  FT_Parameter*  params );

  fn FT_Error /* internal */
  sfnt_load_face( FT_Stream      stream,
                  TT_Face        face,
                  int         face_instance_index,
                  int         num_params,
                  FT_Parameter*  params );

  fn void /* internal */
  sfnt_done_face( TT_Face  face );

  fn FT_Error /* internal */
  tt_face_get_name( TT_Face      face,
                    ushort    nameid,
                    FT_String**  name );


FT_END_HEADER

#endif /* SFOBJS_H_ */


/* END */
