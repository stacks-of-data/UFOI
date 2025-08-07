#include <ufoi.hpp>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

UFOIParser::UFOIParser():
    _bLogging(false),
    _path(nullptr),
    _map_size(NULL),
    _page_size(2048),
    _line(1),
    _scene(nullptr),
    _map_addr(nullptr)
{}

UFOIParser::UFOIParser(bool bLogging, size_t page_size):
    _bLogging(bLogging),
    _path(nullptr),
    _map_size(NULL),
    _page_size(page_size),
    _line(1),
    _scene(nullptr),
    _map_addr(nullptr)
{}

UFOIParser::~UFOIParser()
{}

void UFOIParser::parseMapFile()
{
    struct stat statbuf;

    if (access(this->_path->c_str(), F_OK) == -1)
    {
        if (errno != EACCES)
            throw UFOI::AccessError();
        throw UFOI::FileNotFound();
    }
    if (access(this->_path->c_str(), R_OK) == -1)
    {
        if (errno != EACCES)
            throw UFOI::AccessError();
        throw UFOI::ReadAccessDenied();
    }
    int fd = open(this->_path->c_str(), O_RDONLY);
    if (fd == -1)
        throw UFOI::OpenFileError();
    if (fstat(fd, &statbuf) == -1)
    {
        close(fd);
        throw UFOI::FileStatError();
    }
    this->_map_addr = (char*)mmap(nullptr, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (this->_map_addr == (void*)-1)
        throw UFOI::MemoryMapError();
    this->_map_size = statbuf.st_size;
    this->_map_end = this->_map_addr + this->_map_size;
}

bool UFOIParser::tokenCmp(char* map_ptr, char* tok)
{
    while (true)
    {
        if (*map_ptr != *tok)
            return false;
        if (*tok == '\0')
        {
            if (isspace(*map_ptr) || *map_ptr == '\0' || map_ptr == this->_map_end)
                return true;
            return false;
        }
        map_ptr++;
        tok++;
    }
}

void UFOIParser::parseProcessData()
{
    char* map_ptr = this->_map_addr;

    while (map_ptr != this->_map_end)
    {

    }
}

void UFOIParser::cleanParser()
{
    this->_path = nullptr;
    this->_map_size = NULL;
    this->_page_size = 2048;
    this->_line = 1;
    this->_scene = nullptr;
    this->_map_addr = nullptr;
}

UFOIScene* UFOIParser::parse(const std::string& path)
{
    this->_path = &path;
    this->_scene = new UFOIScene();

    try
    {
        parseMapFile();
        parseProcessData();
        munmap(this->_map_addr, this->_map_size);
    }
    catch (const std::exception& e)
    {
        delete this->_scene;
        if (this->_map_addr)
            munmap(this->_map_addr, this->_map_size);
        cleanParser();
        throw;
    }

    cleanParser();
    return this->_scene;
}