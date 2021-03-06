# s-monitor
a simple command-line based server monitoring tool written in C. s-monitor makes it easy to see the status and usage of your server through an web interface. Its written for and tested on Linux based systems, mainly on amd64 and arm systems.

## Quick start
```bash
$ make
$ ./s-monitor
```
This will then show some basic data on the terminal, full data can be then seen through the webpage of the server: 
`http://servers-hostname/s-monitor`

## How it works
The program parses the data from /proc/cpuinfo and then turns that into a webpage hosted on the local machine. The data for the webpage is stored in a file via symlink at `/var/www/html`. If you don't have this folder see the dependencies section.

## Dependencies 

#### ncurses (compilation only)
to install ncurses on Debian based systems:
```bash
$ sudo apt install libncurses5* libncursesw5-dev
```
*I dont know the package name on Arch based systems but yall use Arch so you can probably figure it out*
#### Apache2
**(Debian)** If you don't have the `/var/www/html/` folder you will need to install apache2, To install just type:
```bash
$ sudo apt install apache2
```
**(Arch)** to install apache2 on arch systems, type:
```bash
$ sudo pacman -S apache
```
By default, apache will set the document root to `/srv/http` and so it will not work with this program. So you you will either have to change the document root or change the install sh file to symlink it to there instead.
