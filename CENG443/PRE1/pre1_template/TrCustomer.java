public class TrCustomer extends Customer {
    public TrCustomer(double x, double y, Common.ProductType[] shoppingList) {
        super(x, y, shoppingList, Common.buyStrategy.Tr);
    }

    @Override
    public void step() {
        //throw new UnsupportedOperationException("Unimplemented method 'step'");
    }
    
}
