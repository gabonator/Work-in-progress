module.exports = {import:convert};

/*
4|47675934||ONT651803027|20180905|63073242|5|2214.40|2680.00|.00|.00|2214.40|2679.40|
|200.00||9.35|11.31|21.0|||||Strikacka injekcni tridilna TERUMO 50ml catheter tip - zanetka (25ks/bal) (SS+50C1)=TER2BS50C||
MER034009013|2.00||32.10|38.84|21.0|||||Teplomer chladnickovy -30+40
VIT641331213200|2.00||48.60|58.81|21.0|||||Tloucek treci drsny,  213a/2  30x135mm (JIZE213A/2)|VIT641331213200|
VIT641331211120|1.00||97.20|117.61|21.0|||||Miska treci drsna, 75ml|VIT641331211120|
|1.00||85.80|103.82|21.0|||||Tloucek treci drsny, 42 x 175 mm||
*/

function convert(data)
{
  if (typeof(data) != "object" || !data.length || data.length < 2)
    return false;

  var partner = data.shift();
  var partnerKey = partner[3].substr(0, 5);

  if (!data) 
  {
    return false;
  }

  var partners = {
    "ONT33,ONTS1,ONTS2,ONTS3,ONTS4,ONTS5,ONTS6,ONTS7,ONTS8,ONTS9,ONTS0" : {
      partnerIdSold: "26002813",
      partnerIdShip: "26006315",
      partnerName: "Perfect",
      address: ["Perfect Distribution a.s. (Třinec)", "Konská 198", "Třinec", "739 61", "CZ"],
      contact: ["libuse.styskalova@pfd.agel.cz", "+420 606 784 687"] // nemame mail a cislo!
    },
    "ONT44,ONT65" : {
      partnerIdSold: "26002813",
      partnerIdShip: "26005857",
      partnerName: "Perfect",
      address: ["Perfect Distribution a.s. Airport Logistic Park", "Kněževes 185", "Kněževes", "252 68", "CZ"],
      contact: ["libuse.styskalova@pfd.agel.cz", "+420 606 784 687"] // nemame mail a cislo!
    },
    "ONT45,ONT55" : {
      partnerIdSold: "26002813",
      partnerIdShip: "26002813",
      partnerName: "Perfect",
      address: ["Perfect Distribution a.s.", "U spalovny 4582/17", "Prostějov", "796 01", "CZ"],
      contact: ["libuse.styskalova@pfd.agel.cz", "+420 606 784 687"] // nemame mail a cislo!
    }
  }

  var result = {
    id: "perfect csv",
    header: {
      documentId: partner[3],      
      purchaseTimestamp: partner[4],
    },
    items: [],
    messages: []
  };
  for (var pid in partners)
  {
    if (pid.indexOf(partnerKey) != -1)
    {
      var partnerInfo = partners[pid];
      for (var i in partnerInfo)
        result.header[i] = partnerInfo[i];
    }
  }

  if (!result.header.partnerIdShip)
  {
    console.log("Partner no match");
    return false;
  }

  for (i in data)
  {
    var item = data[i];
    if (item.length < 14)
      return false;

    var id = item[13];
    var vwrId = conversionTable[id];
    if (!vwrId)
    {
      result.messages.push("Warning, cannot match product id " + id);
      vwrId = id;
    }

    var packQuantity = quantityTable[id];
    if (!packQuantity)
      packQuantity = 1;
    else
    {
      if ((item[1] % packQuantity) != 0)
        result.messages.push("Warning, pack quantity not divisible " + vwrId + " qty: " + item[1] + " pack: " + packQuantity);
    }
 
    result.items.push({
      ean:vwrId, 
      name:item[10],
      quantity:item[1]/packQuantity,
      price:item[3]
    });
  }

  return result;
}

var conversionTable = {
"BRA8728828F":"BRAU8728828F",
"GAM400927":"GAMA400927",
"PHA713865":"NEDFALTEST",
"REG-VIT-221430023100":"LACH10001A25M1000",
"REG-VIT-221430637100":"LACH20038AT0M1000",
"VIT-05200.185":"05200.185",
"VIT-103156X":"103156X",
"VIT-112-2371":"112-2371",
"VIT-153385E":"153385E",
"VIT-20065.293":"20065.293",
"VIT-20066.330":"20066.330",
"VIT-201-0392":"201-0392",
"VIT-20104.334":"20104.334",
"VIT-20422.297":"20422.297",
"VIT-20589.293":"20589.293",
"VIT-20821.296":"20821.296",
"VIT-20823.293":"20823.293",
"VIT-20842.367":"20842.367",
"VIT-20864.320":"20864.320",
"VIT-20905.296":"20905.296",
"VIT-212-0024":"212-0024",
"VIT-212-0326":"212-0326",
"VIT-212-0473":"212-0473",
"VIT-212-0517":"212-0517",
"VIT-212-0634":"212-0634",
"VIT-212-1421":"212-1421",
"VIT-212-3911":"212-3911",
"VIT-212-6102":"212-6102",
"VIT-212-9277":"212-9277",
"VIT-21572.188":"21572.188",
"VIT-23595.328":"23595.328",
"VIT-253380005504":"TOPP05504",
"VIT-28973.363":"28973.363",
"VIT-32045.262H":"32045.262",
"VIT-331500156340":"734-2063",
"VIT-331600471800":"BOET05.011.0100",
"VIT-331690221050":"FLME22105",
"VIT-331693391111":"FLME28063",
"VIT-331850000370":"212-6100",
"VIT-332641530302":"GLAS415.303.02",
"VIT-394030000978":"613-3508",
"VIT-395321056001":"291-1214",
"VIT-395321056005":"291-1211",
"VIT-396137150034":"IBSAWK15003/4",
"VIT-397210003340":"SCNG252",
"VIT-397210008293":"212-0298",
"VIT-397402999998":"IBSA397402999998",
"VIT-443852A":"443852A",
"VIT-624703102110":"516-0707",
"VIT-624703205110":"BINZ3.205.110",
"VIT-624723025858":"BINZ123002",
"VIT-632413001075":"VTRB632413001075",
"VIT-632414204100":"VTRA632414204100",
"VIT-632417010100":"VTRB632417010100",
"VIT-632417010150":"VTRB632417010150",
"VIT-632417010400":"VTRB632417010400",
"VIT-632417010600":"VTRB632417010600",
"VIT-632417012400":"VTRB632417012400",
"VIT-632417012800":"VTRB632417012800",
"VIT-632417106100":"VTRB632417106100",
"VIT-632417405940":"VTRB632417405940",
"VIT-632422015110":"TNOS632422015110",
"VIT-632422015116":"VTRB632422015116",
"VIT-632432110923":"VTRB632432110923",
"VIT-632432111125":"VTRB632432111125",
"VIT-632432111130":"VTRB632432111130",
"VIT-632432111444":"VTRB632432111444",
"VIT-632432351230":"VTRB632432351230",
"VIT-632434026719":"VTRB632000100019",
"VIT-632434116905":"TNOS632434116905",
"VIT-632434116910":"TNOS632434116910",
"VIT-632499890004":"HAVA632499890004",
"VIT-632524325025":"TNOS632524325025",
"VIT-636013120206":"GLAS131.202.06",
"VIT-85680.260H":"85680.260",
"VIT-8930":"BOCH8930",
"VIT-BURK2327-0030  ":"BURK2327-0030",
"VIT-IBSAWK15004/0":"IBSAWK15004/0",
"VIT-LPIT119040":"LPIT119040",
"VIT-OT2001999B":"VITU253380001241",
"VIT-VITU634921275035":"VITU634921275035",
"VIT000000090000":"TNOSTD",
"VIT100001683":"EXAT1683",
"VIT1000078":"MARI1000200091",
"VIT100125101":"EXAT125101",
"VIT111-0930":"111-0930",
"VIT112-0307":"112-0307",
"VIT112-2372":"112-2372",
"VIT112-2890":"112-2890",
"VIT112-2891":"112-2891",
"VIT113-0645":"113-0645",
"VIT113-0646":"113-0646",
"VIT113050503":"IBSASP0029003",
"VIT115-0050":"115-0050",
"VIT129-0289":"129-0289",
"VIT203801001":"VITU801001",
"VIT20880.290":"20880.290",
"VIT20880.320":"20880.320",
"VIT211-0205":"211-0205",
"VIT211-0207":"211-0207",
"VIT211-0208":"211-0208",
"VIT211-0209":"211-0209",
"VIT211-0231":"211-0231",
"VIT213-1122":"213-1122",
"VIT213-1124P":"213-1124",
"VIT213-3403":"213-3403",
"VIT213-3710":"213-3710",
"VIT214-1136":"214-1136",
"VIT215-6511":"215-6511",
"VIT215-9011":"215-9011",
"VIT216-0791":"216-0791",
"VIT216-0792":"216-0792",
"VIT216-0793":"216-0793",
"VIT216-1047":"216-1047",
"VIT216-1342":"216-1342",
"VIT216-1370":"216-1370",
"VIT216-1408":"216-1408",
"VIT216-1413":"216-1413",
"VIT216-1502":"216-1502",
"VIT216-1732":"216-1732",
"VIT216-2639":"216-2639",
"VIT221-0250":"221-0250",
"VIT221-1721":"VTRB632413001035",
"VIT221-1816":"221-1816",
"VIT221-1818":"221-1818",
"VIT221430423100":"LACH30093AP0G1000",
"VIT222521004":"KAKO2521004",
"VIT222526008":"KAKO2526008",
"VIT222526009":"KAKO2526009",
"VIT222526013":"KAKO2526013",
"VIT222526014":"KAKO2526014",
"VIT224416427":"KAKO4416427",
"VIT224416428":"KAKO4416428",
"VIT231-0588":"231-0588",
"VIT23373.320":"23373.320",
"VIT238102000":"GAMA204809",
"VIT238105000":"GAMA204808",
"VIT24575.320":"24575.320",
"VIT282222526015":"KAKO2526015",
"VIT282224411411":"KAKO4411411",
"VIT28222526006":"KAKO2526006",
"VIT293-4186":"293-4186",
"VIT331000458815":"IBSA458815",
"VIT331092600111":"612-1746",
"VIT331312000040":"MRAZ1200/40",
"VIT331331000250":"MRAZ3100/250",
"VIT3313690251350":"FLME25135",
"VIT331383243045":"VITU383243045.010",
"VIT331690210110":"FLME21011",
"VIT331690210550":"FLME21055",
"VIT331690211520":"FLME21152",
"VIT331690213640":"FLME21364",
"VIT331690213670":"FLME21367",
"VIT331690221080":"FLME22108",
"VIT331690221350":"FLME22135",
"VIT331690222130":"FLME22213",
"VIT331690222540":"FLME22254",
"VIT331690226720":"FLME22672",
"VIT331690229520":"FLME22952",
"VIT331690250350":"FLME25035",
"VIT331690251340":"FLME25134",
"VIT331690251710":"FLME25171",
"VIT331690251810":"FLME25181",
"VIT331690251850-BAL":"FLME25185",
"VIT331690270550":"FLME27055",
"VIT33170704129":"221-0154",
"VIT331707081644":"KART1644",
"VIT331707645941":"612-2423",
"VIT331707648081":"612-3788",
"VIT331707649081":"612-3789",
"VIT331707652081":"612-4314",
"VIT331850001080":"612-0940",
"VIT331850001637-04":"215-9012",
"VIT331850001637-06":"215-9014",
"VIT331850001637-10":"215-9016",
"VIT331850001637":"215-9010",
"VIT331850011637":"KART1637-10",
"VIT331850041637":"KART1637-04",
"VIT331850041638":"215-9013",
"VIT331850061637":"KART1637-06",
"VIT331950080009":"129-0324",
"VIT331998000086":"IBSABSA86",
"VIT331998002022":"IBSABSA022/G",
"VIT332100003229":"IBSA3229",
"VIT332100003230":"IBSACM3230",
"VIT336707441941":"GLAS179.303.02",
"VIT336850000150":"GLAS122.303.03",
"VIT336850000566":"GLAS166.303.03",
"VIT336850001079":"GLAS178.303.04",
"VIT388034009013":"VITU8586003880266",
"VIT388034209420":"VITU9586003880020",
"VIT388100700023":"EXAT700023",
"VIT388100800001":"EXAT801110",
"VIT391-2730":"VTRB632492003100",
"VIT396935260020":"609-0127",
"VIT397038715821":"IBSA715821",
"VIT397210001002":"SCNG8112",
"VIT397210001012":"SCNG8132",
"VIT399100232705":"BURK2327-0050",
"VIT399100232710":"BURK2327-0010",
"VIT410-0087":"410-0087",
"VIT414212100":"VTRA632414212100",
"VIT417010250":"VTRB632417010250",
"VIT432141238":"VTRB632432141238",
"VIT432151130":"VTRB632432151130",
"VIT432554845":"VTRA632432554845_U",
"VIT479-1160":"479-1160",
"VIT479-1242":"479-1242",
"VIT479-5165":"479-5165",
"VIT514-0061":"514-0061",
"VIT516-0275":"516-0275",
"VIT525-0150":"525-0150",
"VIT548-3018":"548-3018",
"VIT548-3024":"548-3024",
"VIT609-0136":"609-0136",
"VIT609-0184":"609-0184",
"VIT612-1389":"612-1389",
"VIT612-1920":"612-1920",
"VIT612-2429":"612-2429",
"VIT612-2706":"612-2706",
"VIT612-2707":"612-2707",
"VIT612-2743":"612-2743",
"VIT612-2942":"612-2942",
"VIT612-3742":"612-3742",
"VIT612-3833":"612-3833",
"VIT612-3836":"612-3836",
"VIT612-3843":"612-3843",
"VIT612-3844":"612-3844",
"VIT612-4125":"612-4125",
"VIT612-4750":"612-4750",
"VIT612-9352":"612-9352",
"VIT612-9354":"612-9354",
"VIT613-2050":"613-2050",
"VIT613-2705E":"613-2705",
"VIT613-2773":"613-2773",
"VIT613-3500":"613-3500",
"VIT613-3503":"613-3503",
"VIT613-3504":"613-3504",
"VIT613-3505":"613-3505",
"VIT613-3881":"613-3881",
"VIT613-4093":"613-4093",
"VIT613-4902":"613-4902",
"VIT613-5398":"613-5398",
"VIT620-1921":"620-1921",
"VIT620-2342":"620-2342",
"VIT624703102150":"516-0709",
"VIT624704207110":"BINZ113136",
"VIT624704208125":"BINZ113187",
"VIT624880565050":"PPERM2/56G/50X50",
"VIT624880566060":"PPERM2/56G/60X60",
"VIT624880805050":"PPERPN/80G/M2",
"VIT624880806060":"PPER80G/M2",
"VIT624881005050":"PPERM2/100G/50X50",
"VIT630-1324":"MENZK5800AMNZ72",
"VIT631-0108":"631-0108",
"VIT631-0653":"631-0653",
"VIT631-0723":"631-0723",
"VIT631-0725":"631-0725",
"VIT631-0736":"631-0736",
"VIT631-0739":"631-0739",
"VIT631-0908":"631-0908",
"VIT631-1109":"631-1109",
"VIT631-1128":"631-1128",
"VIT631-1129":"631-1129",
"VIT631-1132":"631-1132",
"VIT631-1133":"631-1133",
"VIT631-9483":"631-9483",
"VIT632411010025":"VTRB632411010025",
"VIT632411010050":"VTRB632411010050",
"VIT632411012025":"VTRB632411012025",
"VIT632411012050":"VTRB632411012050",
"VIT632411106950":"214-0472",
"VIT632411119952":"VTRB632411119952",
"VIT632413001045":"VTRB632413001045",
"VIT632413001055":"VTRB632413001055",
"VIT632413004100":"VTRB632413004100",
"VIT632414104940":"VTRA632414104940",
"VIT632414321100":"VTRB632414321100",
"VIT632417010940":"VTRB632417010940",
"VIT632417012100":"VTRB632417012100",
"VIT632417012150":"VTRB632417012150",
"VIT632417012250":"VTRB632417012250",
"VIT632417012600":"VTRB632417012600",
"VIT632417012940":"VTRB632417012940",
"VIT632417106250":"VTRB632417106250",
"VIT632417106500":"VTRB632417106500",
"VIT632417106940":"VTRB632417106940",
"VIT632417106950":"VTRB632417106950",
"VIT632417117100":"VTRB632417117100",
"VIT632417117250":"VTRB632417117250",
"VIT632417117500":"VTRB632417117500",
"VIT632417119100":"VTRB632417119100",
"VIT632417119940":"VTRB632417119940",
"VIT632422010110":"VTRB632422010110",
"VIT632422012110":"VTRB632422012110",
"VIT632432110819":"VTRB632432110819",
"VIT632432111238":"VTRB632432111238",
"VIT632432111343":"VTRB632432111343",
"VIT632432141125":"VTRB632432141125",
"VIT632432141130":"VTRB632432141130",
"VIT632432141343":"VTRB632432141343",
"VIT632432150923":"VTRB632432150923",
"VIT632432341125":"VTRB632432341125",
"VIT632432341230":"VTRB632432341230",
"VIT632432341443":"VTRB632432341443",
"VIT632432511746":"VTRB632432511746",
"VIT632492004120":"VTRA632492004120",
"VIT632499890010":"HAVA632499890010",
"VIT632531122204":"VTRB632531122204",
"VIT632534104100":"VTRB632534104100",
"VIT632538160080":"VTRB632538160080",
"VIT633516001515":"HAVA12300606231434",
"VIT634423014097":"VTRA634423014098",
"VIT634423016167":"KIMLA416016001011",
"VIT634424155100":"634424155100",
"VIT634986311500":"631-1550",
"VIT63499010103":"631-0656",
"VIT634990810401":"MARI0810401",
"VIT635901000076":"VTRA635901000076",
"VIT635901000078":"VTRA635901000078",
"VIT635991000612":"VTRA635991000612",
"VIT636009520202":"GLAS095.202.02",
"VIT636012420204":"GLAS124.202.04",
"VIT636013020207":"GLAS130.202.07",
"VIT636013023401":"GLAS130.234.01",
"VIT636013023402":"GLAS130.234.02",
"VIT636023820207":"GLAS238.202.07",
"VIT639025001165":"VTRA639025001165",
"VIT641331211100":"JIZE211A/1",
"VIT641331211120":"JIZE211A/1A",
"VIT641331213100":"JIZE213A/1",
"VIT641331213101":"JIZE213B/1",
"VIT641331213200":"JIZE213A/2",
"VIT641331213201":"JIZE213B/2",
"VIT641331213400":"JIZE213A/4",
"VIT655038710036":"IBSA710036",
"VIT690210170":"FLME21017",
"VIT690213270":"FLME21327",
"VIT690230520":"FLMEBSA021",
"VIT690250620":"FLME25062",
"VIT690250720":"FLME25072",
"VIT690251750":"FLME25175",
"VIT690253030":"FLME25303",
"VIT707065295":"612-0957",
"VIT707441941":"213-0262",
"VIT707442081":"213-3725",
"VIT707443081":"213-3730",
"VIT707447941":"213-0256",
"VIT707651081":"612-4312",
"VIT707978941":"VITL978941",
"VIT720-2526":"720-2526",
"VIT720-2527":"720-2527",
"VIT720-2528":"720-2528",
"VIT732-7511":"732-7511",
"VIT793113050502":"IBSASP0028001",
"VIT793175800523-BAL":"CANS8005-23",
"VIT83621.320":"83621.320",
"VIT83625.320":"83625.320",
"VIT83626.290":"83626.290",
"VIT83639.320":"83639.320",
"VIT83872.270":"83872.270",
"VIT84860.360":"85824.360",
"VIT84865.260":"84865.260",
"VIT990101010":"631-0655",
"VIT998000008400":"IBSA37580101",
"VITA16289.14":"A16289.14",
"VITA4148.0025":"A4148.0025",
"VITBINZ113137":"BINZ113137",
"VITBOCH1023R":"232-0215",
"VITBOCH1131":"BOCH1131",
"VITBOCH12620":"BOCH12620",
"VITBURK9614-0050":"BURK9614-0050",
"VITDELT-202847-ks":"DELT202847",
"VITDELTB-200":"DELTB-200",
"VITEXAT105013":"EXAT105013",
"VITFLME21056":"FLME21056",
"VITFLME21361":"FLME21361",
"VITGLAS130.202.05":"GLAS130.202.05",
"VITGLAS130.202.08":"GLAS130.202.08",
"VITGLAS130.202.09":"GLAS130.202.09",
"VITGLAS232.202.09":"GLAS232.202.09",
"VITGLAS238.202.01":"GLAS238.202.01",
"VITGLAS524.303.04":"GLAS524.303.04",
"VITHAVA12300404231434":"HAVA12300404231434",
"VITHAVA632499890022":"HAVA632499890022",
"VITIBSA112080070":"IBSA112080070",
"VITIBSAKST-10UN":"IBSAKST-10UN",
"VITJIZE211A/0":"JIZE211A/0",
"VITJIZE211A/1/0":"JIZE211A/1/0",
"VITJIZE211A/2":"JIZE211A/2",
"VITJIZE211B/1":"JIZE211B/1",
"VITJIZE211B/1/0":"JIZE211B/1/0",
"VITJIZE211B/2":"JIZE211B/2",
"VITJIZE211B/3A":"JIZE211B/3A",
"VITJIZE213A/O":"JIZE213A/0",
"VITKAKO2526011":"KAKO2526011",
"VITKAKO2527001":"KAKO2527001",
"VITKAVA1101400":"VTRA635920201400",
"VITKAVA1101600":"VTRA635920201600",
"VITKAVA632414321950":"VTRB632414321950",
"VITKAVA632422006104":"VTRB632422006104",
"VITKAVA632422015100":"VTRB632422015100",
"VITKAVA632422414208":"VTRB632422414208",
"VITKAVA632431071046":"VTRB632431071046",
"VITKAVA632516001100":"VTRB632516001100",
"VITKAVA632516001120":"VTRB632516001120",
"VITKAVA632531122205":"VTRB632531122205",
"VITKOEHA-1188":"KOEHA-1188",
"VITKOEHA-1194":"KOEHA-1194",
"VITL440941":"GLAS179.303.01",
"VITLACH10023ATOM1000":"LACH10023AT0M1000",
"VITLACH20001ATOM5000":"LACH20001AT0M5000",
"VITLACH20060ATOM1000":"LACH20060AT0M1000",
"VITMARI5600065":"MARI5600065",
"VITMENZBB022022A0D3":"630-2883",
"VITMMMAK102":"MMMAK102",
"VITMMMAK113KS":"MMMAK113",
"VITNEDF396553710104":"NEDF396553710104",
"VITNEDF6045":"NEDF6045",
"VITSCNG142":"SCNG142",
"VITSCNG235":"SCNG235",
"VITSCNG286":"SCNG286",
"VITSCNG8114":"SCNG8114",
"VITSUREALCOM":"SUREALCOM",
"VITSUREALCOMMP":"SUREALCOMMP",
"VITTREF96.8755.9.01":"TREF96.8755.9.01",
"VITU3811002":"VITU3811002",
"VITUS77702":"GEHEUS77702",
"VITVITU21800":"VITU21800",
"VITVTRA632425900035":"VTRA632425900035",
"VITVTRA632425900050":"VTRA632425900050",
"VITVTRA7765/5X200":"VTRA7765/5X200",
"VITVTRA7765/6X200":"VTRA7765/6X200",
"VITVTRA7765/7X300":"VTRA7765/7X300",
"VITVTRABALL3":"VTRABALL3",
"VITVTRABALL5":"VTRABALL5",
"VITVTRB632413001100":"VTRB632413001100",
"VITVTRB632414345250":"VTRB632414345250",
"VITVTRB632492003070":"VTRB632492003070",
"VITVTRB632499890001":"VTRB632499890001",
"VITVTRB632531122202":"VTRB632531122202",
"VITVTRB634952430070":"VTRB634952430070",
"VITVWRI212-0017":"212-0017",
"VWR-632411119025":"VTRB632411119025",
"VWR-BOCH12676":"BOCH12676",
"VWR-FLME28052":"FLME28052",
"VWRMILFSLMPL25SS":"MILFSLMPL25SS",
};


var quantityTable = {
"VIT624703102150":100,
"VIT-112-2371":100,
/*
"BRA8728828F":100,
"PHA713865":10,
"VIT-112-2371":100,
"VIT-331500156340":200,
"VIT-331600471800":100,
"VIT113-0645":20,
"VIT113-0646":10,
"VIT211-0208":5,
"VIT216-0791":45,
"VIT216-0792":20,
"VIT216-0793":80,
"VIT216-2639":250,
"VIT238102000":12,
"VIT3313690251350":50,
"VIT331383243045":10,
"VIT331690211520":200,
"VIT331690221080":50,
"VIT331690221350":50,
"VIT331690222130":50,
"VIT331690226720":50,
"VIT331690229520":50,
"VIT331690250350":50,
"VIT331690251340":100,
"VIT331690251710":100,
"VIT331850001637-04":10,
"VIT331850001637-06":10,
"VIT331850001637-10":10,
"VIT331850001637":10,
"VIT331850011637":10,
"VIT331850041637":10,
"VIT331850041638":10,
"VIT331850061637":10,
"VIT613-3881":25,
"VIT613-4902":25,
"VIT613-5398":25,
"VIT624703102150":100,
"VIT634423014097":250,
"VIT634423016167":293,
"VIT634424155100":78,
"VIT690210170":500,
"VIT690213270":500,
"VIT690250620":100,
"VIT690250720":100,
"VIT690251750":50,
"VIT793175800523-BAL":100,
"VIT853191637":10,
"VIT998000008400":10,
"VITDELT-202847-ks":100,
"VITFLME21056":500,
"VITFLME21361":500,
"VITMMMAK102":20,
"VITMMMAK113KS":5
*/
}