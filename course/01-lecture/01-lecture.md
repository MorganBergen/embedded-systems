# lecture 01

**contents**

1.  [intro](#intro)
2.  [about](#about)
3.  [what do we learn](#what-do-we-learn)
4.  [embedded systems](#embedded-systems)
5.  [breakdown of a modern embedded system](#breakdown-of-a-modern-embedded-system)
6.  [integrated circuits:  types](#integrated-circuits-types)
8.  [internet of things IoT](#internet-of-things-iot)
9.  [cyber-physical systems (cps)](#cyber-physical-systems-cps)
10. [real-time systems](#real-time-systems)
11. [embedded vs general computing systems: number of applications](#embedded-vs-general-computing-systems-number-of-applications)
12. [embedded vs general computing systems:  programmability](#embedded-vs-general-computing-systems-programmability)
13. [embedded vs general computing systems:  run-time constraints](#embedded-vs-general-computing-systems-run-time-constraints)
14. [embedded vs general computing systems:  resource constraints](#embedded-vs-general-computing-systems-resource-constraints)
15. [trends in modern embedded systesm](#trends-in-modern-embedded-systesm)
16. [requirements for CPS/IoT/Embedded Systems](#requirements-for-cpsiotembedded-systems)
17. [performance](#performance)
18. [efficiency](#efficiency)
19. [safety](#safety)
20. [security and privacy](#security-and-privacy)
21. [summary](#summary)
22. [references](#references)

### intro

### about

### what do we learn

### embedded systems

### breakdown of a modern embedded system



DMIPS (Dhrystone MIPS) is a measure of computer performance that is commonly used to evaluate the performance of embedded systems and microprocessors. DMIPS stands for Dhrystone MIPS, which is a synthetic benchmark that measures the performance of a computer system by running a set of synthetic tests.

DMIPS is calculated by taking the number of millions of instructions per second (MIPS) that a system can execute, and then adjusting that number based on the number of Dhrystone instructions that are executed per second. The Dhrystone benchmark is a standard algorithm that has been used for many years to evaluate the performance of embedded systems and microprocessors.

DMIPS is often used as a way to compare the performance of different processors, as it provides a standardized way to measure performance. However, it should be noted that DMIPS is not a perfect measure of performance, as it is a synthetic benchmark and does not take into account real-world usage scenarios.



radiation theraphy machine

therac 25
-[ACEL](https://www.aecl.ca/about-aecl/)
- computer controlled radiation therapy machine
- six people died due to massive overdoses
- caused by synchronization mistakes in the software

The Therac-25 was a radiation therapy machine manufactured by AECL in the 80s, which offered a revolutionary dual treatment mode. It was also designed from the outset to use software based safety systems rather than hardware controls.

The removal of these hardware safety measures had tragic consequences, as race conditions in the codebase led to the death of three patients, and caused debilitating injuries to at least three other patients. The manufacturer ultimately became the target of several lawsuits from families of the victims, and became subject to a Class I recall from the FDA, a situation which only happens if the agency believes there is significant risk of death or serious injury through continued use of a medical device.


