/*
 ============================================================================
 Name        : TCS34725.c
 Author      : cgonzalezbrito
 Version     :
 Copyright   :
 Description : Hello World in C, Ansi-style
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
 	buf[0]=0xA0|address;
 	if (write(file,buf,1) != 1){
 		/* ERROR HANDLING: i2c transaction failed */
 		printf("ERROR WRITE PROCCESS");
 		exit(1);
 	}
 }

 int brightness(int add){
	 char buf[2];
	 int bright=0;
	 int i=0;
	 for(i=0;i<=10;i++){
		 usleep(358000);	//loop 1s
		 address(add);
		 read(file,buf,2);
		 bright = bright + buf[0] + (buf[1]<<8);
	 }
	 return bright/i;
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

	 int addr=0x29;

	 if (ioctl(file, I2C_SLAVE, addr) < 0) {
		 /* ERROR HANDLING; you can check errno to see what went wrong */
		 printf("Failed to acquire bus access and/or talk to slave.\n");
	     exit(1);
	 }


	 /*All set up now*/

	 char buf[10];
	 char buf1[2];

	 //Check connection

	 address(0x12);
	 read(file,buf,1);

	 if (buf[0] != 0x44){ 		/*0x44 = TCS34721 and TCS34725  Datasheet note*/
		 /*NOT MY DEVICE*/
		 printf("DEVICE ERROR");
		 exit(1);
	 } else { printf("Connection OK\n");}


	 /*Configuration:*/

	 //ENABLE Register
	 buf1[0] = 0x80; // Command Register, point to 0x00 register (Enable register)
	 buf1[1] = 0x0B; // 0b00001011 ; Wait Enable, Channels ADC (RGB), ON
	 if (write(file, buf1, 2) != 2) { printf("ERROR WRITE PROCCESS 0"); exit(1); }

	 //RGBC TIMING Register
	 buf1[0] = 0x80 | 0x01; // Command Register, point to 0x01
	 buf1[1] = 0xC0; 		// 154ms
	 if (write(file, buf1, 2) != 2) { printf("ERROR WRITE PROCCESS 0"); exit(1); }

	 //WAIT TIME Register
	 buf1[0] = 0x80 | 0x03; // Command Register, point to 0x03
	 buf1[1] = 0xAB; 		// 204 ms
	 if (write(file, buf1, 2) != 2) { printf("ERROR WRITE PROCCESS 0"); exit(1); }

	 //CONFIGURATION Register
	 buf1[0] = 0x80 | 0x0D; // Command Register, point to 0x0D
	 buf1[1] = 0x00; 		// WLONG = 0 -- 204ms
	 if (write(file, buf1, 2) != 2) { printf("ERROR WRITE PROCCESS 0"); exit(1); }

	 //CONTROL Register
	 buf1[0] = 0x80 | 0x0F; // Command Register, point to 0x0F
	 buf1[1] = 0x01; 		// Gain = 4x
	 if (write(file, buf1, 2) != 2) { printf("ERROR WRITE PROCCESS 0"); exit(1); }

	 printf("Wait .\n");
	 int CiE = brightness(0x14); printf(".\n");
	 int RiE = brightness(0x16); printf(".\n");
	 int GiE = brightness(0x18); printf(".\n");
	 int BiE = brightness(0x1A);

	 printf("Enviroment Values:\nClear Data: 0x%X\nRed Data: 0x%X\nGreen Data: 0x%X\nBlue Data: 0x%X\n",CiE,RiE,GiE,BiE);

	 int C; int R; int G; int B;

	 while (1){

		 usleep(358000);
		 address(0x14); // Command Register: Auto-increment protocol transaction; Point results registers
		 read(file,buf,8);

		 C=buf[0]+ (buf[1]<<8); R=buf[2]+ (buf[3]<<8); G=buf[4]+ (buf[5]<<8); B=buf[6]+ (buf[7]<<8);

		 if ((C >= (CiE*1.02))||(R >= (RiE*1.02))||(G >= (GiE*1.02))||(B >= (BiE*1.02)) ){
			 if ((R >= G)&&(R >= B)){
				 printf("RED\n");
			 }
			 if ((G>=B)&&(G>=R)){
				 printf("GREEN\n");
			 }
			 if ((B>=R)&&(B>=G)){
				 printf("BLUE\n");
			 }
			 printf("C: %X	R: %X	G: %X	B: %X\n",C-CiE,R-RiE,G-GiE,B-BiE);
		 }

	 }
	 return EXIT_SUCCESS;


 }

