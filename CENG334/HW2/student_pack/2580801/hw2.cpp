#include <iostream>
#include "hw2.h"
#include "monitor.h"
/* You can define any global variable
   function and class definition here.
   Programs will first call initStore() then
   all other functions
*/

class Store : public Monitor {
   int cap[3];
   int avail[3];
   int maxOrder;
   int reserved[3];
   Condition customerCV;
   Condition supplierCV[3];

public:
   Store() : supplierCV{Condition(this),Condition(this),Condition(this)}, customerCV(this) {}


   void initStore(int capAAA, int capBBB, int capCCC, int mOrder){
      __synchronized__;
      cap[AAA] = capAAA;
      cap[BBB] = capBBB;
      cap[CCC] = capCCC;
      maxOrder = mOrder;
      avail[AAA] = capAAA;
      avail[BBB] = capBBB;
      avail[CCC] = capCCC;
      reserved[AAA] = 0;
      reserved[BBB] = 0;
      reserved[CCC] = 0;

      customerCV.notifyAll();
      //std::cout << "Store initialized with capacity: " << capAAA << ", " << capBBB << ", " << capCCC << "\n";
      //std::cout << "Max order: " << mOrder << "\n";
      //std::cout << "Available: " << avail[AAA] << ", " << avail[BBB] << ", " << avail[CCC] << "\n";
      //std::cout << "Reserved: " << reserved[AAA] << ", " << reserved[BBB] << ", " << reserved[CCC] << "\n";
   }
   void buy(int countAAA, int countBBB, int countCCC){
      __synchronized__;
      while(!(avail[AAA] >= countAAA && avail[BBB] >= countBBB && avail[CCC] >= countCCC)){
         customerCV.wait();
      }
      avail[AAA] -= countAAA;
      avail[BBB] -= countBBB;
      avail[CCC] -= countCCC;
      //std::cout << "Customer bought " << countAAA << " AAA, " << countBBB << " BBB, " << countCCC << " CCC\n";
      supplierCV[AAA].notifyAll();
      supplierCV[BBB].notifyAll();
      supplierCV[CCC].notifyAll();
      return;
   }
   void maysupply(int itemtype, int count){
      __synchronized__;
      while(avail[itemtype] + count + reserved[itemtype] > cap[itemtype]){
         supplierCV[itemtype].wait();
      }
      //std::cout << "Supplier may supply " << count << " of item type " << itemtype << "\n";
      reserved[itemtype] += count;
   }
   void supply(int itemtype, int count){
      __synchronized__;
      reserved[itemtype] -= count;
      avail[itemtype] += count;

      //std::cout << "Supplier supplied " << count << " of item type " << itemtype << "\n";
      //std::cout << "Available: " << avail[AAA] << ", " << avail[BBB] << ", " << avail[CCC] << "\n";
      //std::cout << "Reserved: " << reserved[AAA] << ", " << reserved[BBB] << ", " << reserved[CCC] << "\n";

      customerCV.notifyAll();
   }
   void monitorStore(int outCap[3], int outAvail[3]){
      __synchronized__;
      outCap[AAA] = cap[AAA];
      outCap[BBB] = cap[BBB];
      outCap[CCC] = cap[CCC];
      outAvail[AAA] = avail[AAA];
      outAvail[BBB] = avail[BBB];
      outAvail[CCC] = avail[CCC];
   }
};

Store store;

void initStore(int cA, int cB, int cC, int mO) {
   store.initStore(cA, cB, cC, mO);
}

void buy(int aA, int aB, int aC) {
   store.buy(aA, aB, aC);
}

void maysupply(int itype, int n) {
   store.maysupply(itype, n);
}

void supply(int itype, int n) {
   store.supply(itype, n);
}

void monitorStore(int c[3], int a[3]) {
   store.monitorStore(c, a);
}
