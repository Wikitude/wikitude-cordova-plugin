//
// Created by simon on 08/04/15.
// Copyright (c) 2015 Wikitude. All rights reserved.
//


#ifndef PLUGIN_H_
#define PLUGIN_H_

#ifdef __cplusplus

#include <list>
#include <string>
#include <memory>
#include <unordered_map>

#include "Geometry.h"
#include "InterfaceOrientation.h"
#include "RenderingAPI.h"
#include "RenderingContext.h"

#include "RecognizedTargetsBucket.h"


namespace wikitude {
    namespace sdk_core {
        namespace impl {
            class PositionableWrapper;
        }
        using impl::PositionableWrapper;
    }
    
    namespace sdk {
        namespace impl {

            class Frame;
            class RecognizedTarget;

            /**
             * Describes the plugin type in more detail.
             * Different plugins are treated differently internally.
             */
            enum class PluginType : int {
                /** Standard plugins are of type Plugin */
                Standard,
                /** Input plugins return Input */
                Input
            };
        
        class Plugin {
            
        public:

            /**
             * Constructor, pass a unique identifier for each of your plugins.
             */
            Plugin(std::string identifier_);

            virtual ~Plugin();

            /**
             * Returns the type of the plugin. Plugins can either be standard plugins or input plugins.
             */
            PluginType getPluginType() const;

            /**
             * Will be called once after your Plugin was successfully added to the Wikitude Engine. Initialize your plugin here.
             */
            virtual void initialize();

            /**
             * Will be called every time the Wikitude Engine pauses.
             */
            virtual void pause();
            
            /**
             * Will be called when the Wikitude Engine starts for the first time and after every pause.
             * 
             * @param pausedTime_ the duration of the pause in milliseconds
             */
            virtual void resume(unsigned int pausedTime_);

            /**
             * Will be called every time the SDK surface size changes.
             * It is also called right after the plugin is initialzed.
             */
            virtual void surfaceChanged(Size<int> renderSurfaceSize_, Size<float> cameraSurfaceScaling_, InterfaceOrientation interfaceOrientation_);

            /**
             * Will be called when the Wikitude Engine shuts down.
             */
            virtual void destroy();

            /**
             * Will be called every time the Wikitude Enigine receives a new camera frame from the platform camera.
             *
             * @param cameraFrame_ frame wrapper object which contains the frame data and some metadata about the frame
             */
            virtual void cameraFrameAvailable(const Frame& cameraFrame_) = 0;

            /**
             * Will be called after every image recognition cycle.
             *
             * @param recognizedTargetsBucket_ an object providing access to all targets recognized in this specific frame
             */
            virtual void update(const RecognizedTargetsBucket& recognizedTargetsBucket_) = 0;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
            virtual void update(const std::list<RecognizedTarget>& recognizedTargets_);
#pragma clang diagnostic pop

            /**
             * Will be called continuously to update positionables.
             *
             * @param positionables_ a dictionary of PositionableWrapper pointers accessible by string ID
             *
             * Note: This method is only available when using the Wikitude Architect SDK (JS API).
             */
            virtual void updatePositionables(const std::unordered_map<std::string, sdk_core::PositionableWrapper*>& positionables_);
            
            /**
             * Will be called before any Wikitude SDK internal rendering is done. Therefore any drawn objects are behind any Wikitude SDK object.
             */
            virtual void startRender();
            
            /**
             * Will be called right after any Wikitude SDK internal rendering is done. Therefore any drawn objects are in front of any Wikitude SDK object.
             */
            virtual void endRender();

            /**
             * Use this method to enqueue JavaScript calls that are evaluated in the upcoming frame.
             * Note: This method is only available when using the Wikitude Architect SDK (JS API).
             * Note: This method should not be overriden.
             */
            virtual void addToJavaScriptQueue(const std::string& javaScriptSnippet_);
            
            /**
             * Method used internally to get all pending JavaScript calls and execute them in the Wikitude Architect SDK (JS API) web view context.
             * Note: This method should not be overriden.
             */
            virtual std::list<std::string>& getJavaScriptQueue();

            /**
             * Returns the identifier of this particular plugin.
             * Note: This method should not be overriden.
             */
            virtual const std::string& getIdentifier() const;

            /**
             * Set's this plugin enabled or not. A enabled plugin receives cameraFrameAvailable, update, startRender and endRender calls. 
             */
            virtual void setEnabled(bool enabled_);
            
            /**
             * Return the enabled state of this particular plugin.
             */
            virtual bool isEnabled() const;
            
            /**
             * When the plugin does some rendering, this method should return the RenderingAPI used. This should match the rendering API chosen when the SDK was started.
             */
            virtual sdk::RenderingAPI requestRendering();
            
            /**
             * Returns the current RenderingContext that can be used for rendering inside the plugin. 
             * For rendering APIs such as Metal, additional objects are needed to do any rendering, and these are supplied in the appropriate subclass of RenderingContext.
             * The RenderingContext returned here is only guaranteed to be valid between calls to startRender and endRender.
             * The RenderingContext returned here is NOT valid if the RenderingAPI returned by the requestRenderingg method is RenderingAPI::None.
             * Note: This method should not be overriden.
             */
            virtual std::shared_ptr<sdk::RenderingContext> getRenderingContext() const;
            
            /**
             * Method used internally to set the current RenderingContext before startRender is called.
             * Note: This method should not be overriden.
             */
            virtual void setRenderingContext(std::shared_ptr<sdk::RenderingContext> renderingContext_);
            
            /**
             * This method is called whenever an internal error occurs that was not directly related to any InputPlugin related API call.
             *
             * The default implementation is empty.
             *
             * @param errorMessage_ describes the internal error in more detail
             */
            virtual void internalError(const std::string& errorMessage_);
            
        protected:
            PluginType      _type;
        private:
            std::string     _identifier;
            bool            _enabled;

            std::list<std::string> _javaScriptQueue;
            std::shared_ptr<sdk::RenderingContext> _renderingContext;
        };
    }
    using impl::PluginType;
    using impl::Plugin;    
}}

#endif /* __cplusplus */

#endif //__Plugin_H_
