#  real-time process scheduling

##  critical instance theorem

-  if a low priority task meets its first deadline when all higher priority tasks are started at the same time, then this task's future deadlines will always be met.

-  example for a low priority task $\tau_{2}$ sinc ethe first instance met the deadline, all future deadlines will be met

[image]()

##  exact schedulability test

-  each task checks if it can meet its first deadline (critical instant theorem)
-  estimating if the lowest priority task met deadline needs several iteration.
-  for lowest priority tasks, it checks if it can meet its first deadline
-  iteratibely calculates response time $r_{i}^{k + 1}$, larger equation for subsequent iteration (i.e., $r_{i}^{k + 1}$) starting ait $k = 0$
-  the following equation calculates the response time $r$ of the lowest priority task
-  $r^{0}$ is the response time of the first iteration

$$r_{i}^{k + 1} = e_{i} + \sum_{j = 1}^{i -1}\bigg\lceil\frac{r_{i}{k}}{p_{j}}\bigg\rceil, \text{ where } r_{i}^{0} = \sum_{j = 1}^{i} e_{j} $$

- the test terminates when, 
    -  $r_{i}^{k + 1} > p_{i}$ which is not schedulable
    -  or when $r_{i}^{k + 1} = r_{i}^{k} \leq p_{i}$ which is schedulable
-  $i$ -> task, $k$ -> iteration
-  assumption:  task $i$ has a lower priority than task $i - 1$

###  find $r_{3}^{3}$
