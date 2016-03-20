Jobs vs. Tasks
==============
This document refers to [Jobs](/parts/jobs.md) and [Tasks](/parts/tasks.md).

You should be familiar with threads from other platforms. Tasks are from usability
point of view almost same. They are switched according their priority and
availability. Jobs are different. They are designed to execute single function at
the time and when this function exits it executes another. It cant interrupt
execution when more important task come. So why use jobs instead of tasks? Task
requires for their run stack memory and during whole live of task is this memory
taken. This limits number of tasks running. Jobs are sharing same stack and only
one function has data on it at the time. This results in less memory consumption.
Another huge difference is how planing works. Tasks are planned based on priority.
Task with higher priority will run unless it isn't suspended. Jobs don't have
priority, but they have to specify time until they should be finished (deadline)
and duration of execution. With these two parameters jobs planner can plan their
execution.
