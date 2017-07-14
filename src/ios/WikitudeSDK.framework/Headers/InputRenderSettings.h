//
//  InputRenderSettings.h
//  FoundationSDK
//
//  Created by Andreas Schacherbauer on 12/03/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef InputRenderSettings_h
#define InputRenderSettings_h

#ifdef __cplusplus


namespace wikitude { namespace sdk {

    namespace impl {

        class InputPlugin;

        class InputRenderSettings {
        public:
            InputRenderSettings(InputPlugin* inputPlugin_);
            virtual ~InputRenderSettings();

            /**
             * Defines if given input frames should be mirrored when rendering. This setting should be used when e.g. front cameras are used.
             *
             * The default constructor sets the _renderedMirrored member variable to false.
             *
             * @return true if given input frames should be mirrored when rendered by the Wikitude SDK, false otherwise.
             */
            bool renderedMirrored();
            
            /**
             * The default constructor sets the _baseOrientationLandscape member variable to false.
             *
             * @return true if the the default device orientation is landscape, false if portrait.
             */
            bool baseOrientationLandscape();

            /**
             * The default constructor sets the _renderTargetTextureId member variable to 0.
             *
             * @return the value that is currently set for the _renderTargetTextureId member variable.
             */
            unsigned int renderTargetTextureId();
            
            /**
             * Sets the _renderedMirrored member variable returned by renderedMirrored.
             *
             * The default constructor sets the _renderedMirrored member variable to false.
             */
            void setRenderedMirrored(bool mirrored);
            
            /**
             * Sets the _baseOrientation member variable returned by baseOrentationLandscape.
             *
             * The default constructor sets the _baseOrientationLandscape member variable to false.
             */
            void setBaseOrientationLandscape(bool baseOrientationLandscape);

            /**
             * Sets the _renderTargetTextureId member variable returned by renderTargetTextureId.
             *
             * The default constructor sets the _renderTargetTextureId member variable to 0.
             *
             * A value greater of 0 indicates that the SDK will render directly into the texture that is associated with this id.
             * If the value is 0, the SDK will render directly to the screen.
             */
            void setRenderTargetTextureId(unsigned int renderTargetTextureId);
            
        private:
            bool            _renderedMirrored;
            bool            _baseOrientationLandscape;

            unsigned int    _renderTargetTextureId;

            InputPlugin*    _inputPlugin;
        };
    }
    using impl::InputRenderSettings;
}}

#endif /* __cplusplus */

#endif /* InputRenderSettings_h */
