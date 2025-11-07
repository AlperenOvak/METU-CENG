import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Common {
    private static final String title = "Economics 101";
    private static final int windowWidth = 825;
    private static final int windowHeight = 500;

    private static final int entityRadius = 7; // radius of drawn entity (customer or store)

    private static final int storeNo = 10; // number of stores in the simulation
    private static final int customerNo = 10; // number of customers

    private static final int stockReplenishmentFrequency = 3000; // number of stepAllEntities calls before replenishing
                                                                 // all stores

    private static final int foodBottomPrice = 20;
    private static final int foodCeilingPrice = 50;
    private static final int electronicsBottomPrice = 200;
    private static final int electronicsCeilingPrice = 2000;
    private static final int LuxuryBottomPrice = 5000;
    private static final int LuxuryCeilingPrice = 10000;

    private static final int minimumShoppingListLength = 5;
    private static final int maximumShoppingListLength = 10;

    private static final int stockStorageMin = 15; // minimum size of storage available for a store
    private static final int stockStorageMax = 25; // maximum number of storage available for a store

    private static final int customerMovementSpeed = 2;
    private static final Font font = new Font("Verdana", Font.BOLD, 10);

    public static String getTitle() {
        return title;
    }

    public static int getWindowWidth() {
        return windowWidth;
    }

    public static int getWindowHeight() {
        return windowHeight;
    }

    public static int getEntityRadius() {
        return entityRadius;
    }

    public static Font getFont() {
        return font;
    }

    public static int getCustomerMovementSpeed() {
        return customerMovementSpeed;
    }

    // TODO
    // put your necessary fields and methods here
    ////
    
    public enum ProductType {
        F,
        E,
        L
    }

    public enum buyStrategy {
        Ch, //cheapest
        Cl, //closest
        Tr  //travelling
    }

    // TODO
    // When adding new stores or customers, their position, shopping list,
    // max stock etc. should be random between the ranges defined above.
    // You can use the function below or define your own function to generate
    // a random integer
    public static int randInt(int min, int max) {
        return ThreadLocalRandom.current().nextInt(min, max + 1);
    }
    // E.g.
    /*
    //Product Generation
    switch(randInt(0,2)){
        case 0:
            //Food
            break;
        case 1:
            //Electronics
            break;
        case 2:
            //Luxury
            break;
     }
    }
    //x position of the center of entity generation
    double centerX = randInt(0,windowWidth-2*entityRadius)
    */

    // TODO
    // Create customers and stores
    // Hint: you can also use a static block for this
    // Also note that you should make sure there are about equal number of stores
    // for all products
    // like 4 stores for food, 3 stores for electronics and 4 stores for luxury etc.
    // Otherwise your simulation may deadlock
    
    ////
    private static List<Store> createStores(){
        int storePerType = storeNo / 3;
        List<Store> foodStores = createStoreWProduct(storePerType, ProductType.F, foodBottomPrice, foodCeilingPrice);
        List<Store> electronicStores = createStoreWProduct(storePerType, ProductType.E, electronicsBottomPrice, electronicsCeilingPrice);
        List<Store> luxuryStores = createStoreWProduct(storePerType + (storeNo % 3), ProductType.L, LuxuryBottomPrice, LuxuryCeilingPrice);
        List<Store> allStores = new ArrayList<>();
        allStores.addAll(foodStores);
        allStores.addAll(electronicStores);
        allStores.addAll(luxuryStores);
        return allStores;
    }

    private static List<Store> createStoreWProduct(int count, ProductType productType, int bottomPrice, int ceilingPrice){
        List<Store> newStores = new ArrayList<>();
        for(int i=0; i<count; i++){
            double centerX = randInt(0, windowWidth - 2 * entityRadius);
            double centerY = randInt(0, windowHeight - 2 * entityRadius);
            Store newStore = new Store(centerX, centerY, productType, randInt(bottomPrice, ceilingPrice), randInt(stockStorageMin, stockStorageMax));
            newStores.add(newStore);
        }
        System.out.println("********************Created " + count + " stores for " + productType);
        return newStores;
    }

    public static List<Store> stores = createStores();

    private static List<Customer> createCustomers(){
        List<Customer> newCustomers = new ArrayList<>();
        for(int i=0; i<customerNo; i++){
            double centerX = randInt(0, windowWidth - 2 * entityRadius);
            double centerY = randInt(0, windowHeight - 2 * entityRadius);
            int shoppingListLength = randInt(minimumShoppingListLength, maximumShoppingListLength);
            List<ProductType> shoppingList = new ArrayList<ProductType>();
            for(int j=0; j<shoppingListLength; j++){
                shoppingList.add(ProductType.values()[randInt(0, 2)]);
            }
            Customer newCustomer;
            switch (randInt(0,2)) {
                case 0:
                    newCustomer = new ChCustomer(centerX, centerY, shoppingList);
                    break;
                case 1:
                    newCustomer = new ClCustomer(centerX, centerY, shoppingList);
                    break;
                case 2:
                    newCustomer = new TrCustomer(centerX, centerY, shoppingList);
                    break;
                default:
                    throw new IllegalStateException("Unexpected value: " + randInt(0,2));
            };
            newCustomers.add(newCustomer);
        }
        return newCustomers;
    }

    public static List<Customer> customers = createCustomers();


    public static double calculateDistance(Position p1, Position p2){
        double a = p1.getX() - p2.getX();
        double b = p1.getY() - p2.getY();
        return  Math.sqrt(a*a + b*b); 
    }
}
