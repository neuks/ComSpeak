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
#include "CSpeaker.h"

CSpeaker::CSpeaker()
{
  m_pVoice = NULL;
  CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice,
      (void**)&m_pVoice);
}

CSpeaker::~CSpeaker()
{
  m_pVoice->Release();
  m_pVoice = NULL;
}

int CSpeaker::SetRate(long nRate)
{
  return m_pVoice->SetRate(nRate);
}

int CSpeaker::SetVolume(USHORT nVolume)
{
  return m_pVoice->SetVolume(nVolume);
}

int CSpeaker::SetPriorityNormal()
{
  return m_pVoice->SetPriority(SPVPRI_NORMAL);
}

int CSpeaker::SetPriorityAlert()
{
  return m_pVoice->SetPriority(SPVPRI_ALERT);
}

int CSpeaker::Speak(LPCWSTR pString, bool bASync)
{
  if (m_pVoice)
  {
    if (bASync)
    {
      return m_pVoice->Speak(pString, SPF_ASYNC|SPF_IS_NOT_XML, NULL);
    }
    else
    {
      return m_pVoice->Speak(pString, SPF_DEFAULT|SPF_IS_NOT_XML, NULL);
    }
  }

  return false;
}

int CSpeaker::Pause()
{
  return m_pVoice->Pause();
}

int CSpeaker::Resume()
{
  return m_pVoice->Pause();
}

int CSpeaker::Skip()
{
  return m_pVoice->Skip(L"SENTENCE", 1, NULL);
}

