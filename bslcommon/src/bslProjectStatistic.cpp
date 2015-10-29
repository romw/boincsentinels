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
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"

IMPLEMENT_DYNAMIC_CLASS(CBSLProjectStatistic, CBSLProjectStatisticEventData);

CBSLProjectStatistic::CBSLProjectStatistic() :
CBSLProjectStatisticEventData()
{
    Clear();
}

CBSLProjectStatistic::~CBSLProjectStatistic()
{
}

bool CBSLProjectStatistic::operator== (const CBSLProjectStatistic& bslProjectStatistic) const
{
    if (m_dCreditHostAverage != bslProjectStatistic.m_dCreditHostAverage) return false;
    if (m_dCreditHostTotal != bslProjectStatistic.m_dCreditHostTotal) return false;
    if (m_dCreditUserAverage != bslProjectStatistic.m_dCreditUserAverage) return false;
    if (m_dCreditUserTotal != bslProjectStatistic.m_dCreditUserTotal) return false;
    if (m_dtTimestamp != bslProjectStatistic.m_dtTimestamp) return false;
    return true;
}

bool CBSLProjectStatistic::operator!= (const CBSLProjectStatistic& bslProjectStatistic) const
{
    return !(*this == bslProjectStatistic);
}

void CBSLProjectStatistic::Clear()
{
    m_dCreditHostAverage = 0.0;
    m_dCreditHostTotal = 0.0;
    m_dCreditUserAverage = 0.0;
    m_dCreditUserTotal = 0.0;
    m_dtTimestamp = wxDateTime((time_t)0);
}

wxDouble CBSLProjectStatistic::GetCreditHostAverage()
{
    return m_dCreditHostAverage;
}

wxDouble CBSLProjectStatistic::GetCreditHostTotal()
{
    return m_dCreditHostTotal;
}

wxDouble CBSLProjectStatistic::GetCreditUserAverage()
{
    return m_dCreditUserAverage;
}

wxDouble CBSLProjectStatistic::GetCreditUserTotal()
{
    return m_dCreditUserTotal;
}

wxDateTime& CBSLProjectStatistic::GetTimestamp()
{
    return m_dtTimestamp;
}

BSLERRCODE CBSLProjectStatistic::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECTSTATISTIC == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0x12952639:    // day
                m_dtTimestamp = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0x511c9d55:    // user_total_credit
                m_dCreditUserTotal = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                break;
            case 0xdab7f530:    // user_expavg_credit
                m_dCreditUserAverage = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                break;
            case 0x018aff20:    // host_total_credit
                m_dCreditHostTotal = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                break;
            case 0xd105bfe3:    // host_expavg_credit
                m_dCreditHostAverage = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLProjectStatistic::ParseEx: Hash: '0x%x', Name: '%s'"),
                    oElement.GetNameHash(),
                    oElement.GetName()
                );
#endif
                if (CBSLXMLElementEx::ElementTypeContainer == oElement.GetType())
                {
                    oDocument.SkipContainer(oElement);
                }
                break;
        }
    }

    return BSLERR_SUCCESS;
}

void CBSLProjectStatistic::SetCreditHostAverage(wxDouble dCreditHostAverage)
{
    m_dCreditHostAverage = dCreditHostAverage;
}

void CBSLProjectStatistic::SetCreditHostTotal(wxDouble dCreditHostTotal)
{
    m_dCreditHostTotal = dCreditHostTotal;
}

void CBSLProjectStatistic::SetCreditUserAverage(wxDouble dCreditUserAverage)
{
    m_dCreditUserAverage = dCreditUserAverage;
}

void CBSLProjectStatistic::SetCreditUserTotal(wxDouble dCreditUserTotal)
{
    m_dCreditUserTotal = dCreditUserTotal;
}

void CBSLProjectStatistic::SetTimestamp(wxDateTime dtTimestamp)
{
    m_dtTimestamp = dtTimestamp;
}
