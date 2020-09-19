module.exports = {import:convert};

function convert(json)
{
  if (!json || !json.formImage || !json.formImage.Pages) 
  {
    return false;
  }
  var data;
  try {
    data = processPdf(json);
  }
  catch (e) {
    return false;
  }

  if (data.table.length < 2 || (data.table.length % 2) != 0)
    return false;
  if (data.table[0].length != 9)
    return false;

  var result = {
    id: "oncomed",
    header: {
      documentId: data.objednavka,  
      purchaseTimestamp: _fixDate(data.datum), //data.table[0][2],
      partnerIdSold: "26003008",
      partnerIdShip: "26003008",
      partnerName: "Oncomed manufacturing a.s.",
      address: ["Oncomed manufacturing a.s.", "Karásek 2229/1b", "Brno-Řečkovice a Mokrá Hora", "621 00", "CZ"],
      contact: ["duskova@oncomed.cz", "515919962"]
    },
    items: [],
    messages: []
  };

  if (data.odberatel != "oncomed manufacturing a.s.")
    result.messages.push("Warning: customer name not matching: "+data.odberatel);
/*
    [                 
      '141-1207',       // katalog
      '420347',         // ean
      '02.10.2020',     // termin
      '200,0',          // pocet MJ
      'l',              // 
      '517,2000',       // cena za MJ
      '21%',            // sazba
      '103 440,00',     // zaklad
      '125 162,40 Kč'   // celkom s dph
    ],
*/

  for (var i=0; i<data.table.length; i+=2)
  {
    if (data.table[i].length != 9 || data.table[i+1].length != 1)
      return false;

    var item = data.table[i];
    result.items.push({
      ean:item[0], 
      name:data.table[i+1][0],
      quantity:_replaceDecimal(data.table[i][3]),
      price:_replaceDecimal(data.table[i][5])
    });
  }

  return result;
}

function _fixDate(d)
{
  return d.split(".").reverse().join("");  
}

function _replaceDecimal(v)
{
  return v.split(",").join(".").split(" ").join("");
}

function processPdf(pdfData)
{
  var pages = pdfData.formImage.Pages;
  if (pages.length > 2) 
    throw "wrong page num " +pages.length;
  var page = pages[0];
  var hlines = page.HLines;
  if (hlines.length < 2)
    throw "wrong hline num " + hlines.length;

  var top = hlines[0].y;
  var bottom = hlines[hlines.length-1].y;

  var texts = [];
  var odberatel = findAttribute(page.Texts, "Odb%C4%9Bratel%3A");
  var objednavka = findAttribute(page.Texts, "Objedn%C3%A1vka%20vydan%C3%A1%20%C4%8D.");
  var datum = findAttribute(page.Texts, "Datum%20vystaven%C3%AD%3A");

  for (var i in page.Texts)
  {
    var t = page.Texts[i];
    if (t.y >= top-1 && t.y <= bottom)
    {
      if (t.R.length != 1) throw "wrong text count";
      texts.push({x:t.x, y:t.y, w:t.w/16, t:decodeURIComponent(t.R[0].T).trim()});
    }
  }
  var table = makeGrid(texts);

  return {odberatel: odberatel, objednavka:objednavka, datum:datum, table:table};
}

function findAttribute(texts, key)
{
  var elem;
  for (var i in texts)
  {
    var t = texts[i];
    if (t.R[0].T == key)
      elem = t;
  }
  if (!elem)
    throw "Not found";

  elem = {...elem};
  elem.x += elem.w/16;

  var dist = (a, b) => Math.sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
  var best = texts[0];
  var bestdist = dist(best, elem);
  for (var i in texts)
  {
    var t = texts[i];
    var d = dist(elem, t);
    if (t.R[0].T != elem.R[0].T && d < bestdist)
    {
      best = t;
      bestdist = d;
    }
  }
  return decodeURIComponent(best.R[0].T);
}

function makeGrid(texts)
{
  let epsilon = 0.1;

  var findAdd = (arr, x) =>
  {
    for (var i in arr)
      if (Math.abs(i - x) < epsilon)
      {
        return ++arr[i].hits;
      }
    arr[x.toFixed(2)] = {hits:1};
    return 1;
  };

  var find = (arr, x) =>
  {
    for (var i in arr)
      if (Math.abs(i - x) < epsilon)
      {
        return arr[i].hits;
      }
    throw "not found";
  };

  var findIndex = (arr, x) =>
  {
    for (var i=0; i<arr.length; i++)
      if (Math.abs(arr[i] - x) < epsilon)
        return i; 
    throw "not found";
  }

  var findAt = (data, xx, yy) =>
  {
    var matches = data.filter(o => o.xx == xx && o.yy == yy); 
    if (matches.length > 1)
      throw "overlaping cells"
    return matches[0];
  };

  var rows = {};
  var columns = {};

  for (var i in texts)
  {
    var t = texts[i];
    findAdd(columns, t.x);
    findAdd(columns, t.x + t.w);
    findAdd(rows, t.y);
  };

  for (var i in texts)
  {
    var t = texts[i];
    var left = find(columns, t.x);
    var right = find(columns, t.x+t.w);
    t._x = (left >= right) ? t.x : t.x + t.w; 
  }

  columns = {};

  for (var i in texts)
  {
    var t = texts[i];
    findAdd(columns, t._x);
  }

  var newrows = [];
  for (var i in rows)
    newrows.push(parseFloat(i));

  var newcols = [];
  for (var i in columns)
    newcols.push(parseFloat(i));

  newrows.sort((a,b) => a-b);
  newcols.sort((a,b) => a-b);

  for (var i in texts)
  {
    var t = texts[i];
    t.xx = findIndex(newcols, t._x);
    t.yy = findIndex(newrows, t.y);
  }

  var result = [];
  for (var y=0; y<newrows.length; y++)
  {
    var row = [];
    for (var x=0; x<newcols.length; x++)
    {
      var obj = findAt(texts, x, y);
      if (obj)
        row[x] = obj.t;
    }
    result.push(row);
  }
  return result;
}
