/******************************************************************************
 *  ComSpeak Version 1.0 - CMANO Log Message Speaker
 *  Copyright (C) 2019, Martin Tang
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *****************************************************************************/
#ifndef __CFetcher_h__
#define __CFetcher_h__

#include "StdAfx.h"

struct CFetcher
{
  FILE *m_pFile;
  bool m_bKeepTalking;
  char m_pSideInfo[1024];
  char m_pPath[MAX_PATH];
  char m_pFilePath[MAX_PATH];

  CFetcher(char *pPath);
  ~CFetcher();

  int CheckScenario();
  int GetLine(char *pLine, int nSize);
};

#endif
