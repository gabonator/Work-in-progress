var PayBySquare = function() {};
PayBySquare.prototype.decode = function(stream)
{
  return decode(stream);
}

PayBySquare.prototype.encode = function(fields)
{
  return encode(fields);
}

// global mess
function _ASSERT(e, msg)
{
  if (!e) console.log("ASSERT: " + msg);
}

function toChar32(n)
{
  var table = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
  return table.charAt(n);
}

function fromChar32(ch)
{
  var table = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
  var i = table.indexOf(ch);
  _ASSERT( i != -1, "Cannot convert char : " + ch );
  return i;
}

function fromBase32(str)
{
  var arrValues = [];
  var nBits = 0;
  var nValue = 0;
  for (var i=0; i<str.length; i++)
  {
    nValue <<= 5;
    nValue |= fromChar32(str.charAt(i));
    nBits += 5;

    //console.log( i +". char = '"+str.charAt(i)+"' value = "+fromChar32(str.charAt(i)) + " sum ="+nValue + " bits="+nBits);

    if ( nBits >= 8 )
    {
       var nExtraBits = (nBits - 8);
       arrValues.push(nValue >> nExtraBits );
       nValue &= (1<<nExtraBits) - 1;
       nBits -= 8; 
    }
  }
  if ( nBits != 0 )
    arrValues.push( nValue );
  return arrValues;
}

function toBase32(arr)
{
  var nBits = 0;
  var nValue = 0;
  var strResult = "";
  for (var i=0; i<arr.length; i++)
  {
    nValue <<= 8;
    nValue |= arr[i];
    nBits += 8;

    while ( nBits >= 5 )
    {
      var nExtraBits = (nBits - 5);

      strResult += toChar32(nValue >> nExtraBits );
      nValue &= (1<<nExtraBits) - 1;
      nBits -= 5;
    }
  }
  return strResult;
}

function toHex16(arr)
{
  var out = "";
  for (var i=0; i<arr.length; i++)
    out += ("0" + arr[i].toString(16)).substr(-2) + " ";
  return out;
}

function makeString(data)
{
  var aux = "";
  for (var i=0; i<data.length; i++)
    aux += String.fromCharCode(data[0]);
  return aux;
}

function decode(code)
{
  var arr = fromBase32(code);

  _ASSERT( (arr[0] >> 4) == 0, "BySquareType mismatch" );
  _ASSERT( (arr[0] & 15) == 0, "Version mismatch" );
  _ASSERT( (arr[1] >> 4) == 0, "Document type mismatch" );


  var arr_u8 = new Uint8Array(arr.length-4+13);
  for (var i=0; i<arr.length-4; i++)
    arr_u8[i+13] = arr[i+4];

  var dataLength = arr[2] + (arr[3] << 8)
  var lzmaConf = {lc:3, lp:0, pb:2, dictSize: 128*1024, dataLength:dataLength};
  arr_u8[0] = lzmaConf.lc + lzmaConf.lp*5 + lzmaConf.pb*9*5;

  arr_u8[1] = (lzmaConf.dictSize >>  0) & 0xff;
  arr_u8[2] = (lzmaConf.dictSize >>  8) & 0xff;
  arr_u8[3] = (lzmaConf.dictSize >> 16) & 0xff;
  arr_u8[4] = (lzmaConf.dictSize >> 24) & 0xff; 

  arr_u8[5] = (lzmaConf.dataLength >>  0) & 0xff;
  arr_u8[6] = (lzmaConf.dataLength >>  8) & 0xff;
  arr_u8[7] = (lzmaConf.dataLength >> 16) & 0xff;
  arr_u8[8] = (lzmaConf.dataLength >> 24) & 0xff;

  arr_u8[9] = 0x00;
  arr_u8[10] = 0x00;
  arr_u8[11] = 0x00;
  arr_u8[12] = 0x00;

  var rawData = LZMA.decompress(arr_u8);
//	console.log(toHex16(rawData));
  var fields = parseStream(rawData);
  return fields;
}

function encode(fields)
{
  var rawDataToCompress = buildStream(fields);
  var rawCompressed = LZMA.compress(rawDataToCompress);
  var lzmaConf = {lc:3, lp:0, pb:2, dictSize: 128*1024, dataLength:rawDataToCompress.length};

//  console.log(toHex16(rawCompressed));

  _ASSERT( rawCompressed[0] == lzmaConf.lc + lzmaConf.lp*5 + lzmaConf.pb*9*5, "LZMA configuration mismatch" );
  _ASSERT( rawCompressed[1] == ((lzmaConf.dictSize >>  0) & 0xff), "LZMA dictionary configuration mismatch.1" );
  _ASSERT( rawCompressed[2] == ((lzmaConf.dictSize >>  8) & 0xff), "LZMA dictionary configuration mismatch.2" );
  _ASSERT( rawCompressed[3] == ((lzmaConf.dictSize >> 16) & 0xff), "LZMA dictionary configuration mismatch.3" );
  _ASSERT( rawCompressed[4] == ((lzmaConf.dictSize >> 24) & 0xff), "LZMA dictionary configuration mismatch.4" ); 

  var finalBuffer = new Uint8Array(rawCompressed.length-13+4);
  finalBuffer[0] = 0;
  finalBuffer[1] = 0;
  finalBuffer[2] = lzmaConf.dataLength & 0xff;
  finalBuffer[3] = lzmaConf.dataLength >> 8;

  for (var i=0; i<rawCompressed.length-13; i++)
    finalBuffer[i+4] = rawCompressed[i+13];

  //console.log(rawCompressed);

  return toBase32(finalBuffer);
}

function buildStream(fields)
{
  var fieldString = fields.join("\t");
  var arrRawData = new Uint8Array(fieldString.length);
  for (var i=0; i<fieldString.length; i++)
    arrRawData[i] = fieldString.charCodeAt(i);
  
  var crc = crc32(arrRawData);

  var arrRawDataWithCrc = new Uint8Array(fieldString.length+4);
  for (var i=0; i<fieldString.length; i++)
    arrRawDataWithCrc[i+4] = fieldString.charCodeAt(i);

  for (var i=0; i<4; i++)
  {
    arrRawDataWithCrc[i] = crc & 0xff;
    crc >>= 8;
  }
  return arrRawDataWithCrc;
}

function parseStream(data)
{
  var aux = "";
  var arrSub = new Uint8Array(data.length-4);

  for (var i=4; i<data.length; i++)
  {
    arrSub[i-4] = data[i];
    aux += String.fromCharCode(data[i]);
  }

  var crc = new Uint32Array(1);
  crc[0] = 0;
  for (var i=3; i>=0; i--)
    crc[0] = (crc[0] << 8) | data[i];

  _ASSERT( crc[0] == crc32(arrSub), "CRC mismatch! " + crc[0].toString(16) + " != " + crc32(arrSub).toString(16) );

  return aux.split("\t");
}

function crc32(data)
{
	var crc_table = [
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
  ];

  crc_update = function(crc, data)
  {
    var tbl_idx;
    tbl_idx = crc ^ (data >> (0 * 4));
    crc = crc_table[tbl_idx & 0x0f] ^ ((crc >> 4) & 0x0fffffff);
    tbl_idx = crc ^ (data >> (1 * 4));
    crc = crc_table[tbl_idx & 0x0f] ^ ((crc >> 4) & 0x0fffffff);
    return crc;
  }

  var ui32 = new Uint32Array(4);
  ui32[0] = 0xffffffff;
  for (var i=0; i<data.length; i++)
    ui32[0] = crc_update(ui32[0], data[i]);

  ui32[0] ^= 0xffffffff;
  return ui32[0];
}
