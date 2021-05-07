set pm3d map

do for [ii=1:3:1] {
  file=sprintf('ergebnis%dA.dat',ii)

  resultName=sprintf('ergebnis%dA.jpg',ii)
  set term jpeg
  set output resultName

  set xrange[0:750]
  set yrange[0:500]

  splot file u ($1):($2):($3)

  if (ii < 3) {
    file=sprintf('ergebnis%dB.dat',ii)

    resultName=sprintf('ergebnis%dB.jpg',ii)
    set term jpeg
    set output resultName

    splot file u ($1):($2):($3) 
  }
}
