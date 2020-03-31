//
//  CameraFocusMode.hpp
//  WikitudeUniversalSDK
//
//  Created by Aitor Font on 11.03.20.
//  Copyright © 2020 Wikitude. All rights reserved.
//

#ifndef CameraFocusMode_hpp
#define CameraFocusMode_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {

    namespace impl {

        /**
         * @brief Use this enum to determine the focus mode of the camera.
         */
        enum class WT_EXPORT_API CameraFocusMode {
            /** Once: The device automatically adjusts the focus once. */
            Once,
            /** Continuous: The device continuously monitors focus and autofocuses when necessary. */
            Continuous,
            /** Off: The device has its focus locked */
            Off
        };
    }
    using impl::CameraFocusMode;
}}

#endif /* __cplusplus */

#endif /* CameraFocusMode_hpp */
