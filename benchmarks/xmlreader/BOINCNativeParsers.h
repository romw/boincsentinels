// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BOINCNATIVEPARSERS_H_
#define BOINCNATIVEPARSERS_H_


// BOINC XML v1
//
extern bool match_tag(wxChar* buf, const wxChar* tag);
extern bool parse_str(wxChar*, const wxChar*, wxChar*, int);
extern bool parse_int(wxChar* buf, const wxChar* tag, int& x);
extern bool parse_double(wxChar* buf, const wxChar* tag, double& x);
extern bool parse_bool(wxChar*, const wxChar*, bool& x);


// BOINC XML v2
//
class MFILE
{
    wxChar* buf;      // NULL-terminated
    int len;
    FILE* f;
public:
    MFILE();
    ~MFILE();
#if 0
    int open(const wxChar* path, const wxChar* mode);
#endif
    int _putchar(wxChar);
    int puts(const wxChar*);
    int vprintf(const wxChar* format, va_list);
    int printf(const wxChar* format, ...);
    size_t write(const void *, size_t size, size_t nitems);
    int close();
    int flush();
    long tell() const;
    void get_buf(wxChar*&, int&);
        // get the MFILE's internal buffer and its length.
        // The caller assumes ownership of the buffer and must free() it.
        // The MFILE's buffer is set to empty
};

class MIOFILE
{
    MFILE* mf;
    wxChar* wbuf;
    int len;
    const wxChar* buf;
public:
    FILE* f;

    MIOFILE();
    ~MIOFILE();
    void init_mfile(MFILE*);
    void init_file(FILE*);
    void init_buf_read(const wxChar*);
    void init_buf_write(wxChar*, int len);
    int printf(const wxChar* format, ...);
    wxChar* fgets(wxChar*, int);
    wxChar _ungetc(wxChar);
    bool eof();
    inline wxChar _getc() {
        if (f) {
            return _fgettc(f);
        }
        return (*buf)?(*buf++):EOF;
    }
};

class XML_PARSER
{
    bool scan_nonws(wxChar&);
    int scan_comment();
    int scan_tag(wxChar*, int, wxChar* ab=0, int al=0);
    int scan_cdata(wxChar*, int);
    bool copy_until_tag(wxChar*, int);
public:
    wxChar parsed_tag[4096];
    bool is_tag;
    MIOFILE* f;
    XML_PARSER(MIOFILE*);
    void init(MIOFILE* mf) {
        f = mf;
    }
    bool get(wxChar*, int, bool&, wxChar* ab=0, int al=0);
    inline bool get_tag(wxChar* ab=0, int al=0) {
        return get(parsed_tag, sizeof(parsed_tag), is_tag, ab, al);
    }
    inline bool match_tag(const wxChar* tag) {
        return !_tcscmp(parsed_tag, tag);
    }
    int get_aux(wxChar* buf, int len, wxChar* attr_buf, int attr_len);
    bool parse_start(const wxChar*);
    bool parse_str(const wxChar*, wxChar*, int);
    bool parse_string(const wxChar*, std::wstring&);
    bool parse_int(const wxChar*, int&);
    bool parse_double(const wxChar*, double&);
    bool parse_ulong(const wxChar*, unsigned long&);
    bool parse_ulonglong(const wxChar*, unsigned long long&);
    bool parse_bool(const wxChar*, bool&);
    int element_contents(const wxChar*, wxChar*, int);
    int copy_element(std::wstring&);
    void skip_unexpected(const wxChar*, bool verbose, const wxChar*);
    void skip_unexpected(bool verbose=false, const wxChar* msg=wxT(""));
};


#endif /* BOINCNATIVEPARSERS_H_ */
