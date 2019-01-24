#ifndef TU_FILEDEVICE_H
#define TU_FILEDEVICE_H

#include <string>
#include <vector>
#include <stdint.h>
#include <stdio.h>

class FileDevice
{
public:
    static bool getContent(const std::string &filename, std::string &cont);
    static bool writeContent(const std::string &filename, const std::string &cont);

    static bool renameSave(const std::string &name, const std::string &tmpName, const std::string &cont);
    static bool getChildren(const std::string &dir, std::vector<std::string> *result);

    static bool deleteFile(const std::string &fname);
    static bool copyFile(const std::string &src, const std::string &target);

    static bool createDir(const std::string &name);
    static bool deleteDir(const std::string &name);

    static bool getFileSize(const std::string &fname, uint64_t *size);
    static bool renameFile(const std::string &src, const std::string &target);

    static bool fileExists(const std::string &fname);
};

#endif // TU_FILEDEVICE_H
