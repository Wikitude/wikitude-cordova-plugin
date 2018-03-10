//
//  InterfaceOrientation.h
//  CommonLibrary
//
//  Created by Daniel Guttenberg on 08/04/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef InterfaceOrientation_h
#define InterfaceOrientation_h

#ifdef __cplusplus


namespace wikitude { namespace sdk {
    
    namespace impl {
        
        enum InterfaceOrientation : int {
            InterfaceOrientationLandscapeLeft = 90,
            InterfaceOrientationLandscapeRight = -90,
            InterfaceOrientationPortrait = 0,
            InterfaceOrientationPortraitUpsideDown = 180
        };
    }
    using impl::InterfaceOrientation;
}}

#endif /* __cplusplus */

#endif /* InterfaceOrientation_h */
