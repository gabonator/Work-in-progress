echo archive=\{\} > archive.js

for f in *.txt
do
  filename="${f%.*}"
  contents=$(<$filename.txt)

  echo archive\[\"$filename\"\] = \"$contents\"\; >> archive.js
done