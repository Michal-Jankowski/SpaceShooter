#include "Shader.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

bool Shader::loadShaderFromFile(const std::string& file, GLenum shaderType) {
    std::vector<std::string> shaderLines;

    if (!getLinesFromFile(file, shaderLines))
        return false;

    const char** programSource = new const char* [shaderLines.size()];
    for (size_t i = 0; i < shaderLines.size(); i++)
        programSource[i] = shaderLines[i].c_str();

    m_shaderID = glCreateShader(shaderType);

    glShaderSource(m_shaderID, static_cast<GLsizei>(shaderLines.size()), programSource, nullptr);
    glCompileShader(m_shaderID);

    delete[] programSource;

    int compilationStatus;
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compilationStatus);

    if (compilationStatus == GL_FALSE)
    {
        char shaderLogBuffer[2048];
        int logLength;
        glGetShaderInfoLog(m_shaderID, 2048, &logLength, shaderLogBuffer);
        std::cout << "Error! Shader file " << file << " wasn't compiled! The compiler returned:\n\n" << shaderLogBuffer << std::endl;
        return false;
    }
    this->m_shaderType = shaderType;
    m_hasLoaded = true;

    return true;
}

bool Shader::hasLoaded() const {
    return m_hasLoaded;
}

GLuint Shader::getShaderID() const {
    return m_shaderID;
}

GLenum Shader::getShaderType() const {
    return m_shaderType;
}

void Shader::deleteShader() {
    if (!m_hasLoaded) {
        return;
    }
    m_hasLoaded = false;
    glDeleteShader(m_shaderID);
}

inline std::vector<std::string> split(std::string s, char t)
{
    std::vector<std::string> res;
    while (true)
    {
        auto pos = s.find(t);
        if (pos == -1)
        {
            if (s.size() > 0)
                res.push_back(s);
            break;
        }
        std::string tp = s.substr(0, pos);
        if (tp.size() != 0)
            res.push_back(tp);
        s = s.substr(pos + 1, s.size() - pos - 1);
    }
    return res;
}

inline std::string upOneDirectory(const std::string& originalPath, char slashCharacter)
{
    bool isTrailingSlash = originalPath.back() == slashCharacter;
    std::vector<std::string> subPaths = split(originalPath, slashCharacter);
    std::string result = "";
    for (size_t i = 0; i < subPaths.size() - 1; i++)
    {
        if (i > 0)
            result += slashCharacter;
        result += subPaths[i];
    }
    if (isTrailingSlash && result.size() > 0)
        result += slashCharacter;

    return result;
}

bool Shader::getLinesFromFile(const std::string& fileName, std::vector<std::string>& result, bool isReadingIncludedFile) const {
    std::ifstream file(fileName);

    if (!file.good()) {
        std::cout << "File " << fileName << " not loaded! Set the working directory of the application to $(SolutionDir)res/)" << std::endl;
        return false;
    }

    std::string startDirectory;
    char slashCharacter = '/';
    size_t slashIndex = -1;
    for (int i = static_cast<int>(fileName.size()) - 1; i >= 0; i--)
    {
        if (fileName[i] == slashCharacter)
        {
            slashIndex = i;
            break;
        }
    }

    startDirectory = fileName.substr(0, slashIndex + 1);

    // Get all lines from a file

    std::string line;
    bool isInsideIncludePart = false;

    while (std::getline(file, line))
    {
        line += "\n"; // getline does not keep newline character
        std::stringstream ss(line);
        std::string firstLine;
        ss >> firstLine;
        if (firstLine == "#include")
        {
            std::string includeFileName;
            ss >> includeFileName;
            if (includeFileName.size() > 0 && includeFileName[0] == '\"' && includeFileName[includeFileName.size() - 1] == '\"')
            {
                includeFileName = includeFileName.substr(1, int(includeFileName.size()) - 2);
                std::string directory = startDirectory;
                std::vector<std::string> subPaths = split(includeFileName, slashCharacter);
                std::string sFinalFileName = "";
                for (const std::string& subPath : subPaths)
                {
                    if (subPath == "..")
                        directory = upOneDirectory(directory, slashCharacter);
                    else
                    {
                        if (sFinalFileName.size() > 0)
                            sFinalFileName += slashCharacter;
                        sFinalFileName += subPath;
                    }
                }
                const auto combinedIncludeFilePath = directory + sFinalFileName;
                getLinesFromFile(startDirectory + includeFileName, result, true);
            }
        }
        else if (firstLine == "#include_part")
            isInsideIncludePart = true;
        else if (firstLine == "#definition_part")
            isInsideIncludePart = false;
        else if (!isReadingIncludedFile || (isReadingIncludedFile && isInsideIncludePart))
            result.push_back(line);
    }

    file.close();

    return true;
}
