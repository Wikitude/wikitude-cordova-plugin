//
//  Positionable.hpp
//  SDKCore
//
//  Created by Daniel Guttenberg on 24/09/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef __PositionableWrapper__
#define __PositionableWrapper__

#ifdef __cplusplus

#include <functional>


namespace wikitude { namespace sdk {

    namespace impl {

        class PositionableFunctionCollection
        {
        public:
            void setSetXHandler(std::function<void(float x_)> setX_) { _setX = setX_; }
            void setSetYHandler(std::function<void(float y_)> setY_) { _setY = setY_; }
            void setSetWorldMatrixHandler(std::function<void(const float* const worldMatrix_)> setWorldMatrix_) { _setWorldMatrix = setWorldMatrix_; }
            void setSetViewMatrixHandler(std::function<void(const float* const viewMatrix_)> setViewMatrix_) { _setViewMatrix = setViewMatrix_; }
            void setSetProjectionMatrixHandler(std::function<void(const float* const projectionMatrix_)> setProjectionMatrix_) { _setProjectionMatrix = setProjectionMatrix_; }
            void setUpdateHandler(std::function<void()> update_) { _update = update_; }
            void setEnteredFieldOfVisionHandler(std::function<void()> enteredFieldOfVision_) { _enteredFieldOfVision = enteredFieldOfVision_; }
            void setExitedFieldOfVisionHandler(std::function<void()> exitedFieldOfVision_) { _exitedFieldOfVision = exitedFieldOfVision_; }

        public:
            std::function<void(float x_)> _setX;
            std::function<void(float y_)> _setY;
            std::function<void(const float* const worldMatrix_)> _setWorldMatrix;
            std::function<void(const float* const viewMatrix_)> _setViewMatrix;
            std::function<void(const float* const projectionMatrix_)> _setProjectionMatrix;
            std::function<void()> _update;
            std::function<void()> _enteredFieldOfVision;
            std::function<void()> _exitedFieldOfVision;
        };

        /**
         * This wrapper class simply forwards calls to the contained implementation according to the pimpl-idiom. This is requires as the interals of the PositionableInternal class are not to be exposed publicly.
         */
        class Positionable {
        public:

            /**
             * Ctor
             *
             * @param positionableFunctionCollection_ A pointer to a PositionableInternal object. Ownership of the memory remains with the caller.
             *
             */
            Positionable(const PositionableFunctionCollection& positionableFunctionCollection_);

            /**
             * Sets the X-coordinate of the 2D screen position.
             *
             * @param x_ The X-coordinate of the 2D screen position in normalized device coordinates [-1, 1].
             *
             */
            void setX(float x_);

            /**
             * Sets the Y-coordinate of the 2D screen position.
             *
             * @param y_ The Y-coordinate of the 2D screen position in normalized device coordinates [-1, 1].
             *
             */
            void setY(float y_);

            /**
             * Sets the 4 by 4 world-matrix.
             *
             * @param worldMatrix_ A float pointer referencing 16 float values in a block of consecutive memory.
             *
             * @discussion For 2D drawables (ImageDrawable, AnimatedImageDrawable, VideoDrawable, Circle, Label, HtmlDrawable) the world-matrix is to be set to the model-view-projection-matrix. The view- and projection matrices are ignored and recommended to be set to the identity-matrix. For 3D drawables (Model) the world matrix is ignored and recommended to be set to the identity-matrix.
             *
             */
            void setWorldMatrix(const float* const worldMatrix_);

            /**
             * Sets the 4 by 4 view-matrix.
             *
             * @param viewMatrix_ A float pointer referencing 16 float values in a block of consecutive memory.
             *
             * @discussion For 2D drawables (ImageDrawable, AnimatedImageDrawable, VideoDrawable, Circle, Label, HtmlDrawable) the view-matrix is ignored and recommended to be set to the identity-matrix. For 3D drawables (Model) the view-matrix is to be set to the model-view-matrix, while the world matrix is ignored and recommended to be so to the identity-matrix.
             */
            void setViewMatrix(const float* const viewMatrix_);

            /**
             * Sets the 4 by 4 projection-matrix.
             *
             * @param projectionMatrix_ A float pointer referencing 16 float values in a block of consecutive memory.
             *
             * @discussion For 2D drawables (ImageDrawable, AnimatedImageDrawable, VideoDrawable, Circle, Label, HtmlDrawable) the projection-matrix is ignored and recommended to be set to the identity-matrix. For 3D drawables (Model) the projection-matrix is to be set to the projection-matrix, while the world matrix is ignored and recommended to be so to the identity-matrix.
             */
            void setProjectionMatrix(const float* const projectionMatrix_);

            /**
             * Updates the contained PositionableImplementation. It advanced the screen snapping timer and sets the required matrices should screen snapping be enabled. Called within the architect loop.
             */
            void update();

            /**
             * To be called within the plugin upon recognizing a target.
             */
            void enteredFieldOfVision();

            /**
             * To be called within the plugin upon losing a tracked target.
             */
            void exitedFieldOfVision();

        private:
            PositionableFunctionCollection _positionableFunctionCollection;
        };
    }
    using impl::PositionableFunctionCollection;
    using impl::Positionable;
}}

#endif /* __cplusplus */

#endif /* defined(__PositionableWrapper__) */
