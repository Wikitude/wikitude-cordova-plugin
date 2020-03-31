//
//  PlaneType.hpp
//  WikitudeUniversalSDK
//
//  Created by Alexandru Florea on 02.08.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef PlaneType_hpp
#define PlaneType_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {

    namespace impl {

        /**
         * @brief Use this enum to determine the type of a plane that was detected by the instant tracker.
         */
        enum class WT_EXPORT_API PlaneType {
            /** HorizontalUpward: The detected plane is horizontal and points upward (e.g. floor). */
            HorizontalUpward,
            /** HorizontalDownward: The detected plane is horizontal and points downward (e.g. ceiling). */
            HorizontalDownward,
            /** Vertical: The detected plane is vertical (e.g. wall). */
            Vertical,
            /** Arbitrary: The detected plane has an arbitrary orientation. */
            Arbitrary,
        };
    }
    using impl::PlaneType;
}}

#endif /* __cplusplus */

#endif /* PlaneType_hpp */
