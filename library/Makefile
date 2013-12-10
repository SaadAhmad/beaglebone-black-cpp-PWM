all: MotorExample BasicPWMExample ServoExample

MotorExample: MotorExample.o PWM.o
	g++ MotorExample.o PWM.o -o MotorExample

BasicPWMExample: BasicPWMExample.o PWM.o
	g++ BasicPWMExample.o PWM.o -o BasicPWMExample

ServoExample: ServoExample.o PWM.o
	g++ ServoExample.o PWM.o -o ServoExample

MotorExample.o: examples/MotorExample.cpp
	g++ -c examples/MotorExample.cpp

BasicPWMExample.o: examples/BasicPWMExample.cpp
	g++ -c examples/BasicPWMExample.cpp

ServoExample.o: examples/ServoExample.cpp
	g++ -c examples/ServoExample.cpp

PWM.o: PWM.cpp
	g++ -c PWM.cpp

clean:
	rm -rf *o MotorExample BasicPWMExample ServoExample

