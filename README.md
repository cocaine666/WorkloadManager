# WorkloadManager
Small way of managing certain workloads on multithreaded systems

# How to implement custom workloads?
Custom workloads are implemented by our WorkloadTemplate that will be released soon enough when the beta build 
becomes 90% usable and without any bugs.

# Will this be able to operate on other OS?
This project will be ported to Linux most likely, considering the amount of free time I have - not soon.

# How is this managing workloads>
What this program does is that it reads your basic system information and runs the workload in a way to make the most
out of your system. WorkloadTemplate (or your custom workload) reads the arguments that Manager pushes (first arg: how
many cores will run -- second arg: what workloads) and starts doing workloads on separate threads simultaneously.
