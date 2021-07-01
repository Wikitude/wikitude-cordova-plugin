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

#include "CompilerAttributes.hpp"


namespace wikitude::sdk {

        /**
         * A simple data type to represent an error. Domains help to reduce the amount of unique codes by introducing an additional layer of separation.
         * Underlying erros can be specified to build up a chain of erros that explain the problem from various different layers. This should help explain where the error originates from.
        */
        class WT_EXPORT_API Error {
        public:
            /* Use this to construct an empty error, if certain APIs require an error object even if no error was actually triggered */
            static Error NoError();
            
            Error(const int code_, const std::string& domain_, const std::string& message_, std::unique_ptr<Error> underlyingError_ = nullptr, bool suppressErrorLogging_ = false);
            Error(const Error& other_);
            virtual ~Error() = default;

            Error& operator = (const Error& other_);
            friend WT_EXPORT_API std::ostream& operator << (std::ostream& os_, const Error& error_);


            int getCode() const;
            const std::string& getDomain() const;
            const std::string& getMessage() const;

            const Error* getUnderlyingError() const;

            /**
             * Returns a string representation of a particular error object. The format is like the following for a error with code 1000, domain "com.example.domain" and message "Description of a fictive error"
             * `code: 1000, domain: "com.example.domain", message: "Description of a fictive error"`
             */
            std::string getDescription() const;

            /**
            * Returns a string representation of a particular error object including all underlying errors.
            * ```
            * {
            *    code: 101,
            *    domain: "com.wikitude.test",
            *    message: "simple error message",
            *    underlyingError: {
            *        code: 5005,
            *        domain: "com.wikitude.subtest",
            *        message: "detailed error message",
            *        underlyingError: {
            *            code: 42,
            *            domain: "com.wikitude.network_layer",
            *            message: "Callback Aborted"
            *        }
            *    }
            * }
            * ```
            */
            std::string getFormattedDescription() const;

        private:
            std::string getUnderlyingFormattedDescription() const;
            
            /* This is private in order to force the usage of the more explicit NoError static function */
            Error();

        protected:
            int               _code;
            std::string       _domain;
            std::string       _message;

            std::unique_ptr<Error>  _underlyingError;
        };
}

#endif /* __cplusplus */

#endif /* Error_h */
