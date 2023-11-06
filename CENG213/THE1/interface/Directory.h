#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include <vector>

class Directory{
public:

	File getFile(int index) const;
	size_t directorySize() const;
	bool isEmpty() const;
	size_t numFiles() const;

	void newFile(const File &file);
	void removeFile(int index);
	void removeFile(File &file);
	void removeBiggestFile();

private:
	std::vector<File> files;
};

File Directory::getFile(int index) const
{
    /* Get the file at the specified index from the directory. */

    if (index < 0 || index >= static_cast<int>(files.size())) {
        return File(); // Return an empty file if the index is out of bounds.
    }
    return files[index]; // Return the file at the given index.
}

size_t Directory::directorySize() const
{
    /* Calculate and return the total size of the directory, which is the sum of the sizes of all files in it. */

    size_t size = 0;
    int numFile = numFiles();
    for (int i = 0; i < numFile; i++) {
        size += files[i].fileSize();
    }
    return size;
}

bool Directory::isEmpty() const
{
    /* Check if the directory is empty (contains no files). */

    return !(static_cast<int>(numFiles())); // The directory is empty if the number of files is zero.
}

size_t Directory::numFiles() const
{
    /* Get the number of files in the directory. */

    return files.size();
}

void Directory::newFile(const File &file)
{
    /* Add a new file to the directory. */

    files.push_back(file); // Append the new file to the list of files in the directory.
}

void Directory::removeFile(int index)
{
    /* Remove a file at the specified index from the directory. */

    if (index < static_cast<int>(files.size())) {
        files.erase(files.begin() + index); // Erase the file at the given index.
    }
}

void Directory::removeFile(File &file)
{
    /* Remove the first occurrence of a specified file from the directory. */

    for (std::vector<File>::iterator it = files.begin(); it != files.end(); ++it) {
        if (*it == file) {
            files.erase(it); // Erase the first occurrence of the specified file.
            break;
        }
    }
}

void Directory::removeBiggestFile()
{
    /* Find and remove the biggest file from the directory. */

    if (isEmpty()) {
        return; // If the directory is empty, do nothing.
    }
    std::vector<File>::size_type maxSize = 0;
    std::vector<File>::size_type biggestFileIndex = 0;
    for (std::vector<File>::size_type i = 0; i < files.size(); i++) {
        if (files[i].fileSize() >= maxSize) {
            maxSize = files[i].fileSize(); // Update the maximum size.
            biggestFileIndex = i; // Keep track of the index of the biggest file.
        }
    }
    files.erase(files.begin() + biggestFileIndex); // Remove the biggest file from the directory.
}

#endif //DIRECTORY_H