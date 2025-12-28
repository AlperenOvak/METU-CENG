import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.time.LocalDate;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Lab3 {
    public static void main(String[] args) throws FileNotFoundException {
        System.out.println("Hello, World!");
        BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(new File("pre_data.csv"))));
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
        

        List<Purchase> purchases = br.lines().skip(1).map(mapToPurhchase).collect(Collectors.toList());


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
        System.out.println(
            purchases.stream().map(p->findSumPrice(p)).max(Comparator.comparing(m -> m.getKey())).get().getValue()
        );

        System.out.println("--------");
    
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