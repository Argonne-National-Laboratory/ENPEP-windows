**Status:** This is a legacy software and no further enhancements or modifications will be made.

# This is back end "Balance" program for ENPEP for Windows available at https://anl.app.box.com/s/ifdzmym0qzjq442x929h

The ENPEP for Windows model has its origins in the DOS version of the Energy and Power Evaluation Program (ENPEP), which was developed by Argonne National Laboratory (ANL) under the auspices of the U.S. Department of Energy (DOE) and the International Atomic Energy Agency (IAEA). However, ENPEP for Windows model is significantly modified and rather different in structure and capabilities from the older DOS version of ENPEP. It fully utilizes the Windows operating environment and provides the user with a graphical interface for designing a comprehensive model of the energy system of a country or region.


## Links
* Source code repository: https://github.com/xxxxxxxxxxxxxxxxxxxxxx
* User guide: [PDF](docs/ENPEP-BALANCE_Manual_20070914.pdf)


## Installation
The Bal.exe is a Windows program and is the back end for ENPEP Windows program and will be installed when ENPEP Windows is installed. 


### Dependencies:
* This is a part of ENPEP Windows and the necessary input files are created using the user interface of ENPEP Windows.  

## Quick start

The [config.json file](config.json) provided in the repository can be used to do a co-simulation after editing in the path names (with any text editor). Then open a command line prompt within the folder containing the **tdcosimapp.py** file (for e.g. by typing Shift+C+M+D) and run the following script to start the co-simulation.

```
windows console Bal.exe log_file.txt
```
### Use cases:
Following example use cases are provided:
1. Bal.exe log_file.txt (make sure that the files in the test Data folder are in the current directory 

## Package details
Technical information on the package can be found here:
1. [ENPEP Windows](docs/ENPEP-BALANCE_Manual_20070914.pdf)

## Issues
No support will be provided for any bugs or errors. The software is provided as is.

## Who is responsible?
**Project PI:**

- Guenter Conzelmann guenter@anl.gov

**Core developers:**

- Prakash Thimmapuram prakash@anl.gov
- Pascal Pochol 

**Contributors:**
- Vladimir Koritarov koritarov@anl.gov
- Richard Cirillo
- Thomas Veselka tdveselka@anl.gov
- Michael North
- Chic Macal macal@anl.gov


## Acknowledgement
We want to acknowledge [Shrirang Abhyankar](https://github.com/abhyshr) for his contributions to the code base development.

We would like to recognize the support of the U.S. Department of Energy (DOE) and the International Atomic Energy Agency (IAEA). 


## Citation
If you use this code please cite it as:
```
@misc{ENPEP Windows,
https://ceeesa.es.anl.gov/projects/Enpepwin.html
}
```
### Copyright and License
Copyright © 2021, UChicago Argonne, LLC

ENPEP- Balance source code is distributed under the terms of [BSD-3 OSS License.](LICENSE.md)
