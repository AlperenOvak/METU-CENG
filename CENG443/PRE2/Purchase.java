
import java.time.LocalDate;


public class Purchase {
    final String name;
    final Integer age;
    final LocalDate date;

    final Double breadPrice;
    final Integer breadQty;

    final Double milkPrice;
    final Integer milkQty;

    final Double eggPrice;
    final Integer eggQty;

    final Double potatoPrice;
    final Integer potatoQty;

    final Double tomatoPrice;
    final Integer tomatoQty;


    public Purchase(String name, Integer age, LocalDate date, 
        Double breadPrice, Integer breadQty, 
        Double milkPrice, Integer milkQty, 
        Double eggPrice, Integer eggQty, 
        Double potatoPrice, Integer potatoQty,
        Double tomatoPrice, Integer tomatoQty
    ){
        this.name = name;
        this.age = age;
        this.date = date;
        this.breadPrice = breadPrice;
        this.breadQty = breadQty;
        this.milkPrice = milkPrice;
        this.milkQty = milkQty;
        this.eggPrice = eggPrice;
        this.eggQty = eggQty;
        this.potatoPrice = potatoPrice;
        this.potatoQty = potatoQty;
        this.tomatoPrice = tomatoPrice;
        this.tomatoQty = tomatoQty;
    }

}