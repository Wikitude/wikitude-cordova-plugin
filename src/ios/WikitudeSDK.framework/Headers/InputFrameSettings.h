//
// InputFrameSettings
//
// Created by Alexander Bendl on 02/01/17.
// Copyright (c) 2017 Wikitude. All rights reserved.
//

#ifndef InputFrameSettings_h
#define InputFrameSettings_h

#include "FrameColorSpace.h"
#include "Geometry.h"

#ifdef __cplusplus

namespace wikitude { namespace sdk {
    namespace impl {

        class InputPlugin;

        class InputFrameSettings {
        public:
            InputFrameSettings(InputPlugin* inputPlugin_);
            virtual ~InputFrameSettings();

            /**
             * Returns the input frame color space.
             * Please refer to the enum documentation about more information. It describes in detail in which format, arrangement and size the Wikitude SDK expects given input frames.
             *
             * @return the color space in which input frames are delivered
             */
            FrameColorSpace getInputFrameColorSpace() const;

            /**
             * Returns the horizontal field of view of the input frame in degree.
             * If the returned value is not correct for the current input  frame, computer vision algorithm preciseness is lost.
             *
             * @return the cameras horizontal field of view in degree.
             */
            float getFrameFieldOfView() const;

            /**
             * Returns the input frame size in pixel.
             *
             * @return the input frame size in pixel
             */
            const Size<int>& getInputFrameSize() const;

            /**
             * Sets the input frame color space.
             * Please refer to the enum documentation about more information. It describes in detail in which format, arrangement and size the Wikitude SDK expects given input frames.
             */
            void setInputFrameColorSpace( FrameColorSpace inputFrameColorSpace_ );

            /**
             * This sets the horizontal field of view of the input frame in degree.
             * If the returned value is not correct for the current input frame, computer vision algorithm preciseness is lost.
             */
            void setFrameFieldOfView( float frameFieldOfView_ );

            /**
             * Sets the input frame size in pixel.
             */
            void setInputFrameSize( const Size<int>& inputFrameSize_ );

        private:
            FrameColorSpace     _inputFrameColorSpace;
            float               _frameFieldOfView;
            Size<int>           _inputFrameSize;
            InputPlugin*        _inputPlugin;
        };
    }
    using impl::InputFrameSettings;
}}

#endif //cplusplus

#endif //InputFrameSettings_h
