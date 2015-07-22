#include <glt/fileutils.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <algorithm>

namespace glt {

bool readAllAsciiText(const std::string& filepath, std::ostream& out)
{
    std::ifstream      file;
    std::ostringstream stream;

    file.open(filepath, std::ios_base::in);

    if (file.is_open())
    {
        out << file.rdbuf();
        file.close();
    }

    return !file.bad() && !file.fail();
}

const std::unordered_map<std::string, int> SHADER_MAP = {
    { "vert", gl::VERTEX_SHADER },
    { "frag", gl::FRAGMENT_SHADER },
    { "geom", gl::GEOMETRY_SHADER },
    { "tese", gl::TESS_EVALUATION_SHADER },
    { "tesc", gl::TESS_CONTROL_SHADER },
    { "comp", gl::COMPUTE_SHADER }
};

GLenum shaderType(const std::string& filename)
{
    std::smatch match;
    std::regex  re(".*\\.(vert|frag|geom|tese|tesc|comp)$",
                   std::regex::ECMAScript | std::regex::icase);

    if (std::regex_match(filename, match, re) && match.size() == 2)
    {
        auto ext = match[1].str();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        auto result = SHADER_MAP.find(ext);
        if (result != SHADER_MAP.end())
            return result->second;
    }

    return -1;
}

} /* end namespace glt */
