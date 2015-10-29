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

#ifndef __STDWX_H__
#define __STDWX_H__


//
// Project Wide Precompiled Header
//


#include <wx/wx.h>
#include <wx/config.h>          // configuration support
#include <wx/debug.h>           // diagnostics support
#include <wx/log.h>             // logging support
#include <wx/cmdline.h>         // command line support
#include <wx/file.h>            // raw file i/o support
#include <wx/ffile.h>           // buffered file i/o support
#include <wx/socket.h>          // socket interface
#include <wx/datetime.h>        // date/time abstraction
#include <wx/stopwatch.h>       // stopwatch abstraction
#include <wx/cshelp.h>          // context sensitive help
#include <wx/aboutdlg.h>        // about dialog
#include <wx/propdlg.h>         // property sheet dialog
#include <wx/notebook.h>        // notebook control support
#include <wx/imaglist.h>        // imagelist control support
#include <wx/listctrl.h>        // listctrl control support
#include <wx/hyperlink.h>       // hyperlink control support
#include <wx/webview.h>         // html window support
#include <wx/webviewarchivehandler.h>
#include <wx/webviewfshandler.h>
#include <wx/tokenzr.h>         // string tokenizer support
#include <wx/dcbuffer.h>        // buffered device contexts
#include <wx/graphics.h>        // native graphics renderer
#include <wx/clipbrd.h>         // clipboard functionality
#include <wx/gauge.h>           // gauge/progress control support
#include <wx/splitter.h>        // splitter control support
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/taskbar.h>

#ifdef wxUSE_NOTIFICATION_MESSAGE
#include <wx/notifmsg.h>
#endif

#include <vector>
#include <iterator>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <cerrno>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <cmath>
#ifdef _WIN32
#include <tchar.h>
#include <winsock.h>
#ifdef _MSC_VER
#include <intrin.h>
#endif
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
#endif


// On the Win32 platform include file and line number information for each
//   memory allocation/deallocation
#if (defined(__WIN32__) && defined(__VISUALC__))

#ifdef _DEBUG

#define malloc(s)                             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s)                          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s)                         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s)                         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define free(p)                               _free_dbg(p, _NORMAL_BLOCK)
#define _msize(p)                             _msize_dbg(p, _NORMAL_BLOCK)
#define _aligned_malloc(s, a)                 _aligned_malloc_dbg(s, a, __FILE__, __LINE__)
#define _aligned_realloc(p, s, a)             _aligned_realloc_dbg(p, s, a, __FILE__, __LINE__)
#define _aligned_offset_malloc(s, a, o)       _aligned_offset_malloc_dbg(s, a, o, __FILE__, __LINE__)
#define _aligned_offset_realloc(p, s, a, o)   _aligned_offset_realloc_dbg(p, s, a, o, __FILE__, __LINE__)
#define _aligned_free(p)                      _aligned_free_dbg(p)

#define DEBUG_NEW                             new(_NORMAL_BLOCK, __FILE__, __LINE__)

// The following macros set and clear, respectively, given bits
// of the C runtime library debug flag, as specified by a bitmask.
#define SET_CRT_DEBUG_FIELD(a)                _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define CLEAR_CRT_DEBUG_FIELD(a)              _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

#else //_DEBUG

#define DEBUG_NEW                             new

#define SET_CRT_DEBUG_FIELD(a)                ((void) 0)
#define CLEAR_CRT_DEBUG_FIELD(a)              ((void) 0)

#endif //_DEBUG

#define new DEBUG_NEW

#endif //__WIN32__ && __VISUALC


// Fix incomplete MinGW/Linux environment stuff
#ifndef _tstof
#ifdef _UNICODE
#ifdef _WIN32
#define _tstof _wtof
#else
#define _tstof(a) wcstof(a, NULL)
#endif
#else
#ifdef _WIN32
#define _tstof _atof
#else
#define _tstof atof
#endif
#endif
#endif

#ifndef _tcstod
#ifdef _UNICODE
#define _tcstod wcstod
#else
#define _tcstod strtod
#endif
#endif

#ifndef _ttoi
#ifdef _UNICODE
#ifdef __WXMAC__
#define _ttoi(str) (int)wcstol(str, (wchar_t**)NULL, 10)
#else
#define _ttoi wtoi
#endif
#else
#define _ttoi atoi
#endif
#endif

#ifndef _tcstol
#ifdef _UNICODE
#define _tcstol wcstol
#else
#define _tcstol strtol
#endif
#endif

#ifndef _tcstoul
#ifdef _UNICODE
#define _tcstoul wcstoul
#else
#define _tcstoul strtoul
#endif
#endif

#ifndef _tcstoll
#ifdef _UNICODE
#ifdef _MSC_VER
#define _tcstoll _wcstoi64
#else
#define _tcstoll wcstoll
#endif
#else
#define _tcstoll strtoll
#endif
#endif

#ifndef _tcstoull
#ifdef _UNICODE
#ifdef _MSC_VER
#define _tcstoull _wcstoui64
#else
#define _tcstoull wcstoull
#endif
#else
#define _tcstoull strtoull
#endif
#endif

#ifndef _istascii
#ifdef _UNICODE
#define _istascii iswascii
#else
#define _istascii isascii
#endif
#endif

#ifndef _istspace
#ifdef _UNICODE
#define _istspace iswspace
#else
#define _istspace isspace
#endif
#endif

#ifndef _tcschr
#ifdef _UNICODE
#define _tcschr wcschr
#else
#define _tcschr strchr
#endif
#endif

#ifndef _tcscmp
#ifdef _UNICODE
#define _tcscmp wcscmp
#else
#define _tcscmp strcmp
#endif
#endif

#ifndef _tcsncmp
#ifdef _UNICODE
#define _tcsncmp wcsncmp
#else
#define _tcsncmp strncmp
#endif
#endif

#ifndef _tcslen
#ifdef _UNICODE
#define _tcslen wcslen
#else
#define _tcslen strlen
#endif
#endif

#ifndef _tcsstr
#ifdef _UNICODE
#define _tcsstr wcsstr
#else
#define _tcsstr strstr
#endif
#endif

#ifndef _tcscat
#ifdef _UNICODE
#define _tcscat wcscat
#else
#define _tcscat strcat
#endif
#endif

#ifndef _tcscpy
#ifdef _UNICODE
#define _tcscpy wcscpy
#else
#define _tcscpy strcpy
#endif
#endif

#ifndef _tcsncpy
#ifdef _UNICODE
#define _tcsncpy wcsncpy
#else
#define _tcsncpy strncpy
#endif
#endif

#ifndef _tfopen
#ifdef _UNICODE
#define _tfopen wfopen
#else
#define _tfopen fopen
#endif
#endif

#ifndef _ftprintf
#ifdef _UNICODE
#define _ftprintf fwprintf
#else
#define _ftprintf fprintf
#endif
#endif

#ifndef _vftprintf
#ifdef _UNICODE
#define _vftprintf vfwprintf
#else
#define _vftprintf vfprintf
#endif
#endif

#ifndef _fgettc
#ifdef _UNICODE
#define _fgettc fgetwc
#else
#define _fgettc fgetc
#endif
#endif

#ifndef _ungettc
#ifdef _UNICODE
#define _ungettc ungetwc
#else
#define _ungettc ungetc
#endif
#endif

#ifndef _fgetts
#ifdef _UNICODE
#define _fgetts fgetws
#else
#define _fgetts fgets
#endif
#endif

#ifndef _stprintf
#ifdef _UNICODE
#define _stprintf swprintf
#else
#define _stprintf sprintf
#endif
#endif

#ifndef _vsntprintf
#ifdef _UNICODE
#ifdef __WXMAC__
#define _vsntprintf vswprintf
#else
#define _vsntprintf vsnwprintf
#endif
#else
#define _vsntprintf vsnprintf
#endif
#endif

#endif //__STDWX_H__

