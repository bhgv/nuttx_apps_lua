/****************************************************************************
 * apps/nshlib/nsh_syscmds.c
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
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

#include <sys/boardctl.h>
#include <stdlib.h>
#include <errno.h>

#include "nsh.h"
#include "nsh_console.h"

/****************************************************************************
 * Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: cmd_shutdown
 ****************************************************************************/

#if (defined(CONFIG_BOARDCTL_POWEROFF) || defined(CONFIG_BOARDCTL_RESET)) && \
    !defined(CONFIG_NSH_DISABLE_SHUTDOWN)

int cmd_shutdown(FAR struct nsh_vtbl_s *vtbl, int argc, char **argv)
{
#if defined(CONFIG_BOARDCTL_POWEROFF) && defined(CONFIG_BOARDCTL_RESET)
  /* If both shutdown and reset are supported, then a single option may
   * be provided to select the reset behavior (--reboot).  We know here
   * that argc is either 1 or 2.
   */

  if (argc == 2)
    {
      /* Verify that the single argument is --reboot */

      if (strcmp(argv[1], "--reboot") != 0)
        {
          nsh_output(vtbl, g_fmtarginvalid, argv[0]);
          return ERROR
        }

      /* Invoke the BOARDIOC_RESET board control to reset the board.  If
       * the board_reset() function returns, then it was not possible to
       * reset the board due to some constraints.
       */

      (void)boardctl(BOARDIOC_RESET, EXIT_SUCCESS);
    }
  else
    {
      /* Invoke the BOARDIOC_POWEROFF board control to shutdown the board.
       * If the board_power_off function returns, then it was not possible
       * to power-off the* board due to some constraints.
       */

      (void)boardctl(BOARDIOC_POWEROFF, EXIT_SUCCESS);
    }

#elif defined(CONFIG_BOARDCTL_RESET)
  /* Only reset behavior is supported and we already know that exactly one
   * argument has been provided.
   */

  /* Verify that the single argument is --reboot */

  if (strcmp(argv[1], "--reboot") != 0)
    {
      nsh_output(vtbl, g_fmtarginvalid, argv[0]);
      return ERROR
    }

  /* Invoke the BOARDIOC_RESET board control to reset the board.  If
   * the board_reset() function returns, then it was not possible to
   * reset the board due to some constraints.
   */

  (void)boardctl(BOARDIOC_RESET, EXIT_SUCCESS);

#else
  /* Only the reset behavior is supported and we already know that there is
   * no argument to the command.
   */

  /* Invoke the BOARDIOC_POWEROFF board control to shutdown the board.  If
   * the board_power_off function returns, then it was not possible to power-
   * off the board due to some constraints.
   */

  (void)boardctl(BOARDIOC_POWEROFF, EXIT_SUCCESS);
#endif

  /* boarctl() will not return in any case.  It if does, it means that
   * there was a problem with the shutdown/resaet operaion.
   */

  nsh_output(vtbl, g_fmtcmdfailed, argv[0], "boardctl", NSH_ERRNO);
  return ERROR;
}
#endif /* CONFIG_BOARDCTL_POWEROFF && !CONFIG_NSH_DISABLE_SHUTDOWN */

/****************************************************************************
 * Name: cmd_poweroff
 ****************************************************************************/

#if defined(CONFIG_BOARDCTL_POWEROFF) && !defined(CONFIG_NSH_DISABLE_POWEROFF)
int cmd_poweroff(FAR struct nsh_vtbl_s *vtbl, int argc, char **argv)
{
  /* Invoke the BOARDIOC_POWEROFF board control to shutdown the board.  If
   * the board_power_off function returns, then it was not possible to power-
   * off the board due to some constraints.
   */

  (void)boardctl(BOARDIOC_POWEROFF, EXIT_SUCCESS);

  /* boarctl() will not return in any case.  It if does, it means that
   * there was a problem with the shutdown operaion.
   */

  nsh_output(vtbl, g_fmtcmdfailed, argv[0], "boardctl", NSH_ERRNO);
  return ERROR;
}
#endif

/****************************************************************************
 * Name: cmd_reboot
 ****************************************************************************/

#if defined(CONFIG_BOARDCTL_RESET) && !defined(CONFIG_NSH_DISABLE_REBOOT)
int cmd_reboot(FAR struct nsh_vtbl_s *vtbl, int argc, char **argv)
{
  /* Invoke the BOARDIOC_RESET board control to reset the board.  If
   * the board_reset() function returns, then it was not possible to
   * reset the board due to some constraints.
   */

  (void)boardctl(BOARDIOC_RESET, EXIT_SUCCESS);

  /* boarctl() will not return in this case.  It if does, it means that
   * there was a problem with the reset operaion.
   */

  nsh_output(vtbl, g_fmtcmdfailed, argv[0], "boardctl", NSH_ERRNO);
  return ERROR;
}
#endif