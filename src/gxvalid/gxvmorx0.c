/****************************************************************************
 *
 * gxvmorx0.c
 *
 *   TrueTypeGX/AAT morx table validation
 *   body for type0 (Indic Script Rearrangement) subtable.
 *
 * Copyright (C) 2005-2024 by
 * suzuki toshiya, Masatake YAMATO, Red Hat K.K.,
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */

/****************************************************************************
 *
 * gxvalid is derived from both gxlayout module and otvalid module.
 * Development of gxlayout is supported by the Information-technology
 * Promotion Agency(IPA), Japan.
 *
 */


#include "gxvmorx.h"


  /**************************************************************************
   *
   * The macro FT_COMPONENT is used in trace mode.  It is an implicit
   * parameter of the FT_TRACE() and FT_ERROR() macros, used to print/log
   * messages during execution.
   */
#undef  FT_COMPONENT
#define FT_COMPONENT  gxvmorx


  static void
  gxv_morx_subtable_type0_entry_validate(
    ushort                        state,
    ushort                        flags,
    GXV_XStateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                         table,
    FT_Bytes                         limit,
    GXV_Validator                    gxvalid )
  {
#ifdef GXV_LOAD_UNUSED_VARS
    ushort  markFirst;
    ushort  dontAdvance;
    ushort  markLast;
#endif
    ushort  reserved;
#ifdef GXV_LOAD_UNUSED_VARS
    ushort  verb;
#endif

    FT_UNUSED( state );
    FT_UNUSED( glyphOffset_p );
    FT_UNUSED( table );
    FT_UNUSED( limit );


#ifdef GXV_LOAD_UNUSED_VARS
    markFirst   = (ushort)( ( flags >> 15 ) & 1 );
    dontAdvance = (ushort)( ( flags >> 14 ) & 1 );
    markLast    = (ushort)( ( flags >> 13 ) & 1 );
#endif

    reserved = (ushort)( flags & 0x1FF0 );
#ifdef GXV_LOAD_UNUSED_VARS
    verb     = (ushort)( flags & 0x000F );
#endif

    if ( 0 < reserved )
    {
      GXV_TRACE(( " non-zero bits found in reserved range\n" ));
      FT_INVALID_DATA;
    }
  }


  fn void /* internal */
  gxv_morx_subtable_type0_validate( FT_Bytes       table,
                                    FT_Bytes       limit,
                                    GXV_Validator  gxvalid )
  {
    FT_Bytes  p = table;


    GXV_NAME_ENTER(
      "morx chain subtable type0 (Indic-Script Rearrangement)" );

    GXV_LIMIT_CHECK( GXV_STATETABLE_HEADER_SIZE );

    gxvalid->xstatetable.optdata               = NULL;
    gxvalid->xstatetable.optdata_load_func     = NULL;
    gxvalid->xstatetable.subtable_setup_func   = NULL;
    gxvalid->xstatetable.entry_glyphoffset_fmt = GXV_GLYPHOFFSET_NONE;
    gxvalid->xstatetable.entry_validate_func =
      gxv_morx_subtable_type0_entry_validate;

    gxv_XStateTable_validate( p, limit, gxvalid );

    GXV_EXIT;
  }


/* END */
