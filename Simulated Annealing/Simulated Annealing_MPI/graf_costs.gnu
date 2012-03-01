set title "Solution cost obtained"

set autoscale     # scale axes automatically
set xlabel "N"
set ylabel "Final cost"

set xtic auto       # set xtics automatically
set ytic auto       # set ytics automatically

set terminal png
set output "graf_costs.png"

plot "res1.txt" using 1:2 with imp lw 2 title "1 processor", \
	"res6.txt" using 1:2 with imp lw 3 title "6 processor", \
	"res12.txt" using 1:2 with imp lw 4 title "12 processor", \
	"res24.txt" using 1:2 with imp lw 5 title "24 processor"




