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

  // kvoli divnemu parsovaniu XML je bud items pole, alebo ak iba jeden objekt
  if (!Array.isArray(items))
    items = [items];

  var partnerName = OrderJour.DeliveryName;
  if (partnerName.indexOf("Spolek pro chemickou") == 0)
    partnerName = "Spolchemie";

  var result = {
    id: "spolchemie",
    header: {
      documentId: documentId,  
      purchaseTimestamp: purchaseTimestamp,
      partnerIdSold: "26000135",
      partnerIdShip: "26005971",
      partnerName: partnerName,
      address: [OrderJour.DeliveryName, OrderJour.DeliveryStreet, OrderJour.DeliveryCity, 
                OrderJour.DeliveryZipCode, OrderJour.DeliveryCountryRegionId],
      contact: ["korinkova@spolchemie.cz", "477 164 632"]
    },
    items: [],
    messages: [],
    errors: []
  };

  if (OrderJour.Dimension && 
      OrderJour.Dimension.element && 
      OrderJour.Dimension.element.length == 4 && 
      OrderJour.Dimension.element[1] && 
      OrderJour.Dimension.element[1] != "")
  {
    result.header.orderDimension = OrderJour.Dimension.element[1];
  }

  if (partnerName != "Spolchemie")
  {
    result.messages.push("Warning: customer name differs from Spolek... ("+formHeader.buyer_name+")");
  }

  for (i in items)
  {
    var item = items[i];
    var ean = item.ExternalItemId;

    if (!ean)
    {
      result.errors.push("ExternalItemId not specified!");
      result.errors.push("- Item " + i + " / " + items.length);
      result.errors.push("- " + JSON.stringify(item, null, 2));
      return result;
    }

    if (ean.length == 12 && (ean[0] < '0' || ean[0] > '9'))
      ean += ".";

    result.items.push({
      ean:ean, 
      name:item.Name.split("\n").join(" "),
      quantity:parseFloat(item.Qty),
      price:parseFloat(item.PurchPrice)
    });
  }
  return result;
}

module.exports = {import:convert};
