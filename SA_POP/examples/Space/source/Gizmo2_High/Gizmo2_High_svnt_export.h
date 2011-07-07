
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl GIZMO2_HIGH_SVNT
// ------------------------------
#ifndef GIZMO2_HIGH_SVNT_EXPORT_H
#define GIZMO2_HIGH_SVNT_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (GIZMO2_HIGH_SVNT_HAS_DLL)
#  define GIZMO2_HIGH_SVNT_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && GIZMO2_HIGH_SVNT_HAS_DLL */

#if !defined (GIZMO2_HIGH_SVNT_HAS_DLL)
#  define GIZMO2_HIGH_SVNT_HAS_DLL 1
#endif /* ! GIZMO2_HIGH_SVNT_HAS_DLL */

#if defined (GIZMO2_HIGH_SVNT_HAS_DLL) && (GIZMO2_HIGH_SVNT_HAS_DLL == 1)
#  if defined (GIZMO2_HIGH_SVNT_BUILD_DLL)
#    define GIZMO2_HIGH_SVNT_Export ACE_Proper_Export_Flag
#    define GIZMO2_HIGH_SVNT_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define GIZMO2_HIGH_SVNT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* GIZMO2_HIGH_SVNT_BUILD_DLL */
#    define GIZMO2_HIGH_SVNT_Export ACE_Proper_Import_Flag
#    define GIZMO2_HIGH_SVNT_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define GIZMO2_HIGH_SVNT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* GIZMO2_HIGH_SVNT_BUILD_DLL */
#else /* GIZMO2_HIGH_SVNT_HAS_DLL == 1 */
#  define GIZMO2_HIGH_SVNT_Export
#  define GIZMO2_HIGH_SVNT_SINGLETON_DECLARATION(T)
#  define GIZMO2_HIGH_SVNT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* GIZMO2_HIGH_SVNT_HAS_DLL == 1 */

// Set GIZMO2_HIGH_SVNT_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (GIZMO2_HIGH_SVNT_NTRACE)
#  if (ACE_NTRACE == 1)
#    define GIZMO2_HIGH_SVNT_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define GIZMO2_HIGH_SVNT_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !GIZMO2_HIGH_SVNT_NTRACE */

#if (GIZMO2_HIGH_SVNT_NTRACE == 1)
#  define GIZMO2_HIGH_SVNT_TRACE(X)
#else /* (GIZMO2_HIGH_SVNT_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define GIZMO2_HIGH_SVNT_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (GIZMO2_HIGH_SVNT_NTRACE == 1) */

#endif /* GIZMO2_HIGH_SVNT_EXPORT_H */

// End of auto generated file.