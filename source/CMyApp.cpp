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
#include "CMyApp.h"

int main()
{
  char pPath[MAX_PATH];

  CoInitialize(NULL);

  printf("ComSpeak Version 1.0 - CMANO Log Message Speaker\n\n");
  printf("Copyright (C) 2019, Martin Tang\n");
  printf("ComSpeak comes with ABSOLUTELY NO WARRANTY; \n");
  printf("This is free software,and you are welcome to\n");
  printf("redistribute it under certain conditions.\n\n");
  printf("* Install: Put this in your CMANO directory.\n");
  printf("* Usage:\n");
  printf("   'N' - Skip current message\n");
  printf("   'Q' - Quit the applciation\n\n");

  GetModuleFileName(NULL, pPath, MAX_PATH);
  PathRemoveFileSpec(pPath);
  strcat(pPath, "\\Logs");
  printf("* Starting process logs from: %s\n\n", pPath);
  
  g_pSpeaker = new CSpeaker;
  g_pFetcher = new CFetcher(pPath);

  g_pSpeaker->SetRate(-1);

  while (true)
  {
    char pMessage[4096];
    wchar_t pMessageW[4096];

    if (g_pFetcher->CheckScenario() == 1)
    {
      // new log file detected
      printf("* New Scenario Detected!\n\n");
      g_pSpeaker->SetPriorityAlert();
      g_pSpeaker->Speak(L"New Scenario Detected!", false);
    }
    else
    {
      // control key detection
      if (GetKeyState('N') & 0x8000)
      {
        g_pSpeaker->Skip();
      }
      else if (GetKeyState('Q') & 0x8000)
      {
        break;
      }
    }

    if (g_pFetcher->GetLine(pMessage, 4096) > 0)
    {
      // Jump over not needed messages
      if (!strncmp(pMessage, "Weapon:", 7))
        continue;

      // Jump over not needed messages
      if (!strncmp(pMessage, "Event:", 6))
        continue;

      // output and speak
      MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pMessage, -1, pMessageW, 4096);
      if (!strncmp(pMessage, "Our side is: ", 13))
      {
        // don't pass important msgs
        printf("* %s\n\n", pMessage);
        g_pSpeaker->Speak(pMessageW, false);
      }
      else
      {
        // keep it overwriting
        printf("%s\n\n", pMessage);
        g_pSpeaker->Speak(pMessageW, true);
      }
    }

    Sleep(10);
  }

  delete g_pSpeaker;
  delete g_pFetcher;

  CoUninitialize();

  return 0;
}

