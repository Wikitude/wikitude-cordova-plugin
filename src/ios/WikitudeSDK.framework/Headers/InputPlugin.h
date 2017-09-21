//
//  InputPlugin.h
//  FoundationSDK
//
//  Created by Andreas Schacherbauer on 29/02/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef InputPlugin_h
#define InputPlugin_h

#ifdef __cplusplus

#include <memory>
#include <functional>

#include "Geometry.h"

#include "Plugin.h"
#include "InputRenderSettings.h"
#include "InputFrameSettings.h"


namespace wikitude { namespace sdk {

    namespace impl {


        class InputFrameBufferController;

        /**
         * InputPlugins can be used to provide custom image data that is then processed and or rendered by the Wikitude SDK.
         * To decide whenever or not the Wikitude SDK should render the given input frame, use the ::requestsInputFrameRendering method.
         * In case the Wikitude SDK takes care of rendering, the memory is managed 100% by the Wikitude SDK internally and no additional code needs to be written. Just make sure that the std::shared_ptr has an appropriate deleter set (Please refer to our examples on how to do so).
         *
         * If ::requestsInputFrameRendering returns false, the Wikitude SDK still tries to manage the input frame data as good as possible, meaning that the input frame data should be retrieved through the ::getPresentableInputFrameData method.
         * This method always returns the input frame data that was processed most recently and is therefore the preferred data to render. If the input frame data is retrieved using this method, the SDK manages again all the memory related operations internally.
         * There might be cases where this is not the desired behaviour. In that case developer can override ::prepareRenderingOfInputFrame and set the managedFromOutside_ flag to true. Doing so will completely turn off any memory management in the background and developer are responsible for making sure that the input frame data, that was given with a certain id, is accessible until it's id was given in a call to ::prepareRenderingOfInputFrame.
         */
        class InputPlugin: public Plugin {

        public:
            /**
             * Defines a function that is used to connect InputPlugins with the Wikitude SDK.
             *
             * @param frameId identifies the newly available camera frame. This id is given to any other input frame related API where a specific frame is addressed.
             * @param frameData is set to a valid memory addess, containing the newly available input frame.
             * @return int specifying if the given information were valid or not
             */
            using InputFrameAvailableNotifier = std::function<int(long frameId, std::shared_ptr<unsigned char> frameData)>;

            /**
             * Defines a function that is used to connect the InputRenderSettings of the InputPlugin with the Wikitude SDK.
             *
             * @param inputRenderSettings_ is used to store all rendering related settings(e.g. should the camera frame be mirrored) of the InputPlugin.
             */
            using InputRenderSettingsChangedNotifier = std::function<void(InputRenderSettings inputRenderSettings_)>;

            /**
             * Defines a function that is used to connect the InputFrameSettings of the InputPlugin with the Wikitude SDK.
             *
             * @param inputFrameSettings_ is used to store all frame related settings(e.g. color space) of the InputPlugin.
             */
            using InputFrameSettingsChangedNotifier = std::function<void(InputFrameSettings inputFrameSettings_)>;

        public:
            InputPlugin(std::string identifier_);
            virtual ~InputPlugin();

            /**
             * Input plugins implement per default the Plugin::update method. The default implementation is empty.
             * Subclasses of InputPlugin can still override update and don't need to call the base class.
             */
            virtual void update(const RecognizedTargetsBucket& recognizedTargetsBucket_);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
            virtual void update(const std::list<RecognizedTarget>& recognizedTargets_);
#pragma clang diagnostic pop

            /**
             * Input plugins implement per default the Plugin::cameraFrameAvailable method. The default implementation is empty.
             * Subclasses of InputPlugin can still override cameraFrameAvailable and don't need to call the base class.
             */
            virtual void cameraFrameAvailable(const Frame& cameraFrame_);

            /**
             * @deprecated use InputFrameSettings instead.
             *
             * Returns the input frame color space.
             * Please refer to the enum documentation about more information. It describes in detail in which format, arrangement and size the Wikitude SDK expects given input frames.
             *
             * @return the color space in which input frames are delivered
             */
            virtual FrameColorSpace getInputFrameColorSpace() __attribute__ ((deprecated)) {
                return YUV_420_NV21;
            };

            /**
             * @deprecated use InputFrameSettings instead.
             *
             * Returns the input frame size in pixel.
             *
             * @return the input frame size in pixel
             */
            virtual Size<int> getInputFrameSize() __attribute__ ((deprecated)) { return { -1, -1 }; };

            /**
             * Defines if input frames delivered from a specific plugin should be rendered by the Wikitude SDK or not.
             *
             * In case input frames should not be rendered, they can still be processed internally or forwarded to other plugins.
             *
             * The default implementation returns true.
             *
             * @return true if input frames should be rendered, false otherwise
             */
            virtual bool requestsInputFrameRendering();

            /**
             * Defines if input frames delivered from a specific plugin should be processed by the Wikitude SDK or not.
             *
             * Returning false means that e.g. no computer vision algorithms are applied. Input frames can still be rendered or forwarded to other plugins.
             *
             * The default implementation returns true.
             *
             * @return true if input frames should be processed internally, false otherwise
             */
            virtual bool requestsInputFrameProcessing();

            /**
             * Defines if input frames delivered from a specific plugin should be forwarded to other registered plugins.
             *
             * In case input frames are not forwarded, other plugins will receive no frame at all.
             *
             * The default implementation returns true.
             *
             * @return true if input frames should be forwarded to other plugins, false otherwise
             */
            virtual bool allowsUsageByOtherPlugins();

            /**
             * Notifies the underlying Wikitude SDK about a new input frame.
             *
             * Depending on the managedFromOutside_ flag, the SDK keeps the given frame data in an internal storage and releases it once the SDK is done with it's internal usage.
             *
             * @param frameId_ is a unique identifier for each frame. Usually it starts at 1 and increments with each new frame. Specifying the same id twice leads to undefined behaviour.
             * @param inputFrame_ represents the input frame data in the color space that was returned from ::getInputFrameColorSpace. Please make sure that an appropriate deleter is set for the std::shared_ptr.
             * @param managedFromOutside_ defines if the Wikitude SDK should take care about the lifetime of the input frame data or not. Please refer to the class documentation for more information.
             */
            void notifyNewInputFrame(long frameId_, std::shared_ptr<unsigned char> inputFrame_, bool managedFromOutside_ = false);

            /**
             * @deprecated use InputFrameSettings instead.
             *
             * Notifies the underlying Wikitude SDK about a new raw camera field of view.
             *
             * This needs to be called when the camera is opened.
             *
             * @param rawCameraFieldOfView_ is the raw field of view from the platform camera.
             */
            void notifyNewRawCameraFieldOfView(float rawCameraFieldOfView_) __attribute__ ((deprecated));

            /**
             * @deprecated use InputFrameSettings instead.
             *
             * Notifies the underlying Wikitude SDK about a new dynamic camera field of view.
             *
             * This needs to be called when the camera field of view is changed for example in the case of a zoom.
             *
             * @param dynamicCameraFieldOfView_ is the new camera field of view.
             */
            void notifyNewDynamicCameraFieldOfView(float dynamicCameraFieldOfView_) __attribute__ ((deprecated));

            /**
             * In case the Wikitude SDK also renders the input frame, the InputRenderSettings object provides more information on how to do so.
             * Subclasses usually change render settings in the constructor of there InputPlugin subclass.
             *
             * @return an InputRenderSettings objects which provides more information about how to render the given input frame data.
             */
            InputRenderSettings& getRenderSettings();

            /**
             * The InputFrameSettings object provides information about the camera frame.
             * Subclasses usually change render settings in the constructor of there InputPlugin subclass.
             *
             * @return an InputFrameSettings objects which provides more information about the given input frame data.
             */
            InputFrameSettings& getFrameSettings();

            /**
             * This method is only called if ::requestsInputFrameRendering returns false. It reports back the last processed frame id. The next time an input frame is rendered, it should be the input frame that is associated with this id.
             *
             * The default implementation uses the input frame id to release any older frames from the internal frame buffer controller.
             *
             * Override this method if input frames are managed outside of the Wikitude SDK.
             *
             * A frame id of -1 indicates that the most recent input frame should be rendered.
             *
             * @param frameId_ is the id of the input frame that was last processed by the Wikitude SDK.
             */
            virtual void prepareRenderingOfInputFrame(long frameId_);

            /**
             * Use this method to retrieve the latest processed input frame data. This method is used when ::requestsInputFrameRendering returns false but the Wikitude SDK should take care about input frame memory management.
             *
             * @return the input frame data that should be used when rendering input frames.
             */
            virtual std::shared_ptr<unsigned char> getPresentableInputFrameData();

            
            /**
             * Use this method to retrieve the latest processed input frame index. This method is used when ::requestsInputFrameRendering returns false but the Wikitude SDK should take care about input frame memory management.
             *
             * @return the input frame index that should be used when rendering input frames. A value of -1 indicates that no target was found .
             */
            virtual long getPresentableInputFrameIndex();

            /**
             * These methods are called from the Wikitude SDK internally when the plugin is registered and should not be invoked from anywhere else.
             */
            void notifyInputFrameSettingsChanged(InputFrameSettings inputFrameSettings_);
            void notifyInputRenderSettingsChanged(InputRenderSettings inputRenderSettings_);
            void setInputFrameAvailableNotifier(InputFrameAvailableNotifier newInputFrameAvailableNotifier);
            void setInputRenderSettingsChangedNotifier(InputRenderSettingsChangedNotifier newInputRenderSettingsChangedNotifier_);
            void setInputFrameSettingsChangedNotifier(InputFrameSettingsChangedNotifier newInputFrameSettingsChangedNotifier_);

        private:

            /**
             * Internal InputPlugin members
             */
            InputFrameAvailableNotifier                     _newInputFrameAvailableNotifier;
            InputRenderSettingsChangedNotifier              _inputRenderSettingsChangedNotifier;
            InputFrameSettingsChangedNotifier               _inputFrameSettingsChangedNotifier;
            InputRenderSettings                             _renderSettings;
            InputFrameSettings                              _frameSettings;
            std::unique_ptr<InputFrameBufferController>     _inputFrameBufferController;
        };
    }
    using impl::FrameColorSpace;
    using impl::InputPlugin;
}}

#endif /* __cplusplus */

#endif /* InputPlugin_h */
