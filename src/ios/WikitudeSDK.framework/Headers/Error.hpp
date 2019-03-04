//
//  Error.h
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 12.08.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef Error_h
#define Error_h

#ifdef __cplusplus

#include <string>
#include <memory>
#include <sstream>


namespace wikitude { namespace sdk {

    namespace impl {


        class Error {
        public:
            Error(const int code_, const std::string& domain_, const std::string& message_, std::unique_ptr<Error> underlyingError_ = nullptr);
            Error(const Error& other_);
            virtual ~Error() = default;

            Error& operator = (const Error& other_);
            friend std::ostream& operator << (std::ostream& os_, const Error& error_);


            int getCode() const;
            const std::string& getDomain() const;
            const std::string& getMessage() const;

            const Error* getUnderlyingError() const;

            std::string getDescription() const;
            std::string getFormattedDescription() const;

        private:
            std::string getUnderlyingFormattedDescription() const;

        protected:
            int               _code;
            std::string       _domain;
            std::string       _message;

            std::unique_ptr<Error>  _underlyingError;
        };
    }
    using impl::Error;
}}

#endif /* __cplusplus */

#endif /* Error_h */
