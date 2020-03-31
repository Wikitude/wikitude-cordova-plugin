//
//  CameraPosition.hpp
//  CommonLibrary
//
//  Created by Andreas Schacherbauer on 19.10.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef CameraPosition_hpp
#define CameraPosition_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {

    namespace impl {

        /** @enum CameraPosition
         *  @brief An enum indicating the physical position of the camera used to capture frames.
         */
        enum class WT_EXPORT_API CameraPosition : int {
            /** @brief Indicates that the camera position is undefined. Desktop web cams might return this value.
             */
            Unspecified,
            /** @brief Indicates that the camera is located on the back.
             */
            Back,
            /** @brief Indicates that the camera is located on the front.
             */
            Front
        };
    }
    using impl::CameraPosition;
}}

#endif /* __cplusplus */

#endif /* CameraPosition_hpp */
