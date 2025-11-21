/**
 ******************************************************************************
 * @file      syscalls.c
 * @brief     STM32CubeIDE Minimal System calls file + ITM/SWO printf support
 ******************************************************************************
 */

/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdint.h>

/* -------------------------------------------------------------------------
 *                      ITM / SWO SUPPORT (STIM0, TPIU, DBGMCU)
 * ------------------------------------------------------------------------- */

static void ITM_Init(void)
{
    // Enable TRACE pins (PB3 = SWO)
    *(volatile uint32_t*)0xE0042004 |= (1 << 5);     // DBGMCU_CR |= TRACE_IOEN

    // Enable TRCENA (Trace enable)
    *(volatile uint32_t*)0xE000EDFC |= 0x01000000;   // DEMCR |= TRCENA

    // Unlock ITM registers
    *(volatile uint32_t*)0xE0000FB0 = 0xC5ACCE55;    // ITM_LAR

    // Configure ITM: enable ITM + SWO + timestamps
    *(volatile uint32_t*)0xE0000E80 = 0x0001000F;    // ITM_TCR

    // Enable stimulus Port 0
    *(volatile uint32_t*)0xE0000E00 = 0x00000001;    // ITM_TER

    // TPIU prescaler: HCLK=84MHz, SWO=2MHz → (84/2)-1 = 41
    *(volatile uint32_t*)0xE0040010 = 41;            // TPI_ACPR

    // NRZ / async SWO
    *(volatile uint32_t*)0xE00400F0 = 2;             // TPI_SPPR

    // Formatter flush control
    *(volatile uint32_t*)0xE0040304 = 0x100;         // TPI_FFCR
}

static void ITM_SendChar(uint8_t ch)
{
    volatile uint32_t *stim = (uint32_t *)0xE0000000; // ITM_STIM0

    // ITM enabled?
    if ((*(uint32_t*)0xE0000E80 & 1) == 0) return;

    // Port 0 enabled?
    if ((*(uint32_t*)0xE0000E00 & 1) == 0) return;

    while (*stim == 0);                 // Wait until ready
    *((volatile uint8_t*)0xE0000000) = ch;
}


/* -------------------------------------------------------------------------
 *                  Weak low-level functions used by newlib
 * ------------------------------------------------------------------------- */

extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

char *__env[1] = { 0 };
char **environ = __env;

void initialise_monitor_handles(void) { }

int _getpid(void) { return 1; }

int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

void _exit (int status)
{
    _kill(status, -1);
    while (1) {}
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
    (void)file;
    for (int i = 0; i < len; i++)
        *ptr++ = __io_getchar();
    return len;
}

/* -------------------------------------------------------------------------
 *                   *** THIS IS THE IMPORTANT PART ***
 *                     printf() → ITM/SWO redirection
 * ------------------------------------------------------------------------- */

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    (void)file;

    static uint8_t itm_initialized = 0;

    if (!itm_initialized)
    {
        ITM_Init();              // Initialize ITM only once
        itm_initialized = 1;
    }

    for (int i = 0; i < len; i++)
        ITM_SendChar(ptr[i]);

    return len;
}

/* -------------------------------------------------------------------------
 *              Remaining syscalls (unchanged defaults)
 * ------------------------------------------------------------------------- */

int _close(int file)
{
    (void)file;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    (void)file;
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _open(char *path, int flags, ...)
{
    (void)path;
    (void)flags;
    return -1;
}

int _wait(int *status)
{
    (void)status;
    errno = ECHILD;
    return -1;
}

int _unlink(char *name)
{
    (void)name;
    errno = ENOENT;
    return -1;
}

int _times(struct tms *buf)
{
    (void)buf;
    return -1;
}

int _stat(char *file, struct stat *st)
{
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _link(char *old, char *new)
{
    (void)old;
    (void)new;
    errno = EMLINK;
    return -1;
}

int _fork(void)
{
    errno = EAGAIN;
    return -1;
}

int _execve(char *name, char **argv, char **env)
{
    (void)name;
    (void)argv;
    (void)env;
    errno = ENOMEM;
    return -1;
}

