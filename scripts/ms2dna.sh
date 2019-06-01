./ms2dna -s 13 ../data/test.ms > tmp.out
DIFF=$(diff tmp.out ../data/test.fasta)
if [ "$DIFF" == "" ] 
then
    printf "Test(ms2dna)\tpass\n"
else
    printf "Test(ms2dna)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
