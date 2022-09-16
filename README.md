# wlac4 (Windows to Linux Api Converter 4)  
  
There are cases when there is a code base that is compatible to [POSIX API](https://en.wikipedia.org/wiki/POSIX).
When there is a necessity to compile the code for Windows Microsoft compiler, then a lot headers/functions/data are not compatible.
The aim of this project to implement missing headers and for each header to implement data and functions (at least frequently used stuff). 
  
Using this approach [Sun XDR RPC](https://web.cs.wpi.edu/~rek/DCS/D04/SunRPC.html) and some dependent projects ported for Windows.
Up to now [WLAC2](https://github.com/davitkalantaryan/wlac2) was used for the porting.
WLAC4 will have a lot of fixes and code simplification. 
Everybdy is welcome to contribute. Whenever somebody has some code for porting to Windows, the libraru can be used, and if 
still some functions are missing for complete port then feel free to implement and create merge request or create an issue 
for implementing missing stuff.  
If something is missing here, then probably that can be found on [WLAC2](https://github.com/davitkalantaryan/wlac2).
  
## Up to now existing headers  
 1. [getopt.h](docs/includes/getopt.h.md)  
 2. [poll.h](docs/includes/poll.h.md)  
 3. [pthread.h](docs/includes/pthread.h.md)  
 4. [stdatomic.h](docs/includes/stdatomic.h.md)  
 5. [syslog.h](docs/includes/syslog.h.md)  
   
 ## Redesigned headers  
   
 Redesigned headers are the headers those exist also for Windows Microsoft compiler, but they are missing some functions or data. 
 In this case the same header is include in the redesigned folder. The regular way of content is this header is including standard header
 then declaration of missing symbols (functions and data).  
 Below is the list of redesigned headers:  
   
  1. [redesigned/stdio.h](docs/includes/redesigned/stdio.h.md)  
  2. [redesigned/string.h](docs/includes/redesigned/string.h.md)  
  3. [redesigned/time.h](docs/includes/redesigned/time.h.md)  
