var PayBySquare = function() 
{
  this.LZMA = typeof LZMA != "undefined" ? LZMA : require("./lzma_worker.js").LZMA;
  this.LZMA.disableEndMark = 1;

  this.char32Table = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
}

PayBySquare.prototype.compressLzma = function(buffer)
{            
  var rawCompressed = this.LZMA.compress(buffer);

  // NOTE: Official documentation says, dictionary size should be 128kB (2^17), but LZMA implementation
  // defaults this value to 2^23. Dictionary size is irrelevant considering the small buffer sizes

  var header = new Uint8Array(13);
  for (var i=0; i<13; i++)
    header[i] = rawCompressed[i];

  var lzmaConf = {lc:3, lp:0, pb:2, dictSize: 1<<23, dataLength:buffer.length};

  this._ASSERT( header[0] == lzmaConf.lc + lzmaConf.lp*5 + lzmaConf.pb*9*5, "LZMA configuration mismatch" );
  this._ASSERT( header[1] == ((lzmaConf.dictSize >>  0) & 0xff), "LZMA dictionary configuration mismatch.1" );
  this._ASSERT( header[2] == ((lzmaConf.dictSize >>  8) & 0xff), "LZMA dictionary configuration mismatch.2" );
  this._ASSERT( header[3] == ((lzmaConf.dictSize >> 16) & 0xff), "LZMA dictionary configuration mismatch.3" );
  this._ASSERT( header[4] == ((lzmaConf.dictSize >> 24) & 0xff), "LZMA dictionary configuration mismatch.4" ); 

  var finalBuffer = new Uint8Array(rawCompressed.length-13);
	
  for (var i=0; i<rawCompressed.length-13; i++)
    finalBuffer[i] = rawCompressed[i+13];

  return finalBuffer;
}

PayBySquare.prototype.decompressLzma = function(buffer, decompressedSize)
{
  var tempBuffer = new Uint8Array(buffer.length+13);

  // NOTE: Official documentation says, dictionary size should be 128kB (2^17), but LZMA implementation
  // defaults this value to 2^23. Dictionary size is irrelevant considering the small buffer sizes

  var lzmaConf = {lc:3, lp:0, pb:2, dictSize: 1<<16, dataLength:decompressedSize};
  tempBuffer[0] = lzmaConf.lc + lzmaConf.lp*5 + lzmaConf.pb*9*5;

  tempBuffer[1] = (lzmaConf.dictSize >>  0) & 0xff;
  tempBuffer[2] = (lzmaConf.dictSize >>  8) & 0xff;
  tempBuffer[3] = (lzmaConf.dictSize >> 16) & 0xff;
  tempBuffer[4] = (lzmaConf.dictSize >> 24) & 0xff; 

  tempBuffer[5] = (lzmaConf.dataLength >>  0) & 0xff;
  tempBuffer[6] = (lzmaConf.dataLength >>  8) & 0xff;
  tempBuffer[7] = (lzmaConf.dataLength >> 16) & 0xff;
  tempBuffer[8] = (lzmaConf.dataLength >> 24) & 0xff;

  tempBuffer[9] = 0x00;
  tempBuffer[10] = 0x00;
  tempBuffer[11] = 0x00;
  tempBuffer[12] = 0x00;


  for (var i=0; i<buffer.length; i++)
    tempBuffer[i+13] = buffer[i];

  var rawDecompressedSigned = this.LZMA.decompress(tempBuffer);

  var rawDecompressedUnsigned = new Uint8Array(rawDecompressedSigned.length);
  for ( var i = 0; i<rawDecompressedSigned.length; i++ )
    rawDecompressedUnsigned[i] = rawDecompressedSigned[i];

  return rawDecompressedUnsigned; 
}

// global mess
PayBySquare.prototype._ASSERT = function(e, msg)
{
  if (!e) 
    throw msg;
}

PayBySquare.prototype.toChar32 = function(n)
{
  return this.char32Table.charAt(n);
}

PayBySquare.prototype.fromChar32 = function(ch)
{
  var i = this.char32Table.indexOf(ch);
  this._ASSERT( i != -1, "Cannot convert char : " + ch );
  return i;
}

PayBySquare.prototype.fromBase32 = function(str)
{
  var arrValues = [];
  var nBits = 0;
  var nValue = 0;
  for (var i=0; i<str.length; i++)
  {
    nValue <<= 5;
    nValue |= this.fromChar32(str.charAt(i));
    nBits += 5;

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

PayBySquare.prototype.toBase32 = function(arr)
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
      var nExtraBits = nBits - 5;

      strResult += this.toChar32(nValue >> nExtraBits);
      nValue &= (1<<nExtraBits) - 1;
      nBits -= 5;
    }
  }

  if ( nBits > 0 )
  {
    var nExtraBits = nBits - 5;

    strResult += this.toChar32(nValue << -nExtraBits);
    nValue &= (1<<nExtraBits) - 1;
  }

  return strResult;
}

PayBySquare.prototype.decode = function(code)
{
  var arr = this.fromBase32(code);

  this._ASSERT( arr.length > 8, "Sequence too short" );
  this._ASSERT( (arr[0] >> 4) == 0, "BySquareType mismatch" );
  this._ASSERT( (arr[0] & 15) == 0, "Version mismatch" );
  this._ASSERT( (arr[1] >> 4) == 0, "Document type mismatch" );

  var arr_u8 = new Uint8Array(arr.length-4);
  for (var i=0; i<arr.length-4; i++)
    arr_u8[i] = arr[i+4];

  var dataLength = arr[2] + (arr[3] << 8);

  var rawData = this.decompressLzma(arr_u8, dataLength);
  var fields = this.parseStream(rawData);

  return fields;
}

PayBySquare.prototype.encode = function(fields)
{
  var rawDataToCompress = this.buildStream(fields);

  this._ASSERT( rawDataToCompress.length < 65535, "Buffer limit exceeded" );

  var compressedBuffer = this.compressLzma(rawDataToCompress);

  var finalBuffer = new Uint8Array(compressedBuffer.length+4);
  finalBuffer[0] = 0;              
  finalBuffer[1] = 0;
  finalBuffer[2] = rawDataToCompress.length & 0xff;
  finalBuffer[3] = rawDataToCompress.length >> 8;

  for (var i=0; i<compressedBuffer.length; i++)
    finalBuffer[i+4] = compressedBuffer[i];

  return this.toBase32(finalBuffer);
}

PayBySquare.prototype.buildStream = function(fields)
{
  var fieldString = fields.join("\t");
  var arrRawData = new Uint8Array(fieldString.length);
  for (var i=0; i<fieldString.length; i++)
    arrRawData[i] = fieldString.charCodeAt(i);
  
  var crc = this.crc32(arrRawData);

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

PayBySquare.prototype.parseStream = function(data)
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

  this._ASSERT( crc[0] == this.crc32(arrSub), "CRC mismatch! " + crc[0].toString(16) + " != " + this.crc32(arrSub).toString(16) );

  return aux.split("\t");
}

PayBySquare.prototype.crc32 = function(data)
{
	var crc_table = [
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
  ];

  var crc_update = function(crc, data)
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

PayBySquare.staticEncode = function(fields)
{
  return (new PayBySquare()).encode(fields);
}

PayBySquare.staticDecode = function(sequence)
{
  return (new PayBySquare()).decode(sequence);
}

module.exports = {decode:PayBySquare.staticDecode, encode:PayBySquare.staticEncode};
