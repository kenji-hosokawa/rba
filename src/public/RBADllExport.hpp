/// @file  RBADllExport.hpp
/// @brief DLL_EXPORT定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBADLLEXPORT_HPP
#define RBADLLEXPORT_HPP

#ifdef _MSC_VER
  #ifndef DLL_EXPORT
    #ifdef _WINDLL
      #define DLL_EXPORT __declspec(dllexport)
    #else
      #define DLL_EXPORT __declspec(dllimport)
    #endif
  #endif
#else
  #define DLL_EXPORT
#endif

#endif
