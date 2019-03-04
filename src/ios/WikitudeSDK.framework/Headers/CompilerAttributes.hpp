//
//  CompilerAttributes.hpp
//  CommonLibrary
//
//  Created by Andreas Schacherbauer on 05.03.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef CompilerAttributes_hpp
#define CompilerAttributes_hpp

#ifdef __cplusplus

#if defined(__GNUC__) && (__GNUC__ >= 4)
    #define NO_DISCARD __attribute__ ((warn_unused_result))
#elif defined(_MSC_VER) && (_MSC_VER >= 1700)
    #define NO_DISCARD _Check_return_
#else
    #define NO_DISCARD
#endif

#if defined(_WIN32) || defined(__WIN32__)
    #define WT_EXPORT_API __declspec(dllexport)
#else
    #define WT_EXPORT_API __attribute__ ((visibility("default")))
#endif

#endif /* __cplusplus */

#endif /* CompilerAttributes_hpp */
