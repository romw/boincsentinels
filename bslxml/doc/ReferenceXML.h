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

/**

\page page_referencexml BOINC Sentinels XML Library Reference Manual
<center>
<h1>BOINC Sentinels XML Library Reference Manual</h1>
\image html boincsentinelsxml128.png
</center>
\n
\version 1.0
\author Rom Walton
\n

\section history Document History

<table border=1>
  <tr>
    <th>Date</th>
    <th>Version</th>
    <th width=100%>Description of Change</th>
  </tr>
  <tr>
    <td>December 23, 2012</td>
    <td>1.0</td>
    <td>Initial Draft</td>
  </tr>
</table>

\section introduction Introduction

The BOINC Sentinels XML Library is a light weight library for parsing the
Extensible Markup Language (XML) emitted by the BOINC platform
(http://boinc.berkeley.edu).  XML emitted by the BOINC platform is loosely
based on the Extensible Markup Language specification
(http://www.w3.org/TR/2008/REC-xml-20081126).

\subsection conventions Conventions



\subsection terminology Terminology



\subsection background Background

In early 2003 a lawsuit was filed against the BOINC project by United Devices.
The out-of-court settlement banned the use of any of the BOINC source code
within commercial products.

BOINC proceeded to roll its own XML parser due to the license change
requirement of the settlement.

Details of the BOINC/United Devices lawsuit can be found here:
http://boinc.berkeley.edu/legal.html

\section started Getting Started



\section concepts Concepts



\section examples Examples


\section results Performance Results
The xmlreader benchmark program was constructed to compare the various methods
of parsing XML in BOINC. Here are the results:

<pre>
Memory scan speed...
    Super sizing task instance list...
    Elapsed Time: 73 milliseconds
    Array Size: 165780000
XML Stream Line Scan speed...
    Super sizing task instance list...
    Elapsed Time: 363 milliseconds
    Line Count: 14240002
BOINC Sentinels XML parser speed...
    Super sizing task instance list...
    Elapsed Time: 864 milliseconds
    Result Count: 210000
BOINC XML parser v1 (parse_* functions) speed...
    Super sizing task instance list...
    Elapsed Time: 7829 milliseconds
    Result Count: 210000
BOINC XML parser v2 (XML_PARSER) speed...
    Super sizing task instance list...
    Elapsed Time: 4520 milliseconds
    Result Count: 210000
</pre>

*/
