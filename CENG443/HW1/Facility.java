import java.util.List;

public class Facility {
    
    static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Error: No arguments provided. Please provide the required input.");
            System.out.println("Usage: java Facility <n> <capacities> <demands>");
            return;
        }


        // read the input parameters from args 
        // when we got java Facility 3 8 7 4 3 2 1.. 2n+1 args n is args[0],
        // capacities of facilities are args[1] to args[n] 
        // and demands are args[n+1] to args[2n]
        int n = Integer.parseInt(args[0]);
        int[] capacities = new int[n];
        for (int i = 0; i < n; i++) {
            capacities[i] = Integer.parseInt(args[i + 1]);
        }
        int[] demands = new int[n];
        for (int i = 0; i < n; i++) {
            demands[i] = Integer.parseInt(args[i + 1 + n]);
        }

        // create tanks
        List<Tank> tanks = new java.util.ArrayList<>();
        for (int i = 0; i < n; i++) {
            tanks.add(new Tank(i + 1, capacities[i], demands[i]));
        }

        MultiLockFacility.FacilityController controller = new MultiLockFacility.FacilityController(tanks);

        // Store producer threads for barrier synchronization
        Thread[] producers = new Thread[n];
        for (int i = 0; i < n; i++) {
            producers[i] = new ProducerThread(tanks.get(i), controller);
            producers[i].start();
        }

        // consumer - pass producer threads for barrier
        Thread consumer = new ConsumerThread(controller);
        consumer.start();
    }
}
