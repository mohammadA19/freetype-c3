/****************************************************************************
 *
 * ftgrays.h
 *
 *   FreeType smooth renderer declaration
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


#ifndef FTGRAYS_H_
#define FTGRAYS_H_

#ifdef __cplusplus
  extern "C" {
#endif


#ifdef STANDALONE_
#include "ftimage.h"
#else
#include <ft2build.h>
#include <freetype/ftimage.h>
#endif



  /*const */FT_Raster_Funcs  ft_grays_raster;


#ifdef __cplusplus
  }
#endif

#endif /* FTGRAYS_H_ */


/* END */
