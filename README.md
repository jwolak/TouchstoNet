[![N|Solid](https://raw.githubusercontent.com/jwolak/TouchstoNet/master/ascii_logo.PNG)](https://nodesource.com/products/nsolid)
# TouchstoNet
**Network traffic generator and performance measurement tool**

## Features
- client and server mode
- message length option (up to 1kB)
- test time option (up to 1h)
- port number
- destination address
- debug mode
- summary print

## Examples:
- Touchstonet help
[![N|Solid](https://github.com/jwolak/TouchstoNet/blob/development/help_print.PNG?raw=true)](https://nodesource.com/products/nsolid)

- instant statistics [pkts, bytes throughput, time]
[![N|Solid](https://github.com/jwolak/TouchstoNet/blob/development/instant_figures.PNG?raw=true)](https://nodesource.com/products/nsolid)

- Finished test summary
[![N|Solid](https://github.com/jwolak/TouchstoNet/blob/development/summary_print.PNG?raw=true)](https://nodesource.com/products/nsolid)

## Building for source:

###### For EquinoxLogger:
```sh
cd TouchstoNet
git clone git@github.com:jwolak/EquinoxC-Logger.git
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


