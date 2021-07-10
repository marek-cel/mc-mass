# MC-Mass

Aircraft mass characteristics (empty mass, center of mass and inertia tensor) estimation tool, which uses formulas from [Raymer D.P. Aircraft Design: A Conceptual Approach](http://doi.org/10.2514/4.104909) and [NASA TP-2015-218751](https://ntrs.nasa.gov/citations/20150021267).

## Installation

### Linux

Linux [dpkg package](https://github.com/marek-cel/mc-mass/releases/download/0.2/mc-mass_0.2_focal_amd64.deb) is provided for Ubuntu 20.04 LTS / LinuxMint 20.x.

### Windows

Windows [zip package](https://github.com/marek-cel/mc-mass/releases/download/0.2/mc-mass_0.2_win64.zip) is provided. It does not require installation.

## Building from source

### Dependencies

MC-Mass requires Qt.

* [Qt5](https://www.qt.io/)

#### Linux

On Ubuntu based Linux distributions those dependencies can be installed with the following command:

```apt install libqt5svg5-dev qtbase5-dev```

#### Windows

On Windows those dependencies have to be installed manually.

### Building using qmake

MC-Mass can be built with ```qmake``` tool. Run qmake on ```mc-mass.pro``` file and then use appropriate building system. You can also use Qt Creator.

![Screenshot](mc-mass_01.jpg)
