//
// Created by ka on 8/14/26.
//

#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <string>

enum class ParseErrorCode {
    UnexpectedToken,
    ExpectedCommand,
    ExpectedRedirectionTarget,
    EmptyPipelineCommand,
};

struct ParseError {
    ParseErrorCode code;
    std::string message;
};

#endif // PARSE_ERROR_H
