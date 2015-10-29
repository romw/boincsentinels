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
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Valkyrie.h"
#include "Utils.h"
#include "DlgControls.h"


IMPLEMENT_DYNAMIC_CLASS(CDlgStaticText, wxStaticText)

BEGIN_EVENT_TABLE(CDlgStaticText, wxStaticText)
END_EVENT_TABLE()

CDlgStaticText::CDlgStaticText() {}

CDlgStaticText::CDlgStaticText(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, label, pos, size, style, name);
}

bool CDlgStaticText::Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    return wxStaticText::Create(parent, id, label, pos, size, style, name);
}

void CDlgStaticText::SetLabel(const wxString& label)
{
    wxStaticText::SetLabel(label);
}


IMPLEMENT_DYNAMIC_CLASS(CDlgDateTime, wxStaticText)

BEGIN_EVENT_TABLE(CDlgDateTime, wxStaticText)
END_EVENT_TABLE()

CDlgDateTime::CDlgDateTime() {}

CDlgDateTime::CDlgDateTime(wxWindow* parent, wxWindowID id, const wxDateTime& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CDlgDateTime::Create(wxWindow* parent, wxWindowID id, const wxDateTime& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, value.Format(), pos, size, style, name);

	m_dtValue = value;

	return bRetVal;
}

wxDateTime CDlgDateTime::GetValue()
{
    return m_dtValue;
}

void CDlgDateTime::SetValue(const wxDateTime& value)
{
    if (m_dtValue != value)
    {
        m_dtValue = value;
        wxStaticText::SetLabel(value.Format());
    }
}


IMPLEMENT_DYNAMIC_CLASS(CDlgTimeSpan, wxStaticText)

BEGIN_EVENT_TABLE(CDlgTimeSpan, wxStaticText)
END_EVENT_TABLE()

CDlgTimeSpan::CDlgTimeSpan() {}

CDlgTimeSpan::CDlgTimeSpan(wxWindow* parent, wxWindowID id, const wxTimeSpan& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CDlgTimeSpan::Create(wxWindow* parent, wxWindowID id, const wxTimeSpan& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, value.Format(), pos, size, style, name);
	
	m_tsValue = value;

    return bRetVal;
}

wxTimeSpan CDlgTimeSpan::GetValue()
{
    return m_tsValue;
}

void CDlgTimeSpan::SetValue(const wxTimeSpan& value)
{
    if (m_tsValue != value)
    {
        m_tsValue = value;
        wxStaticText::SetLabel(value.Format());
    }
}


IMPLEMENT_DYNAMIC_CLASS(CDlgUint32, wxStaticText)

BEGIN_EVENT_TABLE(CDlgUint32, wxStaticText)
END_EVENT_TABLE()

CDlgUint32::CDlgUint32()
{
    m_ulValue = 0;
}

CDlgUint32::CDlgUint32(wxWindow* parent, wxWindowID id, const wxUint32& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CDlgUint32::Create(wxWindow* parent, wxWindowID id, const wxUint32& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);

    m_ulValue = value;
    if (value)
    {
        wxString str;
        str.Printf(wxT("%d"), value);
        SetLabel(str);
    }

    return bRetVal;
}

wxUint32 CDlgUint32::GetValue()
{
    return m_ulValue;
}

void CDlgUint32::SetValue(const wxUint32& value)
{
    if (m_ulValue != value)
    {
        m_ulValue = value;
        if (value)
        {
            wxString str;
            str.Printf(wxT("%d"), m_ulValue);
            SetLabel(str);
        }
    }
}


IMPLEMENT_DYNAMIC_CLASS(CDlgProgress, wxStaticText)

BEGIN_EVENT_TABLE(CDlgProgress, wxStaticText)
END_EVENT_TABLE()

CDlgProgress::CDlgProgress()
{
    m_dValue = 0.0;
}

CDlgProgress::CDlgProgress(wxWindow* parent, wxWindowID id, const wxDouble& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
{
    Create(parent, id, value, pos, size, style, name);
}

bool CDlgProgress::Create(wxWindow* parent, wxWindowID id, const wxDouble& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style, name);

    m_dValue = value;

    wxString str;
    str.Printf(wxT("%.2f%%"), m_dValue * 100);

    SetLabel(str);

    return bRetVal;
}

wxDouble CDlgProgress::GetValue()
{
    return m_dValue;
}

void CDlgProgress::SetValue(const wxDouble& value)
{
    if (value >= 100.0)
    {
        if (m_dValue != 100.0)
        {
            m_dValue = 100.0;
            SetLabel(wxT("100%"));
        }
    }
    else if (m_dValue != value)
    {
        m_dValue = value;

        wxString str;
        str.Printf(wxT("%.3f%%"), m_dValue * 100);

        SetLabel(str);
    }
}


IMPLEMENT_DYNAMIC_CLASS(CDlgByteCount, wxStaticText)

BEGIN_EVENT_TABLE(CDlgByteCount, wxStaticText)
END_EVENT_TABLE()

CDlgByteCount::CDlgByteCount()
{
    m_ullValue = 0;
    m_ullTotal = 0;
}

CDlgByteCount::CDlgByteCount(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CDlgByteCount::Create(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);

    m_ullValue = value;
    m_ullTotal = 0;
    wxStaticText::SetLabel(CUtils::ConstructByteCount(value, m_ullTotal));

	return bRetVal;
}

wxUint64 CDlgByteCount::GetValue()
{
    return m_ullValue;
}

wxUint64 CDlgByteCount::GetTotal()
{
    return m_ullTotal;
}

void CDlgByteCount::SetValue(const wxUint64& value)
{
    if (m_ullValue != value)
    {
        m_ullValue = value;
        wxStaticText::SetLabel(CUtils::ConstructByteCount(value, m_ullTotal));
    }
}

void CDlgByteCount::SetTotal(const wxUint64& value)
{
    if (m_ullTotal != value)
    {
        m_ullTotal = value;
    }
}


IMPLEMENT_DYNAMIC_CLASS(CDlgByteRate, wxStaticText)

BEGIN_EVENT_TABLE(CDlgByteRate, wxStaticText)
END_EVENT_TABLE()

CDlgByteRate::CDlgByteRate()
{
    m_ullValue = 0;
}

CDlgByteRate::CDlgByteRate(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CDlgByteRate::Create(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);

    m_ullValue = value;
    wxStaticText::SetLabel(CUtils::ConstructByteRate(value));

    return bRetVal;
}

wxUint64 CDlgByteRate::GetValue()
{
    return m_ullValue;
}

void CDlgByteRate::SetValue(const wxUint64& value)
{
    if (m_ullValue != value)
    {
        m_ullValue = value;
        wxStaticText::SetLabel(CUtils::ConstructByteRate(value));
    }
}


IMPLEMENT_DYNAMIC_CLASS(CDlgFLOPCount, wxStaticText)

BEGIN_EVENT_TABLE(CDlgFLOPCount, wxStaticText)
END_EVENT_TABLE()

CDlgFLOPCount::CDlgFLOPCount()
{
    m_ullValue = 0;
}

CDlgFLOPCount::CDlgFLOPCount(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CDlgFLOPCount::Create(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);

    m_ullValue = value;
    wxStaticText::SetLabel(CUtils::ConstructFLOPCount(value));

    return bRetVal;
}

wxUint64 CDlgFLOPCount::GetValue()
{
    return m_ullValue;
}

void CDlgFLOPCount::SetValue(const wxUint64& value)
{
    if (m_ullValue != value)
    {
        m_ullValue = value;
        wxStaticText::SetLabel(CUtils::ConstructFLOPCount(value));
    }
}
