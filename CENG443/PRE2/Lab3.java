import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Lab3 {
    public static void main(String[] args) throws FileNotFoundException {
        System.out.println("Hello, World!");
        
        Function<String, Purchase> mapToPurhchase = (line) -> {
            String[] p = line.split(",", -1);
            //System.out.println(p.length);
            Purchase a = new Purchase(p[0], parseInt(p[1]), LocalDate.parse(p[2]), 
                                parseDouble(p[3]),  parseInt(p[4]),
                                parseDouble(p[5]),  parseInt(p[6]),
                                parseDouble(p[7]),  parseInt(p[8]),
                                parseDouble(p[9]),  parseInt(p[10]),
                                parseDouble(p[11]), parseInt(p[12])
            );
            ///System.out.println(a);
            return a;
        };
        

        List<Purchase> purchases = new ArrayList<Purchase>();
        try {
            Stream<String> lines = Files.lines(Paths.get(args[0]));
            purchases = lines.skip(1).map(mapToPurhchase).collect(Collectors.toList());
        } catch (IOException ex) {
            System.getLogger(Lab3.class.getName()).log(System.Logger.Level.ERROR, (String) null, ex);
        }


        // Query 0: test
        System.out.println("Query 1:");
        //purchases.stream().map( c -> c.name).sorted().forEach(System.out::println);
        System.out.println("--------");

        // Q1 : What is the total quantity of products purchased by the 
        // customers whose their names start with ‘A’?
        System.out.println(purchases.stream().filter(p -> p.name.charAt(0) == 'A')
                            .mapToInt(p-> allQuan(p)).sum());

        System.out.println("--------");

        System.out.println("Query 2");
        // q2 : What was the price of most expensive product sold?
        System.out.println(
            purchases.stream().mapToDouble(p -> findMaxPrice(p)).max().getAsDouble()
        );

        System.out.println("--------");


        System.out.println("--------");

        System.out.println("Query 3");
        // q3 : What was the price of most expensive product sold?
        System.out.println(
            purchases.stream().map(p->findSumPrice(p)).max(Comparator.comparing(m -> m.getKey())).get().getValue()
        );

        System.out.println("--------");


        System.out.println("Query 4");
        // q4 : What was the most popular product before 2000, in terms of 
        // total number of purchases whose include that item?
        
        
        Long eggCount = purchases.stream().filter(p-> p.date.getYear() < 2000).filter(p -> p.eggQty != null).count();
        Long breadCount = purchases.stream().filter(p-> p.date.getYear() < 2000).filter(p -> p.breadQty != null).count();
        Long milkCount = purchases.stream().filter(p-> p.date.getYear() < 2000).filter(p -> p.milkQty != null).count();
        Long potatoCount = purchases.stream().filter(p-> p.date.getYear() < 2000).filter(p -> p.potatoQty != null).count();
        Long tomatoCount = purchases.stream().filter(p-> p.date.getYear() < 2000).filter(p -> p.tomatoQty != null).count();

        Map<String, Long> productCount = Map.of(
            "Eggs", eggCount,
            "Breads", breadCount,
            "Milks", milkCount,
            "potatoes", potatoCount,
            "tomatoes", tomatoCount
        );
        String popularProduct = productCount.entrySet().stream()
            .max(Comparator.comparing(Map.Entry::getValue))
            .get()
            .getKey();

        System.out.println(popularProduct);

        System.out.println("--------");


        System.out.println("Query 5");
        // q4 : What was the least popular product after and including 2000, in terms of total number of items purchased?
        
        
        eggCount = purchases.stream().filter(p-> p.date.getYear() >= 2000).filter(p -> p.eggQty != null).count();
        breadCount = purchases.stream().filter(p-> p.date.getYear() >= 2000).filter(p -> p.breadQty != null).count();
        milkCount = purchases.stream().filter(p-> p.date.getYear() >= 2000).filter(p -> p.milkQty != null).count();
        potatoCount = purchases.stream().filter(p-> p.date.getYear() >= 2000).filter(p -> p.potatoQty != null).count();
        tomatoCount = purchases.stream().filter(p-> p.date.getYear() >= 2000).filter(p -> p.tomatoQty != null).count();

        Map<String, Long> productCountt = Map.of(
            "Eggs", eggCount,
            "Breads", breadCount,
            "Milks", milkCount,
            "potatoes", potatoCount,
            "tomatoes", tomatoCount
        );
        String nonpopularProduct = productCountt.entrySet().stream()
            .min(Comparator.comparing(Map.Entry::getValue))
            .get()
            .getKey();

        System.out.println(nonpopularProduct);

        System.out.println("--------");


        System.out.println("Query 6");
        // q6 :   What was the most popular product among teens considering number of purchases 
        // including that item? (Hint: find the product with the smallest average customer age)

        Double eggAvg = purchases.stream().filter(p -> p.eggQty != null).mapToInt(p -> p.age).average().orElse(0);
        Double breadAvg = purchases.stream().filter(p -> p.breadQty != null).mapToInt(p -> p.age).average().orElse(0);
        Double milkAvg = purchases.stream().filter(p -> p.milkQty != null).mapToInt(p -> p.age).average().orElse(0);
        Double tomatoAvg = purchases.stream().filter(p -> p.tomatoQty != null).mapToInt(p -> p.age).average().orElse(0);
        Double potatoAvg = purchases.stream().filter(p -> p.potatoQty != null).mapToInt(p -> p.age).average().orElse(0);

        Map<String, Double> avgAges = Map.of(
            "eggs" , eggAvg,
            "breads", breadAvg,
            "milk", milkAvg,
            "tomato", tomatoAvg,
            "potato", potatoAvg
        );

        String youngPopular = avgAges.entrySet().stream()
            .min(Comparator.comparing(Map.Entry::getValue)).get().getKey();
        System.out.println(
            youngPopular
        );
    
        System.out.println("--------");

        question7(purchases);

    
    }

    private static void question7(List<Purchase> purchases) {
        // What was the most inflated product on the data? When calculating only consider the 
        // oldest and the newest purchase and not the purchases between. As an exercise try to solve 
        // this question by reading the stream only once.
        ProductTracker tracker = purchases.stream()
                                .reduce(new ProductTracker(), 
                                        (acc, p) -> { acc.update(p); return acc; }
                                        );

        Map<String, Double> inflation = Map.of(
        "BREAD", tracker.newestBread.breadPrice - tracker.oldestBread.breadPrice,
        "MILK", tracker.newestMilk.milkPrice - tracker.oldestMilk.milkPrice,
        "EGG", tracker.newestEgg.eggPrice - tracker.oldestEgg.eggPrice,
        "TOMATO", tracker.newestTomato.tomatoPrice - tracker.oldestTomato.tomatoPrice,
        "POTATO", tracker.newestPotato.potatoPrice - tracker.oldestPotato.potatoPrice
        );

        String mostInflated = inflation.entrySet().stream()
                               .max(Comparator.comparing(Map.Entry::getValue))
                               .get()
                               .getKey();

        System.out.println("Most inflated product: " + mostInflated);
    }

    static class ProductTracker {
        Purchase oldestBread, newestBread;
        Purchase oldestMilk, newestMilk;
        Purchase oldestEgg, newestEgg;
        Purchase oldestTomato, newestTomato;
        Purchase oldestPotato, newestPotato;

        // helper to update prices for a new purchase
        void update(Purchase p) {
            if (p.breadPrice != null) {
                if (oldestBread == null || p.date.isBefore(oldestBread.date)) oldestBread = p;
                if (newestBread == null || p.date.isAfter(newestBread.date)) newestBread = p;
            }
            if (p.milkPrice != null) {
                if (oldestMilk == null || p.date.isBefore(oldestMilk.date)) oldestMilk = p;
                if (newestMilk == null || p.date.isAfter(newestMilk.date)) newestMilk = p;
            }
            if (p.eggPrice != null) {
                if (oldestEgg == null || p.date.isBefore(oldestEgg.date)) oldestEgg = p;
                if (newestEgg == null || p.date.isAfter(newestEgg.date)) newestEgg = p;
            }
            if (p.tomatoPrice != null) {
                if (oldestTomato == null || p.date.isBefore(oldestTomato.date)) oldestTomato = p;
                if (newestTomato == null || p.date.isAfter(newestTomato.date)) newestTomato = p;
            }
            if (p.potatoPrice != null) {
                if (oldestPotato == null || p.date.isBefore(oldestPotato.date)) oldestPotato = p;
                if (newestPotato == null || p.date.isAfter(newestPotato.date)) newestPotato = p;
            }
        }

        void update(ProductTracker p){
            this.update(p.oldestBread);
            this.update(p.newestBread);
            this.update(p.oldestMilk);
            this.update(p.newestMilk);
            this.update(p.oldestEgg);
            this.update(p.newestEgg);
            this.update(p.oldestTomato);
            this.update(p.newestTomato);
            this.update(p.oldestPotato);
            this.update(p.newestPotato);
        }
    }



    private static Double findMaxPrice(Purchase p){
        Double maxPrice = (double) 0;
        maxPrice = max(p.breadPrice, maxPrice );
        maxPrice = max(p.milkPrice, maxPrice );
        maxPrice = max(p.eggPrice, maxPrice );
        maxPrice = max(p.tomatoPrice, maxPrice );
        maxPrice = max(p.potatoPrice, maxPrice );

        return maxPrice;
    }

    private static Map.Entry<Double,LocalDate> findSumPrice(Purchase p){
        Double sum = (double) 0;
        if (p.breadPrice != null && p.breadQty != null)
            sum += p.breadPrice * p.breadQty;

        if (p.milkPrice != null && p.milkQty != null)
            sum += p.milkPrice * p.milkQty;

        if (p.eggPrice != null && p.eggQty != null)
            sum += p.eggPrice * p.eggQty;

        if (p.tomatoPrice != null && p.tomatoQty != null)
            sum += p.tomatoPrice * p.tomatoQty;

        if (p.potatoPrice != null && p.potatoQty != null)
            sum += p.potatoPrice * p.potatoQty;

        return Map.entry(sum, p.date);
    }

    private static Double max(Double a, Double b) {
        if (a == null) return b;
        if (b == null) return a;
        return Math.max(a, b);
    }

    private static Integer allQuan(Purchase p){
        Integer sum = 0;
        sum += p.milkQty == null ? 0 : p.milkQty;
        sum += p.eggQty == null ? 0 : p.eggQty;
        sum += p.breadQty == null ? 0 : p.breadQty;
        sum += p.potatoQty == null ? 0 : p.potatoQty;
        sum += p.tomatoQty == null ? 0 : p.tomatoQty;

        return sum;
    }

    private static Double parseDouble(String s) {
        return s.isEmpty() ? null : Double.parseDouble(s);
    }

    private static Integer parseInt(String s) {
        return s.isEmpty() ? null : Integer.parseInt(s);
    }

}