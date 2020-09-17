//
//  InterfaceOrientation.hpp
//  CommonLibrary
//
//  Created by Daniel Guttenberg on 08/04/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef InterfaceOrientation_h
#define InterfaceOrientation_h

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude::sdk {
        
        enum WT_EXPORT_API InterfaceOrientation : int {
            InterfaceOrientationLandscapeLeft = 90,
            InterfaceOrientationLandscapeRight = -90,
            InterfaceOrientationPortrait = 0,
            InterfaceOrientationPortraitUpsideDown = 180,
            InterfaceOrientationUnknown
        };
}

#endif /* __cplusplus */

#endif /* InterfaceOrientation_h */
