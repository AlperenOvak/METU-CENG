public class ClCustomer extends Customer {

    public ClCustomer(double x, double y, Common.ProductType[] shoppingList) {
        super(x, y, shoppingList, Common.buyStrategy.Cl);
    }

    private void findNearestStore() {
        // Find the nearest store that has the desired product in stock
        Store nearestStore = null;
        double minDistance = Double.MAX_VALUE;
        for(Store store : Common.stores){
            if(store.productType == this.shoppingList[0] &&
                minDistance >= Common. store.getPosition()
            ){
                
            }
        }
    }

    @Override
    public void step() {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'step'");
        if(targetStore == null){
            // Find a new store to target
        }else if(targetStore.getPosition() == position){
            targetStore.sellProduct();
            targetStore = null;
            // Find a new store to target
        }else{
            // Move towards target store
            if(targetStore.getPosition().getX() > position.getX()){
                position.setX(position.getX() + 1);
            }else if(targetStore.getPosition().getX() < position.getX()){
                position.setX(position.getX() - 1);
            }

            if(targetStore.getPosition().getY() > position.getY()){
                position.setY(position.getY() + 1);
            }else if(targetStore.getPosition().getY() < position.getY()){
                position.setY(position.getY() - 1);
            }
        }

    }
    
}
