import java.util.ArrayList;

public class ScholarNodePrimaryIndex extends ScholarNode {
	private ArrayList<Integer> paperIds;
	private ArrayList<ScholarNode> children;
	
	public ScholarNodePrimaryIndex(ScholarNode parent) {
		super(parent);
		paperIds = new ArrayList<Integer>();
		children = new ArrayList<ScholarNode>();
		this.type = ScholarNodeType.Internal;
	}
	
	public ScholarNodePrimaryIndex(ScholarNode parent, ArrayList<Integer> paperIds, ArrayList<ScholarNode> children) {
		super(parent);
		this.paperIds = paperIds;
		this.children = children;
		this.type = ScholarNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<ScholarNode> getAllChildren()
	{
		return this.children;
	}

	public ArrayList<Integer> getAllKeys() {return this.paperIds;}

	//for debug
	public Integer firstKey() {
		if (!this.paperIds.isEmpty()) {
			return this.paperIds.get(0);
		}
		return -1; // Return -1 if the list is empty
	}
	
	public ScholarNode getChildrenAt(Integer index) {return this.children.get(index); }
	
	public Integer paperIdCount()
	{
		return this.paperIds.size();
	}

	public Integer paperIdAtIndex(Integer index) {
		if(index >= this.paperIdCount() || index < 0) {
			return -1;
		}
		else {
			return this.paperIds.get(index);
		}
	}
	
	// Extra functions if needed
	public ScholarNode getNextChild(Integer key) {
		for (int i = 0; i < this.paperIds.size(); i++) {
			if (key < this.paperIds.get(i)) {
				return this.children.get(i);
			}
		}
		return this.children.get(this.children.size() - 1);
	}
	public void addPaperId(int index, Integer key) {
		this.paperIds.add(index, key);
	}
	public void addChild(int index, ScholarNode child) {
		this.children.add(index, child);
	}

}
