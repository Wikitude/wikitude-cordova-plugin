//
//  RenderingAPI.h
//  FoundationSDK
//
//  Created by Alexandru Florea on 28/02/17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef RenderingAPI_h
#define RenderingAPI_h

#ifdef __cplusplus

namespace wikitude { namespace sdk {
    
    namespace impl {
        
        enum RenderingAPI {
            OpenGL_ES_2,
            OpenGL_ES_3,
            Metal,
            None
        };    
    }
    using impl::RenderingAPI;
}}

#endif /* __cplusplus */

#endif /* RenderingAPI_h */
