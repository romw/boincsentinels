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
#include "WidgetControls.h"


IMPLEMENT_DYNAMIC_CLASS (CWidgetBitmapButton, wxBitmapButton)

BEGIN_EVENT_TABLE(CWidgetBitmapButton, wxBitmapButton)
    EVT_ERASE_BACKGROUND(CWidgetBitmapButton::OnEraseBackground)
    EVT_PAINT(CWidgetBitmapButton::OnPaint)
END_EVENT_TABLE()

CWidgetBitmapButton::CWidgetBitmapButton() {}

CWidgetBitmapButton::CWidgetBitmapButton(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name )
{
    Create(parent, id, label, pos, size, style, validator, name);
}

bool CWidgetBitmapButton::Create(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name )
{
    bool bRetVal = wxBitmapButton::Create(parent, id, label, pos, size, style|wxTRANSPARENT_WINDOW, validator, name);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());

    return bRetVal;
}

void CWidgetBitmapButton::SetBitmapLabel(const wxBitmap& label)
{
    wxBitmapButton::SetBitmapLabel(label);
}

void CWidgetBitmapButton::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.DrawBitmap(GetBitmapLabel(), 0, 0, true);
}

void CWidgetBitmapButton::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}


IMPLEMENT_DYNAMIC_CLASS (CWidgetStaticBitmap, wxStaticBitmap)

BEGIN_EVENT_TABLE(CWidgetStaticBitmap, wxStaticBitmap)
    EVT_ERASE_BACKGROUND(CWidgetStaticBitmap::OnEraseBackground)
    EVT_PAINT(CWidgetStaticBitmap::OnPaint)
END_EVENT_TABLE()

CWidgetStaticBitmap::CWidgetStaticBitmap() {}

CWidgetStaticBitmap::CWidgetStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
{
    Create(parent, id, bitmap, pos, size, style, name);
}

bool CWidgetStaticBitmap::Create(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
{
    bool bRetVal = wxStaticBitmap::Create(parent, id, bitmap, pos, size, style|wxTRANSPARENT_WINDOW, name);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());

    return bRetVal;
}

void CWidgetStaticBitmap::SetBitmap(const wxBitmap& bitmap)
{
    wxStaticBitmap::SetBitmap(bitmap);
}

void CWidgetStaticBitmap::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.DrawBitmap(GetBitmap(), 0, 0, true);
}

void CWidgetStaticBitmap::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}


IMPLEMENT_DYNAMIC_CLASS (CWidgetStaticText, wxStaticText)

BEGIN_EVENT_TABLE(CWidgetStaticText, wxStaticText)
    EVT_ERASE_BACKGROUND(CWidgetStaticText::OnEraseBackground)
    EVT_PAINT(CWidgetStaticText::OnPaint)
END_EVENT_TABLE()

CWidgetStaticText::CWidgetStaticText() {}

CWidgetStaticText::CWidgetStaticText(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, label, pos, size, style, name);
}

bool CWidgetStaticText::Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, label, pos, size, style|wxTRANSPARENT_WINDOW, name);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());

    return bRetVal;
}

void CWidgetStaticText::SetLabel(const wxString& label)
{
    wxStaticText::SetLabel(label);
}

void CWidgetStaticText::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.SetFont(GetFont());
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(GetForegroundColour());
    dc.DrawText(GetLabel(), 0, 0);
}

void CWidgetStaticText::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

wxSize CWidgetStaticText::DoGetBestClientSize() const 
{
    return GetTextExtent(GetLabel());
}

IMPLEMENT_DYNAMIC_CLASS (CWidgetDeadline, wxStaticText)

BEGIN_EVENT_TABLE(CWidgetDeadline, wxStaticText)
    EVT_ERASE_BACKGROUND(CWidgetDeadline::OnEraseBackground)
    EVT_PAINT(CWidgetDeadline::OnPaint)
END_EVENT_TABLE()

CWidgetDeadline::CWidgetDeadline() {}

CWidgetDeadline::CWidgetDeadline(wxWindow* parent, wxWindowID id, const wxDateTime& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CWidgetDeadline::Create(wxWindow* parent, wxWindowID id, const wxDateTime& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);

	m_dtValue = value;

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());
    SetLabel(value.Format());

    return bRetVal;
}

wxDateTime CWidgetDeadline::GetValue()
{
    return m_dtValue;
}

void CWidgetDeadline::SetValue(const wxDateTime& value)
{
    if (m_dtValue != value)
    {
        m_dtValue = value;
        wxStaticText::SetLabel(value.Format());
    }
}

void CWidgetDeadline::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.SetFont(GetFont());
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(GetForegroundColour());
    dc.DrawText(GetLabel(), 0, 0);
}

void CWidgetDeadline::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

wxSize CWidgetDeadline::DoGetBestClientSize() const 
{
    return GetTextExtent(GetLabel());
}


IMPLEMENT_DYNAMIC_CLASS (CWidgetElapsed, wxStaticText)

BEGIN_EVENT_TABLE(CWidgetElapsed, wxStaticText)
    EVT_ERASE_BACKGROUND(CWidgetElapsed::OnEraseBackground)
    EVT_PAINT(CWidgetElapsed::OnPaint)
END_EVENT_TABLE()

CWidgetElapsed::CWidgetElapsed() {}

CWidgetElapsed::CWidgetElapsed(wxWindow* parent, wxWindowID id, const wxTimeSpan& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CWidgetElapsed::Create(wxWindow* parent, wxWindowID id, const wxTimeSpan& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);
	
	m_tsValue = value;

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());
	SetLabel(value.Format());

    return bRetVal;
}

wxTimeSpan CWidgetElapsed::GetValue()
{
    return m_tsValue;
}

void CWidgetElapsed::SetValue(const wxTimeSpan& value)
{
    if (m_tsValue != value)
    {
        m_tsValue = value;
        wxStaticText::SetLabel(value.Format());
    }
}

void CWidgetElapsed::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.SetFont(GetFont());
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(GetForegroundColour());
    dc.DrawText(GetLabel(), 0, 0);
}

void CWidgetElapsed::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

wxSize CWidgetElapsed::DoGetBestClientSize() const 
{
    return GetTextExtent(GetLabel());
}


IMPLEMENT_DYNAMIC_CLASS (CWidgetProgress, wxPanel)

BEGIN_EVENT_TABLE(CWidgetProgress, wxPanel)
    EVT_ERASE_BACKGROUND(CWidgetProgress::OnEraseBackground)
    EVT_PAINT(CWidgetProgress::OnPaint)
END_EVENT_TABLE()

CWidgetProgress::CWidgetProgress()
{
    m_dValue = 0.0;
}

CWidgetProgress::CWidgetProgress(wxWindow* parent, wxWindowID id, const wxDouble& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
{
    Create(parent, id, value, pos, size, style, name);
}

bool CWidgetProgress::Create(wxWindow* parent, wxWindowID id, const wxDouble& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
{
    bool bRetVal = wxPanel::Create(parent, id, pos, size, style|wxTRANSPARENT_WINDOW, name);

    m_dValue = value;

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());

    m_strValue.Printf(wxT("%.2f%%"), m_dValue * 100);

    return bRetVal;
}

wxDouble CWidgetProgress::GetValue()
{
    return m_dValue;
}

void CWidgetProgress::SetValue(const wxDouble& value)
{
    if (value >= 100.0)
    {
        if (m_dValue != 100.0)
        {
            m_dValue = 100.0;
            m_strValue = wxT("100%");
            GetParent()->RefreshRect(GetRect(), true);
        }
    }
    else if (m_dValue != value)
    {
        m_dValue = value;
        m_strValue.Printf(wxT("%.2f%%"), m_dValue * 100);
        GetParent()->RefreshRect(GetRect(), true);
    }
}

void CWidgetProgress::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    wxRect r;

    // Initialize surface
    dc.SetBackgroundMode(wxTRANSPARENT);

    // What size is the control?
    r = GetClientRect();

    // Draw Background
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(wxPen(GetForegroundColour()));
    dc.DrawRectangle(r);

    // Draw Progress Bar
    r.Deflate(2,2);
    r.width = std::floor(r.width * m_dValue);

    dc.SetBrush(wxBrush(wxT("LIGHT BLUE"), wxSOLID));
    dc.SetPen(wxPen(wxT("LIGHT BLUE")));
    dc.DrawRectangle(r);

    // What size is the control?
    r = GetClientRect();

    // Draw Label
    dc.SetLogicalFunction(wxINVERT);
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(wxPen(GetForegroundColour()));
    dc.DrawLabel(m_strValue, r, wxALIGN_CENTER);
}

void CWidgetProgress::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

wxSize CWidgetProgress::DoGetBestClientSize() const 
{
    return GetTextExtent(GetLabel());
}


IMPLEMENT_DYNAMIC_CLASS (CWidgetRemaining, wxStaticText)

BEGIN_EVENT_TABLE(CWidgetRemaining, wxStaticText)
    EVT_ERASE_BACKGROUND(CWidgetRemaining::OnEraseBackground)
    EVT_PAINT(CWidgetRemaining::OnPaint)
END_EVENT_TABLE()

CWidgetRemaining::CWidgetRemaining() {}

CWidgetRemaining::CWidgetRemaining(wxWindow* parent, wxWindowID id, const wxTimeSpan& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CWidgetRemaining::Create(wxWindow* parent, wxWindowID id, const wxTimeSpan& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);

	m_tsValue = value;

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());
    SetLabel(value.Format());

    return bRetVal;
}

wxTimeSpan CWidgetRemaining::GetValue()
{
    return m_tsValue;
}

void CWidgetRemaining::SetValue(const wxTimeSpan& value)
{
    if (m_tsValue != value)
    {
        m_tsValue = value;
        wxStaticText::SetLabel(value.Format());
    }
}

void CWidgetRemaining::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.SetFont(GetFont());
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(GetForegroundColour());
    dc.DrawText(GetLabel(), 0, 0);
}

void CWidgetRemaining::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

wxSize CWidgetRemaining::DoGetBestClientSize() const 
{
    return GetTextExtent(GetLabel());
}


IMPLEMENT_DYNAMIC_CLASS (CWidgetTitle, wxPanel)

BEGIN_EVENT_TABLE(CWidgetTitle, wxPanel)
    EVT_ERASE_BACKGROUND(CWidgetTitle::OnEraseBackground)
    EVT_PAINT(CWidgetTitle::OnPaint)
END_EVENT_TABLE()

CWidgetTitle::CWidgetTitle() {}

CWidgetTitle::CWidgetTitle(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, label, pos, size, style, name);
}

bool CWidgetTitle::Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxPanel::Create(parent, id, pos, size, style|wxTRANSPARENT_WINDOW, name);

    wxFont font = GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());
    SetFont(font);
    SetLabel(label);

    return bRetVal;
}

void CWidgetTitle::SetLabel(const wxString& label)
{
    if (GetLabel() != label)
    {
        wxPanel::SetLabel(label);
        Refresh();
    }
}

void CWidgetTitle::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    wxString strLabel = GetLabel();
    wxSize sControl, sText, sEllipsis;

    dc.SetFont(GetFont());
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(GetForegroundColour());

    sControl = GetSize();
    sText = dc.GetTextExtent(strLabel);

    // Adapted from ellipsis code in wxRendererGeneric::DrawHeaderButtonContents()
    if (sText.GetWidth() > sControl.GetWidth())
    {
        sEllipsis = dc.GetTextExtent(wxT("..."));
        if (sEllipsis.GetWidth() > sControl.GetWidth())
        {
            strLabel.Clear();
        }
        else
        {
            do
            {
                strLabel.Truncate(strLabel.length() - 1);
                sText = dc.GetTextExtent(strLabel);
            }
            while ((sText.GetWidth() + sEllipsis.GetWidth() > sControl.GetWidth()) && strLabel.length());
            strLabel.append(wxT("..."));
        }
    }

    dc.DrawText(strLabel, 0, 0);
}

void CWidgetTitle::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

wxSize CWidgetTitle::DoGetBestClientSize() const 
{
    return GetTextExtent(GetLabel());
}


IMPLEMENT_DYNAMIC_CLASS (CWidgetTransferRate, wxStaticText)

BEGIN_EVENT_TABLE(CWidgetTransferRate, wxStaticText)
    EVT_ERASE_BACKGROUND(CWidgetTransferRate::OnEraseBackground)
    EVT_PAINT(CWidgetTransferRate::OnPaint)
END_EVENT_TABLE()

CWidgetTransferRate::CWidgetTransferRate()
{
    m_ullValue = 0;
}

CWidgetTransferRate::CWidgetTransferRate(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, value, pos, size, style, name);
}

bool CWidgetTransferRate::Create(wxWindow* parent, wxWindowID id, const wxUint64& value, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    bool bRetVal = wxStaticText::Create(parent, id, wxT(""), pos, size, style|wxTRANSPARENT_WINDOW, name);

    wxString strBuffer;
    wxDouble xTERA = (1024.0*1024.0*1024.0*1024.0);
    wxDouble xGIGA = (1024.0*1024.0*1024.0);
    wxDouble xMEGA = (1024.0*1024.0);
    wxDouble xKILO = (1024.0);

    m_ullValue = value;

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(parent->GetBackgroundColour());
    SetForegroundColour(parent->GetForegroundColour());

    if (value >= xTERA)
    {
        strBuffer.Printf(wxT("%0.2f TB"), value/xTERA);
    }
    else if (value >= xGIGA)
    {
        strBuffer.Printf(wxT("%0.2f GB"), value/xGIGA);
    }
    else if (value >= xMEGA)
    {
        strBuffer.Printf(wxT("%0.2f MB"), value/xMEGA);
    }
    else if (value >= xKILO)
    {
        strBuffer.Printf(wxT("%0.2f KB"), value/xKILO);
    }
    else
    {
        strBuffer.Printf(wxT("%0.0f bytes"), value);
    }

    wxStaticText::SetLabel(strBuffer);

	return bRetVal;
}

wxUint64 CWidgetTransferRate::GetValue()
{
    return m_ullValue;
}

void CWidgetTransferRate::SetValue(const wxUint64& value)
{
    if (m_ullValue != value)
    {
        m_ullValue = value;

        wxString strBuffer;
        wxDouble xTERA = (1024.0*1024.0*1024.0*1024.0);
        wxDouble xGIGA = (1024.0*1024.0*1024.0);
        wxDouble xMEGA = (1024.0*1024.0);
        wxDouble xKILO = (1024.0);

        if (value >= xTERA)
        {
            strBuffer.Printf(wxT("%0.2f TB"), value/xTERA);
        }
        else if (value >= xGIGA)
        {
            strBuffer.Printf(wxT("%0.2f GB"), value/xGIGA);
        }
        else if (value >= xMEGA)
        {
            strBuffer.Printf(wxT("%0.2f MB"), value/xMEGA);
        }
        else if (value >= xKILO)
        {
            strBuffer.Printf(wxT("%0.2f KB"), value/xKILO);
        }
        else
        {
            strBuffer.Printf(wxT("%0.0f bytes"), value);
        }

        wxStaticText::SetLabel(strBuffer);
    }
}

void CWidgetTransferRate::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    dc.SetFont(GetFont());
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(GetForegroundColour());
    dc.DrawText(GetLabel(), 0, 0);
}

void CWidgetTransferRate::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

wxSize CWidgetTransferRate::DoGetBestClientSize() const 
{
    return GetTextExtent(GetLabel());
}

