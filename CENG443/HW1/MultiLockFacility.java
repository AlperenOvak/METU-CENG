import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class MultiLockFacility {

    static class FacilityController {
        private final ReentrantLock barrierLock = new ReentrantLock();
        private final Condition producersCond = barrierLock.newCondition();
        private final Condition consumerCond = barrierLock.newCondition();
        private int fullTanks = 0;
        private boolean producingPhase = true;
        private final int[] isFull;

        private final List<Tank> tanks;
        private final int totalProducers;

        FacilityController(List<Tank> tanks) {
            this.tanks = tanks;
            this.totalProducers = tanks.size();
            this.isFull = new int[totalProducers+1];
        }

        public void produce(Tank tank) throws InterruptedException {
            // Wait at barrier until phase is PRODUCING
            barrierLock.lock();
            try {
                while (!producingPhase || isFull[tank.getId()] == 1) {
                    producersCond.await();
                    Actions.start_element_generator(tank.getId());
                }
            } finally {
                barrierLock.unlock();
            }

            // Produce into tank
            tank.getLock().lock();
            try {
                if (tank.getStock() >= tank.getCapacity()){
                    
                    // increase full Tank count at barrier
                    barrierLock.lock();
                    isFull[tank.getId()] = 1;
                    try {
                        fullTanks++;
                        if (fullTanks == totalProducers) {
                            producingPhase = false;
                            consumerCond.signal();
                        }
                    } finally {
                        barrierLock.unlock();
                    }
                    // return and wait for next phase
                    Actions.stop_element_generator(tank.getId());
                    tank.getLock().unlock();
                    return;
                }

                tank.setStock(tank.getStock() + 1);
                //System.out.println("Tank " + tank.getId() + " stock: " + tank.getStock());
                Actions.generate_element(tank.getId());

            } finally {}
            tank.getLock().unlock();
        }


        public void consumeBatch() throws InterruptedException {
            barrierLock.lock();
            try {
                while (producingPhase) {
                    consumerCond.await();
                    Actions.start_compound_generator();
                }
            } finally {
                barrierLock.unlock();
            }

            for (Tank t : tanks) t.getLock().lock();

            try {
                while (hasEnough()){
                    //System.out.print("Consuming batch: ");
                    for (Tank t : tanks) {
                        t.setStock(t.getStock() - t.getBatch());
                        //System.out.print(t.getStock() + " ");
                    }
                    //System.out.println();
                    Actions.generate_compound();
                }
            } finally {
                for (Tank t : tanks) {
                    t.getLock().unlock();
                }
                switchToProducing();
                Actions.stop_compound_generator();
            }
        }

        private boolean hasEnough() {
            for (Tank t : tanks)
                if (t.getStock() < t.getBatch())
                    return false;
            return true;
        }

        private void switchToProducing() {
            barrierLock.lock();
            try {
                fullTanks = 0;
                producingPhase = true;
                for (int i = 1; i <= totalProducers; i++) {
                    isFull[i] = 0;
                }
                producersCond.signalAll();
            } finally {
                barrierLock.unlock();
            }
        }
    }
}
