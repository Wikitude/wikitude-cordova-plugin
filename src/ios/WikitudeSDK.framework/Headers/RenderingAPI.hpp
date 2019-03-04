//
//  RenderingAPI.hpp
//
//  Created by Alexandru Florea on 28/02/17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef RenderingAPI_hpp
#define RenderingAPI_hpp

#ifdef __cplusplus


namespace wikitude { namespace sdk {
    
    namespace impl {
        
        enum class RenderingAPI {
            OpenGL_ES_2,
            OpenGL_ES_3,
            Metal,
            DirectX,
            None,
            RenderingAPIs
        };    
    }
    using impl::RenderingAPI;
}}

#endif /* __cplusplus */

#endif /* RenderingAPI_hpp */
