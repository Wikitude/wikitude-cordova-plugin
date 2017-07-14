//
//  RecognizedTargetsBucket.h
//  Wikitude SDK
//
//  Created by Andreas Schacherbauer on 12.05.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef RecognizedTargetsBucket_h
#define RecognizedTargetsBucket_h

#ifdef __cplusplus

#include <list>
#include <functional>

#include "RecognizedTarget.h"


namespace wikitude { namespace sdk {

    namespace impl {


        class RecognizedTargetsBucketConnector {
        public:
            void setImageTargetsHandler(std::function<std::list<ImageTarget>&()> getImageTargets_);
            void setObjectTargetsHandler(std::function<std::list<ObjectTarget>&()> getObjectTargets_);
            void setInstantTargetsHandler(std::function<std::list<InstantTarget>&()> getInstantTargets_);
        public:
            std::function<std::list<ImageTarget>&()>    _getImageTargets;
            std::function<std::list<ObjectTarget>&()>   _getObjectTargets;
            std::function<std::list<InstantTarget>&()>  _getInstantTargets;
        };

        class RecognizedTargetsBucket {
        public:
            RecognizedTargetsBucket(const RecognizedTargetsBucketConnector& recognizedTargetsBucketConnector_);
            ~RecognizedTargetsBucket() = default;

            const std::list<ImageTarget>& getImageTargets() const;
            const std::list<ObjectTarget>& getObjectTargets() const;
            const std::list<InstantTarget>& getInstantTargets() const;

        private:
            RecognizedTargetsBucketConnector _recognizedTargetsBucketConnector;
        };
    }
    using impl::RecognizedTargetsBucket;
    using impl::RecognizedTargetsBucketConnector;
}}

#endif /* __cplusplus */

#endif /* RecognizedTargetsBucket_h */
