#include "xil_types.h"
#include "xstatus.h"
#include "LSM6DS0.h"
#include "HTS221.h"
#include "LIS3MDL.h"
#include "LPS25HB.h"
#include "circular_buffer.h"
#include "i2c.h"

// Mailbox commands
#define READ_LSM6DS0_gyroRawData_XYZ	 0x3
#define READ_LSM6DS0_accelRawData_XYZ	 0x5
#define READ_HTS221_TemData 	 		 0x7
#define READ_HTS221_HumidData 	 		 0x9
#define READ_LIS3MDL_MagRawData_XYZ		 0xB // 11
#define READ_LPS25HB_BaroRawData		 0xD
// Log constants
#define LOG_BASE_ADDRESS (MAILBOX_DATA_PTR(4))
#define LOG_ITEM_SIZE sizeof(float)
#define LOG_CAPACITY  (4000/LOG_ITEM_SIZE)


static s16 gyroRawXYZ[3];
static s16 accelRawXYZ[3];
static s16 *tempera;
static s16 *humid;
static s16 magXYZ[3];
static s32 *barom;

int main(void)
{
   int cmd, status;

   i2c_init();

   status = LSM6DS0_init();
   if(status != XST_SUCCESS){
	   return XST_FAILURE;
   }
   status = HTS221_init();
   if(status != XST_SUCCESS){
	   return XST_FAILURE;
   }
   status = LIS3MDL_init();
   if(status != XST_SUCCESS){
	   return XST_FAILURE;
   }
   status = LPS25HB_init();
   if(status != XST_SUCCESS){
	   return XST_FAILURE;
   }
   while(1){
     // wait and store valid command
      while((MAILBOX_CMD_ADDR & 0x01)==0);
      cmd = MAILBOX_CMD_ADDR;
      switch(cmd){
        case 0xF:
        	MAILBOX_DATA(12) = 0x12;
        	MAILBOX_CMD_ADDR = 0x0;
        	break;
        case READ_LSM6DS0_gyroRawData_XYZ:
        	LSM6DS0_read_gyroRaw(gyroRawXYZ);
            MAILBOX_DATA(0) = gyroRawXYZ[0];
            MAILBOX_DATA(1) = gyroRawXYZ[1];
            MAILBOX_DATA(2) = gyroRawXYZ[2];
            MAILBOX_CMD_ADDR = 0x0;
            break;
        case READ_LSM6DS0_accelRawData_XYZ:
        	LSM6DS0_read_accelRaw(accelRawXYZ);
            MAILBOX_DATA(3) = accelRawXYZ[0];
            MAILBOX_DATA(4) = accelRawXYZ[1];
            MAILBOX_DATA(5) = accelRawXYZ[2];
            MAILBOX_CMD_ADDR = 0x0;
            break;
        case READ_HTS221_TemData:
        	HTS221_read_TemperaData(tempera);
            MAILBOX_DATA(6) = *tempera;
            MAILBOX_CMD_ADDR = 0x0;
            break;
        case READ_HTS221_HumidData:
        	HTS221_read_HumidData(humid);
            MAILBOX_DATA(7) = *humid;
            MAILBOX_CMD_ADDR = 0x0;
            break;
        case READ_LIS3MDL_MagRawData_XYZ:
        	LIS3MDL_Read_MagRawData(magXYZ);
            MAILBOX_DATA(8) = magXYZ[0];
            MAILBOX_DATA(9) = magXYZ[1];
            MAILBOX_DATA(10) = magXYZ[2];
            MAILBOX_CMD_ADDR = 0x0;
            break;
        case READ_LPS25HB_BaroRawData:
        	LPS25HB_ReadBaroRawData(barom);
            MAILBOX_DATA(11) = *barom;
            MAILBOX_CMD_ADDR = 0x0;
            break;

        default:
            MAILBOX_CMD_ADDR = 0x0;
            break;
      }
   }
   return 0;
}
