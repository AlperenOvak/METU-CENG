#ifndef DIRECTORY_MAIN_H
#define DIRECTORY_MAIN_H

#include "Node.h"
#include "Block.h"
#include "LinkedList.h"
#include "File.h"
#include "Directory.h"

int main()
{
	// Create some sample blocks
    Block block1 = Block("Block 1");
    Block block2 = Block("Block 2");
    Block block3 = Block("Block 3");

    // Create some sample files with blocks
    File file1 = File();
    file1.newBlock(block1);
    file1.newBlock(block2);
/*	
    File file2;
    file2.newBlock(block3);

    // Create a directory and add files to it
    Directory directory;
    directory.newFile(file1);
    directory.newFile(file2);

    // Test Directory class functions
    std::cout << "Number of files in the directory: " << directory.numFiles() << std::endl;
    std::cout << "Total directory size: " << directory.directorySize() << " bytes" << std::endl;

    File file3;
    directory.newFile(file3);
    std::cout << "Added a new file. Number of files in the directory: " << directory.numFiles() << std::endl;

    directory.removeFile(1);
    std::cout << "Removed the second file. Number of files in the directory: " << directory.numFiles() << std::endl;

    // Test removeBiggestFile function
    directory.removeBiggestFile();
    std::cout << "Removed the biggest file. Number of files in the directory: " << directory.numFiles() << std::endl;
	*/
    return 0;
}

#endif //DIRECTORY_MAIN_H