//
//  RenderingContext.h
//  CommonLibrary
//
//  Created by Alexandru Florea on 09/05/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef __CommonLibrary__RenderingContext__
#define __CommonLibrary__RenderingContext__

#ifdef __cplusplus

namespace wikitude { namespace sdk {
    
    namespace impl {
        
        /**
         * The RenderingContext can be used by plugins to access native state objects of a particular rendering API. This is the base class for derived implementations for each rendering API.
         */
        class RenderingContext {
        public:
            RenderingContext() { }
            virtual ~RenderingContext() { }
        };
    }
    using impl::RenderingContext;
}}

#endif /* __cplusplus */

#endif /* __CommonLibrary__RenderingContext__ */
