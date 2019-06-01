/***** ms2dna.c *************************************************************
 * Description: Convert haplotypes from Hudons's ms program to DNA sequences.
 * Reference: Hudson, R. R. (2002). Generating samples under a Wright-Fisher 
 *   neutral model of genetic variation. Bioinformatics 18: 337-338.
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Jun  1 08:59:10 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "sample.h"
#include "ran.h"
#include "interface.h"
#include "eprintf.h"


int scanFile(FILE *fpin, Args *args){
  Sample *sample;
  FILE *fpout = stdout;

  sample = initializeSample(fpin, args);
  while ((sample = getSample()) != NULL)
    outputSample(fpout);
  freeSample();
  return 0;
}

int main(int argc, char *argv[]){
  FILE *fp;
  Args *args = getArgs(argc, argv);
  int seed;
  setprogname2(argv[0]);
  /* Deal with user interface */
  if(args->v)
    printSplash(args);
  if(args->h || args->err)
    printUsage();
  /* Seed random number generator */
  if (args->s != 0)
    seed = args->s;
  else
    seed = (unsigned int)((unsigned) time(NULL) + getpid());
  init_genrand(seed);
  /* Deal with input files */
  if(args->nf == 0) {
    fp = stdin;
    scanFile(fp, args);
  } else {
    for(int i = 0; i < args->nf; i++) {
      fp = efopen(args->fi[i], "r");
      scanFile(fp, args);
      fclose(fp);
    }
  }
  freeArgs(args);
  return 0;
}

