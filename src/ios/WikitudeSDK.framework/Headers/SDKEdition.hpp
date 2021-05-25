//
//  SDKEdition.hpp
//  WikitudeUniversalSDK
//
//  Created by Alexandru Florea on 23.03.20.
//  Copyright © 2019 Wikitude. All rights reserved.
//

#ifndef SDKEdition_hpp
#define SDKEdition_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude::sdk {

        /**
         * @brief Use this enum to determine which edition of the SDK is running.
         */
        enum class WT_EXPORT_API SDKEdition {
            /** ProfessionalEdition: This is the regular version of the SDK. */
            ProfessionalEdition,
            /** ExpertEdition: The Expert edition of the SDK enables additional features. */
            ExpertEdition
        };
}

#endif /* __cplusplus */

#endif /* SDKEdition_hpp */
