#FILE STRUCTURES & HEADERS:

  - main.c -> include all supporting .h files here... do not include other .c files 
  - [supporting .c file].c -> include this file's .h file here
  - if you create a struct, define the struct in the .h file you use it

#TO COMPILE:

  - gcc -o a.out [supporting .c file here] [supporting .c file here] main.c

#TO RUN:

  - ./a.out


For help with c file structure and compliation https://courses.cs.washington.edu/courses/cse374/20au/lectures/12-structs-in-c/12-structs-in-c.pdf


TODO:

- implement bankers algorithm 
  - returns ready queue safe sequence ( worse option )
  - or returns next safe job from ready queue ( better option )
  
- when mounted on CPU, job checks for requests/releases  (charles working on this @ 9:29 pm)
  - if found, immediately send to wait queue and process next ready queue node
  
- check wait queue before hold queues 
