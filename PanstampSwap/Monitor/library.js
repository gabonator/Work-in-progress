library = [
  {
    product:
    {
      hardwareVersion:0x00000200,
      firmwareVersion:0x00000101,
      manufacturerId:0x00000001,
      productId:0x0000000A
    },
    description:
    {
      short: "DHT22",
      text: "DHT22 sender always in RX mode or modem"
    },
    registers:
    [
      "regCommonProductCode", 
      "regCommoHwVersion", 
      "regCommonFwVersion", 
      "regCommonSysState", 
      "regCommonFreqChannel",
      "regCommonSecuOption", 
      "regCommonPassword", 
      "regCommonSecuNonce", 
      "regCommonNetworkId", 
      "regCommonDevAddress", 
      "regCommonTxInterval",

      "regIdentify", 
      "regSensor", 
      "regListenerAddr", 
      "regMediatorAddr"
    ],
    decoders:
    {
      "regSensor":

  function(data)
  {
    if (data.length != 4)
      return {error: 'invalid data'};

    if (data[0] == 0xee)
      return {error: 'sensor error'};

    return {data:[
      { name:'temperature',
        type:'continuous numeric',
        resolution:0.1,
        range:[-40, 80],
        value:((data[0]<<8)|data[1])/10,
        units:'&deg; C'
      },
      { name:'humidity',
        type:'continuous numeric',
        resolution:0.1,
        range:[0, 100],
        value:((data[2]<<8)|data[3])/10,
        units:'%'
      }
    ]}; 
  }

    }
  }
];
