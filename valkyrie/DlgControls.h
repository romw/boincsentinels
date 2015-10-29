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

#ifndef _DLGCONTROLS_H_
#define _DLGCONTROLS_H_

class CDlgStaticText : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgStaticText)
    DECLARE_EVENT_TABLE()

public:
    CDlgStaticText();
    CDlgStaticText(
        wxWindow* parent,
        wxWindowID id,
        const wxString& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxString& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual void SetLabel(const wxString& label);
};

class CDlgDateTime : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgDeadline)
    DECLARE_EVENT_TABLE()

public:
    CDlgDateTime();
    CDlgDateTime(
        wxWindow* parent,
        wxWindowID id,
        const wxDateTime& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxDateTime& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual wxDateTime GetValue();
    virtual void SetValue(const wxDateTime& value);
private:
    wxDateTime m_dtValue;
};

class CDlgTimeSpan : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgTimeSpan)
    DECLARE_EVENT_TABLE()

public:
    CDlgTimeSpan();
    CDlgTimeSpan(
        wxWindow* parent,
        wxWindowID id,
        const wxTimeSpan& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxTimeSpan& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual wxTimeSpan GetValue();
    virtual void SetValue(const wxTimeSpan& value);
private:
    wxTimeSpan m_tsValue;
};

class CDlgUint32 : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgUint32)
    DECLARE_EVENT_TABLE()

public:
    CDlgUint32();
    CDlgUint32(
        wxWindow* parent,
        wxWindowID id,
        const wxUint32& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxUint32& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual wxUint32 GetValue();
    virtual void SetValue(const wxUint32& value);
private:
    wxUint32 m_ulValue;
};

class CDlgProgress : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgProgress)
    DECLARE_EVENT_TABLE()

public:
    CDlgProgress();
    CDlgProgress(
        wxWindow* parent,
        wxWindowID id,
        const wxDouble& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxDouble& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual wxDouble GetValue();
    virtual void SetValue(const wxDouble& value);
private:
    wxDouble m_dValue;
};

class CDlgByteCount : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgByteCount)
    DECLARE_EVENT_TABLE()

public:
    CDlgByteCount();
    CDlgByteCount(
        wxWindow* parent,
        wxWindowID id,
        const wxUint64& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxUint64& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual wxUint64 GetValue();
    virtual wxUint64 GetTotal();
    virtual void SetValue(const wxUint64& value);
    virtual void SetTotal(const wxUint64& value);
private:
    wxUint64 m_ullValue;
    wxUint64 m_ullTotal;
};

class CDlgByteRate : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgByteRate)
    DECLARE_EVENT_TABLE()

public:
    CDlgByteRate();
    CDlgByteRate(
        wxWindow* parent,
        wxWindowID id,
        const wxUint64& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxUint64& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual wxUint64 GetValue();
    virtual void SetValue(const wxUint64& value);
private:
    wxUint64 m_ullValue;
};

class CDlgFLOPCount : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(CDlgFLOPCount)
    DECLARE_EVENT_TABLE()

public:
    CDlgFLOPCount();
    CDlgFLOPCount(
        wxWindow* parent,
        wxWindowID id,
        const wxUint64& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxUint64& value,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticTextNameStr
    );

    virtual wxUint64 GetValue();
    virtual void SetValue(const wxUint64& value);
private:
    wxUint64 m_ullValue;
};

#endif
