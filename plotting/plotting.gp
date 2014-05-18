#!/usr/bin/gnuplot

set nokey
set xrange [0:1]
set yrange [0:1]

plot "polygon.txt" with linespoints pt 7 ps 0.35 lc -1, \
     "positive.txt" with points pt 7 ps 1 lc 2, \
     "negative.txt" with points pt 7 ps 1 lc 1, \
     "ok.txt" with points pt 7 ps 0.35 lc 9

pause -1
