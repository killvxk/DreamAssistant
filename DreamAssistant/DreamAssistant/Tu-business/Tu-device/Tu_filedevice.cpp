#include "Tu_filedevice.h"

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <direct.h>
#include <functional>

struct ExitCaller {
    ~ExitCaller() { functor_(); }
    ExitCaller(std::function<void()> &&functor) : functor_(std::move(functor)) {}

private:
    std::function<void()> functor_;
};

bool FileDevice::fileExists(const std::string &fname)
{
    return access(fname.c_str(), 0) == 0;
}

bool FileDevice::renameFile(const std::string &src, const std::string &target)
{
    return rename(src.c_str(), target.c_str()) == 0;
}

bool FileDevice::getFileSize(const std::string &fname, uint64_t *size)
{
    struct stat sbuf;
    if (stat(fname.c_str(), &sbuf) != 0) {
        *size = 0;
        return false;
    } else {
        *size = sbuf.st_size;
    }

    return true;
}

bool FileDevice::createDir(const std::string &name)
{
    return mkdir(name.c_str()) == 0;
}

bool FileDevice::deleteDir(const std::string &name)
{
    return rmdir(name.c_str()) == 0;
}

bool FileDevice::deleteFile(const std::string &fname)
{
    return unlink(fname.c_str()) == 0;
}

bool FileDevice::copyFile(const std::string &src, const std::string &target)
{
    return true;
}

bool FileDevice::getChildren(const std::string &dir, std::vector<std::string> *result) 
{
    result->clear();

    DIR *d = opendir(dir.c_str());
    if (d == NULL) {
        return false;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        result->push_back(entry->d_name);
    }

    closedir(d);

    return false;
}

bool FileDevice::renameSave(const std::string &name, const std::string &tmpName, const std::string &cont)
{
    bool is_ok = writeContent(tmpName, cont);
    if (!is_ok) {
        return false;
    }

    unlink(name.c_str());

    return renameFile(tmpName, name);
}

bool FileDevice::getContent(const std::string &filename, std::string &cont) 
{
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        return false;
    }

    ExitCaller ec1([=] { close(fd); });
    char buf[4096];
    for (;;) {
        int r = read(fd, buf, sizeof buf);
        if (r < 0) {
            return false;
        } else if (r == 0) {
            break;
        }
        cont.append(buf, r);
    }

    return true;
}

bool FileDevice::writeContent(const std::string &filename, const std::string &cont) 
{
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return false;
    }

    ExitCaller ec1([=] { close(fd); });
    int r = write(fd, cont.data(), cont.size());
    if (r < 0) {
        return false;
    }

    return true;
}

