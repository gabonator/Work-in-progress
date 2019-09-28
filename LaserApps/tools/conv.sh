echo archive=\{\} > archive.js

for f in *.jpg
do
  filename="${f%.*}"
  echo $filename
  convert $filename.jpg $filename.bmp
  potrace -u 0.1 --invert --longcurve $filename.bmp -s
  node ../tools/simplify $filename.svg $filename.txt
  contents=$(<$filename.txt)
  echo archive\[\"$filename\"\] = $contents\; >> archive.js
  rm $filename.svg
  rm $filename.bmp
  rm $filename.txt
done
