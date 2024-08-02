/****************************************************************************
 *
 * ftgloadr.h
 *
 *   The FreeType glyph loader (specification).
 *
 * Copyright (C) 2002-2024 by
 * David Turner, Robert Wilhelm, and Werner Lemberg
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef FTGLOADR_H_
#define FTGLOADR_H_


#include <freetype/freetype.h>

#include "compiler-macros.h"

FT_BEGIN_HEADER


  /**************************************************************************
   *
   * @struct:
   *   FT_GlyphLoader
   *
   * @description:
   *   The glyph loader is an internal object used to load several glyphs
   *   together (for example, in the case of composites).
   */
  typedef struct  FT_SubGlyphRec_
  {
    int     index;
    ushort  flags;
    int     arg1;
    int     arg2;
    FT_Matrix  transform;

  } FT_SubGlyphRec;


  typedef struct  FT_GlyphLoadRec_
  {
    FT_Outline   outline;       /* outline                   */
    FT_Vector*   extra_points;  /* extra points table        */
    FT_Vector*   extra_points2; /* second extra points table */
    uint      num_subglyphs; /* number of subglyphs       */
    FT_SubGlyph  subglyphs;     /* subglyphs                 */

  } FT_GlyphLoadRec, *FT_GlyphLoad;


  typedef struct  FT_GlyphLoaderRec_
  {
    FT_Memory        memory;
    uint          max_points;
    uint          max_contours;
    uint          max_subglyphs;
    FT_Bool          use_extra;

    FT_GlyphLoadRec  base;
    FT_GlyphLoadRec  current;

    void*            other;            /* for possible future extension? */

  } FT_GlyphLoaderRec, *FT_GlyphLoader;


  /* create new empty glyph loader */
  fn FT_Error /* private */
  FT_GlyphLoader_New( FT_Memory        memory,
                      FT_GlyphLoader  *aloader );

  /* add an extra points table to a glyph loader */
  fn FT_Error /* private */
  FT_GlyphLoader_CreateExtra( FT_GlyphLoader  loader );

  /* destroy a glyph loader */
  fn void /* private */
  FT_GlyphLoader_Done( FT_GlyphLoader  loader );

  /* reset a glyph loader (frees everything int it) */
  fn void /* private */
  FT_GlyphLoader_Reset( FT_GlyphLoader  loader );

  /* rewind a glyph loader */
  fn void /* private */
  FT_GlyphLoader_Rewind( FT_GlyphLoader  loader );

  /* check that there is enough space to add `n_points' and `n_contours' */
  /* to the glyph loader                                                 */
  fn FT_Error /* private */
  FT_GlyphLoader_CheckPoints( FT_GlyphLoader  loader,
                              uint         n_points,
                              uint         n_contours );


#define FT_GLYPHLOADER_CHECK_P( _loader, _count )       \
  ( (_count) == 0                                    || \
    ( (uint)(_loader)->base.outline.n_points    +    \
      (uint)(_loader)->current.outline.n_points +    \
      (uint)(_count) ) <= (_loader)->max_points   )

#define FT_GLYPHLOADER_CHECK_C( _loader, _count )         \
  ( (_count) == 0                                      || \
    ( (uint)(_loader)->base.outline.n_contours    +    \
      (uint)(_loader)->current.outline.n_contours +    \
      (uint)(_count) ) <= (_loader)->max_contours   )

#define FT_GLYPHLOADER_CHECK_POINTS( _loader, _points, _contours ) \
  ( ( FT_GLYPHLOADER_CHECK_P( _loader, _points )   &&              \
      FT_GLYPHLOADER_CHECK_C( _loader, _contours ) )               \
    ? 0                                                            \
    : FT_GlyphLoader_CheckPoints( (_loader),                       \
                                  (uint)(_points),              \
                                  (uint)(_contours) ) )


  /* check that there is enough space to add `n_subs' sub-glyphs to */
  /* a glyph loader                                                 */
  fn FT_Error /* private */
  FT_GlyphLoader_CheckSubGlyphs( FT_GlyphLoader  loader,
                                 uint         n_subs );

  /* prepare a glyph loader, i.e. empty the current glyph */
  fn void /* private */
  FT_GlyphLoader_Prepare( FT_GlyphLoader  loader );

  /* add the current glyph to the base glyph */
  fn void /* private */
  FT_GlyphLoader_Add( FT_GlyphLoader  loader );


FT_END_HEADER

#endif /* FTGLOADR_H_ */


/* END */
