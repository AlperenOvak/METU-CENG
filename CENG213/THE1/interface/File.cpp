#include "File.h"

Block File::getBlock(int index) const
{
	/* TODO */
}

size_t File::fileSize() const
{
	/* TODO */
}

int File::numBlocks() const
{
	/* TODO */
}

bool File::isEmpty() const
{
	/* TODO */
}

bool File::operator==(const File &rhs) const
{
	/* TODO */
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