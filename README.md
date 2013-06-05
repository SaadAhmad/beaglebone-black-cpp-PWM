Introduction
========================
I found that while trying to get PWM control for my motors/servos on the BBB 
many of the old tutorials were no longer working. Using what I found at 
http://www.phys-x.org/rbots/index.php?option=com_content&view=article&id=106:lesson-3-beaglebone-black-pwm&catid=46:beaglebone-black&Itemid=81 
and https://groups.google.com/d/msg/beagleboard/wjbOVE6ItNg/Dym4H4HuI8gJ
I modified the driver and firmware and implemented a library on top of it.

Features
========================
* Allows changing the period of EHRPWM modules at run time
* Allows for servo and motor esc control
* * Basic examples to show LED brightness fading

Installation
========================

NOTE: My kernel building knowledge is limited and these are the stops I followed to make it work. 
      If someone has better/more correct steps please submit them!

Firmware and update driver

Compiling the driver and module (Optional)
-------------------------------
1) Follow the instructions at http://beagleboard.org/linux or http://wiki.beyondlogic.org/index.php/BeagleBoneBlack_Building_Kernel 
   to setup your kernel build files. 
   
2) Copy/paste pwm_test.c into <source_dir>/kernel/drivers/pwm
````sh
cp <repo_dir>/driver/pwm_test.c <source_dir>/kernel/drivers/pwm/
````

3) For the firmware files, copy them over to <source_dir>/kernel/firmware/capes/
````sh
cp <repo_dir>/firmware/*dts <source_dir>/kernel/firmware/capes/
````

4) Open up <source_dir>/kernel/firmware/Makefile and after the  bone_pwm_P9_42-00A0.dtbo \ (line 179) add in the following
````sh
	sc_pwm_P8_13-00A0.dtbo \
	sc_pwm_P8_19-00A0.dtbo \
	sc_pwm_P8_34-00A0.dtbo \
	sc_pwm_P8_36-00A0.dtbo \
	sc_pwm_P8_45-00A0.dtbo \
	sc_pwm_P8_46-00A0.dtbo \
	sc_pwm_P9_14-00A0.dtbo \
	sc_pwm_P9_16-00A0.dtbo \
	sc_pwm_P9_21-00A0.dtbo \
	sc_pwm_P9_22-00A0.dtbo \
	sc_pwm_P9_28-00A0.dtbo \
	sc_pwm_P9_29-00A0.dtbo \
	sc_pwm_P9_31-00A0.dtbo \
	sc_pwm_P9_42-00A0.dtbo \
````

5) Once you have those changes, compile the kernel again so it builds the updated firmware/driver

Using the compiled files
------------------------
Note you can use the compiled kernel driver file however I'm not sure how easily it will work with different kernel versions. 
At the time I compiled it for v3.8.13 and it seems to work for that. If the provided file doesn't work then you might want to try rebuilding it.

1) First make sure that your beaglebone isn't running any any of the overlays from the current bone_pwm and that the pwm_test module isnt loaded
   A reboot should fix this however if you dont want to reboot you can do the following steps to unload the driver 
````sh
cat /sys/devices/bone_capemgr.<WHATEVER YOUR NUMBER IS HERE>/slots
# Find the slot for any pwm modules
echo -<Slot # for the PWM modules> >  /sys/devices/bone_capemgr.<WHATEVER YOUR NUMBER IS HERE>/slots
# Repeat for all modules

#Once done
modprobe -r pwm_test.ko
````

2) Backup the old pwm_test.ko file
````sh
cd /lib/modules/<kernel version>/kernel/drivers/pwm/
cp pwm_test.ko pwm_test.ko.orig   
````
     
3) Find the built pwm_test.ko file and copy it over to /lib/modules/<kernel version>/kernel/drivers/pwm/
 
4) Copy over the build dtbo files to /lib/firmware

5) Youre done setting up the files! Do a reboot and you should be set

Userspace Usage
------------------------
1) Load in the am33xx_pwm module and load in which even PWM pins (the names of the dtb files you copied over) you want loaded.

````sh
echo am33xx_pwm >  /sys/devices/bone_capemgr.<WHATEVER YOUR NUMBER IS HERE>/slots
#Example pin firmware would be sc_pwm_P8_13
echo sc_pwm_P<use whatever pins you want>  /sys/devices/bone_capemgr.<WHATEVER YOUR NUMBER IS HERE>/slots
````

2) Locate the driver interface. It is in /sys/devices/ocp.<number>/pwm_test_<Whatever pin name you chose>

3) Set the periods to to whatever value you want (Make sure that the period on both channels of each EHRPWM is same) by doing
````sh
echo <Period Value> > /sys/devices/ocp.<number>/pwm_test_<Whatever pin name you chose>/period

4) Set the duty to to whatever value you want (Make sure that the period on both channels of each EHRPWM is same) by doing
````sh
echo <Duty Value> > /sys/devices/ocp.<number>/pwm_test_<Whatever pin name you chose>/duty
````

5) Once configured, enable the pwm by doing
````sh
echo 1 > /sys/devices/ocp.<number>/pwm_test_<Whatever pin name you chose>/run
````

6) If you want to reset the period for an EHRPWM where both channels are active, you need to unload the entire PWM module and restart from step 1. (You can skip loading in am33xx_pwm).
This is similar to what you did in the Using compiled files in step 1.  

Library Usage
------------------------
The libary provided wraps most of these functions so that they can be be used in your C++ application. Note this isn't compatible with C
however it would be great if people were willing to help out and make it happen! 

I have provided a BasicPWMExample.cpp which shows 
you how to get an LED to fade in and out (NOTE dont actually connect the LED directly to your PWM output otherwise you may damage it). 
It also inlcudes a MotorExample.cpp which shows you how to use a motor esc (Note there isnt servo example code but it is the same class as MotorControl so it should be the same). 
Just change your angle range and youre good to go!

Just copy over the CPP/Header files into your application and you are good to go!

I have described a bit about the problem I found with the PWM and how the fix works at http://saadahmad.ca/using-pwm-on-the-beaglebone-black/


Enjoy
------------------------
On a smaller note, if anyone knows how to make and submit this as a patch into the BBB kernel I would greatly appreciate some help!  



 
