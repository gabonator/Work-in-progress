module.exports = {import:convert};

/*
Katalogové číslo OP	Popis artiklu	Množství	Z této obj. nedodáno	Cena za MJ	Cena za MJ (měna)	Sleva %	Kód DPH	Celkem (FM)	Celkem (FM) (měna)	Dat.dodávky
631-0108	Super Frost Plus - pozor NOVÁ CENA!!	300	300	362,14	CZK	0	I2	108642	CZK	15.03.2019
556760	Labofix 200ml aerosol bez CFCs	300	300	78,25	CZK	0	I2	23475	CZK	15.03.2019
11028303	Decalcifier DC1 5l	10	10	901,5	CZK	0	I2	9015	CZK	15.03.2019
11028305	Decalcifier DC1 2,5l	5	5	657,6	CZK	0	I2	3288	CZK	15.03.2019
11028306	Decalcifier DC2 2,5l - kys. chlorovodíková	2	2	836,4	CZK	0	I2	1672,8	CZK	15.03.2019
13874550	kazeta MICROTWIN vč. víčka, barva bílá, 500 ks	18	18	939	CZK	0	I2	16902	CZK	15.03.2019
16408370	filtrační vložka do kazet, černá	50	50	191,6	CZK	0	I2	9580	CZK	15.03.2019
631-0659	skla krycí, rozměr 24x24 mm, MRF	10	10	501,6	CZK	0	I2	5016	CZK	15.03.2019
631-0691	skla krycí, rozměr 24x32 mm, MRF	10	10	635	CZK	0	I2	6350	CZK	15.03.2019
631-1574	skla krycí, rozměr 24x50 mm, MRF	50	50	844,09	CZK	0	I2	42204,5	CZK	15.03.2019
631-0664	skla krycí, rozměr 24x60 mm, MRF	10	10	1062	CZK	0	I2	10620	CZK	15.03.2019
512-0573	Idylla filtrační papír Whatman Grade 1, prům. 10 mm	5	5	727,2	CZK	0	I2	3636	CZK	15.03.2019
						0	I2			
*/

function convert(data)
{
  if (!data || typeof(data) != "object" || !data.length || data.length < 2)
    return false;


  if (data[0][0].indexOf("Katalog") != 0 || data[0].length != 11)
    return false;

  var date = data[1][10].split("."); // DD.MM.YYYY
  date = ("0000" + date[2]).substr(-4) + ("00" + date[1]).substr(-2) + ("00" + date[0]).substr(-2); // YYYYMMDD
  documentId = date;

  var result = {
    id: "bamed sap",
    header: {
      documentId: documentId,  
      purchaseTimestamp: date,
      partnerIdSold: "26005265",
      partnerIdShip: "26005265",
      partnerName: "bamed", // vzdy bez medzery
      address: ["bamed s.r.o.", "Litvínovice 32", "Litvínovice (České Budějovice)", "370 01", "CZ"],
      contact: ["bamed@bamed.cz", "386 351 974"]
    },
    items: [],
    messages: []
  };

  data.shift();

  for (i in data)
  {
    var item = data[i];
    if (item.length != 11)
      return false;

    var id = item[0];
    var name = item[1];
    var quantity = item[2];
    var price = item[4];

    price = price.split(",").join(".");

    if (id == "" || name == "")
      continue;

    result.items.push({
      ean:id, 
      name:name,
      quantity:quantity,
      price:price
    });
  }

//  console.log(result.items);

  return result;
}
