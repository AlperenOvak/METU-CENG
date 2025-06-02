/*#include "hw2.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

#define printl(lk, format, ...)                                                \
  pthread_mutex_lock(&lk);                                                     \
  printf(format, __VA_ARGS__);                                                 \
  pthread_mutex_unlock(&lk)

#define CWAIT 1000
#define SWAIT 1000

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int simOver = 0;
int maxOrder;

struct Supply {
  int item;
  int n;
};

int parseStore(char *arg, int cap[3]) {
  char *p = strtok(arg, ":");
  int i = 0, r;
  while (p != NULL) {
    r = atoi(p);
    if (i < 3)
      cap[i] = r;

    p = strtok(NULL, ":");
    i++;
  }
  return r;
}

int parseSuppliers(char *arg, int sup[]) {
  char *p = strtok(arg, ":");
  int i = 0, r;
  while (p != NULL) {
    sup[i++] = atoi(p);

    p = strtok(NULL, ":");
  }
  return i;
}

void *customer(void *n) {
  pthread_detach(pthread_self());
  while (!simOver) {
    int a, b, c;
    usleep(rand() % CWAIT + 10);
    while (1) {
      a = rand() % maxOrder;
      b = rand() % maxOrder;
      c = rand() % maxOrder;
      if (a + b + c > 0)
        break;
    }
    printl(mut, "buying %d,%d,%d\n", a, b, c);
    buy(a, b, c);
    printl(mut, "bought %d,%d,%d\n", a, b, c);
  }
  return NULL;
}

void *supplier(void *p) {
  Supply *s = (Supply *)p;
  pthread_detach(pthread_self());

  while (!simOver) {
    int c[3], a[3];
    printl(mut, "maysupply: %d %d\n", s->item, s->n);
    maysupply(s->item, s->n);
    printl(mut, "maysupplying: %d %d\n", s->item, s->n);
    usleep(rand() % SWAIT + 10);
    supply(s->item, s->n);
    printl(mut, "supplied: %d %d\n", s->item, s->n);
    monitorStore(c, a);
    printl(mut, "store: %d/%d %d/%d %d/%d\n", a[0], c[0], a[1], c[1], a[2],
           c[2]);
  }
  printl(mut, "sim over, supplier: %d\n", s->item);
  return NULL;
}

int main(int argc, char *argv[]) {
  int cap[3];
  int suppliers[100];
  int ncust;
  int nsup;
  int i;

  maxOrder = parseStore(argv[1], cap);
  ncust = atoi(argv[2]);
  nsup = parseSuppliers(argv[3], suppliers);

  initStore(cap[0], cap[1], cap[2], maxOrder);

  for (i = 0; i < ncust; i++) {
    pthread_t tid;
    pthread_create(&tid, NULL, customer, NULL);
  }
  for (i = 0; i < nsup; i++) {
    pthread_t tid;
    Supply *s;
    if (suppliers[i]) {
      s = new Supply;
      s->item = i % 3;
      s->n = suppliers[i];
      pthread_create(&tid, NULL, supplier, (void *)s);
    }
  }

  sleep(1);
  simOver = 1;
  sleep(2);
  return 0;
}*/

// testrun.cpp
#include <iostream>
#include <vector>
#include <atomic>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstring>
#include "hw2.h"
#include "monitor.h"

#ifndef AAA
#define AAA 0
#define BBB 1
#define CCC 2
#endif

static int *crit_fail;
inline void failC(int c) { crit_fail[c] = 1; }

// SCENARIO 1
std::atomic<bool> s1_custDone(false);
void* s1_customer(void*) { buy(2,2,0); s1_custDone = true; return nullptr; }
void* s1_supplier(void*) { maysupply(BBB,1); supply(BBB,1); return nullptr; }
int runScenario1() {
    std::cout<<"Scenario 1… ";
    initStore(5,5,5,5);
    buy(0,4,0); buy(3,0,0);
    pthread_t tc,ts;
    pthread_create(&tc,nullptr,s1_customer,nullptr);
    usleep(100000);
    if(s1_custDone){ std::cout<<"FAIL(1)\n"; failC(1); failC(4); pthread_join(tc,nullptr); return -1; }
    int cap[3],av[3]; monitorStore(cap,av);
    if(av[AAA]!=2||av[BBB]!=1){ std::cout<<"FAIL(11)\n"; failC(11); failC(4);
        maysupply(AAA,2); supply(AAA,2);
        maysupply(BBB,1); supply(BBB,1);
        pthread_join(tc,nullptr); return -1;
    }
    pthread_create(&ts,nullptr,s1_supplier,nullptr);
    pthread_join(ts,nullptr);
    pthread_join(tc,nullptr);
    monitorStore(cap,av);
    if(av[AAA]!=0||av[BBB]!=0){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 2
std::atomic<bool> s2_suppDone(false);
void* s2_supplier(void*){ maysupply(AAA,2); supply(AAA,2); s2_suppDone=true; return nullptr; }
void* s2_customer(void*){ buy(2,0,0); return nullptr; }
int runScenario2(){
    std::cout<<"Scenario 2… ";
    initStore(3,3,3,3);
    pthread_t ts,tc;
    pthread_create(&ts,nullptr,s2_supplier,nullptr);
    usleep(100000);
    if(s2_suppDone){ std::cout<<"FAIL(5)\n"; failC(5); pthread_join(ts,nullptr); return -1; }
    pthread_create(&tc,nullptr,s2_customer,nullptr);
    pthread_join(tc,nullptr);
    usleep(100000);
    if(!s2_suppDone){ std::cout<<"FAIL(10)\n"; failC(10); pthread_join(ts,nullptr); return -1; }
    pthread_join(ts,nullptr);
    int cap[3],av[3]; monitorStore(cap,av);
    if(av[AAA]!=3){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 3
std::atomic<bool> s3_d1(false), s3_d2(false);
void* s3_s1(void*){ maysupply(AAA,5); supply(AAA,5); s3_d1=true; return nullptr; }
void* s3_s2(void*){ maysupply(AAA,3); supply(AAA,3); s3_d2=true; return nullptr; }
void* s3_c(void*){ buy(5,0,0); return nullptr; }
int runScenario3(){
    std::cout<<"Scenario 3… ";
    initStore(10,10,10,10);
    buy(3,0,0);
    pthread_t t1,t2,tc;
    pthread_create(&t1,nullptr,s3_s1,nullptr);
    usleep(100000);
    pthread_create(&t2,nullptr,s3_s2,nullptr);
    usleep(200000);
    if(!s3_d2){ std::cout<<"FAIL(12)\n"; failC(12); pthread_cancel(t1); return -1; }
    pthread_join(t2,nullptr);
    pthread_create(&tc,nullptr,s3_c,nullptr);
    pthread_join(tc,nullptr);
    usleep(100000);
    if(!s3_d1){ std::cout<<"FAIL(10)\n"; failC(10); pthread_cancel(t1); return -1; }
    pthread_join(t1,nullptr);
    int cap[3],av[3]; monitorStore(cap,av);
    if(av[AAA]!=10){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 4
std::atomic<bool> s4_d1(false), s4_d2(false);
void* s4_c1(void*){ buy(1,2,0); s4_d1=true; return nullptr; }
void* s4_c2(void*){ buy(1,1,0); s4_d2=true; return nullptr; }
void* s4_sA(void*){ maysupply(AAA,1); supply(AAA,1); return nullptr; }
void* s4_sB(void*){ maysupply(BBB,2); supply(BBB,2); return nullptr; }
int runScenario4(){
    std::cout<<"Scenario 4… ";
    initStore(3,3,3,3);
    buy(2,2,0);
    pthread_t c1,c2;
    pthread_create(&c1,nullptr,s4_c1,nullptr);
    usleep(100000);
    int cap[3],av[3]; monitorStore(cap,av);
    if(av[AAA]!=1||av[BBB]!=1){ std::cout<<"FAIL(11)\n"; failC(11); pthread_cancel(c1); return -1; }
    pthread_create(&c2,nullptr,s4_c2,nullptr);
    pthread_join(c2,nullptr);
    if(!s4_d2){ std::cout<<"FAIL(11)\n"; failC(11); pthread_cancel(c1); return -1; }
    pthread_t sa,sb;
    pthread_create(&sa,nullptr,s4_sA,nullptr); pthread_join(sa,nullptr);
    pthread_create(&sb,nullptr,s4_sB,nullptr); pthread_join(sb,nullptr);
    usleep(100000);
    if(!s4_d1){ std::cout<<"FAIL(9)\n"; failC(9); pthread_cancel(c1); return -1; }
    pthread_join(c1,nullptr);
    monitorStore(cap,av);
    if(av[AAA]!=0||av[BBB]!=0){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 5
std::atomic<bool> s5_buy(false);
std::atomic<bool> s5_supDone[3];
void* s5_b(void*){ buy(0,0,0); s5_buy=true; return nullptr; }
void* s5_s(void* arg){ int i=(intptr_t)arg; maysupply(i,0); supply(i,0); s5_supDone[i]=true; return nullptr; }
int runScenario5(){
    std::cout<<"Scenario 5… ";
    initStore(10,10,10,5);
    int c0[3],a0[3]; monitorStore(c0,a0);
    pthread_t b,ts[3];
    s5_buy=false; for(int i=0;i<3;i++) s5_supDone[i]=false;
    pthread_create(&b,nullptr,s5_b,nullptr);
    for(int i=0;i<3;i++) pthread_create(&ts[i],nullptr,s5_s,(void*)(intptr_t)i);
    pthread_join(b,nullptr);
    for(int i=0;i<3;i++) pthread_join(ts[i],nullptr);
    int c1[3],a1[3]; monitorStore(c1,a1);
    bool ok=true;
    if(!s5_buy){ std::cout<<"FAIL(13)\n"; failC(13); ok=false; }
    for(int i=0;i<3;i++){
        if(!s5_supDone[i]){ std::cout<<"FAIL(13)\n"; failC(13); ok=false; }
        if(a1[i]!=a0[i]){ std::cout<<"FAIL(3)\n"; failC(3); ok=false; }
    }
    if(ok) std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 6
static int S6_loops;
void* s6_c(void*){ for(int i=0;i<S6_loops;i++) buy(1,1,1); return nullptr; }
void* s6_s(void*){ for(int i=0;i<S6_loops;i++){ maysupply(AAA,1); supply(AAA,1); maysupply(BBB,1); supply(BBB,1); maysupply(CCC,1); supply(CCC,1);} return nullptr; }
int runScenario6(){
    std::cout<<"Scenario 6… ";
    const int C=100,NC=50,NS=50;
    initStore(C,C,C,C);
    S6_loops=100;
    std::vector<pthread_t> vc(NC), vs(NS);
    for(int i=0;i<NC;i++) pthread_create(&vc[i],nullptr,s6_c,nullptr);
    for(int i=0;i<NS;i++) pthread_create(&vs[i],nullptr,s6_s,nullptr);
    for(auto&t:vc) pthread_join(t,nullptr);
    for(auto&t:vs) pthread_join(t,nullptr);
    int cap[3],av[3]; monitorStore(cap,av);
    if(av[AAA]!=C||av[BBB]!=C||av[CCC]!=C){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// ================= SCENARIO 7 =================
// Deterministic mixed‐sequence test (Criterion 3,13)
static const int S7_LOOPS = 30;
void* s7_pattern(void*) {
    for(int i = 0; i < S7_LOOPS; i++) {
        // phase 1: each thread buys one of each
        buy(2,3,1); 
        // phase 2: supply in bulk
        maysupply(AAA,2); supply(AAA,2); 
        maysupply(BBB,3); supply(BBB,3); 
        maysupply(CCC,1); supply(CCC,1); 
        // phase 3: partial buy
    }
    return nullptr;
}
int runScenario7() {
    std::cout << "Scenario 7 – Deterministic mixed sequence... ";
    initStore(50,50,50,5);
    const int THREADS = 20000;
    pthread_t th[THREADS];
    for(int i = 0; i < THREADS; i++)
        pthread_create(&th[i], nullptr, s7_pattern, nullptr);
    for(int i = 0; i < THREADS; i++)
        pthread_join(th[i], nullptr);
    int cap[3], av[3]; monitorStore(cap,av);
    bool ok = true;
    for(int j=0;j<3;j++) if(av[j]<0 || av[j]>cap[j]) { ok=false; failC(3); break; }
    std::cout << (ok ? "PASS\n" : "FAIL (3)\n");
    return 0;
}

// ================= SCENARIO 8 =================
// Deterministic per‐item cycle (Criterion 3,13)
static const int S8_LOOPS = 40;
void* s8_itemCycle(void* arg) {
    int item = (intptr_t)arg;
    for(int i=0;i<S8_LOOPS;i++){
        buy(item==AAA?1:0, item==BBB?1:0, item==CCC?1:0);
        // supply one of this item, then buy one of the same
        maysupply(item,1);
        supply(item,1);
    }
    return nullptr;
}
int runScenario8() {
    std::cout << "Scenario 8 – Deterministic per-item cycle... ";
    initStore(30,30,30,5);
    pthread_t th[3];
    for(int i=0;i<3;i++)
        pthread_create(&th[i], nullptr, s8_itemCycle, (void*)(intptr_t)i);
    for(int i=0;i<3;i++)
        pthread_join(th[i], nullptr);
    int cap[3], av[3]; monitorStore(cap,av);
    bool ok = true;
    for(int j=0;j<3;j++) if(av[j]<0 || av[j]>cap[j]) { ok=false; failC(3); break; }
    std::cout << (ok ? "PASS\n" : "FAIL (3)\n");
    return 0;
}

// SCENARIO 9
int runScenario9(){
    std::cout<<"Scenario 9… ";
    initStore(5,5,5,5);
    buy(5,0,0); buy(0,5,0); buy(0,0,5);
    int c[3],a[3]; monitorStore(c,a);
    if(a[0]||a[1]||a[2]){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 10
std::atomic<bool> s10_d[3];
void* s10_b(void* idx){ int i=(intptr_t)idx; int r[3]={0}; r[i]=1; buy(r[0],r[1],r[2]); s10_d[i]=true; return nullptr;}
int runScenario10(){
    std::cout<<"Scenario 10… ";
    initStore(5,5,5,5);
    pthread_t th[3];
    for(int i=0;i<3;i++){ s10_d[i]=false; pthread_create(&th[i],NULL,s10_b,(void*)(intptr_t)i);}
    for(int i=0;i<3;i++) pthread_join(th[i],NULL);
    int c[3],a[3]; monitorStore(c,a);
    if(a[0]!=4||a[1]!=4||a[2]!=4){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 11
std::atomic<bool> s11_d[3];
void* s11_supp(void* idx){ int i=(intptr_t)idx; maysupply(i,1); supply(i,1); s11_d[i]=true; return nullptr; }
int runScenario11(){
    std::cout<<"Scenario 11… ";
    initStore(5,5,5,5);
    buy(1,1,1);
    pthread_t th[3];
    for(int i=0;i<3;i++){ s11_d[i]=false; pthread_create(&th[i],NULL,s11_supp,(void*)(intptr_t)i);}
    for(int i=0;i<3;i++) pthread_join(th[i],NULL);
    int c[3],a[3]; monitorStore(c,a);
    if(a[0]!=5||a[1]!=5||a[2]!=5){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 12
std::atomic<bool> s12_buy(false);
void* s12_sup(void*){ maysupply(0,1); supply(0,1); return nullptr; }
void* s12_buyt(void*){ buy(0,1,0); s12_buy=true; return nullptr; }
int runScenario12(){
    std::cout<<"Scenario 12… ";
    initStore(1,5,5,5);
    pthread_t sup,bbb;
    pthread_create(&sup,NULL,s12_sup,NULL);
    usleep(100000);
    pthread_create(&bbb,NULL,s12_buyt,NULL);
    usleep(100000);
    if(!s12_buy){ std::cout<<"FAIL(13)\n"; failC(13);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 13
std::atomic<bool> s13_sup(false);
void* s13_cu(void*){ buy(6,0,0); return nullptr; }
void* s13_sp(void*){ maysupply(1,1); supply(1,1); s13_sup=true; return nullptr; }
int runScenario13(){
    std::cout<<"Scenario 13… ";
    initStore(5,6,5,5);
    buy(0,1,0);
    pthread_t cu,sp;
    pthread_create(&cu,NULL,s13_cu,NULL);
    usleep(100000);
    pthread_create(&sp,NULL,s13_sp,NULL);
    usleep(100000);
    if(!s13_sup){ std::cout<<"FAIL(13)\n"; failC(13);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 14
int runScenario14(){
    std::cout<<"Scenario 14… ";
    initStore(2,2,2,2);
    buy(1,1,1);
    initStore(3,3,3,3);
    buy(2,2,2);
    int c[3],a[3]; monitorStore(c,a);
    if(a[0]!=1||a[1]!=1||a[2]!=1){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 15
static int S15_loops=50;
std::atomic<int> S15_b(0),S15_s(0);
void* s15_bu(void*){ for(int i=0;i<S15_loops;i++){ buy(1,0,0); S15_b++; } return nullptr; }
void* s15_su(void*){ for(int i=0;i<S15_loops;i++){ maysupply(0,1); supply(0,1); S15_s++; } return nullptr; }
int runScenario15(){
    std::cout<<"Scenario 15… ";
    initStore(10,5,5,1);
    pthread_t b,s;
    S15_b=0; S15_s=0;
    pthread_create(&b,NULL,s15_bu,NULL);
    pthread_create(&s,NULL,s15_su,NULL);
    pthread_join(b,NULL);
    pthread_join(s,NULL);
    int cap[3],av[3]; monitorStore(cap,av);
    if(av[0]!=10||S15_b!=S15_loops||S15_s!=S15_loops){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 16
static int S16_thr=20,S16_lo=100;
void* s16_b(void*){ for(int i=0;i<S16_lo;i++) buy(1,0,0); return nullptr; }
void* s16_su2(void*){ for(int i=0;i<S16_lo;i++){ maysupply(0,1); supply(0,1);} return nullptr; }
int runScenario16(){
    std::cout<<"Scenario 16… ";
    initStore(50,5,5,1);
    std::vector<pthread_t> bt(S16_thr),st(S16_thr);
    for(int i=0;i<S16_thr;i++){
        pthread_create(&bt[i],NULL,s16_b,NULL);
        pthread_create(&st[i],NULL,s16_su2,NULL);
    }
    for(int i=0;i<S16_thr;i++){
        pthread_join(bt[i],NULL);
        pthread_join(st[i],NULL);
    }
    int cap[3],av[3]; monitorStore(cap,av);
    if(av[0]!=50){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// SCENARIO 17
static int S17_thr=10;
void* s17_o(void*){ for(int i=0;i<20;i++){ buy(0,0,0); maysupply(0,0); supply(0,0);} return nullptr; }
void* s17_m(void*){ int c[3],a[3]; for(int i=0;i<20;i++) monitorStore(c,a); return nullptr; }
int runScenario17(){
    std::cout<<"Scenario 17… ";
    initStore(5,5,5,5);
    std::vector<pthread_t> t1(S17_thr),t2(S17_thr);
    for(int i=0;i<S17_thr;i++){
        pthread_create(&t1[i],NULL,s17_o,NULL);
        pthread_create(&t2[i],NULL,s17_m,NULL);
    }
    for(int i=0;i<S17_thr;i++){
        pthread_join(t1[i],NULL);
        pthread_join(t2[i],NULL);
    }
    std::cout<<"PASS\n";
    return 0;
}

// ================= SCENARIO 18 =================
// Deterministic supply/buy cycle (Criterion 3,13)
static const int S18_LOOPS = 25;
void* s18_cycle(void*) {
    for(int i=0;i<S18_LOOPS;i++){
        buy(2,1,3);
        // supply phases
        maysupply(AAA,2); supply(AAA,2);
        maysupply(BBB,1); supply(BBB,1);
        maysupply(CCC,3); supply(CCC,3);
        // buy phase
    }
    return nullptr;
}
int runScenario18() {
    std::cout << "Scenario 18 – Deterministic supply/buy cycle... ";
    initStore(40,40,40,5);
    const int THREADS = 4;
    pthread_t th[THREADS];
    for(int i=0;i<THREADS;i++)
        pthread_create(&th[i], nullptr, s18_cycle, nullptr);
    for(int i=0;i<THREADS;i++)
        pthread_join(th[i], nullptr);
    int cap[3], av[3]; monitorStore(cap,av);
    bool ok = true;
    for(int j=0;j<3;j++) if(av[j]<0 || av[j]>cap[j]) { ok=false; failC(3); break; }
    std::cout << (ok ? "PASS\n" : "FAIL (3)\n");
    return 0;
}

// SCENARIO 19
std::atomic<bool> s19_d1(false),s19_d2(false);
void* s19_1(void*){ maysupply(1,5); supply(1,5); s19_d1=true; return nullptr; }
void* s19_2(void*){ maysupply(1,3); supply(1,3); s19_d2=true; return nullptr; }
void* s19_cu(void*){ buy(5,5,0); return nullptr; }
int runScenario19(){
    std::cout<<"Scenario 19… ";
    initStore(10,10,10,10);
    buy(0,3,0);
    pthread_t t1,t2,tc;
    pthread_create(&t1,NULL,s19_1,NULL);
    usleep(100000);
    pthread_create(&t2,NULL,s19_2,NULL);
    usleep(200000);
    if(!s19_d2){ std::cout<<"FAIL(12)\n"; failC(12); return -1; }
    pthread_join(t2,NULL);
    pthread_create(&tc,NULL,s19_cu,NULL);
    pthread_join(tc,NULL);
    usleep(100000);
    if(!s19_d1){ std::cout<<"FAIL(10)\n"; failC(10); return -1; }
    pthread_join(t1,NULL);
    int c[3],a[3]; monitorStore(c,a);
    if(a[1]!=10){ std::cout<<"FAIL(3)\n"; failC(3);} else std::cout<<"PASS\n";
    return 0;
}

// ================= SCENARIO 20 =================
// Deterministic cross‐supply/buy (Criterion 3,13)
static const int S20_LOOPS = 20;
void* s20_cross(void* arg) {
    int idx = (intptr_t)arg;
    for(int i=0;i<S20_LOOPS;i++){
        if(idx==0) { buy(0,1,0); maysupply(AAA,1); supply(AAA,1); }
        if(idx==1) { buy(0,0,1); maysupply(BBB,1); supply(BBB,1); }
        if(idx==2) { buy(1,0,0); maysupply(CCC,1); supply(CCC,1); }
    }
    return nullptr;
}
int runScenario20() {
    std::cout << "Scenario 20 – Cross-supply/buy deterministic... ";
    initStore(20,20,20,5);
    //buy(5,5,5);
    pthread_t th[3];
    for(int i=0;i<3;i++)
        pthread_create(&th[i], nullptr, s20_cross, (void*)(intptr_t)i);
    for(int i=0;i<3;i++)
        pthread_join(th[i], nullptr);
    int cap[3], av[3]; monitorStore(cap,av);
    bool ok = true;
    for(int j=0;j<3;j++) if(av[j]<0 || av[j]>cap[j]) { ok=false; failC(3); break; }
    std::cout << (ok ? "PASS\n" : "FAIL (3)\n");
    return 0;
}

int main(){
    crit_fail=(int*)mmap(nullptr,14*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    memset(crit_fail,0,14*sizeof(int));
    struct { int(*fn)(); std::vector<int> t; } tests[20]={
        {runScenario1,{1,2,9}}, {runScenario2,{5,10}}, {runScenario3,{5,6,10,12}},
        {runScenario4,{1,2,4,9,11}}, {runScenario5,{3,13}}, {runScenario6,{3,13}},
        {runScenario7,{3,13}}, {runScenario8,{3,13}}, {runScenario9,{3}},
        {runScenario10,{2,3}},{runScenario11,{6,3}},{runScenario12,{13}},
        {runScenario13,{13}},{runScenario14,{3}},{runScenario15,{3,13}},
        {runScenario16,{3,13}},{runScenario17,{13}},{runScenario18,{3,13}},
        {runScenario19,{5,6,10,12}}, {runScenario20,{3,13}}
    };
    for(int i=0;i<20;i++){
        pid_t pid=fork();
        if(pid==0){ tests[i].fn(); _exit(0); }
        bool timed=false;
        for(int t=0;t<20;t++){
            if(waitpid(pid,nullptr,WNOHANG)==pid) break;
            sleep(1);
            if(t==19){ kill(pid,SIGKILL); waitpid(pid,nullptr,0); timed=true; }
        }
        if(timed){
            std::cerr<<"Scenario "<<(i+1)<<" timed out\n";
            for(int c:tests[i].t) failC(c); failC(13);
        }
    }
    std::cout<<"\n=== Summary ===\n";
    int passed=0;
    for(int c=1;c<=13;c++){
        bool f=crit_fail[c];
        std::cout<<"Criterion "<<c<<": "<<(f?"FAIL":"PASS")<<"\n";
        if(!f) passed++;
    }
    std::cout<<"Score: "<<passed<<"/13\n";
    return 0;
}
