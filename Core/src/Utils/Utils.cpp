#include "Utils.h"
#include "sstream"

namespace gama{
    std::vector<std::string> tokenize(const std::string& target,const std::string& delimiter) {
        std::vector<std::string> tokens;
        std::stringstream statusStream(target);
        std::string token;

        while (getline(statusStream, token, delimiter.front())){
            tokens.push_back(token);
        }

        return tokens;
    }
}