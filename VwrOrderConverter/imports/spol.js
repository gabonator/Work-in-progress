function convert(json)
{
  if (!json || !json.Envelope || !json.Envelope.Body || !json.Envelope.Body.MessageParts || 
      !json.Envelope.Body.MessageParts.PurchaseRequisition ||
      !json.Envelope.Body.MessageParts.PurchaseRequisition.VendPurchOrderJour ||
      !json.Envelope.Body.MessageParts.PurchaseRequisition.VendPurchOrderJour.VendPurchOrderTrans)
  {
    return false; 
  }

  var OrderJour = json.Envelope.Body.MessageParts.PurchaseRequisition.VendPurchOrderJour;

  var purchaseTimestamp = OrderJour.PurchOrderDate.split("-").join("");
  var documentId = OrderJour.PurchOrderDocNum;
  var items = OrderJour.VendPurchOrderTrans;

//  for (var i in OrderJour)
//    if (i.substr(0,5)=="Deliv")
//       console.log(i+"="+OrderJour[i]);

  var result = {
    id: "spolchemie xml",
    header: {
      documentId: documentId,  
      purchaseTimestamp: purchaseTimestamp,
      partnerIdSold: "26000135",
      partnerIdShip: "26000135",
      partnerName: OrderJour.DeliveryName,
      address: [OrderJour.DeliveryName, OrderJour.DeliveryStreet, OrderJour.DeliveryCity, 
                OrderJour.DeliveryZipCode, OrderJour.DeliveryCountryRegionId],
      contact: ["korinkova@spolchemie.cz", "477 164 632"]
    },
    items: [],
    messages: []
  };

  if (OrderJour.DeliveryName.substr(0, 6) != "Spolek")
  {
    result.messages.push("Warning: customer name differs from Spolek... ("+formHeader.buyer_name+")");
  }

  for (i in items)
  {
    var item = items[i];
    result.items.push({
      ean:item.ExternalItemId + ".", 
      name:item.Name.split("\n").join(" "),
      quantity:parseFloat(item.Qty),
      price:parseFloat(item.PurchPrice)
    });
  }
// console.log(result.items);
  return result;
}

module.exports = {import:convert};