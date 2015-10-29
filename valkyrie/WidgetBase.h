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

#ifndef _WIDGETBASE_H_
#define _WIDGETBASE_H_

// Forward Declare
class CSkinManager;
class CWidgetBitmapButton;
class CWidgetStaticText;
class CWidgetStaticBitmap;
class CWidgetTitle;

class CWidgetBase: public wxPanel
{
    DECLARE_DYNAMIC_CLASS(CWidgetBase)
    DECLARE_EVENT_TABLE()

public:
    CWidgetBase();
    CWidgetBase(wxWindow* pParent, wxWindowID iWindowID, wxString strWidgetName = wxEmptyString);
    ~CWidgetBase();

    void OnWidgetBaseInit(wxCommandEvent& event);
    void OnWidgetBaseShowContents(wxCommandEvent& event);
    void OnWidgetBasePaint(wxPaintEvent& event);

    wxString& GetWidgetName();
    void SetWidgetName(wxString strWidgetName);

    virtual bool Show(bool show = true);
    virtual bool ShowContents(bool show = true);
    virtual bool IsShown() const;
    virtual bool IsContentsShown() const;

protected:
    virtual bool CreateControls(bool bEnableContents, bool bShowContents, bool bEnableButtonBar);
    virtual bool OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);
    virtual bool OnCreateContent(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);

    virtual bool UpdateHeaderLayout();

private:
    wxString m_strWidgetName;
    bool m_bInitialized;
    bool m_bVisible;
    bool m_bContentsEnabled;
    bool m_bShowContents;

    wxWindow* m_pParent;

    wxFlexGridSizer* m_pWidgetBaseSizer;
    wxPanel* m_pHeader;
    wxFlexGridSizer* m_pHeaderSizer;
    wxPanel* m_pChevronBar;
    wxFlexGridSizer* m_pChevronBarSizer;
    CWidgetBitmapButton* m_pChevronExpandedCtrl;
    CWidgetBitmapButton* m_pChevronCollapsedCtrl;
    CWidgetTitle* m_pNameCtrl;
    wxPanel* m_pWidgetBaseButtonBar;
    wxPanel* m_pWidgetBaseContents;
};


BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_WIDGETBASE_INIT, 10100 )
DECLARE_EVENT_TYPE( wxEVT_WIDGETBASE_RECALCSIZE, 10101 )
DECLARE_EVENT_TYPE( wxEVT_WIDGETBASE_SHOWCONTENTS, 10102 )
DECLARE_EVENT_TYPE( wxEVT_WIDGETBASE_HIDECONTENTS, 10103 )
END_DECLARE_EVENT_TYPES()

#define EVT_WIDGETBASE_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETBASE_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),
#define EVT_WIDGETBASE_RECALCSIZE(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETBASE_RECALCSIZE, -1, -1, (wxObjectEventFunction) (wxEventFunction) static_cast<wxCommandEventFunction>(&fn), NULL),
#define EVT_WIDGETBASE_SHOWCONTENTS(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETBASE_SHOWCONTENTS, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),
#define EVT_WIDGETBASE_HIDECONTENTS(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETBASE_HIDECONTENTS, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif
