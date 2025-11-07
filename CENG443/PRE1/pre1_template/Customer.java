import java.awt.Color;
import java.awt.Graphics2D;

public abstract class Customer extends Entity {
    Store targetStore;

    final Common.ProductType[] shoppingList;
    final Common.buyStrategy strategy;

    public Customer(double x, double y, Common.ProductType[] shoppingList, Common.buyStrategy strategy) {
        super(x, y);
        this.shoppingList = shoppingList;
        this.strategy = strategy;
    }

    @Override
    public void draw(Graphics2D g2d) {
        String name = String.format("%s : %s, %s, %s ", strategy, shoppingList[0], shoppingList[1], shoppingList[2]);
        drawHelper(g2d, name, Color.GRAY);
    }
}
