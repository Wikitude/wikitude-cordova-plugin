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

namespace wikitude {
    namespace sdk {
        namespace impl {
            enum class RenderingAPI;
        }
        using impl::RenderingAPI;
    }
    namespace universal_sdk {
        namespace impl {
            class RenderingParametersInternal;
        }
        using impl::RenderingParametersInternal;
    }
}

namespace wikitude { namespace sdk {

    namespace impl {


        class RenderingParameters {
        public:
            RenderingParameters(universal_sdk::RenderingParametersInternal& internalRenderingParameters_);

            sdk::RenderingAPI getActiveRenderingAPI() const;

            unsigned int getPreferredFramesPerSecond() const;

        protected:
            universal_sdk::RenderingParametersInternal&     _internalRenderingParameters;
        };
    }
    using impl::RenderingParameters;
}}

#endif /* __cplusplus */

#endif /* RenderingParameters_hpp */
