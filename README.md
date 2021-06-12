SCHEDULING  ALGORITHM

Problem Statement:
A desirable property of any real-time system is the guarantee that it will perform effectively. This can be done in the offline mode under normal situations to ensure system performance based on the regular workload or processes. At times, different users desire different capabilities from the system. The challenge, then, is to provide some mechanism or best case scheduling algorithm to guarantee the maximum performance level under such circumstances.

Objective:
 Implementation of every scheduling algorithm to find aggregate statistics about them and compare them to find the most optimal algorithm in a given situation.
Sub-Objective:
 1.To implement all algorithms and find the best case according to User’s needs.
 2.Compare and check the performance of these algorithms.

Methodology:
The main purpose of scheduling algorithms is to minimize resource starvation and to ensure fairness of resource allocation amongst the parties utilizing the resources. Scheduling deals with the problem of deciding which of the outstanding requests is to be allocated resources.
As mentioned, we need to try every algorithm on a given workload or processes in offline mode and then manipulate the algorithm used by the system according to the user’s need. It will ensure that the system will work effectively under those circumstances.
In our solution, we are using C programming to find an appropriate algorithm in a given situation for CPU Optimization.

 1.First Come First Serve (FCFS) 
   It executes queued requests and processes in order of their arrival. Processes that request the CPU first get the CPU allocation first. This is managed with a FIFO queue.
 2.Priority scheduling
   It is a non-preemptive algorithm.
   Each process is assigned first arrival time if two processes have the same arrival time, then compared to priorities.
 3.Round Robin
   It is a preemptive algorithm.
   The time quantum are assigned to each process in equal portions and in circular order, handling all processes without priority.
 4.Shortest Job First (SJF)
   The process having the smallest execution time is chosen for the next execution. This scheduling method can be preemptive or non-preemptive. It significantly reduces the   
   average waiting time for other processes awaiting execution.

Scope of the Project:
 We can use the implementation of every scheduling algorithm to find aggregate statistics about them and compare them to find the most optimal algorithm in a given situation. We  can find the best case according to User’s needs. Therefore, by using this approach, we can develop a user-friendly operating system. And thus; we can develop a system with     optimum performance.


