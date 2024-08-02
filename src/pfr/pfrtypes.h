/****************************************************************************
 *
 * pfrtypes.h
 *
 *   FreeType PFR data structures (specification only).
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


#ifndef PFRTYPES_H_
#define PFRTYPES_H_

#include <freetype/internal/ftobjs.h>

FT_BEGIN_HEADER

  /************************************************************************/

  /* the PFR Header structure */
  typedef struct  PFR_HeaderRec_
  {
    uint  signature;
    uint    version;
    uint    signature2;
    uint    header_size;

    uint    log_dir_size;
    uint    log_dir_offset;

    uint    log_font_max_size;
    uint  log_font_section_size;
    uint  log_font_section_offset;

    uint  phy_font_max_size;
    uint  phy_font_section_size;
    uint  phy_font_section_offset;

    uint    gps_max_size;
    uint  gps_section_size;
    uint  gps_section_offset;

    uint    max_blue_values;
    uint    max_x_orus;
    uint    max_y_orus;

    uint    phy_font_max_size_high;
    uint    color_flags;

    uint  bct_max_size;
    uint  bct_set_max_size;
    uint  phy_bct_set_max_size;

    uint    num_phy_fonts;
    uint    max_vert_stem_snap;
    uint    max_horz_stem_snap;
    uint    max_chars;

  } PFR_HeaderRec, *PFR_Header;


  /* used in `color_flags' field of the PFR_Header */
#define PFR_FLAG_BLACK_PIXEL    0x01U
#define PFR_FLAG_INVERT_BITMAP  0x02U


  /************************************************************************/

  typedef struct  PFR_LogFontRec_
  {
    uint  size;
    uint  offset;

    int   matrix[4];
    uint    stroke_flags;
    int     stroke_thickness;
    int     bold_thickness;
    int   miter_limit;

    uint  phys_size;
    uint  phys_offset;

  } PFR_LogFontRec, *PFR_LogFont;


#define PFR_LINE_JOIN_MITER   0x00U
#define PFR_LINE_JOIN_ROUND   0x01U
#define PFR_LINE_JOIN_BEVEL   0x02U
#define PFR_LINE_JOIN_MASK    ( PFR_LINE_JOIN_ROUND | PFR_LINE_JOIN_BEVEL )

#define PFR_LOG_STROKE        0x04U
#define PFR_LOG_2BYTE_STROKE  0x08U
#define PFR_LOG_BOLD          0x10U
#define PFR_LOG_2BYTE_BOLD    0x20U
#define PFR_LOG_EXTRA_ITEMS   0x40U


  /************************************************************************/

#define PFR_BITMAP_2BYTE_CHARCODE  0x01U
#define PFR_BITMAP_2BYTE_SIZE      0x02U
#define PFR_BITMAP_3BYTE_OFFSET    0x04U

  /* not part of the specification but used for implementation */
#define PFR_BITMAP_CHARCODES_VALIDATED  0x40U
#define PFR_BITMAP_VALID_CHARCODES      0x80U


  typedef struct  PFR_BitmapCharRec_
  {
    uint    char_code;
    uint    gps_size;
    uint  gps_offset;

  } PFR_BitmapCharRec, *PFR_BitmapChar;


#define PFR_STRIKE_2BYTE_XPPM    0x01U
#define PFR_STRIKE_2BYTE_YPPM    0x02U
#define PFR_STRIKE_3BYTE_SIZE    0x04U
#define PFR_STRIKE_3BYTE_OFFSET  0x08U
#define PFR_STRIKE_2BYTE_COUNT   0x10U


  typedef struct  PFR_StrikeRec_
  {
    uint         x_ppm;
    uint         y_ppm;
    uint         flags;

    uint       gps_size;
    uint       gps_offset;

    uint       bct_size;
    uint       bct_offset;

    /* optional */
    uint         num_bitmaps;
    PFR_BitmapChar  bitmaps;

  } PFR_StrikeRec, *PFR_Strike;


  /************************************************************************/

  typedef struct  PFR_CharRec_
  {
    uint    char_code;
    int     advance;
    uint    gps_size;
    uint  gps_offset;

  } PFR_CharRec, *PFR_Char;


  /************************************************************************/

  typedef struct  PFR_DimensionRec_
  {
    uint  standard;
    uint  num_stem_snaps;
    int*  stem_snaps;

  } PFR_DimensionRec, *PFR_Dimension;

  /************************************************************************/

  typedef struct PFR_KernItemRec_*  PFR_KernItem;

  typedef struct  PFR_KernItemRec_
  {
    PFR_KernItem  next;
    FT_Byte       pair_count;
    FT_Byte       flags;
    short      base_adj;
    uint       pair_size;
    FT_Offset     offset;
    uint     pair1;
    uint     pair2;

  } PFR_KernItemRec;


#define PFR_KERN_INDEX( g1, g2 )                          \
          ( ( (uint)(g1) << 16 ) | (ushort)(g2) )

#define PFR_KERN_PAIR_INDEX( pair )                        \
          PFR_KERN_INDEX( (pair)->glyph1, (pair)->glyph2 )

#define PFR_NEXT_KPAIR( p )  ( p += 2,                              \
                               ( (uint)p[-2] << 16 ) | p[-1] )


  /************************************************************************/

  typedef struct  PFR_PhyFontRec_
  {
    FT_Memory          memory;
    uint          offset;

    uint            font_ref_number;
    uint            outline_resolution;
    uint            metrics_resolution;
    FT_BBox            bbox;
    uint            flags;
    int             standard_advance;

    int             ascent;   /* optional, bbox.yMax if not present */
    int             descent;  /* optional, bbox.yMin if not present */
    int             leading;  /* optional, 0 if not present         */

    PFR_DimensionRec   horizontal;
    PFR_DimensionRec   vertical;

    FT_String*         font_id;
    FT_String*         family_name;
    FT_String*         style_name;

    uint            num_strikes;
    uint            max_strikes;
    PFR_StrikeRec*     strikes;

    uint            num_blue_values;
    int            *blue_values;
    uint            blue_fuzz;
    uint            blue_scale;

    uint            num_chars;
    FT_Offset          chars_offset;
    PFR_Char           chars;

    uint            num_kern_pairs;
    PFR_KernItem       kern_items;
    PFR_KernItem*      kern_items_tail;

    /* not part of the spec, but used during load */
    FT_ULong           bct_offset;
    FT_Byte*           cursor;

  } PFR_PhyFontRec, *PFR_PhyFont;


#define PFR_PHY_VERTICAL          0x01U
#define PFR_PHY_2BYTE_CHARCODE    0x02U
#define PFR_PHY_PROPORTIONAL      0x04U
#define PFR_PHY_ASCII_CODE        0x08U
#define PFR_PHY_2BYTE_GPS_SIZE    0x10U
#define PFR_PHY_3BYTE_GPS_OFFSET  0x20U
#define PFR_PHY_EXTRA_ITEMS       0x80U


#define PFR_KERN_2BYTE_CHAR  0x01U
#define PFR_KERN_2BYTE_ADJ   0x02U


  /************************************************************************/

#define PFR_GLYPH_YCOUNT         0x01U
#define PFR_GLYPH_XCOUNT         0x02U
#define PFR_GLYPH_1BYTE_XYCOUNT  0x04U

#define PFR_GLYPH_SINGLE_EXTRA_ITEMS    0x08U
#define PFR_GLYPH_COMPOUND_EXTRA_ITEMS  0x40U

#define PFR_GLYPH_IS_COMPOUND  0x80U


  /* controlled coordinate */
  typedef struct  PFR_CoordRec_
  {
    uint  org;
    uint  cur;

  } PFR_CoordRec, *PFR_Coord;


  typedef struct  PFR_SubGlyphRec_
  {
    FT_Fixed   x_scale;
    FT_Fixed   y_scale;
    int     x_delta;
    int     y_delta;
    uint  gps_offset;
    uint    gps_size;

  } PFR_SubGlyphRec, *PFR_SubGlyph;


#define PFR_SUBGLYPH_XSCALE        0x10U
#define PFR_SUBGLYPH_YSCALE        0x20U
#define PFR_SUBGLYPH_2BYTE_SIZE    0x40U
#define PFR_SUBGLYPH_3BYTE_OFFSET  0x80U


  typedef struct  PFR_GlyphRec_
  {
    FT_Byte           format;

#if 0
    uint           num_x_control;
    uint           num_y_control;
#endif
    uint           max_xy_control;
    FT_Pos*           x_control;
    FT_Pos*           y_control;


    uint           num_subs;
    uint           max_subs;
    PFR_SubGlyphRec*  subs;

    FT_GlyphLoader    loader;
    FT_Bool           path_begun;

  } PFR_GlyphRec, *PFR_Glyph;


FT_END_HEADER

#endif /* PFRTYPES_H_ */


/* END */
