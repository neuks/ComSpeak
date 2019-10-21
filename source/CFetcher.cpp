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
#include "CFetcher.h"

CFetcher::CFetcher(char *pPath)
{
  m_pFile = NULL;
  m_pFilePath[0] = 0;
  m_pSideInfo[0] = 0;
  m_bCheckOnly = true;
  m_bKeepTalking = false;
  strcpy(m_pPath, pPath);
}

CFetcher::~CFetcher()
{
  fclose(m_pFile);
}

int CFetcher::CheckScenario()
{
  struct dirent *pFile;
  char pFilePath[MAX_PATH] = {0};

  // check for the last log file
  DIR *pDir = opendir(m_pPath);
  {
    int timeval = 0;;
    struct tm time;
    memset(&time, 0, sizeof(time));

    if (pDir == NULL) return -1;

    // loop through the files
    while (pFile = readdir(pDir))
    {
      char *pName = pFile->d_name;

      if (!strcmp(pName, ".")) continue;
      if (!strcmp(pName, "..")) continue;

      if (sscanf(pName, "%d-%d-%d_%d.%d.%d.txt", &time.tm_year, &time.tm_mon,
            &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec) == 6)
      {
        time.tm_year -= 1900;
        time.tm_mon--;

        // get the last log file by filename time tag
        if (timeval < mktime(&time))
        {
          timeval = mktime(&time);
          strcpy(pFilePath, m_pPath);
          strcat(pFilePath, "\\");
          strcat(pFilePath, pName);
        }
      }
      else
      {
        // bypass inalid file names
        continue;
      }
    }
  }
  closedir(pDir);

  // reopen the log file
  if ((pFilePath[0] != 0) && strcmp(pFilePath, m_pFilePath))
  {
    if (m_pFile != NULL)
    {
      fclose(m_pFile);
    }

    if ((m_pFile = fopen(pFilePath, "r")) == NULL)
    {
      return -1;
    }

    if (m_pFilePath[0] != 0)
    {
      m_bCheckOnly = false;
      strcpy(m_pFilePath, pFilePath);

      return 1;
    }
    else
    {
      m_bCheckOnly = true;
      strcpy(m_pFilePath, pFilePath);

      return 0;
    }
  }

  return 0;
}

int CFetcher::GetLine(char *pMessage, int nSize)
{
  char pLine[4096], pParsed[4096], pSideInfo[1024];

  if (m_pFile == NULL)
    return -1;

  // get the log line
  fgets(pLine, 4096, m_pFile);

  // avoid empty lines
  if (strlen(pLine) <= 1)
    return 0;

  if (pLine[0] != '<')
  {
    // remove time tags
    sscanf(pLine, "%*[^-]- %[^$]$", pParsed);
    strcpy(pLine, pParsed);
  }

  // parsing input
  bool bKeep = true;
  int nLength = 0, nKeep = 0;
  for (int i = 0; i < strlen(pLine); i++)
  {
    if (!strncmp(pLine + i, "nbsp;", 5))
    {
      // remove &nbsp;
      i += 4;
    }
    else if (((pLine[i] >= 'a') && (pLine[i] <= 'z')) ||
        ((pLine[i] >= 'A') && (pLine[i] <= 'Z')) ||
        ((pLine[i] >= '0') && (pLine[i] <= '9')))
    {
      // copy words
      if (bKeep && !nKeep)
      {
        if ((pLine[i] == 'n') && (pLine[i + 1] == 'm'))
        {
          i += 2;
          pParsed[nLength++] = ' ';
          pParsed[nLength++] = 'n';
          pParsed[nLength++] = 'a';
          pParsed[nLength++] = 'u';
          pParsed[nLength++] = 't';
          pParsed[nLength++] = 'i';
          pParsed[nLength++] = 'c';
          pParsed[nLength++] = ' ';
          pParsed[nLength++] = 'm';
          pParsed[nLength++] = 'i';
          pParsed[nLength++] = 'l';
          pParsed[nLength++] = 'e';
          pParsed[nLength++] = 's';
          pParsed[nLength++] = '.';
          pParsed[nLength++] = ' ';
        }
        else
        {
          pParsed[nLength++] = pLine[i];
        }
      }
    }
    else switch (pLine[i])
    {
      // removing xml tags
      case '<':
        bKeep = false;
        break;

      case '>':
        bKeep = true;
        break;

      case '(':
        if (bKeep)
        {
          nKeep--;
        }
        break;

      case ')':
        if (bKeep)
        {
          nKeep++;
        }
        break;

      case '[':
      case ']':
      case '-':
      case '+':
      case '\'':
      case '\\':
      case '/':
      case '"':
      case '#':
      case ':':
      case ' ':
        // keep ordinary signs
        if (bKeep && !nKeep) pParsed[nLength++] = pLine[i];
        break;

      case '.':
        if (bKeep && !nKeep)
        {
          if ((pLine[i - 1] >= '0') && (pLine[i - 1] <= '9'))
          {
            pParsed[nLength++] = ' ';
            pParsed[nLength++] = 'p';
            pParsed[nLength++] = 'o';
            pParsed[nLength++] = 'i';
            pParsed[nLength++] = 'n';
            pParsed[nLength++] = 't';
            pParsed[nLength++] = ' ';
            i++;
          }
        }

      case ',':
      case '!':
      case ';':
        if (bKeep && !nKeep)
        {
          // adjust for smooth speaking of sentences
          pParsed[nLength++] = pLine[i];
          pParsed[nLength++] = ' ';
        }
        break;
    }

    // oversize buffer check
    if (nLength > nSize - 5) break;
  }
  pParsed[nLength] = 0;

  // check side info & only speak for our side
  if (sscanf(pParsed, "Switched side to: %[^$]", pSideInfo) == 1)
  {
    // record side info
    sprintf(m_pSideInfo, "[%s]", pSideInfo);
    sprintf(pMessage, "Our side is: %s.", pSideInfo);

    if (m_bCheckOnly == true)
    {
      //fseek(m_pFile, 0, SEEK_END);
      m_bCheckOnly = false;
    }

    return nLength;
  }
  else if (m_pSideInfo[0] != 0)
  {
    if (pParsed[0] == '[')
    {
      if (!strncmp(pParsed, m_pSideInfo, strlen(m_pSideInfo)))
      {
        // speak for our side
        m_bKeepTalking = true;
        strcpy(pMessage, pParsed + strlen(m_pSideInfo) + 1);

        return nLength;
      }
      else
      {
        // stop talking for other sides
        m_bKeepTalking = false;
      }
    }
    else if (m_bKeepTalking == true)
    {
      // speak the breaked continuing lines
      strcpy(pMessage, pParsed);

      return nLength;
    }
  }

  return 0;
}

