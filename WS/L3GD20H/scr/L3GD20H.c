/*
 ============================================================================
 Name        : L3GD20H.c
 Author      : cgonzalezbrito
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

# include <stdio.h>
# include <stdlib.h>

#include <linux/i2c-dev.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

 int file = 0;

void address(int address){
	char buf[1];
	buf[0]=address;
	if (write(file,buf,1) != 1){
		/* ERROR HANDLING: i2c transaction failed */
		printf("ERROR WRITE PROCCESS");
		exit(1);
	}
}

int get_data (char axis, int max){

	char buf[1];
	int status = 0;
	int i=0; int sum=0; int high=0; int low=0;
	int data=0;

	char output_address = 0x29;

	if (axis==0x02){output_address = 0x2B;}
	if (axis==0x04){output_address = 0x2D;}

	while (i<=max){

		//usleep(1000);

		address(0x27);
		read(file,buf,1);
		status = buf[0];

		if((status&0x08)==0x08){			//New Data
			if ((status&axis)==axis){		//New X data
				address(output_address);
				read(file, buf, 1);
				high = buf[0]<<24;
				address(output_address-1);
				read(file,buf,1);
				low = buf[0]<<16;
				sum=sum+high+low;
				i=i+1;
			}

		}else{ }
	}
	sum=sum>>16;

	printf(".\n");
	data=(0xFFFFFFFF-sum/i)+1;
	return data;
}


int main(void){

	 //Open the device file

	 file = open("/dev/i2c-2", O_RDWR);

	 if (file < 0){
		 /* ERROR HANDLING: you can check errno to see what went wrong*/
		 perror("Failed to open the i2c bus");
		 exit(1);
	 }

	 //Device address

	 int addr=0x6b;

	 if (ioctl(file, I2C_SLAVE, addr) < 0) {
		 /* ERROR HANDLING; you can check errno to see what went wrong */
		 printf("Failed to acquire bus access and/or talk to slave.\n");
	     exit(1);
	 }


	 /*All set up now*/

	 char buf[10];

	 address(0x0F);
	 read(file,buf,1);

	 printf("L3GD20H DEVICE: 0x%X\n",buf[0]);

	 if (buf[0] != 0xD7){ 		/*0x44 = TCS34721 and TCS34725  Datasheet note*/
		 /*NOT MY DEVICE*/
		 printf("DEVICE ERROR");
		 exit(1);
	 } else { printf("Connection OK\n");}

	 /*Configuration Proccess*/

	 buf[0] = 0x20;
	 buf[1] = 0x0F;				/*ODR 100Hz*/

	 if (write(file, buf, 2) != 2) {	/*Point ID Register*/
		 /* ERROR HANDLING: i2c transaction failed */
		 printf("ERROR WRITE PROCCESS");
		 exit(1);
	 }

	 buf[0] = 0x21;
	 buf[1] = 0x20;

	 if (write(file, buf, 2) != 2) {
		 printf("ERROR WRITE PROCCESS");
		 exit(1);
	 }


	 buf[0] = 0x23;
	 buf[1] = 0x30;			/*2000 dsp*/

	 if (write(file, buf, 2) != 2) {
		 printf("ERROR WRITE PROCCESS");
		 exit(1);
	 }

	 buf[0] = 0x39;
	 buf[1] = 0x00;				/*ODR 100Hz*/

	 if (write(file, buf, 2) != 2) {	/*Point ID Register*/
		 /* ERROR HANDLING: i2c transaction failed */
		 printf("ERROR WRITE PROCCESS");
		 exit(1);
	 }

	 /*CALIBRATION Proccess (1)*/

	 //char response = 'n';
	 //int cflag = 0;
	 //printf("Do you want calibrate the device?(S/n):");
	 //scanf("%c",&response);

	 /*ADQ Proccess*/

	 printf("Setting thresholds.\nWait .\n");

	 char Xaxis= 0x01; char Yaxis= 0x02; char Zaxis= 0x04;
	 int xthreshold=get_data(Xaxis,40);
	 int ythreshold=get_data(Yaxis,40);
	 int zthreshold=get_data(Zaxis,40);

	 printf("Threshold X = %f degrees\n",xthreshold* 0.070*0.1);
	 printf("Threshold Y = %f degrees\n",ythreshold* 0.070*0.1);
	 printf("Threshold Z = %f degrees\n",zthreshold* 0.070*0.1);

	 int status=0;
	 int notmovement=0;

	 int xoutput=0; double xdisplacement=0; int xhigh=0; int xlow=0; int xsum=0;
	 int youtput=0; double ydisplacement=0; int yhigh=0; int ylow=0; int ysum=0;
	 int zoutput=0; double zdisplacement=0; int zhigh=0; int zlow=0; int zsum=0;

	 /*CALIBRATION Proccess (2)*/
	 //if ((response == 's')||(response == 'S')){
	 //	 printf("Put the device in 90 in x axis\n");
	 //	 cflag = 1;
	 //}


	 while (1){
		 //usleep(1000);
		 address(0x27);
		 read(file,buf,1);
		 status = buf[0];
		 if((status&0x08)==0x08){			//New Data

			 //xoutput=get_data(Xaxis,1);

			 address(0x29);
			 read(file, buf, 1);
			 xhigh = buf[0]<<24;
			 address(0x28);
			 read(file,buf,1);
			 xlow = buf[0]<<16;
			 xsum=xhigh+xlow;
			 xsum=xsum>>16;
			 xoutput = -1*((0xFFFFFFFF-xsum)+1);

			 //youtput=1;//get_data(Yaxis,1);

			 address(0x2B);
			 read(file, buf, 1);
			 yhigh = buf[0]<<24;
			 address(0x2A);
			 read(file,buf,1);
			 ylow = buf[0]<<16;
			 ysum=yhigh+ylow;
			 ysum=ysum>>16;
			 youtput =-1*((0xFFFFFFFF-ysum)+1);

			 //zoutput=1;//get_data(Zaxis,1);

			 address(0x2D);
			 read(file, buf, 1);
			 zhigh = buf[0]<<24;
			 address(0x2C);
			 read(file,buf,1);
			 zlow = buf[0]<<16;
			 zsum=zhigh+zlow;
			 zsum=zsum>>16;
			 zoutput =-1*((0xFFFFFFFF-zsum)+1);

			 if (((xoutput*0.070*0.01)>=(xthreshold* 0.070*0.03))||((xoutput*0.070*0.01)<=-(xthreshold* 0.070*0.03))||((youtput*0.070*0.01)>=(ythreshold* 0.070*0.03))||((youtput*0.070*0.01)<=-(ythreshold* 0.070*0.03))||((zoutput*0.070*0.01)>=(zthreshold* 0.070*0.03))||((zoutput*0.070*0.01)<=-(zthreshold* 0.070*0.03))){

				 xdisplacement = xdisplacement + 0.01*(xoutput)*0.070;
				 ydisplacement = ydisplacement + 0.01*(youtput)*0.070;
				 zdisplacement = zdisplacement + 0.01*(zoutput)*0.070;
				 notmovement = 0;

				 printf("X: %f			Y: %f			Z: %f\n",xdisplacement,ydisplacement,zdisplacement);


			 } else {
				 notmovement=notmovement+1;
				 if (notmovement>=100){
					 xdisplacement=0; ydisplacement=0; zdisplacement=0;
				 }

			 }
			 //printf ("Data\n");
		 }else{ }// printf("No data\n"); }

	 }

	 return EXIT_SUCCESS;

 }

