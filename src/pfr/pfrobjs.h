/****************************************************************************
 *
 * pfrobjs.h
 *
 *   FreeType PFR object methods (specification).
 *
 * Copyright (C) 2002-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef PFROBJS_H_
#define PFROBJS_H_

#include "pfrtypes.h"


FT_BEGIN_HEADER

  typedef struct PFR_FaceRec_*  PFR_Face;

  typedef struct PFR_SizeRec_*  PFR_Size;

  typedef struct PFR_SlotRec_*  PFR_Slot;


  typedef struct  PFR_FaceRec_
  {
    FT_FaceRec      root;
    PFR_HeaderRec   header;
    PFR_LogFontRec  log_font;
    PFR_PhyFontRec  phy_font;

  } PFR_FaceRec;


  typedef struct  PFR_SizeRec_
  {
    FT_SizeRec  root;

  } PFR_SizeRec;


  typedef struct  PFR_SlotRec_
  {
    FT_GlyphSlotRec  root;
    PFR_GlyphRec     glyph;

  } PFR_SlotRec;


  fn FT_Error /* internal */
  pfr_face_init( FT_Stream      stream,
                 FT_Face        face,           /* PFR_Face */
                 int         face_index,
                 int         num_params,
                 FT_Parameter*  params );

  fn void /* internal */
  pfr_face_done( FT_Face  face );               /* PFR_Face */


  fn FT_Error /* internal */
  pfr_face_get_kerning( FT_Face     face,       /* PFR_Face */
                        uint     glyph1,
                        uint     glyph2,
                        FT_Vector*  kerning );


  fn FT_Error /* internal */
  pfr_slot_init( FT_GlyphSlot  slot );          /* PFR_Slot */

  fn void /* internal */
  pfr_slot_done( FT_GlyphSlot  slot );          /* PFR_Slot */


  fn FT_Error /* internal */
  pfr_slot_load( FT_GlyphSlot  slot,            /* PFR_Slot */
                 FT_Size       size,            /* PFR_Size */
                 uint       gindex,
                 int      load_flags );


FT_END_HEADER

#endif /* PFROBJS_H_ */


/* END */
