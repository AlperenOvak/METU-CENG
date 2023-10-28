#include "File.h"

Block File::getBlock(int index) const
{
	/* TODO */
	if (index < 0 || index >= blocks.getSize()) {
        return Block("");
    }
    return blocks.getNodeAtIndex(index)->data;
}

size_t File::fileSize() const
{
	/* TODO */
	size_t size = 0;
    for (int i = 0; i < blocks.getSize(); i++) {
        size += blocks.getNodeAtIndex(i)->data.getSize();
    }
    return size;
}

int File::numBlocks() const
{
	/* TODO */
	std::cout<<blocks.getSize()<<std::endl;
	return blocks.getSize();
}

bool File::isEmpty() const
{
	/* TODO */
	return 0;//blocks.isEmpty();
}

bool File::operator==(const File &rhs) const
{
	/* TODO */
	if (numBlocks() != rhs.numBlocks()) {
        return false;
    }
    for (int i = 0; i < numBlocks(); i++) {
        if (!(getBlock(i) == rhs.getBlock(i))) {
            return false;
        }
    }
    return true;
}

void File::newBlock(const Block &block)
{
	/* TODO */
}

void File::removeBlock(int index)
{
	/* TODO */
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
	/* TODO */
}

void File::printContents() const{
	if(isEmpty()){
		std::cout << "File is empty" << std::endl;
	}
	else{
		for(int i = 0; i < blocks.getSize(); i++){
			Node<Block> *block = blocks.getNodeAtIndex(i);
			std::cout << block->data.getContent();
		}
		std::cout << std::endl << fileSize() << std::endl;
	}
}