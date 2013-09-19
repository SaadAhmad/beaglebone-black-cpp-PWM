MotorExample: MotorExample.o PWM.o
	g++ MotorExample.o PWM.o -o MotorExample

BasicPWMExample: BasicPWMExample.o PWM.o
	g++ BasicPWMExample.o PWM.o -o BasicPWMExample

MotorExample.o: examples/MotorExample.cpp
	g++ -c examples/MotorExample.cpp

BasicPWMExample.o: examples/BasicPWMExample.cpp
	g++ -c examples/BasicPWMExample.cpp

PWM.o: PWM.cpp
	g++ -c PWM.cpp

clean:
	rm -rf *o MotorExample BasicPWMExample

