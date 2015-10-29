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

#ifndef _DATABASE_H_
#define _DATABASE_H_

template<class EntryType>
class CDatabase
{
public:
    typedef typename std::vector<EntryType>::iterator vecIt;

    CDatabase()
    {
        m_pLocker = new wxCriticalSection();
        wxASSERT(m_pLocker);
    }

    ~CDatabase()
    {
        m_pLocker->Enter();
        for (vecIt iter = m_Database.begin(); iter != m_Database.end(); ++iter)
        {
            EntryType pEntry = (EntryType) *iter;
            delete pEntry;
        }
        m_Database.clear();
        m_pLocker->Leave();

        delete m_pLocker;
        m_pLocker = NULL;
    }

    BSLERRCODE Add(EntryType pEntry)
    {
        m_pLocker->Enter();
        m_Database.push_back(pEntry);
        m_pLocker->Leave();
        return BSLERR_SUCCESS;
    }

    BSLERRCODE Delete(EntryType pEntry)
    {
        m_pLocker->Enter();
        vecIt iter = m_Database.begin();
        while (iter != m_Database.end())
        {
            EntryType pCurrentRecord = (EntryType) *iter;
            if (pCurrentRecord == pEntry)
            {
                pCurrentRecord->Dispose();
                iter = m_Database.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        m_pLocker->Leave();
        return BSLERR_SUCCESS;
    }

    BSLERRCODE Enumerate(std::vector<EntryType>& oEntries)
    {
        m_pLocker->Enter();
        oEntries.reserve(m_Database.size());
        for (vecIt iter = m_Database.begin(); iter != m_Database.end(); ++iter)
        {
            oEntries.push_back(*iter);
        }
        m_pLocker->Leave();
        return BSLERR_SUCCESS;
    }

    BSLERRCODE Lock()
    {
        m_pLocker->Enter();
        return BSLERR_SUCCESS;
    }

    BSLERRCODE Unlock()
    {
        m_pLocker->Leave();
        return BSLERR_SUCCESS;
    }

    std::vector<EntryType> m_Database;
    wxCriticalSection* m_pLocker;
};


template<class IndexType, class EntryType, class BSLBasicType>
class CDatabaseIndexed
{
public:
    typedef typename std::vector<IndexType>::iterator vecIt;

    CDatabaseIndexed()
    {
        m_pLocker = new wxCriticalSection();
        wxASSERT(m_pLocker);
    }

    ~CDatabaseIndexed()
    {
        m_pLocker->Enter();
        vecIt iter = m_Database.begin();
        while (iter != m_Database.end())
        {
            delete ((IndexType)*iter).GetRecord();
            iter++;
        }
        m_Database.clear();
        m_pLocker->Leave();

        delete m_pLocker;
        m_pLocker = NULL;
    }

    BSLERRCODE Add(IndexType oEntry)
    {
        m_pLocker->Enter();
        m_Database.push_back(oEntry);
        m_pLocker->Leave();
        return BSLERR_SUCCESS;
    }

    BSLERRCODE Delete(IndexType oEntry)
    {
        IndexType idxRecord;

        m_pLocker->Enter();
        vecIt iter = m_Database.begin();
        while (iter != m_Database.end())
        {
            idxRecord = (IndexType)*iter;
            if (idxRecord == oEntry)
            {
                delete idxRecord.GetRecord();
                iter = m_Database.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        m_pLocker->Leave();
        return BSLERR_SUCCESS;
    }

    BSLERRCODE Enumerate(std::vector<EntryType>& oEntries)
    {
        IndexType idxRecord;

        m_pLocker->Enter();
        oEntries.reserve(m_Database.size());
        for (vecIt iter = m_Database.begin(); iter != m_Database.end(); ++iter)
        {
            idxRecord = (IndexType)*iter;
            oEntries.push_back(idxRecord.GetRecord());
        }
        m_pLocker->Leave();
        return BSLERR_SUCCESS;
    }

    BSLERRCODE Find(IndexType oEntry, EntryType* ppEntry, BSLBasicType pBSLBasicType)
    {
        BSLERRCODE rc = BSLERR_OBJECT_NOT_FOUND;
        IndexType idxRecord;

        *ppEntry = NULL;

        m_pLocker->Enter();
        for (vecIt iter = m_Database.begin(); iter != m_Database.end(); ++iter)
        {
            idxRecord = (IndexType)*iter;
            if (idxRecord == oEntry)
            {
                *ppEntry = idxRecord.GetRecord();
                rc = BSLERR_SUCCESS;

                break;
            }
        }

        if (*ppEntry && pBSLBasicType)
        {
            CObjectLocker olLock(*ppEntry);
            *pBSLBasicType = **ppEntry;
        }
        m_pLocker->Leave();

        return rc;
    }

    std::vector<IndexType> m_Database;
    wxCriticalSection* m_pLocker;
};

#endif

///
/// \}
