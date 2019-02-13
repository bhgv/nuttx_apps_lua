/****************************************************************************
 * examples/rfid_readuid/rfid_readuid.c
 *
 *   Copyright (C) 2016 Gregory Nutt. All rights reserved.
 *   Author: Alan Carvalho de Assis <acassis@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <nuttx/contactless/mfrc522.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef CONFIG_CL_MFRC522
#  error "CONFIG_CL_MFRC522 is not defined in the configuration"
#endif

#ifndef CONFIG_EXAMPLES_RFID_READUID_DEVNAME
#  define CONFIG_EXAMPLES_RFID_READUID_DEVNAME "/dev/rfid0"
#endif


/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * rfid_readuid_main
 ****************************************************************************/

#ifdef BUILD_MODULE
int main(int argc, FAR char *argv[])
#else
int rfid_readuid_main(int argc, char *argv[])
#endif
{
  int fd;
  int ret;
  int count = 0;
  
  int buf_len = 2+ 10*2 +1;
  char* buffer = malloc(buf_len);

  char* cmd_rd_uid = "Ruid:";
  char* cmd_rd_dmp = "Rdump:";

  if(buffer == NULL)
    return -ENOMEM;

  fd = open(CONFIG_EXAMPLES_RFID_READUID_DEVNAME, O_RDWR);
  if (fd < 0)
    {
      printf("Failed to open %s\n", CONFIG_EXAMPLES_RFID_READUID_DEVNAME);
      return -1;
    }

  /* Try to read a card up to 3 times */

  while (count < 10)
    {
      printf("Trying to READ: ");

      /* 11 bytes = 0x12345678\0 */

      if(!write(fd, cmd_rd_uid, strlen(cmd_rd_uid))){
        free(buffer);
        close(fd);
        return -EIO;
        }

      ret = read(fd, buffer, buf_len);
      if (ret == buf_len)
        {
          printf("RFID CARD UID = %s\n", buffer);
          free(buffer);
#if 0
          buffer = malloc(1024);
          if(buffer == NULL)
            return -ENOMEM;
          buf_len = 1024;
          if(!write(fd, cmd_rd_dmp, strlen(cmd_rd_dmp))){
            free(buffer);
            close(fd);
            return -EIO;
            }
          
          ret = read(fd, buffer, buf_len);
          if (ret == buf_len){
            int i, j;
            printf("RFID CARD DUMP:\n");
            for(i = 0; i < 64; i++){
              printf("\nblock %d:\n", i);
              for(j = 0; j < 16; j++){
                printf("%2X ", buffer[i*64 + j]);
                }
              }
            }
          free(buffer);
#endif
          close(fd);
          return OK;
        }
//        else{
//          free(buffer);
//          close(fd);
//          return -EIO;
//        }

      if (ret == -EAGAIN || ret == -EPERM)
        {
          printf("Card is not present!\n");
        }
      else
        {
          printf("Unknown error!\n");
        }

      /* Wait 500ms before trying again */

      usleep(1000000);
      count++;
    }

  free(buffer);
  close(fd);
  return 0;
}

