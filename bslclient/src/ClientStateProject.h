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
/// \defgroup LibraryState Library State
/// \{

#ifndef _CLIENTSTATEPROJECT_H_
#define _CLIENTSTATEPROJECT_H_

class CProject: public CObject, public CBSLProject
{
    DECLARE_DYNAMIC_CLASS(CProject)

public:
    CProject();
    CProject(const CBSLProject&);
    virtual ~CProject();

    /// \brief Assignment Operator
    virtual CProject& operator= (const CBSLProject&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLProject&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLProject&);

    /// \brief Add a application to the host.
    /// \param[in] pProjectStatistic A pointer to the application to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddProjectStatistic(CProjectStatistic* pProjectStatistic);

    /// \brief Delete a application from the host.
    /// \param[in] pProjectStatistic A pointer to the application to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteProjectStatistic(CProjectStatistic* pProjectStatistic);

    /// \brief Retrieve all the applications.
    /// \param[out] oProjectStatistics a vector containing all the applications.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateProjectStatistics(std::vector<CProjectStatistic*>& oProjectStatistics);

    /// \brief Find an application pointer for a given unique application key.
    /// \param[in] dtTimestamp the application key to find.
    /// \param[out] ppProjectStatistic a pointer to the desired application.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindProjectStatistic(
        wxDateTime dtTimestamp,
        CProjectStatistic** ppProjectStatistic,
        CBSLProjectStatistic* pProjectStatistic = NULL
    );

    virtual void Dispose();

	BSLERRCODE Update(CBSLProject&);

private:
    CDatabase<CProjectStatistic*>* m_pProjectStatisticsDatabase;
};


class CProjectIndex
{
public:
    CProjectIndex();
    CProjectIndex(CProject* pProject);
    CProjectIndex(wxUint32 uiMasterURLHash);
    virtual ~CProjectIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CProjectIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CProjectIndex&);

    /// \brief
    CProject* GetRecord();
    /// \brief
    wxUint32 GetMasterURLHash();

private:
    CProject* m_pProject;
    wxUint32 m_uiMasterURLHash;
};

#endif

///
/// \}
