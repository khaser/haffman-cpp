#!/usr/bin/bash

TMP=tmp.txt
OUTPUT=output.txt

runWith() {
    ./hw-02_huffman -c -f $1 -o $TMP &> /dev/null && ./hw-02_huffman -u -f $TMP -o $OUTPUT &> /dev/null
    rm -f $TMP 
}

ok=1
for FILE in $(ls samples/*); do
    echo -e "[smoke] Running on $FILE"
    runWith $FILE 
    if ! diff $FILE $OUTPUT &> /dev/null; then
        ok=0
        echo $FILE FAIL
    fi
done

rm -f $OUTPUT

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

if [ $ok -eq 1 ]; then
    echo -e "[smoke] ${GREEN}SMOKE SUCCESS$NC"
else
    echo -e "[smoke] ${RED}SMOKE FAIL$NC"
fi
