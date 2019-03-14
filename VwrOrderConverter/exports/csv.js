function toCsv(data)
{
  var out = [];
  var print = (arr) => out.push(arr.join(";"));

  print(["BEGIN", data.header.documentId, data.header.partnerName, "VWR", "ORDERS", data.header.purchaseTimestamp, "102511", ""]);
  print(["HEAD", data.header.documentId, data.header.purchaseTimestamp, "", "CZK", ""]);
  print(["SOLDTO", data.header.partnerIdSold, /*data.header.partnerName*/data.header.address[0]]); // parner name musi byt iba ID v begin riadku, tu uz moze byt aj s medzerami
  print(["SHIPTO", data.header.partnerIdShip, 
         data.header.address[0], "", "", "", //"", 
         data.header.address[1], "", "", "", "", 
         data.header.address[2], data.header.address[3], data.header.address[4], 
         data.header.contact[0], data.header.contact[1]]);

  for (var i = 0; i < data.items.length; i++)
  {
    var item = data.items[i];

    print([
      "LINE", 
      ("000000" + (i+1)).substr(-6),
      "",
      item.ean,
      item.name,
      parseFloat(item.quantity).toFixed(3),
      "",
      data.header.purchaseTimestamp,
      item.price !== null ? item.price : "", // ocakavana cena
      item.price !== null ? (item.price*item.quantity).toFixed(2) : ""  // ocakavana cena
    ]);
  }
  print(["END", data.header.documentId]); 

  return out.join("\x0d") + "\x0d";
}

module.exports = {export:toCsv};