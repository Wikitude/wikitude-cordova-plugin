//
//  RenderingParameters.hpp
//  WikitudeiOSComponent
//
//  Created by Andreas Schacherbauer on 18.01.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef RenderingParameters_hpp
#define RenderingParameters_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"
namespace wikitude::universal_sdk {
    class RenderingParametersInternal;
}

namespace wikitude::sdk {

        enum class RenderingAPI;
        class WT_EXPORT_API RenderingParameters {
        public:
            RenderingParameters(universal_sdk::RenderingParametersInternal& internalRenderingParameters_);

            sdk::RenderingAPI getActiveRenderingAPI() const;

            unsigned int getPreferredFramesPerSecond() const;

        protected:
            universal_sdk::RenderingParametersInternal&     _internalRenderingParameters;
        };
}

#endif /* __cplusplus */

#endif /* RenderingParameters_hpp */
