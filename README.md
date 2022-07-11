[![N|Solid](https://raw.githubusercontent.com/jwolak/TouchstoNet/master/ascii_logo.PNG)](https://nodesource.com/products/nsolid)

**Network traffic generator and performance measurement tool**

## Features:
- client and server mode
- packets length option (up to 1kB)
- test time option (up to 1h)
- port number
- destination address
- debug mode
- instant figures when test is running
- summary print (also after test is interrupted by user [Ctrl+C])

## Examples:
- Touchstonet help:

[![N|Solid](https://github.com/jwolak/TouchstoNet/blob/development/help_print.PNG?raw=true)](https://nodesource.com/products/nsolid)

- Instant statistics [pkts and bytes throughput, time]:

[![N|Solid](https://github.com/jwolak/TouchstoNet/blob/development/instant_figures.PNG?raw=true)](https://nodesource.com/products/nsolid)

- Finished test summary:

[![N|Solid](https://github.com/jwolak/TouchstoNet/blob/development/summary_print.PNG?raw=true)](https://nodesource.com/products/nsolid)

```sh
Server (debug mode): Touchstonet -s -p 777 -d c

Client (debug mode): Touchstonet -c -p 777 -a 127.0.0.1 -t 10 -l 256 -d c
```

## Building for source:

###### For EquinoxLogger:
```sh
cd TouchstoNet
git clone git@github.com:jwolak/EquinoxC-Logger.git
git checkout static_library_version
cd Build/
cmake CMakeLists.txt
make
```

###### For UnitTests:

```sh
cd TouchstoNet/UnitTests/UnityTestFramework/Unity
cmake CMakeLists.txt
make
cd TouchstoNet/UnitTests/Build
cmake CMakeLists.txt
make
```

## License

BSD 3-Clause License
**Copyright (c) 2022, Janusz Wolak,**
All rights reserved.

