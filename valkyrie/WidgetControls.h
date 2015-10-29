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

#ifndef _WIDGETCONTROLS_H_
#define _WIDGETCONTROLS_H_

class CWidgetBitmapButton : public wxBitmapButton
{
    DECLARE_DYNAMIC_CLASS (CWidgetBitmapButton)
    DECLARE_EVENT_TABLE()

public:
    CWidgetBitmapButton();
    CWidgetBitmapButton(
        wxWindow* parent,
        wxWindowID id,
        const wxBitmap& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxButtonNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxBitmap& label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxButtonNameStr
    );

    virtual bool HasTransparentBackground() { return true; };

    virtual void SetBitmapLabel(const wxBitmap& label);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
};

class CWidgetStaticBitmap : public wxStaticBitmap
{
    DECLARE_DYNAMIC_CLASS (CWidgetStaticBitmap)
    DECLARE_EVENT_TABLE()

public:
    CWidgetStaticBitmap();
    CWidgetStaticBitmap(
        wxWindow* parent,
        wxWindowID id,
        const wxBitmap& bitmap,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticBitmapNameStr
    );

    bool Create(
        wxWindow* parent,
        wxWindowID id,
        const wxBitmap& bitmap,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxStaticBitmapNameStr
    );

    virtual bool HasTransparentBackground() { return true; };

    virtual void SetBitmap(const wxBitmap& bitmap);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
};

class CWidgetStaticText : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS (CWidgetStaticText)
    DECLARE_EVENT_TABLE()

public:
    CWidgetStaticText();
    CWidgetStaticText(
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

    virtual bool HasTransparentBackground() { return true; };

    virtual void SetLabel(const wxString& label);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual wxSize DoGetBestClientSize() const; 
};

class CWidgetDeadline : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS (CWidgetDeadline)
    DECLARE_EVENT_TABLE()

public:
    CWidgetDeadline();
    CWidgetDeadline(
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

    virtual bool HasTransparentBackground() { return true; };

    virtual wxDateTime GetValue();
    virtual void SetValue(const wxDateTime& value);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual wxSize DoGetBestClientSize() const; 
private:
    wxDateTime m_dtValue;
};

class CWidgetElapsed : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS (CWidgetElapsed)
    DECLARE_EVENT_TABLE()

public:
    CWidgetElapsed();
    CWidgetElapsed(
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

    virtual bool HasTransparentBackground() { return true; };

    virtual wxTimeSpan GetValue();
    virtual void SetValue(const wxTimeSpan& value);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual wxSize DoGetBestClientSize() const; 
private:
    wxTimeSpan m_tsValue;
};

class CWidgetProgress : public wxPanel
{
    DECLARE_DYNAMIC_CLASS (CWidgetProgress)
    DECLARE_EVENT_TABLE()

public:
    CWidgetProgress();
    CWidgetProgress(
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

    virtual bool HasTransparentBackground() { return true; };

    virtual wxDouble GetValue();
    virtual void SetValue(const wxDouble& value);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual wxSize DoGetBestClientSize() const; 
private:
    wxDouble m_dValue;
    wxString m_strValue;
};

class CWidgetRemaining : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS (CWidgetRemaining)
    DECLARE_EVENT_TABLE()

public:
    CWidgetRemaining();
    CWidgetRemaining(
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

    virtual bool HasTransparentBackground() { return true; };

    virtual wxTimeSpan GetValue();
    virtual void SetValue(const wxTimeSpan& value);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual wxSize DoGetBestClientSize() const; 
private:
    wxTimeSpan m_tsValue;
};

class CWidgetTitle : public wxPanel
{
    DECLARE_DYNAMIC_CLASS (CWidgetText)
    DECLARE_EVENT_TABLE()

public:
    CWidgetTitle();
    CWidgetTitle(
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

    virtual bool HasTransparentBackground() { return true; };

    virtual void SetLabel(const wxString& label);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual wxSize DoGetBestClientSize() const; 
};

class CWidgetTransferRate : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS (CWidgetTransferRate)
    DECLARE_EVENT_TABLE()

public:
    CWidgetTransferRate();
    CWidgetTransferRate(
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

    virtual bool HasTransparentBackground() { return true; };

    virtual wxUint64 GetValue();
    virtual void SetValue(const wxUint64& value);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnEraseBackground(wxEraseEvent& event);
    virtual wxSize DoGetBestClientSize() const; 
private:
    wxUint64 m_ullValue;
};

#endif
