// AI ALERT
// AI ALERT
// AI ALERT
// AI ALERT
// AI ALERT
// AI ALERT


// I again implement produce and consume functions 
// inside of this controller to see both functions to understand what happens for both
// after development finished, I move it to thread classes accordingly with thanks to AI.
// Again my inner goal for this is obeying the OOP principles -> Single Responsibility Principle (SRP)


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

        // Getters and setters for SRP
        public ReentrantLock getBarrierLock() {
            return barrierLock;
        }

        public Condition getProducersCond() {
            return producersCond;
        }

        public Condition getConsumerCond() {
            return consumerCond;
        }

        public boolean isProducingPhase() {
            return producingPhase;
        }

        public void setProducingPhase(boolean producingPhase) {
            this.producingPhase = producingPhase;
        }

        public int[] getIsFull() {
            return isFull;
        }

        public int getFullTanks() {
            return fullTanks;
        }

        public void setFullTanks(int fullTanks) {
            this.fullTanks = fullTanks;
        }

        public int getTotalProducers() {
            return totalProducers;
        }

        public List<Tank> getTanks() {
            return tanks;
        }
        
    }
}
