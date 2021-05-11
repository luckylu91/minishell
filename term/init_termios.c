#include "terminal.h"

/* Restore terminal to original settings
*/
void	terminal_done(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &term.terminal_original);
}

/* "Default" signal handler: restore terminal, then exit.
*/
void	terminal_signal(int signum)
{
	if (STDOUT_FILENO != -1)
		tcsetattr(STDOUT_FILENO, TCSANOW, &term.terminal_original);
	printf("exiting...\n");
	exit(0);
}

/* Initialize terminal for non-canonical, non-echo mode,
 * that should be compatible with standard C I/O.
 * Returns 0 if success, nonzero errno otherwise.
*/
int	init_termios(void)
{
	struct sigaction act;

	/* Obtain terminal settings. */
	if (tcgetattr(STDOUT_FILENO, &term.terminal_original) ||
		tcgetattr(STDOUT_FILENO, &term.terminal_settings))
	{
		errno = ENOTSUP;
		return (-1);
	}
	// if (atexit(terminal_done))
	// {
	// 	errno = ENOTSUP;
	// 	return (-1);
	// }

	// /* Let BREAK cause a SIGINT in input. */
	// term.terminal_settings.c_iflag &= ~IGNBRK;
	// term.terminal_settings.c_iflag |=  BRKINT;

	// /* Ignore framing and parity errors in input. */
	// term.terminal_settings.c_iflag |=  IGNPAR;
	// term.terminal_settings.c_iflag &= ~PARMRK;

	/* Do not strip eighth bit on input. */
	term.terminal_settings.c_iflag &= ~ISTRIP;

	/* Do not do newline translation on input. */
	// terminal_settings.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	term.terminal_settings.c_iflag &= ~(INLCR | IGNCR);

	/* Use 8-bit characters. This too may affect standard streams,
	 * but any sane C library can deal with 8-bit characters. */
	term.terminal_settings.c_cflag &= ~CSIZE;
	term.terminal_settings.c_cflag |=  CS8;

	/* Enable receiver. */
	term.terminal_settings.c_cflag |=  CREAD;

	/* Let INTR/QUIT/SUSP/DSUSP generate the corresponding signals. */
	term.terminal_settings.c_lflag |=  ISIG;

	/* Enable noncanonical mode.
	 * This is the most important bit, as it disables line buffering etc. */
	term.terminal_settings.c_lflag &= ~ICANON;

	/* Disable echoing input characters. */
	term.terminal_settings.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);

	/* Disable implementation-defined input processing. */
	term.terminal_settings.c_lflag &= ~IEXTEN;

	/* To maintain best compatibility with normal behaviour of terminals,
	 * we set TIME=0 and MAX=1 in noncanonical mode. This means that
	 * read() will block until at least one byte is available. */
	term.terminal_settings.c_cc[VTIME] = 0;
	term.terminal_settings.c_cc[VMIN] = 1;

	/* Set the new terminal settings.
	 * Note that we don't actually check which ones were successfully
	 * set and which not, because there isn't much we can do about it. */
	tcsetattr(STDOUT_FILENO, TCSANOW, &term.terminal_settings);

	/* Done. */
	return (0);
}
