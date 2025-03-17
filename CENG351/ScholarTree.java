import java.util.ArrayList;
import java.util.Objects;

public class ScholarTree {
	
	public ScholarNode primaryRoot;		//root of the primary B+ tree
	public ScholarNode secondaryRoot;	//root of the secondary B+ tree
	public ScholarTree(Integer order) {
		ScholarNode.order = order;
		primaryRoot = new ScholarNodePrimaryLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new ScholarNodeSecondaryLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addPaper(CengPaper paper) {
		//primary
		ScholarNodePrimaryLeaf primaryLeaf = findPrimaryLeaf(paper.paperId());
		insertPrimary(primaryLeaf, paper);

		//secondary
		ScholarNodeSecondaryLeaf secondaryLeaf = findSecondaryLeaf(paper.journal());
		insertSecondary(secondaryLeaf, paper);
	}

	private ScholarNodePrimaryLeaf findPrimaryLeaf(Integer paperId) {
		ScholarNode currentNode = primaryRoot;
		while (currentNode.getType() == ScholarNodeType.Internal) {
			ScholarNodePrimaryIndex internalNode = (ScholarNodePrimaryIndex) currentNode;
			currentNode = internalNode.getNextChild(paperId);
		}
		return (ScholarNodePrimaryLeaf) currentNode;
	}

	private void insertPrimary(ScholarNodePrimaryLeaf leaf, CengPaper paper) {
		int index = findInsertIndex(leaf.getPapers(), paper.paperId());
		leaf.addPaper(index, paper);

		// Check overflow
		if (leaf.getPapers().size() > (2 * ScholarNode.order)) {
			handlePrimaryOverflow(leaf);
		}
	}

	private void handlePrimaryOverflow(ScholarNodePrimaryLeaf leaf) {
		ScholarNodePrimaryLeaf sibling = new ScholarNodePrimaryLeaf(leaf.getParent());

		int splitIndex = leaf.getPapers().size() / 2;
		for (int i = splitIndex; i < leaf.getPapers().size(); i++) {
			sibling.addPaper(sibling.getPapers().size(), leaf.getPapers().get(i));
		}
		while (leaf.getPapers().size() > splitIndex) {
			leaf.getPapers().remove(splitIndex);
		}

		Integer promotedKey = sibling.getPapers().get(0).paperId();

		ScholarNodePrimaryIndex parent = (ScholarNodePrimaryIndex) leaf.getParent();

		if (parent == null) {
			ScholarNodePrimaryIndex newRoot = new ScholarNodePrimaryIndex(null);
			newRoot.addPaperId(0, promotedKey);
			newRoot.addChild(0, leaf);
			newRoot.addChild(1, sibling);
			leaf.setParent(newRoot);
			sibling.setParent(newRoot);
			primaryRoot = newRoot;
		} else {
			//System.out.println("***********"+parent.firstKey().toString());
			int insertPos = 0;
			for (; insertPos < parent.paperIdCount(); insertPos++) {
				if (promotedKey < parent.paperIdAtIndex(insertPos)) {
					break;
				}
			}
			parent.addPaperId(insertPos, promotedKey);
			parent.addChild(insertPos + 1, sibling);
			sibling.setParent(parent);

			if (parent.paperIdCount() > (2 * ScholarNode.order)) {
				//System.out.println("***********PARENT OVERFLOW "+parent.firstKey().toString());
				handlePrimaryInternalOverflow(parent);
			}
		}
	}

	private void handlePrimaryInternalOverflow(ScholarNodePrimaryIndex node) {
		ScholarNodePrimaryIndex sibling = new ScholarNodePrimaryIndex(node.getParent());
		int splitIndex = node.paperIdCount() / 2;

		Integer promotedKey = node.paperIdAtIndex(splitIndex);
		//System.out.println("***********middle key "+promotedKey.toString());

		//System.out.println("***********TRANSFER TO NEW NODE");
		for (int i = splitIndex + 1; i < node.paperIdCount(); i++) {
			sibling.addPaperId(sibling.paperIdCount(), node.paperIdAtIndex(i));
			//System.out.println("***********"+node.paperIdAtIndex(i).toString());
		}
		//System.out.println("***********UPDATE TO NEW NODE");
		for (int i = splitIndex + 1; i < node.getAllChildren().size(); i++) {
			ScholarNode child = node.getChildrenAt(i);
			sibling.addChild(sibling.getAllChildren().size(), child);
			child.setParent(sibling);  // Update the parent reference of the child
		}
		//System.out.println("***********REMOVE OLD NODE");
		node.getAllKeys().subList(splitIndex, node.paperIdCount()).clear();
		node.getAllChildren().subList(splitIndex + 1, node.getAllChildren().size()).clear();

		if (node.getParent() == null) {
			//System.out.println("***********CREATE NEW ROOT");
			ScholarNodePrimaryIndex newRoot = new ScholarNodePrimaryIndex(null);
			newRoot.addPaperId(0, promotedKey);
			newRoot.addChild(0, node);
			newRoot.addChild(1, sibling);
			node.setParent(newRoot);
			sibling.setParent(newRoot);
			primaryRoot = newRoot;
		} else {
			ScholarNodePrimaryIndex parent = (ScholarNodePrimaryIndex) node.getParent();
			int insertPos = 0;
			for (; insertPos < parent.paperIdCount(); insertPos++) {
				if (promotedKey < parent.paperIdAtIndex(insertPos)) {
					break;
				}
			}
			parent.addPaperId(insertPos, promotedKey);
			parent.addChild(insertPos + 1, sibling);

			//recursive
			if (parent.paperIdCount() > (2 * ScholarNode.order)) {
				handlePrimaryInternalOverflow(parent);
			}
		}
	}

	private int findInsertIndex(ArrayList<CengPaper> papers, int paperId) {
		for (int i = 0; i < papers.size(); i++) {
			if (paperId < papers.get(i).paperId()) {
				return i;
			}
		}
		return papers.size();
	}

	private ScholarNodeSecondaryLeaf findSecondaryLeaf(String journal) {
		ScholarNode currentNode = secondaryRoot;
		while (currentNode.getType() == ScholarNodeType.Internal) {
			ScholarNodeSecondaryIndex internalNode = (ScholarNodeSecondaryIndex) currentNode;
			currentNode = internalNode.getNextChild(journal);
		}
		return (ScholarNodeSecondaryLeaf) currentNode;
	}

	private void insertSecondary(ScholarNodeSecondaryLeaf leaf, CengPaper paper) {
		ArrayList<String> journals = leaf.getJournals();

		int journalIndex = journals.indexOf(paper.journal());

		if (journalIndex == -1) {
			addNewJournal(leaf, paper);
		} else {
			addExistingJournal(leaf, paper, journalIndex);
		}

		if (leaf.journalCount() > (2 * ScholarNode.order)) {
			handleSecondaryOverflow(leaf);
		}
	}
	private int findInsertIndexForJournal(ArrayList<String> journals, String journal) {
		for (int i = 0; i < journals.size(); i++) {
			if (journal.compareTo(journals.get(i)) < 0) {
				return i;
			}
		}
		return journals.size();
	}

	private void addNewJournal(ScholarNodeSecondaryLeaf leaf, CengPaper paper) {
		ArrayList<String> journals = leaf.getJournals();
		ArrayList<ArrayList<Integer>> paperIdBuckets = leaf.getPaperIdBucket();

		int insertIndex = findInsertIndexForJournal(journals, paper.journal());
		journals.add(insertIndex, paper.journal());
		ArrayList<Integer> newBucket = new ArrayList<>();
		newBucket.add(paper.paperId());
		paperIdBuckets.add(insertIndex, newBucket);
	}
	private void addExistingJournal(ScholarNodeSecondaryLeaf leaf, CengPaper paper, int journalIndex) {
		leaf.getPaperIdBucket().get(journalIndex).add(paper.paperId());
	}
	private int findInsertPositionForKey(ScholarNodeSecondaryIndex node, String key) {
		ArrayList<String> keys = node.getAllKeys();
		for (int i = 0; i < keys.size(); i++) {
			if (key.compareTo(keys.get(i)) < 0) {
				return i;
			}
		}
		return keys.size();
	}

	private void handleSecondaryOverflow(ScholarNodeSecondaryLeaf leaf) {
		ScholarNodeSecondaryLeaf sibling = new ScholarNodeSecondaryLeaf(leaf.getParent());
		int splitIndex = leaf.journalCount() / 2;
		for (int i = splitIndex; i < leaf.journalCount(); i++) {
			sibling.getJournals().add(leaf.getJournals().get(i));
			sibling.getPaperIdBucket().add(leaf.getPaperIdBucket().get(i));
		}
		while (leaf.journalCount() > splitIndex) {
			leaf.getJournals().remove(splitIndex);
			leaf.getPaperIdBucket().remove(splitIndex);
		}

		String promotedKey = sibling.getJournals().get(0);

		if (leaf.getParent() == null) {
			//Create root
			ScholarNodeSecondaryIndex newRoot = new ScholarNodeSecondaryIndex(null);
			newRoot.addJournal(0, promotedKey);
			newRoot.addChild(0, leaf);
			newRoot.addChild(1, sibling);
			leaf.setParent(newRoot);
			sibling.setParent(newRoot);
			secondaryRoot = newRoot;
		} else {
			//update parent
			ScholarNodeSecondaryIndex parent = (ScholarNodeSecondaryIndex) leaf.getParent();
			int insertPos = findInsertPositionForKey(parent, promotedKey);
			parent.addJournal(insertPos, promotedKey);
			parent.addChild(insertPos + 1, sibling);

			//recursive
			if (parent.journalCount() > (2 * ScholarNode.order)) {
				handleSecondaryInternalOverflow(parent);
			}
		}
	}

	private void handleSecondaryInternalOverflow(ScholarNodeSecondaryIndex node) {
		ScholarNodeSecondaryIndex sibling = new ScholarNodeSecondaryIndex(node.getParent());
		int splitIndex = node.journalCount() / 2;

		String promotedKey = node.journalAtIndex(splitIndex);
		//System.out.println(splitIndex+" "+node.getAllChildren().size());
		for (int i = splitIndex + 1; i < node.journalCount(); i++) {
			sibling.addJournal(sibling.journalCount(), node.journalAtIndex(i));
		}
		for (int i = splitIndex + 1; i < node.getAllChildren().size(); i++) {
			ScholarNode child = node.getChildrenAt(i);
			sibling.addChild(sibling.getAllChildren().size(), child);
			child.setParent(sibling);
		}

		node.getAllKeys().subList(splitIndex, node.journalCount()).clear();
		node.getAllChildren().subList(splitIndex + 1, node.getAllChildren().size()).clear();

		if (node.getParent() == null) {
			ScholarNodeSecondaryIndex newRoot = new ScholarNodeSecondaryIndex(null);
			newRoot.addJournal(0, promotedKey);
			newRoot.addChild(0, node);
			newRoot.addChild(1, sibling);
			node.setParent(newRoot);
			sibling.setParent(newRoot);
			secondaryRoot = newRoot;
		} else {
			ScholarNodeSecondaryIndex parent = (ScholarNodeSecondaryIndex) node.getParent();
			int insertPos = 0;
			for (; insertPos < parent.journalCount(); insertPos++) {
				if (promotedKey.compareTo(parent.journalAtIndex(insertPos)) < 0) {
					break;
				}
			}
			parent.addJournal(insertPos, promotedKey);
			parent.addChild(insertPos + 1, sibling);

			if (parent.journalCount() > (2 * ScholarNode.order)) {
				handleSecondaryInternalOverflow(parent);
			}
		}
	}

	public CengPaper searchPaper(Integer paperId) {
		ScholarNode currentNode = primaryRoot;
		int level = 0;

		while (currentNode.getType() == ScholarNodeType.Internal) {
			ScholarNodePrimaryIndex internalNode = (ScholarNodePrimaryIndex) currentNode;
			System.out.print("\t".repeat(level) + "<index>\n");
			for (int i = 0; i < internalNode.paperIdCount(); i++) {
				System.out.print("\t".repeat(level) + internalNode.paperIdAtIndex(i) + "\n");
			}
			System.out.print("\t".repeat(level) + "</index>\n");
			currentNode = internalNode.getNextChild(paperId);
			level++;
		}

		ScholarNodePrimaryLeaf leafNode = (ScholarNodePrimaryLeaf) currentNode;

		for (CengPaper paper : leafNode.getPapers()) {
			if (paper.paperId().equals(paperId)) {
				System.out.print("\t".repeat(level) + "<data>\n");
				System.out.print("\t".repeat(level) + "<record>" + paper.fullName() +  "</record>\n");
				System.out.print("\t".repeat(level) + "</data>\n");
				return paper;
			}
		}

		// If the paperId is not found
		System.out.println("Could not find " + paperId);
		return null;
	}

	private CengPaper findPaperPrimaryTree(Integer paperId) {
		ScholarNode currentNode = primaryRoot;

		while (currentNode.getType() == ScholarNodeType.Internal) {
			ScholarNodePrimaryIndex internalNode = (ScholarNodePrimaryIndex) currentNode;
			currentNode = internalNode.getNextChild(paperId);
		}

		ScholarNodePrimaryLeaf leafNode = (ScholarNodePrimaryLeaf) currentNode;

		for (CengPaper paper : leafNode.getPapers()) {
			if (paper.paperId().equals(paperId)) {
				return paper;
			}
		}

		return null;
	}

	public void searchJournal(String journal) {
		ScholarNode currentNode = secondaryRoot;
		int level = 0; //depth

		while (currentNode.getType() == ScholarNodeType.Internal) {
			ScholarNodeSecondaryIndex internalNode = (ScholarNodeSecondaryIndex) currentNode;
			System.out.print("\t".repeat(level) + "<index>\n");
			for (int i = 0; i < internalNode.journalCount(); i++) {
				System.out.print("\t".repeat(level) + internalNode.journalAtIndex(i) + "\n");
			}
			System.out.print("\t".repeat(level) + "</index>\n");

			currentNode = internalNode.getNextChild(journal);
			level++; //Increment depth
		}


		ScholarNodeSecondaryLeaf leafNode = (ScholarNodeSecondaryLeaf) currentNode;

		ArrayList<String> journals = leafNode.getJournals();
		ArrayList<ArrayList<Integer>> paperIdBuckets = leafNode.getPaperIdBucket();
		for (int i = 0; i < journals.size(); i++) {
			if (journals.get(i).equals(journal)) {
				System.out.print("\t".repeat(level) + "<data>\n");
				System.out.print("\t".repeat(level ) + journal + "\n");
				for (Integer paperId : paperIdBuckets.get(i)) {
					CengPaper paper = findPaperPrimaryTree(paperId);
					if (paper != null) {
						System.out.print("\t".repeat(level+1) + "<record>" + paper.fullName() + "</record>\n");
					}
				}
				System.out.print("\t".repeat(level) + "</data>\n");
				return;
			}
		}

		System.out.println("Could not find " + journal);
	}

	public void printPrimaryScholar() {
		// TODO: Implement this method
		// print the primary B+ tree in Depth-first order
		printPrimaryNodeRecursive(primaryRoot, 0);
	}

	private void printPrimaryNodeRecursive(ScholarNode node, int level) {
		if (node.getType() == ScholarNodeType.Internal) {
			ScholarNodePrimaryIndex internalNode = (ScholarNodePrimaryIndex) node;

			System.out.print("\t".repeat(level) + "<index>\n");
			for (int i = 0; i < internalNode.paperIdCount(); i++) {
				System.out.print("\t".repeat(level) + internalNode.paperIdAtIndex(i) + "\n");
			}
			System.out.print("\t".repeat(level) + "</index>\n");

			for (int i = 0; i < internalNode.getAllChildren().size(); i++) {
				printPrimaryNodeRecursive(internalNode.getChildrenAt(i), level + 1);
			}
		} else if (node.getType() == ScholarNodeType.Leaf) {
			ScholarNodePrimaryLeaf leafNode = (ScholarNodePrimaryLeaf) node;

			System.out.print("\t".repeat(level) + "<data>\n");
			for (CengPaper paper : leafNode.getPapers()) {
				System.out.print("\t".repeat(level) + "<record>" + paper.fullName() + "</record>\n");
			}
			System.out.print("\t".repeat(level) + "</data>\n");
		}
	}

	public void printSecondaryScholar() {
		// TODO: Implement this method
		// print the secondary B+ tree in Depth-first order
		printSecondaryNodeRecursive(secondaryRoot, 0);
	}

	private void printSecondaryNodeRecursive(ScholarNode node, int level) {
		if (node.getType() == ScholarNodeType.Internal) {
			ScholarNodeSecondaryIndex internalNode = (ScholarNodeSecondaryIndex) node;

			System.out.print("\t".repeat(level) + "<index>\n");
			for (int i = 0; i < internalNode.journalCount(); i++) {
				System.out.print("\t".repeat(level) + internalNode.journalAtIndex(i) + "\n");
			}
			System.out.print("\t".repeat(level) + "</index>\n");

			for (int i = 0; i < internalNode.getAllChildren().size(); i++) {
				printSecondaryNodeRecursive(internalNode.getChildrenAt(i), level + 1);
			}
		} else if (node.getType() == ScholarNodeType.Leaf) {
			ScholarNodeSecondaryLeaf leafNode = (ScholarNodeSecondaryLeaf) node;

			System.out.print("\t".repeat(level) + "<data>\n");
			ArrayList<String> journals = leafNode.getJournals();
			ArrayList<ArrayList<Integer>> paperIdBuckets = leafNode.getPaperIdBucket();

			for (int i = 0; i < journals.size(); i++) {
				System.out.print("\t".repeat(level ) + journals.get(i) + "\n");
				for (Integer paperId : paperIdBuckets.get(i)) {
					System.out.print("\t".repeat(level + 1) + "<record>" + paperId + "</record>\n");
				}
			}
			System.out.print("\t".repeat(level) + "</data>\n");
		}
	}
	
	// Extra functions if needed
}


