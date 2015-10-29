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

///
/// \defgroup BSLCommon BOINC Sentinels Common Library Interface
/// \{

#ifndef _BSLCOMMONTASK_H_
#define _BSLCOMMONTASK_H_

#define BSLXMLTAGHASH_TASK \
    0x3e7f01e4

class CBSLTask: public CBSLTaskEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLTask)

public:
    CBSLTask();
    virtual ~CBSLTask();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLTask&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLTask&) const;

    /// \brief Initialize CBSLTask state.
    void Clear();

    /// \brief Returns the URL of the project that generated the task.
    wxString& GetProject();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief Returns the application name for the task.
    wxString& GetAppName();
    /// \brief
    wxUint32 GetAppNameHash();
    /// \brief Returns the name of the task.
    wxString& GetName();
    /// \brief
    wxUint32 GetNameHash();
    /// \brief Returns the maximum number of bytes of disk space that can be used by the task.
    wxUint64 GetRuntimeBoundDisk();
    /// \brief Returns the maximum number of FLOPS (Floating Point Operations) that can be used by the task.
    wxUint64 GetRuntimeBoundFLOPS();
    /// \brief Returns the maximum number of bytes of RAM that can be used by the task.
    wxUint64 GetRuntimeBoundMemory();
    /// \brief Returns the estimated number of FLOPS (Floating Point Operations) that can be used by the task.
    wxUint64 GetRuntimeEstimatedFLOPS();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the URL of the project that generated the task.
    void SetProject(wxString strProject);
    /// \brief
    void SetProject(wxString strProject, wxUint32 uiHash);
    /// \brief Sets the application name for the task.
    void SetAppName(wxString strAppName);
    /// \brief Sets the name of the task.
    void SetName(wxString strName);
    /// \brief Sets the maximum number of bytes of disk space that can be used by the task.
    void SetRuntimeBoundDisk(wxUint64 ullRuntimeBoundDisk);
    /// \brief Sets the maximum number of FLOPS (Floating Point Operations) that can be used by the task.
    void SetRuntimeBoundFLOPS(wxUint64 ullRuntimeBoundFLOPS);
    /// \brief Sets the maximum number of bytes of RAM that can be used by the task.
    void SetRuntimeBoundMemory(wxUint64 ullRuntimeBoundMemory);
    /// \brief Returns the estimated number of FLOPS (Floating Point Operations) that can be used by the task.
    void SetRuntimeEstimatedFLOPS(wxUint64 ullRuntimeEstimatedFLOPS);

private:
    wxString m_strProject;
    wxUint32 m_uiProjectHash;
    wxString m_strAppName;
    wxUint32 m_uiAppNameHash;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxUint64 m_ullRuntimeBoundDisk;
    wxUint64 m_ullRuntimeBoundFLOPS;
    wxUint64 m_ullRuntimeBoundMemory;
    wxUint64 m_ullRuntimeEstimatedFLOPS;
};

#endif

///
/// \}
