//
//  MetalRenderingObjects.h
//  WikitudeUniversalSDK
//
//  Created by Daniel Guttenberg on 16.5.2018.
//  Copyright (c) 2018 Wikitude. All rights reserved.
//


#ifndef MetalRenderingObjects_hpp
#define MetalRenderingObjects_hpp

#ifdef __cplusplus

#import <Metal/MTLDevice.h>
#import <Metal/MTLRenderCommandEncoder.h>
#import <Metal/MTLPixelFormat.h>

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {
    
        namespace impl {
            
            class WT_EXPORT_API MetalRenderingObjects {
            public:
                MetalRenderingObjects(id<MTLDevice> device_, id<MTLRenderCommandEncoder> commandEncoder_, MTLPixelFormat pixelFormat_);
                
                id<MTLDevice> getDevice() const;
                id<MTLRenderCommandEncoder> getCommandEncoder() const;
                MTLPixelFormat getPixelFormat() const;
                
            private:
                id<MTLDevice>                   _device;
                id<MTLRenderCommandEncoder>     _commandEncoder;
                MTLPixelFormat                  _pixelFormat;
            };
            
        }
        using impl::MetalRenderingObjects;
}}

#endif /* __cplusplus */

#endif /* MetalRenderingObjects_hpp */
