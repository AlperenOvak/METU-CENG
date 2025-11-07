import java.awt.Color;
import java.awt.Graphics2D;
import java.util.List;

public abstract class Customer extends Entity {
    Store targetStore;
    static int movementSpeed = Common.getCustomerMovementSpeed();

    List<Common.ProductType> shoppingList;
    final Common.buyStrategy strategy;

    public Customer(double x, double y, List<Common.ProductType>  shoppingList, Common.buyStrategy strategy) {
        super(x, y);
        this.shoppingList = shoppingList;
        this.strategy = strategy;
    }

    protected abstract void findNextStore();

    protected abstract void handleOutOfStock();

    private void goOut(){
        
    }

    private void buyProduct(){
        targetStore.sellProduct();
        shoppingList.remove(0);
    }

    @Override
    public void step() {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'step'");
        if(shoppingList.isEmpty()){
                // Finished shopping
            return;
        }
        if(targetStore == null){
            findNextStore();
        }else if(targetStore.getPosition() == position){
            try {
                buyProduct();
            } catch (Exception e) {  //handle different type of exceptions !!!
                handleOutOfStock();
            }
            if(shoppingList.isEmpty()){
                // Finished shopping
                return;
            }
            targetStore = null;
            findNextStore();
        }else{
            // Move towards target store
            double dx = targetStore.getPosition().getX() - this.position.getX();
            double dy = targetStore.getPosition().getY() - this.position.getY();
            double distance = Math.sqrt(dx * dx + dy * dy);
            if (distance <= movementSpeed) {
                // Arrive at the store
                this.position = targetStore.getPosition();
            } else {
                // Move towards the store
                double ratio = movementSpeed / distance;
                this.position = new Position(
                    this.position.getX() + dx * ratio,
                    this.position.getY() + dy * ratio
                );  
            }
        }

    }

    @Override
    public void draw(Graphics2D g2d) {
        var first = !shoppingList.isEmpty() ? shoppingList.get(0) : "";
        var second = shoppingList.size() > 1 ? shoppingList.get(1) : "";
        var third = shoppingList.size() > 2 ? shoppingList.get(2) : "";
        String name = String.format("%s : %s, %s, %s ", strategy, first, second, third);
        drawHelper(g2d, name, Color.GRAY);
    }
}
