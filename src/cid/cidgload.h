/****************************************************************************
 *
 * cidgload.h
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


#ifndef CIDGLOAD_H_
#define CIDGLOAD_H_


#include "cidobjs.h"


FT_BEGIN_HEADER


#if 0

  /* Compute the maximum advance width of a font through quick parsing */
  fn FT_Error /* internal */
  cid_face_compute_max_advance( CID_Face  face,
                                int*   max_advance );

#endif /* 0 */

  fn FT_Error /* internal */
  cid_slot_load_glyph( FT_GlyphSlot  glyph,         /* CID_Glyph_Slot */
                       FT_Size       size,          /* CID_Size       */
                       uint       glyph_index,
                       int      load_flags );


  fn FT_Error /* internal */
  cid_compute_fd_and_offsets( CID_Face   face,
                              uint    glyph_index,
                              FT_ULong*  fd_select_p,
                              FT_ULong*  off1_p,
                              FT_ULong*  off2_p );


FT_END_HEADER

#endif /* CIDGLOAD_H_ */


/* END */
