import java.util.*;

public class TrCustomer extends Customer {
    public TrCustomer(double x, double y, List<Common.ProductType> shoppingList) {
        super(x, y, shoppingList, Common.buyStrategy.Tr);
    }

    private HashMap<Store, Boolean> visited;
    
    @Override
    protected void findNextStore() {
        Store nearestStore = null;
        double minDistance = Double.MAX_VALUE;
        for(Store store : Common.stores){
            double distance = Common.calculateDistance(store.getPosition(), this.getPosition());
            if(store.productType == this.shoppingList.get(0) &&
                minDistance >= distance && distance != 0) 
            {
                minDistance = distance;
                nearestStore = store;
            }
        }
        this.targetStore = nearestStore;
        
    }

    @Override
    protected void handleOutOfStock() {
        findNextStore();
    }
    
}
