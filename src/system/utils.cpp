#include "pch.h"
#include "utils.h"

#include "Log.h"
#include "exception/Exception.h"

#include <stdio.h>
#include <string>

namespace tk {
std::string read_file(const char* filename)
{
    try {
        FILE* fp;
        if ((fp = fopen(filename, "r")) == NULL) {
            throw Exception("Unable to open file. Does it exists ?");
        }

        std::string data;
        char c;
        for (unsigned i = 0; (c = fgetc(fp)) != EOF; i++) {
            data.push_back(c);
        }

        return data;

    } catch (Exception& e) {
        LOG_ERROR("Could not read file \"{}\": {}", filename, e.what());
        throw Exception("Failed to read file \"" + std::string(filename) + "\"");
    }
}
};  // namespace tk