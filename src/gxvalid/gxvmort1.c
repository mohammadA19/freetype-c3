/****************************************************************************
 *
 * gxvmort1.c
 *
 *   TrueTypeGX/AAT mort table validation
 *   body for type1 (Contextual Substitution) subtable.
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


#include "gxvmort.h"


  /**************************************************************************
   *
   * The macro FT_COMPONENT is used in trace mode.  It is an implicit
   * parameter of the FT_TRACE() and FT_ERROR() macros, used to print/log
   * messages during execution.
   */
#undef  FT_COMPONENT
#define FT_COMPONENT  gxvmort


  typedef struct  GXV_mort_subtable_type1_StateOptRec_
  {
    ushort  substitutionTable;
    ushort  substitutionTable_length;

  }  GXV_mort_subtable_type1_StateOptRec,
    *GXV_mort_subtable_type1_StateOptRecData;

#define GXV_MORT_SUBTABLE_TYPE1_HEADER_SIZE \
          ( GXV_STATETABLE_HEADER_SIZE + 2 )


  static void
  gxv_mort_subtable_type1_substitutionTable_load( FT_Bytes       table,
                                                  FT_Bytes       limit,
                                                  GXV_Validator  gxvalid )
  {
    FT_Bytes  p = table;

    GXV_mort_subtable_type1_StateOptRecData  optdata =
      (GXV_mort_subtable_type1_StateOptRecData)gxvalid->statetable.optdata;


    GXV_LIMIT_CHECK( 2 );
    optdata->substitutionTable = FT_NEXT_USHORT( p );
  }


  static void
  gxv_mort_subtable_type1_subtable_setup( ushort      table_size,
                                          ushort      classTable,
                                          ushort      stateArray,
                                          ushort      entryTable,
                                          ushort*     classTable_length_p,
                                          ushort*     stateArray_length_p,
                                          ushort*     entryTable_length_p,
                                          GXV_Validator  gxvalid )
  {
    ushort  o[4];
    ushort  *l[4];
    ushort  buff[5];

    GXV_mort_subtable_type1_StateOptRecData  optdata =
      (GXV_mort_subtable_type1_StateOptRecData)gxvalid->statetable.optdata;


    o[0] = classTable;
    o[1] = stateArray;
    o[2] = entryTable;
    o[3] = optdata->substitutionTable;
    l[0] = classTable_length_p;
    l[1] = stateArray_length_p;
    l[2] = entryTable_length_p;
    l[3] = &( optdata->substitutionTable_length );

    gxv_set_length_by_ushort_offset( o, l, buff, 4, table_size, gxvalid );
  }


  static void
  gxv_mort_subtable_type1_offset_to_subst_validate(
    short          wordOffset,
    const FT_String*  tag,
    FT_Byte           state,
    GXV_Validator     gxvalid )
  {
    ushort  substTable;
    ushort  substTable_limit;

    FT_UNUSED( tag );
    FT_UNUSED( state );


    substTable =
      ((GXV_mort_subtable_type1_StateOptRec *)
       (gxvalid->statetable.optdata))->substitutionTable;
    substTable_limit =
      (ushort)( substTable +
                   ((GXV_mort_subtable_type1_StateOptRec *)
                    (gxvalid->statetable.optdata))->substitutionTable_length );

    gxvalid->min_gid = (ushort)( ( substTable       - wordOffset * 2 ) / 2 );
    gxvalid->max_gid = (ushort)( ( substTable_limit - wordOffset * 2 ) / 2 );
    gxvalid->max_gid = (ushort)( FT_MAX( gxvalid->max_gid,
                                            gxvalid->face->num_glyphs ) );

    /* XXX: check range? */

    /* TODO: min_gid & max_gid comparison with ClassTable contents */
  }


  static void
  gxv_mort_subtable_type1_entry_validate(
    FT_Byte                         state,
    ushort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
#ifdef GXV_LOAD_UNUSED_VARS
    ushort  setMark;
    ushort  dontAdvance;
#endif
    ushort  reserved;
    short   markOffset;
    short   currentOffset;

    FT_UNUSED( table );
    FT_UNUSED( limit );


#ifdef GXV_LOAD_UNUSED_VARS
    setMark       = (ushort)(   flags >> 15            );
    dontAdvance   = (ushort)( ( flags >> 14 ) & 1      );
#endif
    reserved      = (ushort)(    flags        & 0x3FFF );

    markOffset    = (short)( glyphOffset_p->ul >> 16 );
    currentOffset = (short)( glyphOffset_p->ul       );

    if ( 0 < reserved )
    {
      GXV_TRACE(( " non-zero bits found in reserved range\n" ));
      GXV_SET_ERR_IF_PARANOID( FT_INVALID_DATA );
    }

    gxv_mort_subtable_type1_offset_to_subst_validate( markOffset,
                                                      "markOffset",
                                                      state,
                                                      gxvalid );

    gxv_mort_subtable_type1_offset_to_subst_validate( currentOffset,
                                                      "currentOffset",
                                                      state,
                                                      gxvalid );
  }


  static void
  gxv_mort_subtable_type1_substTable_validate( FT_Bytes       table,
                                               FT_Bytes       limit,
                                               GXV_Validator  gxvalid )
  {
    FT_Bytes   p = table;
    ushort  num_gids = (ushort)(
                 ((GXV_mort_subtable_type1_StateOptRec *)
                  (gxvalid->statetable.optdata))->substitutionTable_length / 2 );
    ushort  i;


    GXV_NAME_ENTER( "validating contents of substitutionTable" );
    for ( i = 0; i < num_gids; i++ )
    {
      ushort  dst_gid;


      GXV_LIMIT_CHECK( 2 );
      dst_gid = FT_NEXT_USHORT( p );

      if ( dst_gid >= 0xFFFFU )
        continue;

      if ( dst_gid < gxvalid->min_gid || gxvalid->max_gid < dst_gid )
      {
        GXV_TRACE(( "substTable include a strange gid[%d]=%d >"
                    " out of define range (%d..%d)\n",
                    i, dst_gid, gxvalid->min_gid, gxvalid->max_gid ));
        GXV_SET_ERR_IF_PARANOID( FT_INVALID_GLYPH_ID );
      }
    }

    GXV_EXIT;
  }


  /*
   * subtable for Contextual glyph substitution is a modified StateTable.
   * In addition to classTable, stateArray, and entryTable, the field
   * `substitutionTable' is added.
   */
  fn void /* internal */
  gxv_mort_subtable_type1_validate( FT_Bytes       table,
                                    FT_Bytes       limit,
                                    GXV_Validator  gxvalid )
  {
    FT_Bytes  p = table;

    GXV_mort_subtable_type1_StateOptRec  st_rec;


    GXV_NAME_ENTER( "mort chain subtable type1 (Contextual Glyph Subst)" );

    GXV_LIMIT_CHECK( GXV_MORT_SUBTABLE_TYPE1_HEADER_SIZE );

    gxvalid->statetable.optdata =
      &st_rec;
    gxvalid->statetable.optdata_load_func =
      gxv_mort_subtable_type1_substitutionTable_load;
    gxvalid->statetable.subtable_setup_func =
      gxv_mort_subtable_type1_subtable_setup;
    gxvalid->statetable.entry_glyphoffset_fmt =
      GXV_GLYPHOFFSET_ULONG;
    gxvalid->statetable.entry_validate_func =

      gxv_mort_subtable_type1_entry_validate;
    gxv_StateTable_validate( p, limit, gxvalid );

    gxv_mort_subtable_type1_substTable_validate(
      table + st_rec.substitutionTable,
      table + st_rec.substitutionTable + st_rec.substitutionTable_length,
      gxvalid );

    GXV_EXIT;
  }


/* END */
