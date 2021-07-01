//
//  WTDeprecation.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 22.04.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTDeprecation_h
#define WTDeprecation_h

#define WT_DEPRECATED_SINCE(__version__, __msg__) __attribute__((deprecated("Deprecated in Wikitude SDK " #__version__ ". " __msg__)))

#endif /* WTDeprecation_h */
