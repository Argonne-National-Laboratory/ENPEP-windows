**Status:** This is a legacy software and no further enhancements or modifications will be made.

# ENPEP for Windows

The ENPEP for Windows model has its origins in the DOS version of the Energy and Power Evaluation Program (ENPEP), which was developed by Argonne National Laboratory (ANL) under the auspices of the U.S. Department of Energy (DOE) and the International Atomic Energy Agency (IAEA). However, ENPEP for Windows model is significantly modified and rather different in structure and capabilities from the older DOS version of ENPEP. It fully utilizes the Windows operating environment and provides the user with a graphical interface for designing a comprehensive model of the energy system of a country or region.


## Links
* Source code repository: https://github.com/Argonne-National-Laboratory/ENPEP-windows
* User guide: [PDF](docs/ENPEP-BALANCE_Manual_20070914.pdf)

## Installation
The Bal.exe in bin folder is a executable file that is the back end for ENPEP Windows program. Lunching the file will run the installation and model. 


### Note:
* The necessary input files are created by the user interface of ENPEP Windows.  

## Quick start
Following example use cases are provided:
1. Bal.exe log_file.txt (make sure that the files in the test Data folder are in the current directory 
```
windows console> cd <projectroot>/bin
windows console> Bal.exe log_file.txt
```

## Package details
Technical information of the software can be found here:
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
