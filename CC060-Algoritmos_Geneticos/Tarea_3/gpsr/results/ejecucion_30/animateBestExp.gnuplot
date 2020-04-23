do for [i=1:9] {
  plot 'res0'.i.'' using 2:3 with lines title 'res0'.i.''
}

plot 'res10' using 2:3 with lines title 'res10'

do for [i=1:9] {
  plot 'res1'.i.'' using 2:3 with lines title 'res1'.i.''
}

plot 'res20' using 2:3 with lines title 'res20'

do for [i=1:9] {
  plot 'res2'.i.'' using 2:3 with lines title 'res2'.i.''
}

plot 'res30' using 2:3 with lines title 'res30'
