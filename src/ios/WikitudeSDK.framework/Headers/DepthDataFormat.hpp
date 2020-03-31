//
//  DepthDataFormat.hpp
//  CommonLibrary
//
//  Created by Andreas Schacherbauer on 21.11.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef DepthDataFormat_hpp
#define DepthDataFormat_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {

    namespace impl {


        enum class WT_EXPORT_API DepthDataFormat {
            FLOAT_32,
            FLOAT_32_NORMALIZED,
            INTEGER_8,
            INTEGER_16,
            INTEGER_32
        };
    }
    using impl::DepthDataFormat;
}}

#endif /* __cplusplus */

#endif /* DepthDataFormat_hpp */
