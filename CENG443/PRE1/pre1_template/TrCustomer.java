import java.util.*;

public class TrCustomer extends Customer {
    public TrCustomer(double x, double y, List<Common.ProductType> shoppingList) {
        super(x, y, shoppingList, Common.buyStrategy.Tr);
    }

    private HashMap<Store, Boolean> visited = new HashMap<>();

    private void resetMap(){
        visited =  new HashMap<>();
    }
    
    @Override
    protected void findNextStore() {
        Store nearestStore = null;
        double minDistance = Double.MAX_VALUE;
        for(Store store : Common.stores){
            if(visited.containsKey(store)){
                continue;
            }
            double distance = Common.calculateDistance(store.getPosition(), this.getPosition());
            if(this.shoppingList.contains(store.productType) &&
                minDistance >= distance && distance != 0) 
            {
                minDistance = distance;
                nearestStore = store;
            }
        }
        if(nearestStore != null){
            visited.put(nearestStore, true);
        }else{
            resetMap();
        }
        this.targetStore = nearestStore;
    }

    @Override
    protected void handleOutOfStock() {
        findNextStore();
    }
    
}
