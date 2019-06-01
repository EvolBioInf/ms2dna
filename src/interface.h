/***** interface.h **********************************************************
 * Description: Convert ms output to DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Jun  1 08:59:10 2019
 ****************************************************************************/
#ifndef INTERFACE
#define INTERFACE

#define DEFAULT_G 0.5

/* define argument container */
typedef struct args{
  char    h; /* help message?         */
  char    v; /* version message?      */
  char  err; /* error                 */
  int     s; /* random number seed    */
  float   g; /* GC content            */
  char **fi; /* input files           */
  int    nf; /* number of input files */
} Args;

Args *getArgs(int argc, char *argv[]);
Args *newArgs();
void freeArgs(Args *args);
void printUsage();
void printSplash(Args *args);

#endif
