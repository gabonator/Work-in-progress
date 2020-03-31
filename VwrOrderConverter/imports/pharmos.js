function convert(json)
{
  if (!json || !json.order || !json.order.items || !json.order.items.item) 
  {
    return false;
  }

  var result = {
    id: "pharmos",
    header: {
      documentId: json.order.order_id,  
      purchaseTimestamp: json.order.date_cre.split("-").join(""),
      partnerIdSold: "26002042",
      partnerIdShip: "26005965",
      partnerName: "Pharmos",
      address: ["Pharmos, a.s. Brandýsek", "Slánská 79", "Brandýsek", "273 41", "CZ"],
      contact: ["marie.baladova@pharmos.cz", "312 777 057"]
    },
    items: [],
    messages: []
  };

  if (json.order.provider_id != "63073242" ||
      json.order.partner_id != "19010290" ||
      (json.order.branch_id != "500000" && json.order.branch_id != "409999"))
  {
    result.messages.push("Warning, customer id not matching");
  }

  var items = json.order.items.item;
  if (!isArray(items))
    items = [items];

  for (i in items)
  {
    var item = items[i];
    var id = item.prod_id;
    var vwrId = conversionTable[id];
    if (!vwrId)
    {
      result.messages.push("Warning, cannot match product id " + id);
      vwrId = id;
    }

    result.items.push({
      ean:vwrId, 
      name:item.prod_title,
      quantity:item.qty,
      price:item.price
    });
  }

  return result;
}

function isArray(what) {
    return Object.prototype.toString.call(what) === '[object Array]';
}

var conversionTable = {
"761617":"VITU3402007/K",
"761456":"VITU41042",
"730210":"LACH51015000P00001",
"719686":"GLAS177.303.07",
"716622":"TNOS632524325025",
"714633":"GLAS177.303.06",
"713915":"JIZE211A/1/0",
"713914":"JIZE211A/0",
"713881":"VTRB632432141444",
"713880":"VTRB632432141130",
"713874":"VTRB632492002060",
"713865":"NEDFALTEST",
"713596":"NEDFALTEST1",
"712878":"GAMA204811",
"712777":"TNOS632524201000",
"710944":"JIZE213A/1",
"710920":"VTRB632432141125",
"710895":"MARI1000200091",
"710786":"VTRB632492003100",
"710634":"IBSA331127000001",
"710581":"GLAS178.303.05",
"710421":"MARI1000000091",
"710408":"VTRB632432141343",
"710395":"JIZE213A/3",
"710394":"JIZE213B/2",
"710393":"JIZE213A/2",
"710392":"JIZE213B/1",
"710386":"JIZE211B/2",
"710381":"JIZE211A/2",
"710380":"JIZE211A/1A",
"710363":"VITU801001",
"710361":"EXAT3402001",
"710343":"MARI4205200",
"710272":"VTRB632432140923",
"710225":"VTRB632492005150",
"710224":"VTRB632492003090",
"710221":"VTRB632492002050",
"710220":"VTRB632492003080",
"710215":"VTRA632414204940",
"710213":"VTRA632414204500",
"710210":"VTRA632414204100",
"710206":"VTRA632414104940",
"710205":"VTRA632414104500",
"710204":"VTRA632414204250",
"710203":"VTRA632414104100",
"710174":"VTRB632432151238",
"710169":"VTRB632534104100",
"710167":"VTRB632534104050",
"710159":"VTRB632417012100",
"710157":"VTRB632411010050",
"710156":"VTRB632411010025",
"710153":"VTRB632417012940",
"710151":"VTRB632417012400",
"710150":"VTRB632417012250",
"710149":"VTRB632417012150",
"710148":"VTRB632411012050",
"710123":"VTRA632492004120",
"709939":"IBSA40005",
"308040":"VITU50002",
"308020":"VITU41040",
"308017":"IBSA40061",
"308016":"IBSA635038040006",
"308014":"IBSA20000973",
"308013":"IBSAP_0011/G"
};

module.exports = {import:convert};

/*
partner_id, branch_id, name
19010290,100000,PHARMOS, a.s. Ostrava
19010290,200000,PHARMOS, a.s. Prost
19010290,409999,PHARMOS, a.s. Hradec Kr
19010290,459999,PHARMOS, a.s. Brno
19010290,500000,PHARMOS, a.s. Brand
19010290,550000,PHARMOS, a.s. Plze
19010290,708888,PHARMOS, a.s. T
19010290,750000,PHARMOS, a.s. T
25534459,600000,Jihlavsk
25633741,300000,Pra
27837921,103054,Zenagel a.s., Brand
27837921,609049,Zenagel a.s., Prost
27837921,707150,Zenagel a.s., Ostrava
27837921,3305006,Zenagel a.s., Plze
27837921,3502023,Zenagel a.s., Hradec Kr
65139577,3502025,PHARMACY-distribuce l
65139577,3602047,PHARMACY-distribuce l
65139577,3705006,PHARMACY-distribuce l
65139577,3707023,PHARMACY-distribuce l
65139577,8705001,PHARMACY-distribuce l



także sold to je 26002042

Pharmos, a.s.
Těšínská 1349/296
716 00 Ostrava – Radvanice
Telefon: 312 777 057
marie.baladova@pharmos.cz


no a ship to bude vzdy 26005965
Pharmos, a.s. Brandýsek
Slánská 79
273 41 Brandýsek
Telefon: 312 777 057
marie.baladova@pharmos.cz


{ order:
   { order_id: '8172842425',
     order_cen: '',
     date_cre: '2018-08-22',
     provider_id: '63073242',
     partner_id: '19010290',
     branch_id: '500000',
     compensation: '0',
     text: '',
     items: { item: [Array] } } }

{ qty: '3.00',
  price: '23.00',
  prod_id: '710149',
  prod_title: 'Kýdinka vysoký  150ml          153',
  code_pdk: '4207149',
  code_apa: '4207149',
  code_sukl: '',
  code_ean: 'N' }

*/

