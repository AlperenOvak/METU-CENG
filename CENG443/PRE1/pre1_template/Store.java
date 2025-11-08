import java.awt.Color;
import java.awt.Graphics2D;

public class Store extends Entity {
    final Common.ProductType productType; 
    final  Integer prize;
    final Integer stock_limit;
    Integer stock;
    private int iteration = 0;
    final int stockReplenishmentFrequency;

    public Integer getPrize() {
        return prize;
    }

    public Common.ProductType getProductType() {
        return productType;
    }

    public Integer getStock() {
        return stock;
    }


    public void sellProduct(){
        if(this.stock==0){
            // throw not enough stock exception
            throw new IllegalStateException("Not enough stock");
        }else{
            this.stock -= 1;
        }
    }

    public Store(double x, double y, 
                Common.ProductType productType, 
                Integer prize, Integer stock, int stockReplenishmentFrequency) {
        super(x, y);
        this.productType = productType;
        this.prize = prize;
        this.stock = stock;
        this.stock_limit = stock;
        this.stockReplenishmentFrequency = stockReplenishmentFrequency;
    }

    @Override
    public void draw(Graphics2D g2d) {
        //System.out.println("Drawing Store");
        String name = String.format("%s, %d, %d", productType, prize, stock);
        drawHelper(g2d, name, Color.ORANGE);
    }

    @Override
    public void step() {
        iteration++;
        if(stockReplenishmentFrequency == iteration){
            iteration = 0;
            stock = stock_limit;
        }
    }
    
}
