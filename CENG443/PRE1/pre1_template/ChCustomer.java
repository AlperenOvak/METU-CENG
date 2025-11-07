import java.util.*;

public class ChCustomer extends Customer {
    public ChCustomer(double x, double y, List<Common.ProductType> shoppingList) {
        super(x, y, shoppingList, Common.buyStrategy.Ch);
    }

    @Override
    protected void findNextStore() {
        Store cheapestStore = null;
        double minPrice = Double.MAX_VALUE;
        for(Store store : Common.stores){
            double distance = Common.calculateDistance(store.getPosition(), this.getPosition());
            if(store.productType == this.shoppingList.get(0) &&
                minPrice >= store.prize && distance != 0) 
            {
                minPrice = store.prize;
                cheapestStore = store;
            }
        }
        this.targetStore = cheapestStore;
    }

    @Override
    protected void handleOutOfStock() {
        // wait until stocks are refreshed
    }
    
}
