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

#ifndef _BSLCOMMONPROJECTSTATISTIC_H_
#define _BSLCOMMONPROJECTSTATISTIC_H_

#define BSLXMLTAGHASH_PROJECTSTATISTIC \
    0x33be5a8a

class CBSLProjectStatistic: public CBSLProjectStatisticEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLProjectStatistic)

public:
    CBSLProjectStatistic();
    virtual ~CBSLProjectStatistic();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLProjectStatistic&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLProjectStatistic&) const;

    /// \brief Initialize CBSLProjectStatistic state.
    void Clear();

    /// \brief Returns the hosts average credit for a given day.
    wxDouble GetCreditHostAverage();
    /// \brief Returns the hosts total credit for a given day.
    wxDouble GetCreditHostTotal();
    /// \brief Returns the users average credit for a given day.
    wxDouble GetCreditUserAverage();
    /// \brief Returns the users total credit for a given day.
    wxDouble GetCreditUserTotal();
    /// \brief Returns the time stamp of the statistic.
    wxDateTime& GetTimestamp();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the hosts average credit for a given day.
    void SetCreditHostAverage(wxDouble dCreditHostAverage);
    /// \brief Sets the hosts total credit for a given day.
    void SetCreditHostTotal(wxDouble dCreditHostTotal);
    /// \brief Sets the users average credit for a given day.
    void SetCreditUserAverage(wxDouble dCreditUserAverage);
    /// \brief Sets the users total credit for a given day.
    void SetCreditUserTotal(wxDouble dCreditUserTotal);
    /// \brief Sets the time stamp of the statistic.
    void SetTimestamp(wxDateTime dtTimestamp);

private:
    wxDouble m_dCreditHostAverage;
    wxDouble m_dCreditHostTotal;
    wxDouble m_dCreditUserAverage;
    wxDouble m_dCreditUserTotal;
    wxDateTime m_dtTimestamp;
};

#endif

///
/// \}
