./ms2dna > tmp.out
DIFF=$(diff tmp.out ../data/ms2dna.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(ms2dna)\tpass\n"
else
    printf "Test(ms2dna)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
