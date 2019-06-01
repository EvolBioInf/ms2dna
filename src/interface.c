/***** interface.c **********************************************************
 * Description: Convert ms output to DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Jun  1 08:59:10 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"
#include "eprintf.h"

Args *newArgs() {
  Args *args = (Args *)emalloc(sizeof(Args));
  args->h   = 0;
  args->v   = 0;
  args->s   = 0;
  args->g   = DEFAULT_G;
  args->err = 0;
  return args;
}

void freeArgs(Args *args) {
  free(args);
}

Args *getArgs(int argc, char *argv[]) {
  int c;
  char *optString = "hvs:g:";
  Args *args = newArgs();

  while ((c = getopt(argc, argv, optString)) != -1) {
    switch(c) {
    case 's': /* random number seed */
      args->s = atoi(optarg);
      break;
    case 'g':
      args->g = atof(optarg);
      break;
    case 'h': /* help       */
      args->h = 1;
      break;
    case 'v': /* version    */
      args->v = 1;
      break;
    case '?':
      args->err = 1;
      if(optopt == 'i')
	fprintf(stderr, "Error: Option `%c` requires an argument.\n", optopt);
      else if(isprint(optopt))
	fprintf(stderr, "Error: Unknown option `%c`.\n", optopt);
      else
	fprintf(stderr, "Error: Unknown option character `\\x%x`.\n", optopt);
    default:
      args->err = 1;
      return args;
    }
  }
  args->fi = argv + optind;
  args->nf = argc - optind;

  return args;
}

void printUsage() {
  printf("Usage: %s [options] [inputFiles]\n", progname());
  printf("<DESCRIPTION>\n");
  printf("Example: %s -i 2\n", progname());
  printf("Options:\n");
  printf("\t[-g <NUM> GC content; default: %.2f]\n", DEFAULT_G);
  printf("\t[-s <NUM> seed for random number generator; default: system]\n");
  printf("\t[-h print this help message and exit]\n");
  printf("\t[-v print version & program information and exit]\n");
  exit(0);
}

void printSplash(Args *args) {
  printf("%s ", progname());
  int l = strlen(VERSION);
  for(int i = 0; i < l - 1; i++)
    printf("%c", VERSION[i]);
  printf(", %s\n", DATE);
  printf("Author: Bernhard Haubold & Peter Pfaffelhuber\n");
  printf("License: GNU General Public License, https://www.gnu.org/licenses/gpl.html\n");
  printf("Bugs: haubold@evolbio.mpg.de\n");
  exit(0);
}
