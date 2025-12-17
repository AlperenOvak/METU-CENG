// AI ALERT
// AI ALERT
// AI ALERT
// AI ALERT
// AI ALERT
// AI ALERT

//I implement this class previously inside of MultiLockFacility
//and its fields were public and there was no getter or setter.
//Thankfully I change it and move it to here with AI to obey the OOP principles -> Encapsulation.



import java.util.concurrent.locks.ReentrantLock;

public class Tank {
    private int id;
    private int stock = 0;
    private final int capacity;
    private final int batch; // amount consumed at a time
    private final ReentrantLock lock = new ReentrantLock();

    public Tank(int id, int capacity, int batch) {
        this.id = id;
        this.capacity = capacity;
        this.batch = batch;
    }

    // Getters
    public int getId() {
        return id;
    }

    public int getStock() {
        return stock;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getBatch() {
        return batch;
    }

    public ReentrantLock getLock() {
        return lock;
    }

    // Setters
    public void setStock(int stock) {
        this.stock = stock;
    }
}