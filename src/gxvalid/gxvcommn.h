/****************************************************************************
 *
 * gxvcommn.h
 *
 *   TrueTypeGX/AAT common tables validation (specification).
 *
 * Copyright (C) 2004-2024 by
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


  /*
   * keywords in variable naming
   * ---------------------------
   * table:  Of type FT_Bytes, pointing to the start of this table/subtable.
   * limit:  Of type FT_Bytes, pointing to the end of this table/subtable,
   *         including padding for alignment.
   * offset: Of type uint, the number of octets from the start to target.
   * length: Of type uint, the number of octets from the start to the
   *         end in this table/subtable, including padding for alignment.
   *
   *  _MIN, _MAX: Should be added to the tail of macros, as INT_MIN, etc.
   */


#ifndef GXVCOMMN_H_
#define GXVCOMMN_H_


#include "gxvalid.h"
#include <freetype/internal/ftdebug.h>
#include <freetype/ftsnames.h>


FT_BEGIN_HEADER


  /* some variables are not evaluated or only used in trace */

#ifdef  FT_DEBUG_LEVEL_TRACE
#define GXV_LOAD_TRACE_VARS
#else
#undef  GXV_LOAD_TRACE_VARS
#endif

#undef GXV_LOAD_UNUSED_VARS /* debug purpose */

#define IS_PARANOID_VALIDATION                             \
          ( gxvalid->root->level >= FT_VALIDATE_PARANOID )
#define GXV_SET_ERR_IF_PARANOID( err )                              \
          do { if ( IS_PARANOID_VALIDATION ) ( err ); } while ( 0 )


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                         VALIDATION                            *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  typedef struct GXV_ValidatorRec_*  GXV_Validator;


#define DUMMY_LIMIT 0

  typedef void
  (*GXV_Validate_Func)( FT_Bytes       table,
                        FT_Bytes       limit,
                        GXV_Validator  gxvalid );


  /* ====================== LookupTable Validator ======================== */

  typedef union  GXV_LookupValueDesc_
  {
    ushort u;
    short  s;

  } GXV_LookupValueDesc;

  typedef const GXV_LookupValueDesc* GXV_LookupValueCPtr;

  typedef enum  GXV_LookupValue_SignSpec_
  {
    GXV_LOOKUPVALUE_UNSIGNED = 0,
    GXV_LOOKUPVALUE_SIGNED

  } GXV_LookupValue_SignSpec;


  typedef void
  (*GXV_Lookup_Value_Validate_Func)( ushort            glyph,
                                     GXV_LookupValueCPtr  value_p,
                                     GXV_Validator        gxvalid );

  typedef GXV_LookupValueDesc
  (*GXV_Lookup_Fmt4_Transit_Func)( ushort            relative_gindex,
                                   GXV_LookupValueCPtr  base_value_p,
                                   FT_Bytes             lookuptbl_limit,
                                   GXV_Validator        gxvalid );


  /* ====================== StateTable Validator ========================= */

  typedef enum  GXV_GlyphOffset_Format_
  {
    GXV_GLYPHOFFSET_NONE   = -1,
    GXV_GLYPHOFFSET_UCHAR  = 2,
    GXV_GLYPHOFFSET_CHAR,
    GXV_GLYPHOFFSET_USHORT = 4,
    GXV_GLYPHOFFSET_SHORT,
    GXV_GLYPHOFFSET_ULONG  = 8,
    GXV_GLYPHOFFSET_LONG

  } GXV_GlyphOffset_Format;


#define GXV_GLYPHOFFSET_FMT( table )           \
        ( gxvalid->table.entry_glyphoffset_fmt )

#define GXV_GLYPHOFFSET_SIZE( table )              \
        ( gxvalid->table.entry_glyphoffset_fmt / 2 )


  /* ----------------------- 16bit StateTable ---------------------------- */

  typedef union  GXV_StateTable_GlyphOffsetDesc_
  {
    FT_Byte    uc;
    ushort  u;       /* same as GXV_LookupValueDesc */
    FT_ULong   ul;
    FT_Char    c;
    short   s;       /* same as GXV_LookupValueDesc */
    FT_Long    l;

  } GXV_StateTable_GlyphOffsetDesc;

  typedef const GXV_StateTable_GlyphOffsetDesc* GXV_StateTable_GlyphOffsetCPtr;

  typedef void
  (*GXV_StateTable_Subtable_Setup_Func)( ushort      table_size,
                                         ushort      classTable,
                                         ushort      stateArray,
                                         ushort      entryTable,
                                         ushort*     classTable_length_p,
                                         ushort*     stateArray_length_p,
                                         ushort*     entryTable_length_p,
                                         GXV_Validator  gxvalid );

  typedef void
  (*GXV_StateTable_Entry_Validate_Func)(
     FT_Byte                         state,
     ushort                       flags,
     GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
     FT_Bytes                        statetable_table,
     FT_Bytes                        statetable_limit,
     GXV_Validator                   gxvalid );

  typedef void
  (*GXV_StateTable_OptData_Load_Func)( FT_Bytes       table,
                                       FT_Bytes       limit,
                                       GXV_Validator  gxvalid );

  typedef struct  GXV_StateTable_ValidatorRec_
  {
    GXV_GlyphOffset_Format              entry_glyphoffset_fmt;
    void*                               optdata;

    GXV_StateTable_Subtable_Setup_Func  subtable_setup_func;
    GXV_StateTable_Entry_Validate_Func  entry_validate_func;
    GXV_StateTable_OptData_Load_Func    optdata_load_func;

  } GXV_StateTable_ValidatorRec, *GXV_StateTable_ValidatorRecData;


  /* ---------------------- 32bit XStateTable ---------------------------- */

  typedef GXV_StateTable_GlyphOffsetDesc  GXV_XStateTable_GlyphOffsetDesc;

  typedef const GXV_XStateTable_GlyphOffsetDesc* GXV_XStateTable_GlyphOffsetCPtr;

  typedef void
  (*GXV_XStateTable_Subtable_Setup_Func)( FT_ULong       table_size,
                                          FT_ULong       classTable,
                                          FT_ULong       stateArray,
                                          FT_ULong       entryTable,
                                          FT_ULong*      classTable_length_p,
                                          FT_ULong*      stateArray_length_p,
                                          FT_ULong*      entryTable_length_p,
                                          GXV_Validator  gxvalid );

  typedef void
  (*GXV_XStateTable_Entry_Validate_Func)(
     ushort                       state,
     ushort                       flags,
     GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
     FT_Bytes                        xstatetable_table,
     FT_Bytes                        xstatetable_limit,
     GXV_Validator                   gxvalid );


  typedef GXV_StateTable_OptData_Load_Func  GXV_XStateTable_OptData_Load_Func;


  typedef struct  GXV_XStateTable_ValidatorRec_
  {
    int                                  entry_glyphoffset_fmt;
    void*                                optdata;

    GXV_XStateTable_Subtable_Setup_Func  subtable_setup_func;
    GXV_XStateTable_Entry_Validate_Func  entry_validate_func;
    GXV_XStateTable_OptData_Load_Func    optdata_load_func;

    FT_ULong                             nClasses;
    ushort                            maxClassID;

  } GXV_XStateTable_ValidatorRec, *GXV_XStateTable_ValidatorRecData;


  /* ===================================================================== */

  typedef struct  GXV_ValidatorRec_
  {
    FT_Validator  root;

    FT_Face       face;
    void*         table_data;

    FT_ULong      subtable_length;

    GXV_LookupValue_SignSpec        lookupval_sign;
    GXV_Lookup_Value_Validate_Func  lookupval_func;
    GXV_Lookup_Fmt4_Transit_Func    lookupfmt4_trans;
    FT_Bytes                        lookuptbl_head;

    ushort  min_gid;
    ushort  max_gid;

    GXV_StateTable_ValidatorRec     statetable;
    GXV_XStateTable_ValidatorRec    xstatetable;

#ifdef FT_DEBUG_LEVEL_TRACE
    uint             debug_indent;
    const FT_String*    debug_function_name[3];
#endif

  } GXV_ValidatorRec;


#define GXV_TABLE_DATA( tag, field )                             \
        ( ( (GXV_ ## tag ## _Data)gxvalid->table_data )->field )

#undef  FT_INVALID_
#define FT_INVALID_( _error )                                     \
          ft_validator_error( gxvalid->root, FT_THROW( _error ) )

#define GXV_LIMIT_CHECK( _count )                                       \
          {|                                                \
            if ( p + _count > ( limit? limit : gxvalid->root->limit ) ) \
              FT_INVALID_TOO_SHORT;                                     \
          |}


#ifdef FT_DEBUG_LEVEL_TRACE

#define GXV_INIT  gxvalid->debug_indent = 0

#define GXV_NAME_ENTER( name )                                \
          {|                                      \
            gxvalid->debug_indent += 2;                       \
            FT_TRACE4(( "%*.s", gxvalid->debug_indent, "" )); \
            FT_TRACE4(( "%s table\n", name ));                \
          |}

#define GXV_EXIT  gxvalid->debug_indent -= 2

#define GXV_TRACE( s )                                        \
          {|                                      \
            FT_TRACE4(( "%*.s", gxvalid->debug_indent, "" )); \
            FT_TRACE4( s );                                   \
          |}

#else /* !FT_DEBUG_LEVEL_TRACE */

#define GXV_INIT                do { } while ( 0 )
#define GXV_NAME_ENTER( name )  do { } while ( 0 )
#define GXV_EXIT                do { } while ( 0 )

#define GXV_TRACE( s )          do { } while ( 0 )

#endif  /* !FT_DEBUG_LEVEL_TRACE */


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                    32bit alignment checking                   *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

#define GXV_32BIT_ALIGNMENT_VALIDATE( a ) \
          {|                  \
            {                             \
              if ( (a) & 3 )              \
                FT_INVALID_OFFSET;        \
            }                             \
          |}


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                    Dumping Binary Data                        *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

#define GXV_TRACE_HEXDUMP( p, len )                     \
          {|                                \
            {                                           \
              FT_Bytes  b;                              \
                                                        \
                                                        \
              for ( b = p; b < (FT_Bytes)p + len; b++ ) \
                FT_TRACE1(("\\x%02x", *b));             \
            }                                           \
          |}

#define GXV_TRACE_HEXDUMP_C( p, len )                   \
          {|                                \
            {                                           \
              FT_Bytes  b;                              \
                                                        \
                                                        \
              for ( b = p; b < (FT_Bytes)p + len; b++ ) \
                if ( 0x40 < *b && *b < 0x7E )           \
                  FT_TRACE1(("%c", *b));                \
                else                                    \
                  FT_TRACE1(("\\x%02x", *b));           \
            }                                           \
          |}

#define GXV_TRACE_HEXDUMP_SFNTNAME( n )               \
          GXV_TRACE_HEXDUMP( n.string, n.string_len )


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                         LOOKUP TABLE                          *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  fn void /* internal */
  gxv_BinSrchHeader_validate( FT_Bytes       p,
                              FT_Bytes       limit,
                              ushort*     unitSize_p,
                              ushort*     nUnits_p,
                              GXV_Validator  gxvalid );

  fn void /* internal */
  gxv_LookupTable_validate( FT_Bytes       table,
                            FT_Bytes       limit,
                            GXV_Validator  gxvalid );


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                          Glyph ID                             *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  fn int /* internal */
  gxv_glyphid_validate( ushort      gid,
                        GXV_Validator  gxvalid );


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                        CONTROL POINT                          *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  fn void /* internal */
  gxv_ctlPoint_validate( ushort      gid,
                         ushort      ctl_point,
                         GXV_Validator  gxvalid );


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                          SFNT NAME                            *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  fn void /* internal */
  gxv_sfntName_validate( ushort      name_index,
                         ushort      min_index,
                         ushort      max_index,
                         GXV_Validator  gxvalid );


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                          STATE TABLE                          *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  fn void /* internal */
  gxv_StateTable_subtable_setup( ushort      table_size,
                                 ushort      classTable,
                                 ushort      stateArray,
                                 ushort      entryTable,
                                 ushort*     classTable_length_p,
                                 ushort*     stateArray_length_p,
                                 ushort*     entryTable_length_p,
                                 GXV_Validator  gxvalid );

  fn void /* internal */
  gxv_XStateTable_subtable_setup( FT_ULong       table_size,
                                  FT_ULong       classTable,
                                  FT_ULong       stateArray,
                                  FT_ULong       entryTable,
                                  FT_ULong*      classTable_length_p,
                                  FT_ULong*      stateArray_length_p,
                                  FT_ULong*      entryTable_length_p,
                                  GXV_Validator  gxvalid );

  fn void /* internal */
  gxv_StateTable_validate( FT_Bytes       table,
                           FT_Bytes       limit,
                           GXV_Validator  gxvalid );

  fn void /* internal */
  gxv_XStateTable_validate( FT_Bytes       table,
                            FT_Bytes       limit,
                            GXV_Validator  gxvalid );


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                 UTILITY MACROS AND FUNCTIONS                  *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  fn void /* internal */
  gxv_array_getlimits_byte( FT_Bytes       table,
                            FT_Bytes       limit,
                            FT_Byte*       min,
                            FT_Byte*       max,
                            GXV_Validator  gxvalid );

  fn void /* internal */
  gxv_array_getlimits_ushort( FT_Bytes       table,
                              FT_Bytes       limit,
                              ushort*     min,
                              ushort*     max,
                              GXV_Validator  gxvalid );

  fn void /* internal */
  gxv_set_length_by_ushort_offset( ushort*     offset,
                                   ushort**    length,
                                   ushort*     buff,
                                   uint        nmemb,
                                   ushort      limit,
                                   GXV_Validator  gxvalid );

  fn void /* internal */
  gxv_set_length_by_ulong_offset( FT_ULong*      offset,
                                  FT_ULong**     length,
                                  FT_ULong*      buff,
                                  uint        nmemb,
                                  FT_ULong       limit,
                                  GXV_Validator  gxvalid);


#define GXV_SUBTABLE_OFFSET_CHECK( _offset )          \
          {|                              \
            if ( (_offset) > gxvalid->subtable_length ) \
              FT_INVALID_OFFSET;                      \
          |}

#define GXV_SUBTABLE_LIMIT_CHECK( _count )                  \
          {|                                    \
            if ( ( p + (_count) - gxvalid->subtable_start ) > \
                   gxvalid->subtable_length )                 \
              FT_INVALID_TOO_SHORT;                         \
          |}

#define GXV_STATETABLE_HEADER_SIZE  ( 2 + 2 + 2 + 2 )
#define GXV_STATEHEADER_SIZE        GXV_STATETABLE_HEADER_SIZE

#define GXV_XSTATETABLE_HEADER_SIZE  ( 4 + 4 + 4 + 4 )
#define GXV_XSTATEHEADER_SIZE        GXV_XSTATETABLE_HEADER_SIZE


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                        Table overlapping                      *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/

  typedef struct  GXV_odtect_DataRec_
  {
    FT_Bytes    start;
    FT_ULong    length;
    FT_String*  name;

  } GXV_odtect_DataRec,  *GXV_odtect_Data;

  typedef struct  GXV_odtect_RangeRec_
  {
    uint          nRanges;
    GXV_odtect_Data  range;

  } GXV_odtect_RangeRec, *GXV_odtect_Range;


  fn void /* internal */
  gxv_odtect_add_range( FT_Bytes          start,
                        FT_ULong          length,
                        const FT_String*  name,
                        GXV_odtect_Range  odtect );

  fn void /* internal */
  gxv_odtect_validate( GXV_odtect_Range  odtect,
                       GXV_Validator     gxvalid );


#define GXV_ODTECT( n, odtect )                              \
          GXV_odtect_DataRec   odtect ## _range[n];          \
          GXV_odtect_RangeRec  odtect ## _rec = { 0, NULL }; \
          GXV_odtect_Range     odtect = NULL

#define GXV_ODTECT_INIT( odtect )                      \
          {|                               \
            odtect ## _rec.nRanges = 0;                \
            odtect ## _rec.range   = odtect ## _range; \
            odtect                 = & odtect ## _rec; \
          |}


 /* */

FT_END_HEADER

#endif /* GXVCOMMN_H_ */


/* END */
