Jobs
====
Jobs allows periodic execution of different short functions. It is designed to host
control loops. So called functions should be short.

Every job must specify deadline and if not set otherwise also its duration.

If tasks support is enabled jobs can be also executed on multiple tasks, which is
handy if you divide sensor reading and control algorithm, because control
algorithm can than run when for example mcu waiting for response from sensor.
Always be sure that jobs are running on tasks with highest priority, otherwise
deadlines might not be fulfilled every time.

Be aware of taking mutexes and semaphores. It can sometime result in long task
suspension and that would result to deadline misses.
