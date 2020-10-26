#! /usr/bin/gnuplot -persist
set terminal png enhanced
set output "plot.png"
set size ratio 0.5
set xlabel "Время обработки, с" 
set ylabel "Повышение сорбции красителя, %" 
set xtics ("0" 0, "15" 15, "30" 30, "60" 60, "120" 120, "180" 180)
set autoscale y
set grid
set key autotitle columnhead
 
plot "data.csv" using 1:2 smooth csplines notitle with lines lt 1,\
"data.csv" using 1:2 with points pointsize 1 pointtype 7 lt 1,\
"data.csv" using 1:3 smooth csplines notitle with lines lt 2,\
"data.csv" using 1:3 with points pointsize 1 pointtype 13 lt 2
