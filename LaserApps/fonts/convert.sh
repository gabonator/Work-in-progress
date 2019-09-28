echo fonts=\{\} > fonts.js

for f in *.CHR
do
  filename="${f%.*}"
  node convert $f >> fonts.js
done

echo module.exports = fonts\; >> fonts.js
