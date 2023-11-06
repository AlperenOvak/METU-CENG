#ifndef FILE_H
#define FILE_H

#include "LinkedList.h"
#include "Block.h"

class File{
public:

	Block getBlock(int index) const;
	size_t fileSize() const;
	int numBlocks() const;
	bool isEmpty() const;
	bool operator==(const File &rhs) const;

	void newBlock(const Block &block);
	void removeBlock(int index);
	void mergeBlocks(int sourceIndex, int destIndex);
	void printContents() const;

private:
	LinkedList<Block> blocks;
};

Block File::getBlock(int index) const
{
    /* Get a block at the specified index from the file. */

    if (index < 0 || index >= blocks.getSize()) {
        return Block(""); // Return an empty block if the index is out of bounds.
    }
    return blocks.getNodeAtIndex(index)->data; // Return the block at the given index.
}

size_t File::fileSize() const
{
    /* Calculate and return the total size of the file by summing the sizes of all blocks. */

    size_t size = 0;
    for (int i = 0; i < numBlocks(); i++) {
        size += blocks.getNodeAtIndex(i)->data.getSize();
    }
    return size;
}

int File::numBlocks() const
{
    /* Get the number of blocks in the file. */
    return blocks.getSize();
}

bool File::isEmpty() const
{
    /* Check if the file is empty (contains no blocks). */
    return blocks.isEmpty();
}

bool File::operator==(const File &rhs) const
{
    /* Compare this file to another file for equality. */

    if (numBlocks() != rhs.numBlocks()) {
        return false; // If the number of blocks is different, the files are not equal.
    }
    for (int i = 0; i < numBlocks(); i++) {
        if (!(getBlock(i) == rhs.getBlock(i))) {
            return false; // If any block in the files is not equal, the files are not equal.
        }
    }
    return true; // If all blocks match, the files are equal.
}

void File::newBlock(const Block &block)
{
    /* Add a new block to the file. */
    blocks.append(block);
}

void File::removeBlock(int index)
{
    /* Remove a block at the specified index from the file. */

    if (index >= 0 && index < blocks.getSize()) {
        Node<Block>* nodeToRemove = blocks.getNodeAtIndex(index);
        if (nodeToRemove != NULL) {
            blocks.removeNode(nodeToRemove); // Remove the block at the given index.
        }
    }
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
    /* Merge the content of a block at the source index into a block at the destination index. */

    if (sourceIndex < 0 || sourceIndex >= blocks.getSize() ||
        destIndex < 0 || destIndex >= blocks.getSize()) {
        return; // If source or destination index is out of bounds, do nothing.
    }

    Block& sourceBlock = blocks.getNodeAtIndex(sourceIndex)->data;
    Block& destBlock = blocks.getNodeAtIndex(destIndex)->data;

    destBlock = destBlock + sourceBlock; // Merge the content of source block into the destination block.

    removeBlock(sourceIndex); // Remove the source block.
}

void File::printContents() const
{
    if (isEmpty()) {
        std::cout << "File is empty" << std::endl; // Print a message if the file is empty.
    } else {
        for (int i = 0; i < blocks.getSize(); i++) {
            Node<Block> *block = blocks.getNodeAtIndex(i);
            std::cout << block->data.getContent(); // Print the content of each block in the file.
        }
        std::cout << std::endl << fileSize() << std::endl; // Print the total file size.
    }
}
#endif //FILE_H