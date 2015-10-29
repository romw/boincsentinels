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

\page page_designxml BOINC Sentinels XML Library Design
<center>
<h1>BOINC Sentinels XML Library Design Document</h1>
\image html boincsentinelsxml128.png
</center>
\n
\version 1.0
\author Rom Walton
\date October 20, 2012
\n

\section introduction Introduction
\n
\subsection purpose Purpose
BOINC Sentinels is meant to be an incubation project to explore different user
interfaces and data models for displaying data about a BOINC client.
BOINC (http://boinc.berkeley.edu) is an open source project for volunteer
computing/distributed computing (http://www.distributedcomputing.info/).

Efficient XML parsing is something of a dark art. Since BOINC has a well known
structure and is stable we can more efficiently parse the returned XML by creating a
special purpose parser.

By reducing the inefficiencies of the XML parser the remaining CPU cycles can
be left to the project applications.

\subsection scope Scope
This software design document describes the architecture and system design of the
BOINC Sentinels User Interface Libraries.\n
\n
Specifically:
\li libbslxml

\subsection intendedaudience Intended Audience
The intended audience for this document are engineers or researchers, who want
to modify and/or extend the existing reference implementation. As described software
is implemented using wxWidgets (http://www.wxwidgets.org/), the reader should have some
knowledge of the C/C++ programming language as well user interface event driven
methodologies.

\subsection references References
The BOINC Sentinels project homepage contains all relevant documentation, source code,
and additional analysis tools:\n
https://projects.romwnet.org/boincsentinels/

\section systemoverview System Overview
Taking advantage of BOINC's simplistic use of the XML standard(s) we should be able to
improve the overall performance of the BOINC Sentinels XML parser relative to any of
the generic implementations.

\section designconsiderations Design Considerations

\subsection assumptionsdependencies Assumptions and Dependencies
See \subpage page_boincxmlparser for a complete list of assumptions the BOINC XML
infrastructure makes.

\subsection goalguidelines Goals and Guidelines

\subsubsection compliance Compliance
The oracle for this library is whatever XML the BOINC client emits as part of a GUI remote
procedure call.

\subsubsection performance Performance
All inefficiencies should be removed.  Any user interface will be making thousands of
remote procedure calls, if not millions, during the course of execution.

CPU cycles not spent parsing can be used by project applications.

\subsubsection portability Portability
This library should be able to function on any platform supported by BOINC.

\section architecturalstrategies Architectural Strategies

\subsection destructive Destructive Parsing
Destructive parsing is the technique where you modify the original buffer while parsing
for content and copy the correctly parsed input to its final destination.

By using destructive parsing we can reduce the number of memory allocations required.

\subsection hashmaps Hash Maps
FNV1 hashes should be computed for the names and values of XML elements and XML attributes
as they are parsed.

Using FNV1 hashes for the names reduces the amount of time needed to find which variable
the data is destined for.  Despite processor advances strstr() compares are still more
expensive than integer compares.

\subsection singlepass Single Pass Parsing
Single pass parsing should avoid going over the same memory addresses more than once.

The only exception to this should be when the library copies a null-terminated string to
its final location or the null-terminated string is converted into a numerical value.

\subsection nativestring Platform String Type
Using the platforms string type reduces the number of times a strings encoding needs to
be changed.  On average this can reduce CPU utilization by 10%-15% on Windows when
making a Win32 API call.

\section systemarchitecture System Architecture

\section detailedsystemdesign Detailed System Design

\subsection CBSLXMLStream CBSLXMLStreamEx
CBSLXMLStreamEx is a container for the buffer to be parsed. It should provide functions
sufficient for navigating an XML stream.

\subsection CBSLXMLConverterEx CBSLXMLConverterEx
CBSLXMLConverterEx should provide functions to converted a null terminated string into
various native data types. CBSLXMLConverterEx should also provide functions for decoding
XML entities.

\subsection CBSLXMLAttributeEx CBSLXMLAttributeEx
CBSLXMLAttributeEx is a class that encapsulates an XML Attribute.

\subsection CBSLXMLElementEx CBSLXMLElementEx
CBSLXMLElementEx is a class that encapsulates an XML Element.

It has the following properties:
1. It can contain one or more CBSLXMLAttributeEx references.
2. It cannot contain child CBSLXMLElementEx references.

\subsection CBSLXMLDictionaryEx CBSLXMLDictionaryEx
CBSLXMLDictionaryEx is a container for one or more CBSLXMLElementEx references.

\section glossary Glossary

\section bibliography Bibliography


*/
