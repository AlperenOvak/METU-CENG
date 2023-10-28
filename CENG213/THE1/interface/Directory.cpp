#include "Directory.h"

File Directory::getFile(int index) const
{
	/* TODO */
	if (index < 0 || index >= static_cast<int>(files.size())) {
        return File();
    }
    return files[index];
}

size_t Directory::directorySize() const
{
	/* TODO */
	size_t size = 0;
	int numFile = numFiles();
    for (int i=0;i<numFile;i++) {
        size += files[i].fileSize();
    }
    return size;
}

bool Directory::isEmpty() const
{
	/* TODO */
	return !(static_cast<int>(numFiles()));
}

size_t Directory::numFiles() const
{
	/* TODO */
	return files.size();
}

void Directory::newFile(const File &file)
{
	/* TODO */
	files.push_back(file);
}

void Directory::removeFile(int index)
{
	/* TODO */
	if (index < static_cast<int>(files.size())) {
        files.erase(files.begin() + index);
    }
}

void Directory::removeFile(File &file)
{
	/* TODO */
	for (std::vector<File>::iterator it = files.begin(); it != files.end(); ++it) {
        if (*it == file) {
            files.erase(it);
            break;
        }
    }
	
}

void Directory::removeBiggestFile()
{
	/* TODO */
	if (isEmpty()) {
        return;
    }
    std::vector<File>::size_type maxSize = 0;
    std::vector<File>::size_type biggestFileIndex = 0;
    for (std::vector<File>::size_type i = 0; i < files.size(); i++) {
        if (files[i].fileSize() >= maxSize) {
            maxSize = files[i].fileSize();
            biggestFileIndex = i;
        }
    }
    files.erase(files.begin() + biggestFileIndex);
}
