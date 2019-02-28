set size square
set xrange [ -30000 : 30000 ]
set yrange [ -30000 : 30000 ]
set xlabel "x" 
set ylabel "y"
set title "cnbody"
plot "out.txt" using 1:2 with lines
