public class ChCustomer extends Customer {
    public ChCustomer(double x, double y, Common.ProductType[] shoppingList) {
        super(x, y, shoppingList, Common.buyStrategy.Ch);
    }

    @Override
    public void step() {
        // TODO Auto-generated method stub
        //throw new UnsupportedOperationException("Unimplemented method 'step'");
    }
    
}
