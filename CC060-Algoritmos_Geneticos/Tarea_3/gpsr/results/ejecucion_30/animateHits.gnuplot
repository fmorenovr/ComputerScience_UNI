do for [i=1:9] {
  plot 'res0'.i.'' using 1:4 title 'res0'.i.'' w p lt 4
}

plot 'res10' using 1:4 title 'res10' w p lt 4

do for [i=1:9] {
  plot 'res1'.i.'' using 1:4 title 'res1'.i.'' w p lt 4
}

plot 'res20' using 1:4 title 'res20' w p lt 4

do for [i=1:9] {
  plot 'res2'.i.'' using 1:4 title 'res2'.i.'' w p lt 4
}

plot 'res30' using 1:4 title 'res30' w p lt 4
