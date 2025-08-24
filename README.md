# MC-Mass

Aircraft mass characteristics (empty mass, center of mass and inertia tensor) estimation tool, which uses formulas from [Raymer D.P. Aircraft Design: A Conceptual Approach](http://doi.org/10.2514/4.104909) and [NASA TP-2015-218751](https://ntrs.nasa.gov/citations/20150021267).

## Documentation

Documentation is available [here](https://github.com/marek-cel/mc-mass/docs/mc-mass.pdf).

## Installation

### Linux

Linux [dpkg package](https://github.com/marek-cel/mc-mass/releases/download/1.0/mc-mass_1.0_noble_amd64.deb) is provided for Ubuntu 20.04 LTS / LinuxMint 20.x.

### Windows

Windows [zip package](https://github.com/marek-cel/mc-mass/releases/download/1.0/mc-mass_1.0_win64.zip) is provided. It does not require installation.

## Building from source

### Dependencies

MC-Mass requires Qt and libxml2.

* [Qt5](https://www.qt.io/)
* [libmcutil](https://gitlab.gnome.org/GNOME/libxml2)

#### Linux

On Ubuntu based Linux distributions Qt can be installed with the following command:

```apt install qtbase5-dev libqt5opengl5-dev libxml2-dev```

#### Windows

On Windows those dependencies can be installed using vcpkg.


