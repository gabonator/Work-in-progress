function convert(json)
{
  if (!json || !json.biztalk_1 || !json.biztalk_1.body || 
    !json.biztalk_1.body.xml_document || !json.biztalk_1.body.xml_document.line_items)
  {
    return false;
  }

  var items = json.biztalk_1.body.xml_document.line_items.item;
  var formHeader = json.biztalk_1.body.xml_document.form_header;
  var purchaseTimestamp = formHeader.document_date.split("-").join("");
  var documentId = formHeader.userdocid;

  var result = {
    id: "helago xml",
    header: {
      documentId: documentId,  
      purchaseTimestamp: purchaseTimestamp,
      partnerIdSold: "26000611",
      partnerIdShip: "26000611",
      partnerName: formHeader.buyer_name,
      address: ["HELAGO-CZ, s.r.o.", "Kladská 1082", "Hradec Králové 3", "500 03", "CZ"],
      contact: ["odbyt@helago-cz.cz", "495 768 317"]
    },
    items: [],
    messages: []
  };

  if (formHeader.buyer_name != "HELAGO-CZ, s.r.o.")
  {
    result.messages.push("Warning: customer name differs from HELAGO ("+formHeader.buyer_name+")");
  }

  for (i in items)
  {
    var item = items[i];
    result.items.push({
      ean:item.article_ean + ".", 
      name:item.article_name,
      quantity:item.quantity,
      price:null
    });
  }

  return result;
}

module.exports = {import:convert};