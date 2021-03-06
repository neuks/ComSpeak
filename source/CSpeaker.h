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
#ifndef __CSpeaker_h__
#define __CSpeaker_h__

#include "StdAfx.h"

struct CSpeaker
{
  ISpVoice *m_pVoice;

  CSpeaker();
  ~CSpeaker();

  int SetRate(long nRate);
  int SetVolume(USHORT nVolume);

  int SetPriorityNormal();
  int SetPriorityAlert();

  int Speak(LPCWSTR pString, bool bASync);
  int Pause();
  int Resume();
  int Skip();
};

#endif
