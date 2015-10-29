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

#include "stdwx.h"
#include "BOINCNativeParsers.h"

#if   defined(_WIN32) && !defined(__MINGW32__)
static __inline int _swprintf(wchar_t * _String, size_t _Count, const wchar_t * _Format, ...)
{
    va_list _Arglist;
    int _Ret;
    _crt_va_start(_Arglist, _Format);
    _Ret = _vswprintf_c_l(_String, _Count, _Format, NULL, _Arglist);
    _crt_va_end(_Arglist);
    return _Ret;
}
#elif defined(_WIN32) && defined(__MINGW32__)
static __inline int swprintf(wchar_t * _String, size_t _Count, const wchar_t * _Format, ...)
{
    int retval;
    va_list va;
    va_start(va, _Format);
    retval = swprintf(_String, _Format, va);
    va_end(va);
    return retval;
}
#endif

// version of strcpy that works even if strings overlap (p < q)
//
void strcpy_overlap(wxChar* p, const wxChar* q) {
    while (1) {
        *p++ = *q;
        if (!*q) break;
        q++;
    }
}

// return true if the tag appears in the line
//
bool match_tag(wxChar* buf, const wxChar* tag)
{
    if (_tcsstr(buf, tag))
        return true;
    return false;
}

// parse an integer of the form <tag>1234</tag>
// return true if it's there
// Note: this doesn't check for the end tag
//
bool parse_int(wxChar* buf, const wxChar* tag, int& x)
{
    const wxChar* p = _tcsstr(buf, tag);
    if (!p)
        return false;
    int y = _tcstol(p + _tcslen(tag), 0, 0); // this parses 0xabcd correctly
    if (errno == ERANGE)
        return false;
    x = y;
    return true;
}

// Same, for doubles
//
bool parse_double(wxChar* buf, const wxChar* tag, double& x)
{
    double y;
    const wxChar* p = _tcsstr(buf, tag);
    if (!p)
        return false;
    y = _tstof(p+_tcslen(tag));
    x = y;
    return true;
}

// Parse a boolean; tag is of form "foobar"
// Accept either <foobar/>, <foobar />, or <foobar>0|1</foobar>
// (possibly with leading/trailing white space)
//
bool parse_bool(wxChar* buf, const wxChar* tag, bool& result)
{
    wxChar tag2[256], tag3[256];
    int x;

    // quick check to reject most cases
    //
    if (!_tcsstr(buf, tag))
    {
        return false;
    }
    _stprintf(tag2, sizeof(tag2), wxT("<%s/>"), tag);
    _stprintf(tag3, sizeof(tag3), wxT("<%s />"), tag);
    if (match_tag(buf, tag2) || match_tag(buf, tag3))
    {
        result = true;
        return true;
    }
    _stprintf(tag2, sizeof(tag2), wxT("<%s>"), tag);
    if (parse_int(buf, tag2, x))
    {
        result = (x != 0);
        return true;
    }
    return false;
}

// parse a string of the form ...<tag attrs>string</tag>...;
// returns the "string" part.
// Does XML unescaping (replace &lt; with <)
// "string" may not include '<'
// Strips white space from ends.
// Use "<tag", not "<tag>", if there might be attributes
//
bool parse_str(wxChar* buf, const wxChar* tag, wxChar* dest, int destlen)
{
    const wxChar* p;
    int len;

    p = _tcsstr(buf, tag);
    if (!p)
        return false;
    p = _tcschr(p, '>');
    p++;
    const wxChar* q = _tcschr(p, '<');
    if (!q)
        return false;
    len = (int) (q - p);
    if (len >= destlen)
        len = destlen - 1;
    _tcsncpy(dest, p, len);
    return true;
}

// we got an unrecognized line.
// If it has two <'s (e.g. <foo>xx</foo>) return 0.
// If it's of the form <foo/> return 0.
// If it's of the form <foo> then scan for </foo> and return 0.
// Otherwise return ERR_XML_PARSE
//
int skip_unrecognized(wxChar* buf, MIOFILE& fin) {
    wxChar* p, *q, buf2[256];
    std::wstring close_tag;

    p = _tcschr(buf, wxT('<'));
    if (!p) {
        return -112;
    }
    if (_tcschr(p+1, wxT('<'))) {
        return 0;
    }
    q = _tcschr(p+1, wxT('>'));
    if (!q) {
        return -112;
    }
    if (q[-1] == '/') return 0;
    *q = 0;
    close_tag = std::wstring(wxT("</")) + std::wstring(p+1) + std::wstring(wxT(">"));
    while (fin.fgets(buf2, 256)) {
        if (_tcsstr(buf2, close_tag.c_str())) {
            return 0;
        }
    }
    return -112;
}

// remove whitespace from start and end of a string
//
void strip_whitespace(wxChar *str) {
    size_t n;
    while (1) {
        if (!str[0]) break;
        if (!_istascii(str[0])) break;
        if (!_istspace(str[0])) break;
        strcpy_overlap(str, str+1);
    }
    while (1) {
        n = _tcslen(str);
        if (n == 0) break;
        if (!_istascii(str[n-1])) break;
        if (!_istspace(str[n-1])) break;
        str[n-1] = 0;
    }
}

// NOTE: these used to take std::wstring instead of char* args.
// But this performed poorly.
//
// NOTE: output buffer should be 6X size of input
//
void xml_escape(const wxChar* in, wxChar* out, int len) {
    wxChar buf[256], *p;
    p = out;
    for (; *in; in++) {
        wxChar x = *in;
        x &= 0xff;   // just in case
        if (x == wxT('<')) {
            _tcscpy(p, wxT("&lt;"));
            p += 4;
        } else if (x == wxT('&')) {
            _tcscpy(p, wxT("&amp;"));
            p += 5;
        } else if (x>127) {
            _stprintf(buf, sizeof(buf), wxT("&#%d;"), x);
            _tcscpy(p, buf);
            p += _tcslen(buf);
        } else if (x<32) {
            switch(x) {
            case 9:
            case 10:
            case 13:
                _stprintf(buf, sizeof(buf), wxT("&#%d;"), x);
                _tcscpy(p, buf);
                p += _tcslen(buf);
                break;
            }
        } else {
            *p++ = x;
        }
        if (p > out + len - 8) break;
    }
    *p = 0;
}

void xml_unescape(wxChar* buf) {
    wxChar* out = buf;
    wxChar* in = buf;
    while (*in) {
        if (*in != '&') {       // avoid strncmp's if possible
            *out++ = *in++;
        } else if (!_tcsncmp(in, wxT("&lt;"), 4)) {
            *out++ = wxT('<');
            in += 4;
        } else if (!_tcsncmp(in, wxT("&gt;"), 4)) {
            *out++ = wxT('>');
            in += 4;
        } else if (!_tcsncmp(in, wxT("&quot;"), 4)) {
            *out++ = wxT('"');
            in += 6;
        } else if (!_tcsncmp(in, wxT("&apos;"), 4)) {
            *out++ = wxT('\'');
            in += 6;
        } else if (!_tcsncmp(in, wxT("&amp;"), 5)) {
            *out++ = wxT('&');
            in += 5;
        } else if (!_tcsncmp(in, wxT("&#"), 2)) {
            in += 2;
            wxChar c = _ttoi(in);
            *out++ = c;
            in = _tcschr(in, wxT(';'));
            if (in) in++;
        } else {
            *out++ = *in++;
        }
    }
    *out = 0;
}

// Note: XML unescaping never increases string length
//
void xml_unescape(std::wstring& in) {
    size_t n = in.size()+1;
    wxChar* buf = (wxChar*)malloc(n*sizeof(wxChar));
    _tcscpy(buf, in.c_str());
    xml_unescape(buf);
    in = buf;
    free(buf);
}

MFILE::MFILE() {
    buf = (wxChar*)malloc(64*1024);
    len = 0;
}

MFILE::~MFILE() {
    if (buf) free(buf);
    if (f) fclose(f);
}

#if 0
int MFILE::open(const wxChar* path, const wxChar* mode) {
    f = _tfopen(path, mode);
    if (!f) return -108;
    if (!buf) buf = (wxChar*)malloc(64*1024);
    return 0;
}
#endif

// seems like Win's realloc is stupid,  Make it smart.
//
static inline wxChar* realloc_aux(wxChar* p, size_t len) {
    if (!p) {
        return (wxChar*)malloc(64*1024);
    }
#ifdef _WIN32
    return (wxChar*) realloc(p, len*2*sizeof(wxChar));
#else
    return (wxChar*) realloc(p, len*sizeof(wxChar));
#endif
}

#define BUFSIZE 100000

int MFILE::vprintf(const wxChar* format, va_list ap) {
    wxChar buf2[BUFSIZE];
    int n, k;

    k = _vsntprintf(buf2, BUFSIZE, format, ap);
    if (k<=-1 || k>=BUFSIZE) {
        _ftprintf(stderr, wxT("ERROR: buffer too small in MFILE::vprintf()\n"));
        _ftprintf(stderr, wxT("ERROR: format: %s\n"), format);
        _ftprintf(stderr, wxT("ERROR: k=%d, BUFSIZE=%d\n"), k, BUFSIZE);
        return -1;
    }
    n = (int)_tcslen(buf2);
    buf = (wxChar*)realloc_aux(buf, len+n+1);
    if (!buf) {
        _ftprintf(stderr, wxT("ERROR: realloc() failed in MFILE::vprintf()\n"));
        exit(1);
    }
    _tcsncpy(buf+len, buf2, n);
    len += n;
    buf[len] = 0;
    return k;
}

int MFILE::printf(const wxChar* format, ...) {
    int n;
    va_list ap;

    va_start(ap, format);
    n = MFILE::vprintf(format, ap);
    va_end(ap);
    return n;
}

size_t MFILE::write(const void *ptr, size_t size, size_t nitems) {
    buf = (wxChar*)realloc_aux( buf, len+(size*nitems)+1 );
    if (!buf) {
        _ftprintf(stderr, wxT("ERROR: realloc() failed in MFILE::write()\n"));
        exit(1);
    }
    memcpy( buf+len, ptr, size*nitems );
    len += (int)size*(int)nitems;
    buf[len] = 0;
    return nitems;
}

int MFILE::_putchar(wxChar c) {
    buf = (wxChar*)realloc_aux(buf, len+1+1);
    if (!buf) {
        _ftprintf(stderr, wxT("ERROR: realloc() failed in MFILE::_putchar()\n"));
        exit(1);
    }
    buf[len] = c;
    len++;
    buf[len] = 0;
    return c;
}

int MFILE::puts(const wxChar* p) {
    int n = (int)_tcslen(p);
    buf = (wxChar*)realloc_aux(buf, len+n+1);
    if (!buf) {
        _ftprintf(stderr, wxT("ERROR: realloc() failed in MFILE::puts()\n"));
        exit(1);
    }
    _tcsncpy(buf+len, p, n);
    len += n;
    buf[len] = 0;
    return n;
}

int MFILE::close() {
    int retval = 0;
    if (f) {
        flush();
        fclose(f);
        f = NULL;
    }
    if (buf) {
        free(buf);
        buf = NULL;
    }
    return retval;
}

int MFILE::flush() {
    int n, old_len = len;

    n = (int)fwrite(buf, 1, len, f);
    len = 0;
    if (n != old_len) return -105;
    if (fflush(f)) return -216;
#ifndef _WIN32
    if (fsync(fileno(f)) < 0) return -217;
#endif
    return 0;
}

long MFILE::tell() const {
    return f ? ftell(f) : -1;
}

void MFILE::get_buf(wxChar*& b, int& l) {
    b = buf;
    l = len;
    buf = 0;
    len = 0;
}

MIOFILE::MIOFILE() {
    mf = 0;
    f = 0;
    buf = 0;
}

MIOFILE::~MIOFILE() {
}

void MIOFILE::init_mfile(MFILE* _mf) {
    mf = _mf;
}

void MIOFILE::init_file(FILE* _f) {
    f = _f;
}

void MIOFILE::init_buf_read(const wxChar* _buf) {
    buf = _buf;
}

void MIOFILE::init_buf_write(wxChar* _buf, int _len) {
    wbuf = _buf;
    len = _len;
    wbuf[0] = 0;
}

bool MIOFILE::eof() {
    if (f) {
        if (!feof(f)) {
            return false;
        }
    }
    return true;
}

int MIOFILE::printf(const wxChar* format, ...) {
    int retval;

    va_list ap;
    va_start(ap, format);
    if (mf) {
        retval = mf->vprintf(format, ap);
    } else if (f) {
        retval = _vftprintf(f, format, ap);
    } else {
        size_t cursize = _tcslen(wbuf);
        size_t remaining_len = len - cursize;
        retval = _vsntprintf(wbuf+cursize, remaining_len, format, ap);
    }
    va_end(ap);
    return retval;
}

wxChar* MIOFILE::fgets(wxChar* dst, int dst_len) {
    if (f) {
        return ::_fgetts(dst, dst_len, f);
    }
    const wxChar* q = _tcschr(buf, '\n');
    if (!q) return 0;

    q++;
    int n = (int)(q - buf);
    if (n > dst_len-1) n = dst_len-1;
    memcpy(dst, buf, n*sizeof(wxChar));
    dst[n] = 0;

    buf = q;
    return dst;
}

wxChar MIOFILE::_ungetc(wxChar c) {
    if (f) {
        return _ungettc(c, f);
    } else {
        buf--;
        // NOTE: we assume that the char being pushed
        // is what's already there
        //*buf = c;
    }
    return c;
}

XML_PARSER::XML_PARSER(MIOFILE* _f) {
    f = _f;
}

// read until find non-whitespace char.
// Return the char in the reference param
// Return true iff reached EOF
//
bool XML_PARSER::scan_nonws(wxChar& first_char) {
    wxChar c;
    while (1) {
        c = f->_getc();
        if ((char)c == EOF) return true;
        wxUint32 uc = c;
        if (_istspace(uc)) continue;
        first_char = c;
        return false;
    }
    return false;
}

#define XML_PARSE_COMMENT   1
#define XML_PARSE_EOF       2
#define XML_PARSE_CDATA     3
#define XML_PARSE_TAG       4
#define XML_PARSE_DATA      5

int XML_PARSER::scan_comment() {
    wxChar buf[256];
    wxChar* p = buf;
    while (1) {
        wxChar c = f->_getc();
        if ((char)c == EOF) return XML_PARSE_EOF;
        *p++ = c;
        *p = 0;
        if (_tcsstr(buf, wxT("-->"))) {
            return XML_PARSE_COMMENT;
        }
        if (_tcslen(buf) > 32) {
            strcpy_overlap(buf, buf+16);
            p -= 16;
        }
    }
    return 0;
}

int XML_PARSER::scan_cdata(wxChar* buf, int len) {
    wxChar* p = buf;
    len--;
    while (1) {
        wxChar c = f->_getc();
        if ((char)c == EOF) return XML_PARSE_EOF;
        if (len) {
            *p++ = c;
            len--;
        }
        if (c == '>') {
            *p = 0;
            wxChar* q = _tcsstr(buf, wxT("]]>"));
            if (q) {
                *q = 0;
                return XML_PARSE_CDATA;
            }
        }
    }
    return 0;
}

// we just read a <; read until we find a >.
// Given <tag [attr=val attr=val] [/]>:
// - copy tag (or tag/) to buf
// - copy "attr=val attr=val" to attr_buf
//
// Return either
// XML_PARSE_TAG
// XML_PARSE_COMMENT
// XML_PARSE_EOF
// XML_PARSE_CDATA
//
int XML_PARSER::scan_tag(
    wxChar* buf, int _tag_len, wxChar* attr_buf, int attr_len
) {
    wxInt32 c;
    wxChar* buf_start = buf;
    bool found_space = false;
    int tag_len = _tag_len;

    for (int i=0; ; i++) {
        c = f->_getc();
        if ((char)c == EOF) return XML_PARSE_EOF;
        if (c == wxT('>')) {
            *buf = 0;
            if (attr_buf) *attr_buf = 0;
            return XML_PARSE_TAG;
        }
        if (_istspace(c)) {
            if (found_space && attr_buf) {
                if (--attr_len > 0) {
                    *attr_buf++ = c;
                }
            }
            found_space = true;
        } else if (c == wxT('/')) {
            if (--tag_len > 0) {
                *buf++ = c;
            }
        } else {
            if (found_space) {
                if (attr_buf) {
                    if (--attr_len > 0) {
                        *attr_buf++ = c;
                    }
                }
            } else {
                if (--tag_len > 0) {
                    *buf++ = c;
                }
            }
        }

        // check for comment start
        //
        if (i==2 && !_tcsncmp(buf_start, wxT("!--"), 3)) {
            return scan_comment();
        }
        if (i==7 && !_tcsncmp(buf_start, wxT("![CDATA["), 8)) {
            return scan_cdata(buf_start, tag_len);
        }
    }
    return 0;
}

// read and copy text to buf; stop when find a <;
// ungetc() that so we read it again
// Return true iff reached EOF
//
bool XML_PARSER::copy_until_tag(wxChar* buf, int len) {
    wxInt32 c;
    while (1) {
        c = f->_getc();
        if ((char)c == EOF) return true;
        if (c == wxT('<')) {
            f->_ungetc(c);
            *buf = 0;
            return false;
        }
        if (--len > 0) {
            *buf++ = c;
        }
    }
    return false;
}

// Scan something, either tag or text.
// Strip whitespace at start and end.
// Return true iff reached EOF
//
int XML_PARSER::get_aux(wxChar* buf, int len, wxChar* attr_buf, int attr_len) {
    bool eof;
    wxChar c, retval;

    while (1) {
        eof = scan_nonws(c);
        if (eof) return XML_PARSE_EOF;
        if (c == wxT('<')) {
            retval = scan_tag(buf, len, attr_buf, attr_len);
            if (retval == XML_PARSE_EOF) return retval;
            if (retval == XML_PARSE_COMMENT) continue;
        } else {
            buf[0] = c;
            eof = copy_until_tag(buf+1, len-1);
            if (eof) return XML_PARSE_EOF;
            retval = XML_PARSE_DATA;
        }
        strip_whitespace(buf);
        return retval;
    }
    return false;
}

bool XML_PARSER::get(
    wxChar* buf, int len, bool& _is_tag, wxChar* attr_buf, int attr_len
) {
    switch (get_aux(buf, len, attr_buf, attr_len)) {
    case XML_PARSE_EOF: return true;
    case XML_PARSE_TAG:
        _is_tag = true;
        break;
    case XML_PARSE_DATA:
    case XML_PARSE_CDATA:
    default:
        _is_tag = false;
        break;
    }
    return false;
}

#define MAX_XML_STRING  262144

// We just parsed "parsed_tag".
// If it matches "start_tag", and is followed by a string
// and by the matching close tag, return the string in "buf",
// and return true.
//
bool XML_PARSER::parse_str(const wxChar* start_tag, wxChar* buf, int len) {
    bool eof;
    wxChar end_tag[256], tag[256];

    // handle the archaic form <tag/>, which means empty string
    //
    size_t n = _tcslen(parsed_tag);
    if (parsed_tag[n-1] == wxT('/')) {
        _tcscpy(tag, parsed_tag);
        tag[n-1] = 0;
        if (!_tcscmp(tag, start_tag)) {
            _tcscpy(buf, wxT(""));
            return true;
        }
    }

    // check for start tag
    //
    if (_tcscmp(parsed_tag, start_tag)) return false;

    end_tag[0] = '/';
    _tcscpy(end_tag+1, start_tag);

    // get text after start tag
    //
    int retval = get_aux(buf, len, 0, 0);
    if (retval == XML_PARSE_EOF) return false;

    // if it's the end tag, return empty string
    //
    if (retval == XML_PARSE_TAG) {
        if (_tcscmp(buf, end_tag)) {
            return false;
        } else {
            _tcscpy(buf, wxT(""));
            return true;
        }
    }

    eof = get(tag, sizeof(tag), is_tag);
    if (eof) return false;
    if (!is_tag) return false;
    if (_tcscmp(tag, end_tag)) return false;
    if (retval != XML_PARSE_CDATA) {
        xml_unescape(buf);
    }
    return true;
}

bool XML_PARSER::parse_string(const wxChar* start_tag, std::wstring& str) {
    wxChar buf[MAX_XML_STRING];
    bool flag = parse_str(start_tag, buf, sizeof(buf));
    if (!flag) return false;
    str = buf;
    return true;
}

// Same, for integers
//
bool XML_PARSER::parse_int(const wxChar* start_tag, int& i) {
    wxChar buf[256], *end;
    bool eof;
    wxChar end_tag[256], tag[256];

    if (_tcscmp(parsed_tag, start_tag)) return false;

    end_tag[0] = wxT('/');
    _tcscpy(end_tag+1, start_tag);

    eof = get(buf, sizeof(buf), is_tag);
    if (eof) return false;
    if (is_tag) {
        if (!_tcscmp(buf, end_tag)) {
            i = 0;      // treat <foo></foo> as <foo>0</foo>
            return true;
        } else {
            return false;
        }
    }
    errno = 0;
    int val = _tcstol(buf, &end, 0);
    if (errno) return false;
    if (end != buf+_tcslen(buf)) return false;

    eof = get(tag, sizeof(tag), is_tag);
    if (eof) return false;
    if (!is_tag) return false;
    if (_tcscmp(tag, end_tag)) return false;
    i = val;
    return true;
}

// Same, for doubles
//
bool XML_PARSER::parse_double(const wxChar* start_tag, double& x) {
    wxChar buf[256], *end;
    bool eof;
    wxChar end_tag[256], tag[256];

    if (_tcscmp(parsed_tag, start_tag)) return false;

    end_tag[0] = wxT('/');
    _tcscpy(end_tag+1, start_tag);

    eof = get(buf, sizeof(buf), is_tag);
    if (eof) return false;
    if (is_tag) {
        if (!_tcscmp(buf, end_tag)) {
            x = 0;      // treat <foo></foo> as <foo>0</foo>
            return true;
        } else {
            return false;
        }
    }
    errno = 0;
    double val = _tcstod(buf, &end);
    if (errno) return false;
    if (end != buf+_tcslen(buf)) return false;

    eof = get(tag, sizeof(tag), is_tag);
    if (eof) return false;
    if (!is_tag) return false;
    if (_tcscmp(tag, end_tag)) return false;
    x = val;
    return true;
}

// Same, for unsigned long
//
bool XML_PARSER::parse_ulong(const wxChar* start_tag, unsigned long& x) {
    wxChar buf[256], *end;
    bool eof;
    wxChar end_tag[256], tag[256];

    if (_tcscmp(parsed_tag, start_tag)) return false;

    end_tag[0] = wxT('/');
    _tcscpy(end_tag+1, start_tag);

    eof = get(buf, sizeof(buf), is_tag);
    if (eof) return false;
    if (is_tag) {
        if (!_tcscmp(buf, end_tag)) {
            x = 0;      // treat <foo></foo> as <foo>0</foo>
            return true;
        } else {
            return false;
        }
    }
    errno = 0;
    unsigned long val = _tcstoul(buf, &end, 0);
    if (errno) return false;
    if (end != buf+_tcslen(buf)) return false;

    eof = get(tag, sizeof(tag), is_tag);
    if (eof) return false;
    if (!is_tag) return false;
    if (_tcscmp(tag, end_tag)) return false;
    x = val;
    return true;
}

// Same, for unsigned long long
//
bool XML_PARSER::parse_ulonglong(const wxChar* start_tag, unsigned long long& x) {
    wxChar buf[256], *end;
    bool eof;
    wxChar end_tag[256], tag[256];

    if (_tcscmp(parsed_tag, start_tag)) return false;

    end_tag[0] = wxT('/');
    _tcscpy(end_tag+1, start_tag);

    eof = get(buf, sizeof(buf), is_tag);
    if (eof) return false;
    if (is_tag) {
        if (!_tcscmp(buf, end_tag)) {
            x = 0;      // treat <foo></foo> as <foo>0</foo>
            return true;
        } else {
            return false;
        }
    }
    errno = 0;
    unsigned long long val = _tcstoull(buf, &end, 0);
    if (errno) return false;
    if (end != buf+_tcslen(buf)) return false;

    eof = get(tag, sizeof(tag), is_tag);
    if (eof) return false;
    if (!is_tag) return false;
    if (_tcscmp(tag, end_tag)) return false;
    x = val;
    return true;
}

// Same, for bools
//
bool XML_PARSER::parse_bool(const wxChar* start_tag, bool& b) {
    wxChar buf[256], *end;
    bool eof;
    wxChar end_tag[256], tag[256];

    // handle the archaic form <tag/>, which means true
    //
    _tcscpy(tag, start_tag);
    _tcscat(tag, wxT("/"));
    if (!_tcscmp(parsed_tag, tag)) {
        b = true;
        return true;
    }

    // otherwise look for something of the form <tag>int</tag>
    //
    if (_tcscmp(parsed_tag, start_tag)) return false;

    eof = get(buf, sizeof(buf), is_tag);
    if (eof) return false;
    if (is_tag) return false;
    bool val = (_tcstol(buf, &end, 0) != 0);
    if (end != buf+_tcslen(buf)) return false;

    end_tag[0] = '/';
    _tcscpy(end_tag+1, start_tag);
    eof = get(tag, sizeof(tag), is_tag);
    if (eof) return false;
    if (!is_tag) return false;
    if (_tcscmp(tag, end_tag)) return false;
    b = val;
    return true;
}

// parse a start tag (optionally preceded by <?xml>)
//
bool XML_PARSER::parse_start(const wxChar* start_tag) {
    wxChar tag[256];
    bool eof;

    eof = get(tag, sizeof(tag), is_tag);
    if (eof || !is_tag ) {
        return false;
    }
    if (_tcsstr(tag, wxT("?xml"))) {
        eof = get(tag, sizeof(tag), is_tag);
        if (eof || !is_tag ) {
            return false;
        }
    }
    if (_tcscmp(tag, start_tag)) {
        return false;
    }
    return true;
}

// copy everything up to (but not including) the given end tag.
// The copied text may include XML tags.
// strips whitespace.
//
int XML_PARSER::element_contents(const wxChar* end_tag, wxChar* buf, int buflen) {
    int n=0;
    int retval=0;
    while (1) {
        if (n == buflen-1) {
            retval = -112;
            break;
        }
        wxChar c = f->_getc();
        if ((char)c == EOF) {
            retval = -112;
            break;
        }
        buf[n++] = c;
        buf[n] = 0;
        wxChar* p = _tcsstr(buf, end_tag);
        if (p) {
            *p = 0;
            break;
        }
    }
    buf[n] = 0;
    strip_whitespace(buf);
    return retval;
}

// We got an unexpected tag.
// If it's an end tag, do nothing.
// Otherwise skip until the end tag, if any
//
void XML_PARSER::skip_unexpected(
    const wxChar* start_tag, bool verbose, const wxChar* where
) {
    wxChar tag[256], end_tag[256];

    if (verbose) {
        _ftprintf(stderr, wxT("Unrecognized XML in %s: %s\n"), where, start_tag);
    }
    if (_tcschr(start_tag, wxT('/'))) return;
    _stprintf(end_tag, sizeof(end_tag), wxT("/%s"), start_tag);
    while (!get(tag, sizeof(tag), is_tag)) {
        if (verbose) {
            _ftprintf(stderr, wxT("Skipping: %s\n"), tag);
        }
        if (!is_tag) continue;
        if (!_tcscmp(tag, end_tag)) return;
        skip_unexpected(tag, verbose, where);
    }
}

// we just parsed a tag.
// copy this entire element, including start and end tags, to the buffer
//
int XML_PARSER::copy_element(std::wstring& out) {
    wxChar end_tag[256], buf[1024];

    // handle <foo/> case
    //
    size_t n = _tcslen(parsed_tag);
    if (parsed_tag[n-1] == wxT('/')) {
        out = wxT("<");
        out += parsed_tag;
        out += wxT(">");
        return 0;
    }
    if (_tcschr(parsed_tag, wxT('/'))) return -112;
    out = wxT("<");
    out += parsed_tag;
    out += wxT(">");
    _stprintf(end_tag, sizeof(end_tag), wxT("</%s>"), parsed_tag);
    int retval = element_contents(end_tag, buf, sizeof(buf));
    if (retval) return retval;
    out += buf;
    out += end_tag;
    return 0;
}

void XML_PARSER::skip_unexpected(bool verbose, const wxChar* msg) {
    skip_unexpected(parsed_tag, verbose, msg);
}


