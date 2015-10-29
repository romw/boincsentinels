// BOINC Sentinels.
// https://projects.romwnet.org/boincsentinels
// Copyright (C) 2009-2014 Rom Walton
//
// BOINC Sentinels is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC Sentinels is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC Sentinels.  If not, see <http://www.gnu.org/licenses/>.
//

#include "stdwx.h"
#include "Hunter.h"
#include "LogManager.h"

CLogManager::CLogManager() :
wxLogStderr()
{
    m_pLock = new wxCriticalSection();
    wxASSERT(m_pLock);

    if (wxFileExists(wxT("BOINC-Sentinels-Hunter.log")))
    {
        wxRenameFile(wxT("BOINC-Sentinels-Hunter.log"), wxT("BOINC-Sentinels-Hunter.bak"), true);
    }

    m_pFile = new wxFFile(wxT("BOINC-Sentinels-Hunter.log"), wxT("a"));
    m_fp = m_pFile->fp();
}

CLogManager::~CLogManager()
{
    m_fp = stderr;
    if (m_pFile->IsOpened())
    {
        m_pFile->Close();
        delete m_pFile;
        m_pFile = NULL;
    }

    delete m_pLock;
    m_pLock = NULL;
}

void CLogManager::DoLogText(const wxString& msg)
{
#ifdef __WXMSW__
    wxString strDebug = msg + wxString(wxT("\r\n"));
    ::OutputDebugString(strDebug.wx_str());
#endif

    m_pLock->Enter();

    // Do we need to cycle the log file?
    if (m_pFile->Length() > 1024 * 1024 * 8)
    {
        m_pFile->Close();

        wxRenameFile(wxT("BOINC-Sentinels-Hunter.log"), wxT("BOINC-Sentinels-Hunter.bak"), true);

        m_pFile->Open(wxT("BOINC-Sentinels-Hunter.log"), wxT("a"));
        m_fp = m_pFile->fp();
    }

    wxDateTime dtTimestamp = wxDateTime::UNow();
    wxString strBuffer;

    strBuffer.Printf(wxT("%s: %d: %s\n"), dtTimestamp.Format(wxT("%H:%M:%S.%l")).wx_str(), (int)wxThread::GetCurrentId(), msg.wx_str());
    m_pFile->Write(strBuffer.wx_str());

    fflush(m_fp);

    m_pLock->Leave();
}
